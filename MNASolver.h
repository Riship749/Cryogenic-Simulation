#pragma once
#include "Netlist.h"
#include "Types.h"
#include <vector>
using namespace std;

class MNASolver {
private:
    //whole ciruit
    NetList& circuit;
    //does to get format Ax = B
    vector<vector<Complex>> matrixA;
    vector<Complex> vectorB;
    vector<Complex> nodeVoltagesX;
    
public:
    //consructor
    MNASolver(NetList& net);
    void buildMatrices(double freq, double temp);
    //base function to solve
    vector<Complex> solve(double freq, double temp);
    Complex getNodeVoltage(int node) const;

};