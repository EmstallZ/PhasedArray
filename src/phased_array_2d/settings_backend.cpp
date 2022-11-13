#define _USE_MATH_DEFINES

#include "settings_backend.h"

bool* Element::getActivePointer()
{
    bool* ptr = &active;
    return ptr;
}

float* Element::getPhasePointer() {
    float* ptr = &phase;
    return ptr;
}

float* Element::getAmplitudePointer() {
    float* ptr = &amplitude;
    return ptr;
}

float* Element::getFrequencyPointer() {
    float* ptr = &frequency;
    return ptr;
}

int Element::getUniqueID()
{
    return Element::uniqueID;
}

std::string Element::getName()
{
    return std::string(Element::name);
}

bool Element::isActive()
{
    return Element::active;
}

Element::Element(std::string name, int uniqueID)
{
    Element::phase = 0;
    Element::amplitude = 1;
    Element::frequency = 1 * (float)M_PI;
    Element::active = true;
    Element::name = name;
    Element::uniqueID = uniqueID;
}

Element::~Element()
{
}
