#pragma once
#include "Component.h"
#include <cmath>
#include "MaterialLHeader.h"
#include "MaterialLibrary.h"

class Resistor : public Component {
protected:
    MaterialProfile material;
    double parasiticInductance = 0.0;  // Series parasitic inductance [H]
    double selfCapacitance     = 0.0;  // Parallel self-capacitance   [F]
    // Reference temperature for resistivity ratio scaling [K]
    double referenceTemp = 300.0;
public: 
    using Component::Component; // makes subclass
    void setMaterial(const MaterialProfile& mat) { material = mat;}
    // Set parasitic L and C from datasheet or measurement
    void setParasitics(double L, double C) {
        parasiticInductance = L;
        selfCapacitance     = C;
    }
 
    // Override reference temperature if needed
    void setReferenceTemp(double T) { referenceTemp = T; }
 
    // Computes R(T) using material resistivity ratio scaling.
    double resistanceAtTemperature(double temp) const;
 
    Complex getImpedance(double freq, double temp) const override;

    // Quantum voltage noise power spectral density.
    double quantumVoltageNoisePSD(double freq, double temp) const;
};

class Capacitor: public Component {
public:
    double capacitance; //need way to better that it
    using Component::Component; // sublass 
    Complex getImpedance(double freq, double temp) const override;
};