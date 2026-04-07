#include "Netlist.h"
#include "PassiveComponents.h" // We must include the subclasses to instantiate them
#include <algorithm>           // For std::max
using namespace std;

void NetList::addResistor(std::string name, int n1, int n2, double resistance) {

    components.push_back(std::make_shared<Resistor>(name, n1, n2, resistance));


    numNodes = std::max({numNodes, n1, n2});
}


void NetList::addCapacitor(std::string name, int n1, int n2, double capacitance) {
    components.push_back(std::make_shared<Capacitor>(name, n1, n2, capacitance));
    numNodes = std::max({numNodes, n1, n2});
}


int NetList::getNodeCount() const {
    return numNodes;
}