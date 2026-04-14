#pragma once
#include <cmath>
#include <complex>
#include <vector>

using namespace std;
typedef complex<double> cd;

class SeriesConductance {
private:
    double T1, T2;       
    double gap_distance; 
    const double pi = 2.0 * acos(0.0);
    
    double calculateLPhi(double temperature) {
        double L0 = 100e-9; 
        if (temperature < 0.1)  {
            temperature = 0.1;
        }
        return L0 * pow(temperature, -0.5); 
    }

public:
    static constexpr double G0 = 7.748e-5; 

    SeriesConductance(double t1, double t2, double gap) 
        : T1(t1), T2(t2), gap_distance(gap) {}

    struct TransferMatrix {
        cd m11, m12, m21, m22;
    };

    TransferMatrix multiply(TransferMatrix A, TransferMatrix B) {
        return {
            A.m11*B.m11 + A.m12*B.m21, A.m11*B.m12 + A.m12*B.m22,
            A.m21*B.m11 + A.m22*B.m21, A.m21*B.m12 + A.m22*B.m22
        };
    }

    double SeriesConductanceForN(const vector<double>& Conductances, double electron_wavelength, double gaplength) {
        TransferMatrix M_total = {1, 0, 0, 1};
        double theta = (2.0 * pi * gaplength) / electron_wavelength;
        
        TransferMatrix M_gap = { exp(cd(0, theta)), 0, 
                                 0,                 exp(cd(0, -theta)) };
                                 
        for (size_t i = 0; i < Conductances.size(); ++i) {
            double T_prob = Conductances[i] / G0;
            if (T_prob > 1.0) T_prob = 1.0;

            double t = sqrt(T_prob);
            double r_mag = sqrt(1.0 - T_prob);
            cd r(0, r_mag); 

            TransferMatrix M_res = {
                cd(1.0 / t), cd(conj(r) / t),
                cd(r / t),   cd(1.0 / t)
            };

            M_total = multiply(M_total, M_res);

            if (i < Conductances.size() - 1) {
                M_total = multiply(M_total, M_gap);
            }
        }

        double T_total = 1.0 / norm(M_total.m11);
        return G0 * T_total;
    }
    
    double getSeriesConductance(double electron_wavelength, double temperature) {
        double R1 = 1.0 - T1;
        double R2 = 1.0 - T2;
        
        double theta = (2.0 * pi * gap_distance) / electron_wavelength;
        double denominator = 1.0 + (R1 * R2) - (2.0 * sqrt(R1 * R2) * cos(2.0 * theta));
        double T_quantum = (T1 * T2) / denominator;
        
        double T_classical = (T1 * T2) / (T1 + T2 - T1 * T2);
        
        double L_phi = calculateLPhi(temperature);
        double dephasing_factor = exp(-gap_distance / L_phi);
        
        double T_final = (dephasing_factor * T_quantum) + ((1.0 - dephasing_factor) * T_classical);
        
        return G0 * T_final;
    }
};