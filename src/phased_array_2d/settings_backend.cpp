#define _USE_MATH_DEFINES

#include "settings_backend.h"


int Element::getUniqueID()
{
    return uniqueID;
}

std::string Element::getName()
{
    return std::string(Element::name);
}

bool Element::isActive()
{
    return active;
}

Element::Element(std::string name, int uniqueID)
{
    Element::phase = 0;
    Element::amplitude = 1;
    Element::frequency = 1 * M_PI;
    Element::active = true;
    Element::name = name;
    Element::uniqueID = uniqueID;
}

Element::~Element()
{
}
