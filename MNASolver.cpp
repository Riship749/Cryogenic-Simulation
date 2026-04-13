#include "MNASolver.h"
#include <vector>
#include <string>
#include <iostream>
#include "eigen-5.0.0/Eigen/Dense"

using namespace std;

MNASolver::MNASolver(NetList& net) : circuit(net) {}

//return vector with all the nodal voltages
vector<Complex> MNASolver::solve(double freq, double temp) {
    int n = circuit.getNodeCount();
    if(n ==0) {
        return {};
    }
    Eigen::MatrixXcd A = Eigen::MatrixXcd::Zero(n,n);
    Eigen::VectorXcd b = Eigen::VectorXcd::Zero(n);
    for (const auto& comp : circuit.getComponents()) {
        Complex Z = comp->getImpedance(freq, temp);
        Complex Y = 1.0 / Z;
        int i = comp->getNode1();
        int j = comp -> getNode2();
        
        //check if node is ground and skip
        if (i != 0) A(i-1, i-1) += Y;
        if (j != 0) A(j-1, j-1) += Y;
        if (i != 0 && j != 0) {
            A(i-1, j-1) -= Y;
            A(j-1, i-1) -= Y;
        }
    }
    //TEST SIGNAL -> CHANGE IN FUTURE TO MAKE DYNAMIC
    if(n > 0) {
        b(0) = Complex(1.0, 0.0);
    }
    // 4. Solve the system: A * x = b
    Eigen::VectorXcd x = A.partialPivLu().solve(b);

    // 5. Convert the Eigen vector back to a standard C++ vector to return
    std::vector<Complex> nodeVoltages(x.data(), x.data() + x.size());
    return nodeVoltages;
}

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