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