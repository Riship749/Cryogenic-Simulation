#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <complex>
#include <cmath>

using Complex = std::complex<double>;

class DataLogger {
public:
    

    static void exportToCSV(const std::string& filename, const std::vector<double>& frequencies, const std::vector<std::vector<Complex>>& allResults) {
        double pi = std::acos(-1.0);
        std::ofstream file(filename);
        //header for csv
        file << "Frequency_Hz,Node1_Mag_dB,Node1_Phase_deg\n";
        for(size_t i = 0; i<frequencies.size(); ++i) {
            double freq = frequencies[i];
            Complex v1 = allResults[i][0];
            double mag_dB = 20.0 * std::log10(std::abs(v1));
            double phase_deg = std::arg(v1) * (180.0/ pi);
            file << freq << "," << mag_dB << "," << phase_deg << "\n";
        }
        file.close();
    }
};
