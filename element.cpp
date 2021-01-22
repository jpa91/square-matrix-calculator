/**
    \file element.cpp
    \brief Implementation of the Element class
*/

#include "element.h"
#include <iostream>

std::ostream& operator <<(std::ostream& os, const Element& e)
{
    os << e.toString();
    return os;
}

bool operator ==(const Element& lhs, const Element& rhs)
{
    return (lhs.toString() == rhs.toString());
}