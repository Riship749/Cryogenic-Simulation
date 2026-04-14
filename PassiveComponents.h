#pragma once
#include "Component.h"
#include <cmath>
#include "MaterialLHeader.h"
#include "MaterialLibrary.h"
#include "ConductorSeries.h"  // Includes the file we just formatted


class Resistor : public Component {
protected:
    MaterialProfile material;
public: 
    using Component::Component; 
    void setMaterial(const MaterialProfile& mat) { material = mat;}
    Complex getImpedance(double freq, double temp) const override;
};

class Capacitor: public Component {
public:
    double capacitance; 
    using Component::Component; 
   Complex getImpedance(double freq, double temp) const override;
   
};

// NEW WRAPPER CLASS
class QuantumSeriesResistor : public Component {
private:
    MaterialProfile material1;
    MaterialProfile material2;
    double L1, W1, t1; 
    double L2, W2, t2; 
    double gap_distance;
    double electron_wavelength;

public:
    QuantumSeriesResistor(std::string _name, int n1, int n2, 
                          MaterialProfile mat1, double l1, double w1, double th1,
                          MaterialProfile mat2, double l2, double w2, double th2,
                          double gap, double wave_len);

    Complex getImpedance(double freq, double temp) const override;
};

