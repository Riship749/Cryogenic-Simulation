#include "Netlist.h"
#include "PassiveComponents.h" 
#include <algorithm>          
#include <iostream>
using namespace std;

void NetList::addResistor(std::string name, int n1, int n2, double resistance, MaterialProfile mat) {
    auto r = std::make_shared<Resistor>(name, n1, n2, resistance);
    if (mat.isDefined) r->setMaterial(mat);
    components.push_back(r);
    numNodes = std::max({numNodes, n1, n2});
}
void NetList::addResistor(std::string name, int n1, int n2, double length, double width, double thickness, MaterialProfile mat) {
    if (!mat.isDefined) {
        std::cerr << "Warning: Material undefined for " << name << ". Defaulting to 1 Ohm." << std::endl;
        addResistor(name, n1, n2, 1.0);
        return;
    }

    // Calculate cross-sectional area (m^2)
    double area = width * thickness;
    
    // Fetch nominal resistivity at 300 Kelvin
    double rho_300K = mat.getResistivity(300.0);
    
    // Calculate nominal resistance: R = rho * (L / A)
    double calculatedResistance = rho_300K * (length / area);

    // Create the resistor and set its material for dynamic cryogenic scaling later
    auto r = std::make_shared<Resistor>(name, n1, n2, calculatedResistance);
    r->setMaterial(mat);
    
    components.push_back(r);
    numNodes = std::max({numNodes, n1, n2});

}


void NetList::addCapacitor(std::string name, int n1, int n2, double capacitance) {
    components.push_back(std::make_shared<Capacitor>(name, n1, n2, capacitance));
    numNodes = std::max({numNodes, n1, n2});
}


int NetList::getNodeCount() const {
    return numNodes;
}


void NetList::addQuantumResistor(std::string name, int n1, int n2, 
                                 MaterialProfile mat1, double l1, double w1, double th1,
                                 MaterialProfile mat2, double l2, double w2, double th2,
                                 double gap, double wave_len) {
                                     
    auto qr = std::make_shared<QuantumSeriesResistor>(name, n1, n2, mat1, l1, w1, th1, mat2, l2, w2, th2, gap, wave_len);
    components.push_back(qr);
    numNodes = std::max({numNodes, n1, n2});
}