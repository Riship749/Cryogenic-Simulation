#pragma once
#include "Component.h"
#include <cmath>
#include <numbers>
class Resistor : public Component {
public: 
    using Component::Component; // makes subclass

    Complex getImpedance(double freq, double temp) {
        //Add quantum affects and temp. dependence on material

        //Only affect real value of Z
        return Complex(value, 0.0);
    }

};

class Capacitor: public Component {
public:
    double capacitance; 
    double pi = std::acos(-1.0);
    using Component::Component; // sublass
    Complex getImpedance(double freq, double temp) {
        if(freq == 0.0) {
            return Complex(INFINITY, 0.0); // DC 
        }
        double omega = 2.0 * pi * freq;
        //need add way to caclualte capacitance dealing with Q.M. and temp
        return Complex(0.0, -1.0/(omega * capacitance));
    }
};