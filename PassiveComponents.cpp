#include "PassiveComponents.h"
#include <algorithm>

Complex Resistor::getImpedance(double freq, double temp) const {
    if (material.isDefined) {
        if (material.isSuperconductor && temp <= material.critical_temp_Tc) {
            double omega = 2.0 * pi * freq;
            return Complex(0.0, omega * material.kinetic_inductance_Lk);
        }
        double rho_current = material.getResistivity(temp);
        double rho_300K = material.getResistivity(300.0);
        double dynamicR = value * (rho_current / rho_300K);
        return Complex(dynamicR, 0.0);
    }
    return Complex(value, 0.0);
}

Complex Capacitor::getImpedance(double freq, double temp) const {
    if(freq == 0.0) return Complex(INFINITY, 0.0);
    double omega = 2.0 * pi * freq;
    return Complex(0.0, -1.0 / (omega * value)); 
}

// NEW WRAPPER IMPLEMENTATION
QuantumSeriesResistor::QuantumSeriesResistor(std::string _name, int n1, int n2, 
                      MaterialProfile mat1, double l1, double w1, double th1,
                      MaterialProfile mat2, double l2, double w2, double th2,
                      double gap, double wave_len)
    : Component(_name, n1, n2, 0.0), 
      material1(mat1), L1(l1), W1(w1), t1(th1),
      material2(mat2), L2(l2), W2(w2), t2(th2),
      gap_distance(gap), electron_wavelength(wave_len) {}

Complex QuantumSeriesResistor::getImpedance(double freq, double temp) const {
    double rho1 = material1.getResistivity(temp);
    double rho2 = material2.getResistivity(temp);

    double R1 = rho1 * (L1 / (W1 * t1));
    double R2 = rho2 * (L2 / (W2 * t2));

    double G1 = 1.0 / R1;
    double G2 = 1.0 / R2;

    double G0 = SeriesConductance::G0;
    double T1 = std::min(1.0, G1 / G0);
    double T2 = std::min(1.0, G2 / G0);

    SeriesConductance quantumModel(T1, T2, gap_distance);
    double G_total = quantumModel.getSeriesConductance(electron_wavelength, temp);

    // Prevent divide by zero error if conductance drops extremely low
    if (G_total < 1e-15) return Complex(1e15, 0.0);
    
    return Complex(1.0 / G_total, 0.0);
}