#include "PassiveComponents.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
//hello
Complex Resistor::getImpedance(double freq, double temp) {
        //Add quantum affects and temp. dependence on material

        //Only affect real value of Z 
        return Complex(value, 0.0);
}

Complex Capacitor::getImpedance(double freq, double temp) {
        if(freq == 0.0) {
            return Complex(INFINITY, 0.0); // DC 
        }
        double omega = 2.0 * pi * freq;
        //need add way to caclualte capacitance dealing with Q.M. and temp 
        return Complex(0.0, -1.0/(omega * capacitance));
}