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
    
    void buildMatrices(double freq, double temp);
public:
    //consructor
    MNASolver(NetList& net);

    //base function to solve
    void solve(double freq, double temp);
    Complex getNodeVoltage(int node) const;

};