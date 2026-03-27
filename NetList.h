#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include <vector>
using namespace std;
class NetList {
private:

    //vector of components 
    vector<shared_ptr<Component>> components;
    //number nodes
    int numNodes;
public: 
    //implement later
    void addResistor(string name, int n1, int n2, double resistance);
    void addCapacitor(string name, int n1, int n2, double capacitance);

    //return total number of unique nodes to the size of the MNA results
    int getNodeCount() const;
    
    //getters for components
    const vector<shared_ptr<Component>>& getComponents() const {
        return components;
    }
};
