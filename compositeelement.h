/**
    \file compositeelement.h
    \brief Header for the CompositeElement class
*/

#pragma once

#include "element.h"
#include <iostream>
#include <functional>
#include <memory>
#include <string>

/**
    \class CompositeElement
    \brief A class for an integer arithmetic
*/
class CompositeElement : public Element
{
public:
    /**
        \brief Parametric constructor
        \param e1 reference to an Element object
        \param e2 reference to an Element object
        \param op reference to std::function<int(int,int)>
        \param opc char that is the symbol of the operation
    */
    CompositeElement(const Element&, const Element&, const std::function<int(int, int)>&, char);

    /**
        \brief Copy constructor
        \param e CompositeElement object that is copied
    */
    CompositeElement(const CompositeElement&);

    /**
        \brief Destructor
    */
    virtual ~CompositeElement();

    /**
        \brief Method for creating a string representation of the integer arithmetic
        \return string that is the string representation of the integer arithmetic
    */
    std::string toString() const;

    /**
        \brief Method for determining the value of the integer arithmetic
        \param v valuation object
        \return int value of the integer arithmetic
    */
    int evaluate(const Valuation&) const;

    /**
        \brief Method for creating a copy of the object and returning a smart pointer to it
        \return unique_ptr to the created CompositeElement object
    */
    std::unique_ptr<Element> clone() const;

    /**
        \brief Operator for assignment
        \param e reference to a CompositeElement object that is the integer arithmetic to assign from
        \return Reference to a CompositeElement object that has been assigned
    */
    CompositeElement& operator =(const CompositeElement&);

private:
    std::unique_ptr<Element> oprnd1;

    std::unique_ptr<Element> oprnd2;

    std::function<int(int, int)> op_fun;

    char op_char;
};