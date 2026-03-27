#pragma once
#include <string>
#include <iostream>
#include "Types.h"
class Component {
protected:
    string name; 
    int node1;
    int node2;
    double value; // value of all components in there respectitive units;
public: 
    Component(string _name, int n1, int n2, double val): name(_name), node1(n1), node2(n2), value(val) {}
    virtual ~Component() = default;
    //Overrride in other components -> get each own Z to add up
    virtual Complex getImpedance(double freq, double temperature) const = 0;
    //getters for nodes
    int getNode1() {
        return node1;
    }
    int getNode2() {
        return node2;
    }
};