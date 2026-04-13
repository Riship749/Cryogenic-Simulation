#pragma once
#include "Component.h"
#include <cmath>
#include "MaterialLHeader.h"
#include "MaterialLibrary.h"

class Resistor : public Component {
protected:
    MaterialProfile material;
public: 
    using Component::Component; // makes subclass
    void setMaterial(const MaterialProfile& mat) { material = mat;}
    Complex getImpedance(double freq, double temp) const override;

};

class Capacitor: public Component {
public:
    double capacitance; //need way to better that it
    using Component::Component; // sublass 
    Complex getImpedance(double freq, double temp) const override;
};