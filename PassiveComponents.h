#pragma once
#include "Component.h"
#include <cmath>

class Resistor : public Component {
public: 
    using Component::Component; // makes subclass

    Complex getImpedance(double freq, double temp) {
    }

};

class Capacitor: public Component {
public:
    double capacitance; //need way to better that it
    double pi = std::acos(-1.0);
    using Component::Component; // sublass 
    Complex getImpedance(double freq, double temp) {

    }
};