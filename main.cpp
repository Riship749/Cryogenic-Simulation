#include <iostream>
#include "NetList.h"
#include "MNASolver.h"
#include "PassiveComponents.h"

int main() {
    std::cout << "Starting Quantum Control Simulator - Phase 1" << std::endl;

    NetList circuit;

    circuit.addResistor("R1", 1, 2, 50.0);
    
    circuit.addResistor("R2", 2, 0, 50.0);

    MNASolver solver(circuit);

    solver.buildMatrices(0.0, 20); 

    std::cout << "Matrix built successfully." << std::endl;

    return 0;
}