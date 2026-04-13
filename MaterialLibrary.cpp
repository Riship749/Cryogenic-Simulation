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
        return mat;
    }

    MaterialProfile Aluminum() {
        MaterialProfile mat;
        mat.name = "Aluminum";
        mat.isDefined = true;
        mat.isSuperconductor = true;
        mat.critical_temp_Tc = 1.2; //
        mat.kinetic_inductance_Lk = 2.0e-12; //FIX
        return mat;
    }
}