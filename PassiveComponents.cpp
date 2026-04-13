#include "PassiveComponents.h"

Complex Resistor::getImpedance(double freq, double temp) const {
    if (material.isDefined) {
        // 1. Check for Superconductivity State Change
        if (material.isSuperconductor && temp <= material.critical_temp_Tc) {
            double omega = 2.0 * pi * freq;
            // Resistance is zero, only Kinetic Inductance remains
            return Complex(0.0, omega * material.kinetic_inductance_Lk);
        }

        // 2. Normal State: Apply Polynomial Scaling
        double rho_current = material.getResistivity(temp);
        double rho_300K = material.getResistivity(300.0);
        
        // value is the nominal Ohms provided in the netlist
        double dynamicR = value * (rho_current / rho_300K);
        return Complex(dynamicR, 0.0);
    }
    // Fallback for ideal testing
    return Complex(value, 0.0);
}

Complex Capacitor::getImpedance(double freq, double temp) const {
    if(freq == 0.0) return Complex(INFINITY, 0.0);
    double omega = 2.0 * pi * freq;
    // Standard ideal capacitor for now
    return Complex(0.0, -1.0 / (omega * value)); 
}