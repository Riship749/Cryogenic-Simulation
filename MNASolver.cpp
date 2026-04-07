#include "MNASolver.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

void MNASolver::buildMatrices(double freq, double temp) {
    int numberNodes = circuit.getNodeCount();
    matrixA.assign(numberNodes, vector<Complex>(numberNodes, Complex(0.0, 0.0)));
    vectorB.assign(numberNodes, Complex(0,0));
    for(const auto& comp: circuit.getComponents()) {
        //get impedence (z) for teach component
        Complex z = comp->getImpedance(freq, temp);
        //calcuate inverse -> admittance (y)
        Complex y = 1.0/z;
        int i = comp -> getNode1(); //node 1 -> where current is from
        int j = comp -> getNode2(); // node 2 -> where current goes to
        //don't want to add for ground
        if( i != 0) {
            matrixA[i-1][j-1] +=y; // Diagonal entry for node i
        }
        if (j!=0) {
            matrixA[j-1][i-1] += y; // Diagonal entry for node j
        } 
        if(i!= 0 && j!=0) {
            matrixA[i-1][j-1] -= y; // Off-diagonal
            matrixA[j-1][i-1] -= y; // Off-diagonal
        }
        

    }
}