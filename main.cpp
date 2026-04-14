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
    
    // Add parallel capacitor
    //circuit.addCapacitor("C1", 1, 0, 0.05e-12); 

    // Physical parameters for the traces
    double length = 100.0e-6;
    double width  = 2.0e-6;
    double thickness = 500.0e-9;
    
    // Quantum specific parameters
    double gap_distance = 50.0e-9;         // 50nm gap
    double electron_wavelength = 10.0e-9;  // Arbitrary wave parameter for testing

    // Add our new Quantum Wrapper (using Aluminum for both sides of the gap)
    circuit.addQuantumResistor("R_QuantumTrace", 1, 0, 
                               MaterialLibrary::Steel(), length, width, thickness,
                               MaterialLibrary::Steel(), length, width, thickness,
                               gap_distance, electron_wavelength);

    MNASolver solver(circuit);

    // 2. Setup the Frequency Sweep Parameters
    double startFreq = 10.0e9;  // 10 GHz
    double stopFreq  = 100.0e9; // 100 GHz
    int numPoints    = 1000;
    double stepSize  = (stopFreq - startFreq) / numPoints;

    std::vector<double> frequencies;
    std::vector<std::vector<Complex>> classicalSweep;
    std::vector<std::vector<Complex>> quantumSweep;

    // 3. Run the Sweep
    std::cout << "Solving matrices..." << std::endl;
    std::cout << "Nodes detected: " << circuit.getNodeCount() << std::endl; 
    
    for (int i = 0; i <= numPoints; ++i) {
        double currentFreq = startFreq + (i * stepSize);
        frequencies.push_back(currentFreq);

        // --- Classical Run (300 Kelvin) ---
        std::vector<Complex> volt_class = solver.solve(currentFreq, 300.0);
        if(volt_class.empty()) {
            std::cerr << "Error, 0 voltage at freq (classical): " << currentFreq << std::endl;
        }
        classicalSweep.push_back(volt_class);

        // --- Quantum Run (1.2 Kelvin) ---
        std::vector<Complex> volt_quant = solver.solve(currentFreq, 1.2);
        quantumSweep.push_back(volt_quant);
    }

    // 4. Export the Data
    std::string outputFile = "ac_sweep_results.csv";
    DataLogger::exportToCSV(outputFile, frequencies, classicalSweep, quantumSweep);

    std::cout << "Simulation complete. Data saved to " << outputFile << std::endl;

    return 0;
}