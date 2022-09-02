#pragma once
#include <cmath>
#include <iostream>
#include <string>

class Element
{

private:
    int uniqueID;
    std::string name;

    float phase;
    float amplitude;
    float frequency;
    bool active;

public:
    bool* getActivePointer();
    float* getPhasePointer();
    float* getAmplitudePointer();
    float* getFrequencyPointer();

    int getUniqueID();
    std::string getName();
    
    bool isActive();

    Element(std::string name, int uniqueID);
    ~Element();
};
