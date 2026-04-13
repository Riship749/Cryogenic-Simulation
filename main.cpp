#include <iostream>
#include <vector>
#include "NetList.h"
#include "MNASolver.h"
#include "DataLogger.h"
#include "PassiveComponents.h"

int main() {
    std::cout << "Initializing 60GHz AC Sweep Simulation..." << std::endl;

    // 1. Build the Circuit
    NetList circuit;
    
    // Create a parallel RC circuit (acts as a low-pass filter)
    // 50 Ohms resistance
    circuit.addResistor("R1", 1, 0, 50.0); 
    // 0.05 picoFarads capacitance
    circuit.addCapacitor("C1", 1, 0, 0.05e-12); 

    MNASolver solver(circuit);

    // 2. Setup the Frequency Sweep Parameters
    double startFreq = 10.0e9;  // 10 GHz
    double stopFreq  = 100.0e9; // 100 GHz
    int numPoints    = 1000;
    double stepSize  = (stopFreq - startFreq) / numPoints;

    std::vector<double> frequencies;
    std::vector<std::vector<Complex>> sweepResults;

    // 3. Run the Sweep
    std::cout << "Solving matrices..." << std::endl;
    std::cout << "Nodes detected: " << circuit.getNodeCount() << std::endl; // <-- ADD THIS
    for (int i = 0; i <= numPoints; ++i) {
        double currentFreq = startFreq + (i * stepSize);
        frequencies.push_back(currentFreq);

        // Solve the circuit at 2.0 Kelvin
        std::vector<Complex> voltages = solver.solve(currentFreq, 2.0);

        if(voltages.empty()) {
        std::cerr << "Error, 0 voltage at freq: " << currentFreq << std::endl;
        }
        
    sweepResults.push_back(voltages);

    }

    // 4. Export the Data
    std::string outputFile = "ac_sweep_results.csv";
    DataLogger::exportToCSV(outputFile, frequencies, sweepResults);

    std::cout << "Simulation complete. Data saved to " << outputFile << std::endl;

    return 0;
}