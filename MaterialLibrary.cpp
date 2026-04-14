#include "MaterialLibrary.h"

namespace MaterialLibrary {

    MaterialProfile Tungsten() {
        MaterialProfile mat;
        mat.name = "Tungsten";
        mat.isDefined = true;
        mat.A = -1.5374e-07;
        mat.B = 3.2560e-04;
        mat.C = 2.5708e-01;
        mat.D = -6.7530;
        mat.RRR_floor = 0.492;
        mat.isSuperconductor = false;
        return mat;
    }

    MaterialProfile Iron() {
        MaterialProfile mat;
        mat.name = "Iron";
        mat.isDefined = true;
        mat.A = 1.9683e-07;
        mat.B = 5.5125e-04;
        mat.C = 1.6178e-01;
        mat.D = -0.83249;
        mat.RRR_floor = 4.054;
        mat.isSuperconductor = false;
        return mat;
    }

    MaterialProfile Aluminum() {
        MaterialProfile mat;
        mat.name = "Aluminum";
        mat.isDefined = true;
        mat.isSuperconductor = true;
        mat.critical_temp_Tc = 1.2; 
        mat.kinetic_inductance_Lk = 2.0e-12; // Needs quantum literature validation
        return mat;
    }

    MaterialProfile Copper() {
        MaterialProfile mat;
        mat.name = "OFHC Copper (RRR 50)";
        mat.isDefined = true;
        // PENDING REGRESSION - Update these once calculated
        mat.A = 0.0; 
        mat.B = 0.0;
        mat.C = 0.0;
        mat.D = 0.338; 
        mat.RRR_floor = 0.338; // Anchored to 4.2K RRR 50 limit [cite: 58]
        mat.isSuperconductor = false;
        return mat;
    }

    MaterialProfile Steel() {
        MaterialProfile mat;
        mat.name = "Stainless Steel 304/316";
        mat.isDefined = true;
        mat.A = -2.4151e-06;
        mat.B = 2.0616e-03;
        mat.C = 4.2999e-01;
        mat.D = 4.9719e+02;
        mat.RRR_floor = 500.00; // Median baseline at 4.2K [cite: 77, 91]
        mat.isSuperconductor = false;
        return mat;
    }

    MaterialProfile CuNi() {
        MaterialProfile mat;
        mat.name = "Cupro-Nickel 70/30";
        mat.isDefined = true;
        mat.A = 1.4604e-10;
        mat.B = -1.3637e-07;
        mat.C = 1.7025e-02;
        mat.D = 3.3502e+02;
        mat.RRR_floor = 335.09; // Clamped by heavy solid-solution scattering [cite: 104, 114]
        mat.isSuperconductor = false;
        return mat;
    }

    MaterialProfile PhosphorBronze() {
        MaterialProfile mat;
        mat.name = "Phosphor Bronze C51000";
        mat.isDefined = true;
        mat.A = -6.5628e-07;
        mat.B = 6.0387e-04;
        mat.C = 3.3970e-02;
        mat.D = 101.88;
        mat.RRR_floor = 102.22; // Based on RRR of 1.24 [cite: 131, 138]
        mat.isSuperconductor = false;
        return mat;
    }

    MaterialProfile BerylliumCopper() {
        MaterialProfile mat;
        mat.name = "Beryllium Copper C17200";
        mat.isDefined = true;
        mat.A = -4.4203e-07;
        mat.B = 4.0286e-04;
        mat.C = 2.6162e-02;
        mat.D = 53.02;
        mat.RRR_floor = 53.26; // Age-hardened TH04/TF00 limit [cite: 176, 183]
        mat.isSuperconductor = false;
        return mat;
    }

}