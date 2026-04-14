#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <complex>
#include <cmath>

using Complex = std::complex<double>;

class DataLogger {
public:
    static void exportToCSV(const std::string& filename, 
                            const std::vector<double>& frequencies, 
                            const std::vector<std::vector<Complex>>& classicalResults,
                            const std::vector<std::vector<Complex>>& quantumResults) {
                                
        double pi = std::acos(-1.0);
        std::ofstream file(filename);
        
        // Updated header for side-by-side comparison
        file << "Frequency_Hz,Class_Mag_dB,Class_Phase_deg,Quant_Mag_dB,Quant_Phase_deg\n";
        
        for(size_t i = 0; i < frequencies.size(); ++i) {
            double freq = frequencies[i];
            
            // Classical Node 1 processing
            Complex v1_class = classicalResults[i][0];
            double mag_class = 20.0 * std::log10(std::abs(v1_class));
            double phase_class = std::arg(v1_class) * (180.0 / pi);

            // Quantum Node 1 processing
            Complex v1_quant = quantumResults[i][0];
            double mag_quant = 20.0 * std::log10(std::abs(v1_quant));
            double phase_quant = std::arg(v1_quant) * (180.0 / pi);
            
            file << freq << "," << mag_class << "," << phase_class << "," 
                 << mag_quant << "," << phase_quant << "\n";
        }
        file.close();
    }
};