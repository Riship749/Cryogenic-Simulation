#pragma once
#include <string>
#include <cmath>

struct MaterialProfile {
    std::string name     = "Undefined";
    bool isDefined       = false;
    // Regression Coefficients (Normal State)
    double A = 0.0;   // cubic  term
    double B = 0.0;   // quadratic term
    double C = 0.0;   // linear term
    double D = 0.0;   // constant term    double RRR_floor = 0;
    double RRR_floor = 1.0;

    // Superconducting Parameters
    bool isSuperconductor = false;
    double critical_temp_Tc = 0.0; // K
    double kinetic_inductance_Lk = 0.0; // In Henries
    // Evaluates the resistivity polynomial safely
    // Computes the resistivity of this material at a given
    // temperature using the polynomial fit: rho(T) = A*T^3 + ...
    // Returns: resistivity in Ohm*meters at temperature temp (K).
    // Returns 0 if material is not defined.
    double getResistivity(double temp) const {
        if (!isDefined || temp <= 0.0) return 0.0;
 
        // Superconductor below Tc: resistivity collapses to ~0
        if (isSuperconductor && temp < critical_temp_Tc) return 0.0;
 
        return A * temp * temp * temp
             + B * temp * temp
             + C * temp
             + D;
    }
};
 