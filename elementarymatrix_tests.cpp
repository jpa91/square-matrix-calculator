/**
    \file elementarymatrix_tests.cpp
    \brief Unit tests for SymbolicSquareMatrix and ConcreteSquareMatrix classes
*/

#include "catch.hpp"
#include "element.h"
#include "compositeelement.h"
#include "elementarymatrix.h"

TEST_CASE("SymbolicSquareMatrix * operator test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[x,1,0][2,y,0][a,3,0]]" };
    SymbolicSquareMatrix m2{ "[[4,z,0][w,5,0][b,6,0]]" };
    Valuation valu;
    valu['x'] = 3;
    valu['y'] = -5;
    valu['z'] = 7;
    valu['w'] = -1;
    valu['a'] = 1;
    valu['b'] = 2;
    CHECK((m1 * m2).toString() == "[[(((x*4)+(1*w))+(0*b)),(((x*z)+(1*5))+(0*6)),(((x*0)+(1*0))+(0*0))][(((2*4)+(y*w))+(0*b)),(((2*z)+(y*5))+(0*6)),(((2*0)+(y*0))+(0*0))][(((a*4)+(3*w))+(0*b)),(((a*z)+(3*5))+(0*6)),(((a*0)+(3*0))+(0*0))]]");
    SymbolicSquareMatrix m3;
    CHECK_THROWS(m1 * m3);
    CHECK_THROWS_AS((m1 * m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 * m3), "Incompatible matrices");
    (m1 * m2).evaluate(valu).print(std::cout);
}

TEST_CASE("SymbolicSquareMatrix - operator test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[x,1][2,y]]" };
    SymbolicSquareMatrix m2{ "[[4,z][w,5]]" };
    CHECK((m1 - m2).toString() == "[[(x-4),(1-z)][(2-w),(y-5)]]");
    SymbolicSquareMatrix m3;
    CHECK_THROWS(m1 - m3);
    CHECK_THROWS_AS((m1 - m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 - m3), "Incompatible matrices");
}

TEST_CASE("SymbolicSquareMatrix + operator test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[x,1][2,y]]" };
    SymbolicSquareMatrix m2{ "[[4,z][w,5]]" };
    CHECK((m1 + m2).toString() == "[[(x+4),(1+z)][(2+w),(y+5)]]");
    SymbolicSquareMatrix m3;
    CHECK_THROWS(m1 + m3);
    CHECK_THROWS_AS((m1 + m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 + m3), "Incompatible matrices");
}

TEST_CASE("SymbolicSquareMatrix evaluate test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m{ "[[y,4][6,z]]" };
    SymbolicSquareMatrix m2;
    Valuation v;
    v['y'] = 3;
    v['z'] = -5;
    CHECK(m.evaluate(v).toString() == "[[3,4][6,-5]]");
    CHECK(m2.evaluate(v).toString() == "[[]]");
}

TEST_CASE("SymbolicSquareMatrix print and << operator test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[y,4][6,z]]" };
    m1.print(std::cout);
    std::cout << m1 << std::endl;
}

TEST_CASE("SymbolicSquareMatrix move assignment operator test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[y,4][6,z]]" };
    SymbolicSquareMatrix m2;
    m2 = std::move(m1);
    CHECK(m2.toString() == "[[y,4][6,z]]");
    CHECK(m1.toString() == "[[]]");
    m2 = std::move(m2);
    CHECK(m2.toString() == "[[y,4][6,z]]");
}

TEST_CASE("SymbolicSquareMatrix assignment operator test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[y,4][6,z]]" };
    SymbolicSquareMatrix m2;
    m2 = m1;
    CHECK(m2 == m1);
    m1 = m1;
    CHECK(m1 == m1);
    SymbolicSquareMatrix m3;
    m2 = m3;
    CHECK(m2.toString() == "[[]]");
}

TEST_CASE("SymbolicSquareMatrix == operator test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[y,4][6,z]]" };
    SymbolicSquareMatrix m2{ "[[x,3][2,v]]" };
    CHECK(m1 == m1);
    CHECK_FALSE(m1 == m2);
}

TEST_CASE("SymbolicSquareMatrix transpose test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m{ "[[x,3][2,v]]" };
    CHECK(m.transpose().toString() == "[[x,2][3,v]]");
}

TEST_CASE("SymbolicSquareMatrix parametric constructor test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m{ "[[x,3][2,v]]" };
    CHECK(m.toString() == "[[x,3][2,v]]");
}

TEST_CASE("SymbolicSquareMatrix default constructor test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m;
    CHECK(m.toString() == "[[]]");
    CHECK_THROWS(SymbolicSquareMatrix{ "" });
    CHECK_THROWS_AS((SymbolicSquareMatrix{ "" }), std::invalid_argument);
    CHECK_THROWS_WITH((SymbolicSquareMatrix{ "" }), "Not a square matrix");
}

TEST_CASE("SymbolicSquareMatrix copy constructor test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[x,3][2,v]]" };
    SymbolicSquareMatrix m2{ m1 };
    CHECK(m2.toString() == "[[x,3][2,v]]");
    CHECK(m1.getN() == 2);
}

TEST_CASE("SymbolicSquareMatrix move constructor test", "[SymbolicSquareMatrix]")
{
    SymbolicSquareMatrix m1{ "[[x,3][2,v]]" };
    SymbolicSquareMatrix m2{ std::move(m1) };
    CHECK(m2.toString() == "[[x,3][2,v]]");
    CHECK(m1.toString() == "[[]]");
}

TEST_CASE("ConcreteSquareMatrix + operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m2{ "[[-5,0,-2][1,2,3][0,-7,0]]" };
    CHECK((m1 += m2).toString() == "[[-2,-1,2][-6,0,2][6,-7,1]]");
    CHECK((m1 -= m2).toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    CHECK((m1 + m2).toString() == "[[-2,-1,2][-6,0,2][6,-7,1]]");
    ConcreteSquareMatrix m3{ "[[3,-1][-7,-2]]" };
    CHECK_THROWS(m1 + m3);
    CHECK_THROWS_AS((m1 + m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 + m3), "Incompatible matrices");
}

TEST_CASE("ConcreteSquareMatrix - operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m2{ "[[-5,0,-2][1,2,3][0,-7,0]]" };
    CHECK((m1 += m2).toString() == "[[-2,-1,2][-6,0,2][6,-7,1]]");
    CHECK((m1 -= m2).toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    CHECK((m1 - m2).toString() == "[[8,-1,6][-8,-4,-4][6,7,1]]");
    ConcreteSquareMatrix m3{ "[[3,-1][-7,-2]]" };
    CHECK_THROWS(m1 - m3);
    CHECK_THROWS_AS((m1 - m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 - m3), "Incompatible matrices");
}

TEST_CASE("ConcreteSquareMatrix * operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m2{ "[[-5,0,-2][1,2,3][0,-7,0]]" };
    CHECK((m1 += m2).toString() == "[[-2,-1,2][-6,0,2][6,-7,1]]");
    CHECK((m1 -= m2).toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    CHECK((m1 * m2).toString() == "[[-16,-30,-9][33,3,8][-30,-7,-12]]");
    ConcreteSquareMatrix m3{ "[[3,-1][-7,-2]]" };
    CHECK_THROWS(m1 * m3);
    CHECK_THROWS_AS((m1 * m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 * m3), "Incompatible matrices");
}

TEST_CASE("ConcreteSquareMatrix print method test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    m1.print(std::cout);
}

TEST_CASE("ConcreteSquareMatrix *= operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m2{ "[[-5,0,-2][1,2,3][0,-7,0]]" };
    CHECK((m1 += m2).toString() == "[[-2,-1,2][-6,0,2][6,-7,1]]");
    CHECK((m1 -= m2).toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    CHECK((m1 *= m2).toString() == "[[-16,-30,-9][33,3,8][-30,-7,-12]]");
    ConcreteSquareMatrix m3{ "[[3,-1][-7,-2]]" };
    CHECK_THROWS(m1 *= m3);
    CHECK_THROWS_AS((m1 *= m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 *= m3), "Incompatible matrices");
}

TEST_CASE("ConcreteSquareMatrix -= operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m2{ "[[-5,0,-2][1,2,3][0,-7,0]]" };
    CHECK((m1 += m2).toString() == "[[-2,-1,2][-6,0,2][6,-7,1]]");
    CHECK((m1 -= m2).toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    ConcreteSquareMatrix m3{ "[[3,-1][-7,-2]]" };
    CHECK_THROWS(m1 -= m3);
    CHECK_THROWS_AS((m1 -= m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 -= m3), "Incompatible matrices");
}

TEST_CASE("ConcreteSquareMatrix += operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m2{ "[[-5,0,-2][1,2,3][0,-7,0]]" };
    CHECK((m1 += m2).toString() == "[[-2,-1,2][-6,0,2][6,-7,1]]");
    ConcreteSquareMatrix m3{ "[[3,-1][-7,-2]]" };
    CHECK_THROWS(m1 += m3);
    CHECK_THROWS_AS((m1 += m3), std::invalid_argument);
    CHECK_THROWS_WITH((m1 += m3), "Incompatible matrices");
}

TEST_CASE("ConcreteSquareMatrix move assignment operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    m1 = std::move(m1);
    CHECK(m1.toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    ConcreteSquareMatrix m5{ "[[]]" };
    m5 = std::move(m1);
    CHECK(m5.toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    CHECK(m1.toString() == "[[]]");
}

TEST_CASE("ConcreteSquareMatrix assignment operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    m1 = m1;
    CHECK(m1.toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    ConcreteSquareMatrix m2{ "[[]]" };
    m2 = m1;
    CHECK(m1.toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    CHECK(m2.toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
}

TEST_CASE("ConcreteSquareMatrix == operator test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m2{ "[[-5,0,-2][1,2,3][0,-7,0]]" };
    CHECK(m1 == m1);
    CHECK_FALSE(m1 == m2);
}

TEST_CASE("ConcreteSquareMatrix parametric constructor test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    CHECK(m1.toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    ConcreteSquareMatrix m4{ "[]" };
    CHECK(m4.toString() == "[[]]");
    CHECK_THROWS(ConcreteSquareMatrix{ "" });
    CHECK_THROWS_AS((ConcreteSquareMatrix{ "" }), std::invalid_argument);
    CHECK_THROWS_WITH((ConcreteSquareMatrix{ "" }), "Not a square matrix");
}


TEST_CASE("ConcreteSquareMatrix transpose method test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    CHECK(m1.transpose().toString() == "[[3,-7,6][-1,-2,0][4,-1,1]]");
}

TEST_CASE("ConcreteSquareMatrix default constructor test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m0;
    CHECK(m0.toString() == "[[]]");
}

TEST_CASE("ConcreteSquareMatrix copy constructor test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m2{ m1 };
    CHECK(m2.toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
}

TEST_CASE("ConcreteSquareMatrix move constructor test", "[ConcreteSquareMatrix]")
{
    ConcreteSquareMatrix m1{ "[[3,-1,4][-7,-2,-1][6,0,1]]" };
    ConcreteSquareMatrix m5{ std::move(m1) };
    CHECK(m5.toString() == "[[3,-1,4][-7,-2,-1][6,0,1]]");
    CHECK(m1.toString() == "[[]]");
}

TEST_CASE("isSquareMatrix test", "[isSquareMatrix]") {
    CHECK(isSquareMatrix("[]"));
    CHECK(!isSquareMatrix("[1]"));
    CHECK(isSquareMatrix("[[1]]"));
    CHECK(isSquareMatrix("[[-1]]"));
    CHECK(!isSquareMatrix("[45]"));
    CHECK(!isSquareMatrix("[-634]"));
    CHECK(isSquareMatrix("[[]]"));
    CHECK(!isSquareMatrix("[[1,2][2,1][3,4]]"));
    CHECK(isSquareMatrix("[[3,-1][512,-15125]]"));
    CHECK(!isSquareMatrix("[[1,2][2,1]"));
    CHECK(!isSquareMatrix("[[1,2,3][2,1]]"));
    CHECK(!isSquareMatrix("[[1,2][2,1][1,2,3]]"));
    CHECK(!isSquareMatrix(""));
    CHECK(!isSquareMatrix("]["));
    CHECK(!isSquareMatrix("[[]]]"));
    CHECK(!isSquareMatrix("[[2,3]]3,1]]"));
    CHECK(!isSquareMatrix("[ ]"));
    CHECK(!isSquareMatrix("[[ ]]"));
    CHECK(!isSquareMatrix("[[[]]]"));
    CHECK(!isSquareMatrix("[[[3]]]"));
    CHECK(!isSquareMatrix("[-634-]"));
    CHECK(!isSquareMatrix("[[1,2]1[2,1]"));
    CHECK(!isSquareMatrix("[3[1,2][2,1]"));
    CHECK(!isSquareMatrix("[-[1,2][2,1]"));
    CHECK(!isSquareMatrix("[[1,2][2,1]5"));
    CHECK(!isSquareMatrix("[[1,2][2,1]-"));
    CHECK(!isSquareMatrix("[[1,2]1[2,1]"));
    CHECK(!isSquareMatrix("[[1,2]-[2,1]"));
    CHECK(!isSquareMatrix("[[1,][2,1]"));
    CHECK(!isSquareMatrix("[[,2][2,1]"));
    CHECK(!isSquareMatrix("[[--]]"));
}

TEST_CASE("isSymbolicSquareMatrix test", "[isSymbolicSquareMatrix]")
{
    CHECK(isSymbolicSquareMatrix("[[a]]"));
    CHECK(!isSymbolicSquareMatrix("[[aa]]"));
    CHECK(!isSymbolicSquareMatrix("[[1a]]"));
    CHECK(!isSymbolicSquareMatrix("[[a1]]"));
    CHECK(isSymbolicSquareMatrix("[[a,b][b,a]]"));
    CHECK(!isSymbolicSquareMatrix("[[a,b][b,a]]a"));
    CHECK(!isSymbolicSquareMatrix("[[a,b][b,a][a,b]]"));
    CHECK(isSymbolicSquareMatrix("[]"));
    CHECK(isSymbolicSquareMatrix("[[]]"));
    CHECK(!isSymbolicSquareMatrix("[1]"));
    CHECK(isSymbolicSquareMatrix("[[1]]"));
    CHECK(!isSymbolicSquareMatrix("[[1,]]"));
    CHECK(isSymbolicSquareMatrix("[[-1]]"));
    CHECK(!isSymbolicSquareMatrix("[45]"));
    CHECK(!isSymbolicSquareMatrix("[-634]"));
    CHECK(isSymbolicSquareMatrix("[[]]"));
    CHECK(!isSymbolicSquareMatrix("[[1,2][2,1][3,4]]"));
    CHECK(isSymbolicSquareMatrix("[[3,-1][512,-15125]]"));
    CHECK(!isSymbolicSquareMatrix("[[1,2][2,1]"));
    CHECK(!isSymbolicSquareMatrix("[[1,2,3][2,1]]"));
    CHECK(!isSymbolicSquareMatrix("[[1,2][2,1][1,2,3]]"));
    CHECK(!isSymbolicSquareMatrix(""));
    CHECK(!isSymbolicSquareMatrix("[["));
    CHECK(!isSymbolicSquareMatrix("]["));
    CHECK(!isSymbolicSquareMatrix("[[]]]"));
    CHECK(!isSymbolicSquareMatrix("[[2,3]]3,1]]"));
    CHECK(!isSymbolicSquareMatrix("[ ]"));
    CHECK(!isSymbolicSquareMatrix("[[ ]]"));
    CHECK(!isSymbolicSquareMatrix("[[[]]]"));
    CHECK(!isSymbolicSquareMatrix("[[[3]]]"));
    CHECK(!isSymbolicSquareMatrix("[-634-]"));
    CHECK(!isSymbolicSquareMatrix("[[1,2]1[2,1]"));
    CHECK(!isSymbolicSquareMatrix("[3[1,2][2,1]"));
    CHECK(!isSymbolicSquareMatrix("[-[1,2][2,1]"));
    CHECK(!isSymbolicSquareMatrix("[[1,2][2,1]5"));
    CHECK(!isSymbolicSquareMatrix("[[1,2][2,1]-"));
    CHECK(!isSymbolicSquareMatrix("[[1,2]1[2,1]"));
    CHECK(!isSymbolicSquareMatrix("[[1,2]-[2,1]"));
    CHECK(!isSymbolicSquareMatrix("[[1,][2,1]"));
    CHECK(!isSymbolicSquareMatrix("[[1,2][2]]"));
    CHECK(!isSymbolicSquareMatrix("[[,2][2,1]"));
    CHECK(!isSymbolicSquareMatrix("[[--]]"));
}