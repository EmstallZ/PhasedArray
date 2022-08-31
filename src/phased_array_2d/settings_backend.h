#pragma once
#include <cmath>
#include <iostream>
#include <string>

class Element
{

private:
    int uniqueID;
    std::string name;

    double phase;
    double amplitude;
    double frequency;

    bool active;

public:
    int getUniqueID();
    std::string getName();

    bool isActive();

    Element(std::string name, int uniqueID);
    ~Element();
};
