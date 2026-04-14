#include "PassiveComponents.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace {
    constexpr double PI   = 3.14159265358979323846;
    constexpr double HBAR = 1.054571817e-34;   // J*s
    constexpr double KB   = 1.380649e-23;      // J/K
}

double Resistor::resistanceAtTemperature(double temp) const {
    if (temp <= 0.0)
        throw std::invalid_argument("Temperature must be > 0 K.");
 
    // If no material is set, return the og value unchanged
    if (!material.isDefined)
        return value;
 
    // Get resistivity at the given temp and at reference temp
    double rho_T   = material.getResistivity(temp);
    double rho_ref = material.getResistivity(referenceTemp);
 
    // Can't scale by zero or negative resistivity
    if (rho_ref <= 0.0 || rho_T <= 0.0)
        return value;
 
    // Scale the nominal resistance by the resistivity ratio
    double R = value * (rho_T / rho_ref);

    if (material.RRR_floor > 0.0) {
        double R_min = value / material.RRR_floor;
        if (R < R_min) R = R_min;
    }
 
    return R;
}

Complex Resistor::getImpedance(double freq, double temp) {
        //Add quantum affects and temp. dependence on material
        if (freq < 0.0)
                throw std::invalid_argument("Frequency must be >= 0.");
        if (temp <= 0.0)
                throw std::invalid_argument("Temperature must be > 0 K.");
        
        //temp dependent resistance
        double R = resistanceAtTemperature(temp);

        //super-conducting state
        double L = parasiticInductance;
        if (material.isSuperconductor && temp < material.critical_temp_Tc) {
                R  = 0.0;
                L += material.kinetic_inductance_Lk;  // kinetic inductance adds to parasitic L
        }

        //if freq happens to = 0 (DC Case)
        if (freq == 0.0)
                return Complex(R, 0.0);
        
                const double omega = 2.0 * PI * freq;

        //Series branch Z = R + j*omega*L
        Complex Zseries(R, omega * L);

        //Parallel self-capacitance
        if (selfCapacitance <= 0.0)
                return Zseries;
        
        // Total admittance Y = 1/Z_series + j*omega*C
        // Then Z = 1/Y
        //Only affect real value of Z 
        Complex Ytotal = (1.0 / Zseries) + Complex(0.0, omega * selfCapacitance);
        return 1.0 / Ytotal;
        }
}

// Computes the quantum voltage noise power spectral density.
double Resistor::quantumVoltageNoisePSD(double freq, double temp) const {
    if (freq <= 0.0)
        throw std::invalid_argument("Frequency must be > 0 for noise PSD.");
    if (temp <= 0.0)
        throw std::invalid_argument("Temperature must be > 0 K.");
 
    const double omega = 2.0 * PI * freq;
    const double x     = (HBAR * omega) / (2.0 * KB * temp);
 
    // coth(x) = cosh(x)/sinh(x)
    // For large x (very cold / high freq), coth(x) -> 1.0
    double cothx;
    if (x > 100.0) {
        cothx = 1.0;  // numerical safety: avoid overflow in cosh/sinh
    } else {
        cothx = std::cosh(x) / std::sinh(x);
    }
 
    // Re[Z(omega, T)] — only the real part contributes to noise
    double ReZ = std::real(getImpedance(freq, temp));
 
    // S_VV = hbar*omega * coth(hbar*omega / 2kBT) * Re[Z]
    return HBAR * omega * cothx * ReZ;
}

Complex Capacitor::getImpedance(double freq, double temp) {
        if(freq == 0.0) {
            return Complex(INFINITY, 0.0); // DC 
        }
        double omega = 2.0 * pi * freq;
        //need add way to caclualte capacitance dealing with Q.M. and temp 
        return Complex(0.0, -1.0/(omega * capacitance));        
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