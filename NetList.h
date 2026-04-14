#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include <vector>
#include "MaterialLHeader.h"

using namespace std;
class NetList {
private:

    //vector of components 
    vector<shared_ptr<Component>> components;
    //number nodes
    int numNodes = 0;
public: 
    //Existing method for explicit resistance
    void addResistor(string name, int n1, int n2, double resistance, MaterialProfile mat = MaterialProfile());
    
    //Overloaded method for physical layout dimensions (in meters)
    void addResistor(string name, int n1, int n2, double length, double width, double thickness, MaterialProfile mat);

    void addCapacitor(string name, int n1, int n2, double capacitance);

    //return total number of unique nodes to the size of the MNA results
    int getNodeCount() const;
    //NEW ONE TO USE -> ADD Q.M
    void addQuantumResistor(string name, int n1, int n2, 
                            MaterialProfile mat1, double l1, double w1, double th1,
                            MaterialProfile mat2, double l2, double w2, double th2,
                            double gap, double wave_len);
    
    //getters for components
    const vector<shared_ptr<Component>>& getComponents() const {
        return components;
    }
};
