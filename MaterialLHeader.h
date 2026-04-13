#pragma once
#include <string>
#include <cmath>

struct MaterialProfile {
    std::string name = "Generic";
    bool isDefined = false;
    // Regression Coefficients (Normal State)
    double A = 0, B = 0, C = 0, D = 0;
    double RRR_floor = 0;
    // Superconducting Parameters
    bool isSuperconductor = false;
    double critical_temp_Tc = 0.0; // K
    double kinetic_inductance_Lk = 0.0; // In Henries
    // Evaluates the resistivity polynomial safely
    double getResistivity(double temp) const {
        if (!isDefined) return 1.0;
        // Cubic fit: Ax^3 + Bx^2 + Cx + D
        //Get values from other code (GetEquation.py)
        double rho = (A * std::pow(temp, 3)) + (B * std::pow(temp, 2)) + (C * temp) + D;
        
        // Safety catch: NIST residual floor or cryogenic limit
        if (temp <= 10.0 || rho < RRR_floor) {
            return RRR_floor;
        }
        return rho;
    }
};