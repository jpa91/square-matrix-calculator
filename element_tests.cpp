/**
    \file elementarymatrix_tests.cpp
    \brief Unit tests for IntElement, CompositeElement and VariableElement classes
*/

#include "catch.hpp"
#include "element.h"
#include "compositeelement.h"
#include "elementarymatrix.h"

TEST_CASE("CompositeElement assignment operator test", "[CompositeElement]")
{
    VariableElement e1{ 'x' };
    VariableElement e2{ 'y' };
    char c = '*';
    CompositeElement ce{ e1,e2,std::multiplies<int>(),c };
    VariableElement e3{ 'a' };
    VariableElement e4{ 'b' };
    char d = '-';
    CompositeElement ce2{ e3,e4,std::minus<int>(),d };
    ce2 = ce;
    CHECK(ce2.clone()->toString() == "(x*y)");
}

TEST_CASE("CompositeElement clone method test", "[CompositeElement]")
{
    VariableElement e1{ 'x' };
    VariableElement e2{ 'y' };
    char c = '*';
    CompositeElement ce{ e1,e2,std::multiplies<int>(),c };
    CHECK(ce.clone()->toString() == "(x*y)");
}

TEST_CASE("CompositeElement evaluate method test", "[CompositeElement]")
{
    VariableElement e1{ 'x' };
    VariableElement e2{ 'y' };
    Valuation v;
    Valuation v2;
    v['x'] = 3;
    v['y'] = -5;
    char c = '*';
    CompositeElement ce{ e1,e2,std::multiplies<int>(),c };
    CHECK(ce.toString() == "(x*y)");
    CHECK(ce.evaluate(v) == -15);
    CHECK_THROWS_AS((ce.evaluate(v2)), std::invalid_argument);
    CHECK_THROWS_WITH((ce.evaluate(v2)), "No value specified for the variable element");
}

TEST_CASE("CompositeElement copy constructor test", "[CompositeElement]")
{
    IntElement e1{ 1 };
    IntElement e2{ -2 };
    char c = '*';
    CompositeElement ce{ e1,e2,std::multiplies<int>(),c };
    CompositeElement ce2{ ce };
    CHECK(ce2.toString() == "(1*-2)");
}

TEST_CASE("CompositeElement parametric constructor test", "[CompositeElement]")
{
    IntElement e1{ 1 };
    IntElement e2{ -2 };
    char c = '+';
    CompositeElement ce{ e1,e2,std::multiplies<int>(),c };
    CHECK(ce.toString() == "(1+-2)");
}

TEST_CASE("IntElement + operator test", "[IntElement]")
{
    IntElement e1{ 1 };
    IntElement e2{ 2 };
    CHECK((e1 + e2).getVal() == 3);
    CHECK(e1.getVal() == 1);
}

TEST_CASE("IntElement - operator test", "[IntElement]")
{
    IntElement e1{ 1 };
    IntElement e2{ 2 };
    CHECK((e1 - e2).getVal() == -1);
    CHECK(e1.getVal() == 1);
}

TEST_CASE("IntElement * operator test", "[IntElement]")
{
    IntElement e1{ 1 };
    IntElement e2{ 2 };
    CHECK((e1 * e2).getVal() == 2);
    CHECK(e1.getVal() == 1);
}

TEST_CASE("IntElement += operator test", "[IntElement]")
{
    IntElement e1{ 1 };
    IntElement e2{ 2 };
    CHECK((e1 += e2).getVal() == 3);
    CHECK(e1.getVal() == 3);
}

TEST_CASE("IntElement -= operator test", "[IntElement]")
{
    IntElement e1{ 1 };
    IntElement e2{ 2 };
    CHECK((e1 -= e2).getVal() == -1);
    CHECK(e1.getVal() == -1);
}

TEST_CASE("IntElement *= operator test", "[IntElement]")
{
    IntElement e1{ 1 };
    IntElement e2{ 2 };
    CHECK((e1 *= e2).getVal() == 2);
    CHECK(e1.getVal() == 2);
}

TEST_CASE("IntElement == operator test", "[IntElement]")
{
    IntElement e;
    IntElement e2{ 1 };
    CHECK(e == e);
    CHECK(!(e == e2));
}

TEST_CASE("IntElement clone() test", "[IntElement]")
{
    IntElement e{ 3 };
    CHECK(e.clone()->toString() == "3");
}

TEST_CASE("IntElement << operator test", "[IntElement]")
{
    IntElement e{ 3 };
    std::cout << e << std::endl;
}

TEST_CASE("IntElement copy constructor test", "[IntElement]")
{
    IntElement e{ 3 };
    IntElement e2{ e };
    CHECK(e2.getVal() == 3);
}

TEST_CASE("IntElement default constructor test", "[IntElement]")
{
    IntElement e;
    CHECK(e.getVal() == 0);
}

TEST_CASE("IntElement evaluate() test", "[IntElement]")
{
    IntElement e{ 2 };
    Valuation v;
    CHECK(e.evaluate(v) == 2);
}

TEST_CASE("IntElement parametric constructor, setVal() and getVal() test", "[IntElement]")
{
    IntElement v{1};
    v.setVal(3);
    CHECK(v.getVal() == 3);
}

TEST_CASE("IntElement toString() test", "[IntElement]")
{
    IntElement e{ 2 };
    CHECK(e.toString() == "2");
}

TEST_CASE("VariableElement == operator test", "[VariableElement]")
{
    VariableElement e;
    VariableElement e2{ 'y' };
    CHECK(e == e);
    CHECK(!(e == e2));
}

TEST_CASE("VariableElement clone() test", "[VariableElement]")
{
    VariableElement e{ 'k' };
    CHECK(e.clone()->toString() == "k");
}

TEST_CASE("VariableElement << operator test", "[VariableElement]")
{
    VariableElement e{ 'k' };
    std::cout << e << std::endl;
}

TEST_CASE("VariableElement copy constructor test", "[VariableElement]")
{
    VariableElement e{ 'y' };
    VariableElement e2{ e };
    CHECK(e2.getVal() == 'y');
}

TEST_CASE("VariableElement default constructor test", "[VariableElement]")
{
    VariableElement e;
    CHECK(e.getVal() == 'x');
}

TEST_CASE("VariableElement evaluate() test", "[IntElement]")
{
    VariableElement e{ 'y' };
    Valuation v;
    v['y'] = 3;
    CHECK(e.evaluate(v) == 3);
    Valuation w;
    CHECK_THROWS(e.evaluate(w));
    CHECK_THROWS_AS((e.evaluate(w)), std::invalid_argument);
    CHECK_THROWS_WITH((e.evaluate(w)), "No value specified for the variable element");
}

TEST_CASE("VariableElement parametric constructor, setVal() and getVal() test", "[VariableElement]")
{
    VariableElement v{'k'};
    v.setVal('y');
    CHECK(v.getVal() == 'y');
}

TEST_CASE("VariableElement toString() test", "[VariableElement]")
{
    VariableElement e{ 'P' };
    CHECK(e.toString() == "P");
}