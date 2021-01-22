/**
    \file compositeelement.cpp
    \brief Implementation of the CompositeElement class
*/

#include "compositeelement.h"

CompositeElement::CompositeElement(const Element& e1, const Element& e2, const std::function<int(int, int)>& op, char opc)
{
    oprnd1 = std::move(e1.clone());
    oprnd2 = std::move(e2.clone());
    op_char = opc;
    op_fun = op;
}

CompositeElement::CompositeElement(const CompositeElement& e)
{
    oprnd1 = std::move(e.oprnd1->clone());
    oprnd2 = std::move(e.oprnd2->clone());
    op_char = e.op_char;
    op_fun = e.op_fun;
}

CompositeElement::~CompositeElement() = default;

int CompositeElement::evaluate(const Valuation & v) const
{
    return op_fun(oprnd1->evaluate(v), oprnd2->evaluate(v));
}

std::string CompositeElement::toString() const
{
    std::string str = "(" + oprnd1->toString() + op_char + oprnd2->toString() + ")";
    return str;
}

std::unique_ptr<Element> CompositeElement::clone() const
{
    return std::unique_ptr<Element>(new CompositeElement{ *this });
}

CompositeElement& CompositeElement::operator =(const CompositeElement & e)
{
    oprnd1 = std::move(e.oprnd1->clone());
    oprnd2 = std::move(e.oprnd2->clone());
    op_char = e.op_char;
    op_fun = e.op_fun;
    return *this;
}