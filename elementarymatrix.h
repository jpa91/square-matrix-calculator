/**
    \file element.h
    \brief Header for the ElementarySquareMatrix class template
*/

#pragma once

#include "element.h"
#include "compositeelement.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

/**
    \class TElement
    \brief Defines a class for a matrix of integer values or variables
    \tparam Type type of the class
*/
template<typename Type> class ElementarySquareMatrix
{
	public:
        /**
            \brief Default constructor
            \tparam Type type of the class
        */
		ElementarySquareMatrix<Type>();

        /**
            \brief Parametric constructor
            \param String representation of the matrix
            \tparam Type type of the class
            \exception std::invalid_argument Not a square matrix
        */
		ElementarySquareMatrix<Type>(const std::string& str_m);

        /**
            \brief Copy constructor
            \param m ElementarySquareMatrix object that is copied
            \tparam Type type of the class
        */
        ElementarySquareMatrix<Type>(const ElementarySquareMatrix<Type>& m);

        /**
            \brief Move constructor
            \param m ElementarySquareMatrix object that is moved
            \tparam Type type of the class
        */
        ElementarySquareMatrix<Type>(ElementarySquareMatrix<Type> && m);

        /**
            \brief Destructor
        */
        virtual ~ElementarySquareMatrix() = default;

        /**
            \brief Method for creating a new matrix that is a transpose of the matrix
            \tparam Type type of the class
            \return ElementarySquareMatrix object that is the transpose of the matrix
        */
        ElementarySquareMatrix<Type> transpose();

        /**
            \brief Method for creating a string representation of the matrix
            \return string that is the string representation of the matrix
        */
        std::string toString() const;

        /**
            \brief Method for outputting the string representation of the matrix
            \param os stream to print in
        */
        void print(std::ostream& os) const;

        /**
            \brief Getter for the size n of the matrix
            \return unsigned int value of the attribute n
        */
        unsigned int getN() const;

        /**
            \brief Operator for comparison
            \param rhs reference to a ElementarySquareMatrix object to compare to
            \tparam Type type of the class
            \return Boolean value of the comparison
        */
        bool operator ==(const ElementarySquareMatrix<Type>& rhs) const;

        /**
            \brief Operator for assignment
            \param m reference to a ElementarySquareMatrix object that is the matrix to assign from
            \tparam Type type of the class
            \return Reference to a ElementarySquareMatrix object that has been assigned
        */
        ElementarySquareMatrix<Type>& operator =(const ElementarySquareMatrix<Type>& m);

        /**
            \brief Operator for move assignment
            \param m reference to a ElementarySquareMatrix object that is the matrix to assign from
            \tparam Type type of the class
            \return Reference to a ElementarySquareMatrix object that has been assigned
        */
        ElementarySquareMatrix<Type>& operator =(ElementarySquareMatrix<Type>&& m);

        /**
            \brief Operator for addition
            \param rhs reference to a ElementarySquareMatrix object that is the matrix to add
            \return Reference to a ElementarySquareMatrix object that is the result of the addition
            \tparam Type type of the class
            \exception std::invalid_argument Incompatible matrices
        */
        ElementarySquareMatrix<Type>& operator +=(const ElementarySquareMatrix<Type>& rhs);

        /**
            \brief Operator for subtraction
            \param rhs reference to a ElementarySquareMatrix object that is the matrix to subtract
            \return Reference to a ElementarySquareMatrix object that is the result of the subtraction
            \tparam Type type of the class
            \exception std::invalid_argument Incompatible matrices
        */
        ElementarySquareMatrix<Type>& operator -=(const ElementarySquareMatrix<Type>& rhs);

        /**
            \brief Operator for multiplication
            \param rhs reference to a ElementarySquareMatrix object that is the matrix to multiply with
            \return Reference to a ElementarySquareMatrix object that is the result of the multiplication
            \tparam Type type of the class
            \exception std::invalid_argument Incompatible matrices
        */
        ElementarySquareMatrix<Type>& operator *=(const ElementarySquareMatrix<Type>& rhs);

        /**
            \brief Operator for addition
            \param lhs reference to a ElementarySquareMatrix object that is the left hand side of the addition
            \param rhs reference to a ElementarySquareMatrix object that is the right hand side of the addition
            \return ElementarySquareMatrix object that is the result of the addition
            \tparam Type type of the class
            \exception std::invalid_argument Incompatible matrices
        */
        ElementarySquareMatrix<Type> operator +(const ElementarySquareMatrix<Type>& rhs);

        /**
            \brief Operator for subtraction
            \param lhs reference to a ElementarySquareMatrix object that is the left hand side of the subtraction
            \param rhs reference to a ElementarySquareMatrix object that is the right hand side of the subtraction
            \return ElementarySquareMatrix object that is the result of the subtraction
            \tparam Type type of the class
            \exception std::invalid_argument Incompatible matrices
        */
        ElementarySquareMatrix<Type> operator -(const ElementarySquareMatrix<Type>& rhs);

        /**
            \brief Operator for multiplication
            \param lhs reference to a ElementarySquareMatrix object that is the left hand side of the multiplication
            \param rhs reference to a ElementarySquareMatrix object that is the right hand side of the multiplication
            \return ElementarySquareMatrix object that is the result of the multiplication
            \tparam Type type of the class
            \exception std::invalid_argument Incompatible matrices
        */
        ElementarySquareMatrix<Type> operator *(const ElementarySquareMatrix<Type>& rhs);

        /**
            \brief Method for determining the value of each integer variable in the matrix
            \param v valuation object
            \return ElementarySquareMatrix<IntElement> object that is the same matrix with variables replaced with the actual values
        */
        ElementarySquareMatrix<IntElement> evaluate(const Valuation& v) const;

	private:
		unsigned int n;
		std::vector<std::vector<std::unique_ptr<Element>>> elements;
};

/**
    \brief Method for checking if a string represents a square matrix with integer values
    \param str reference to a string
    \return Boolean value of the check
*/
bool isSquareMatrix(const std::string&);

/**
    \brief Method for checking if a string represents a square matrix with integer values and variables
    \param str reference to a string
    \return Boolean value of the check
*/
bool isSymbolicSquareMatrix(const std::string&);

/**
    \class ConcreteSquareMatrix
    \brief Class for a matrix with integer values
*/
using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;

/**
    \class ConcreteSquareMatrix
    \brief Class for a matrix with integer values and variables
*/
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;

template<typename Type>
ElementarySquareMatrix<Type>::ElementarySquareMatrix(const std::string& str_m)
{
	if (isSquareMatrix(str_m) && (typeid(Type) == typeid(IntElement)))
	{
        if (str_m == "[[]]") { n = 0; }

        else
        {
            // First determine n
            // '[' or ']' increments n
            n = std::count(str_m.begin() + 1, str_m.end(), '[');

            // Initialize row container
            //                                                                              EDITED
            std::vector<std::unique_ptr<Element>> row;

            // Initialize string where each element's value is read into
            std::string sr = "";
            for (auto ite = str_m.begin(); ite != str_m.end() - 1; ite++)
            {
                // Do nothing if a new row begins
                if (*ite == '[') {}

                // If the current character denotes next element or next row
                else if (*ite == ',' || *ite == ']')
                {
                    //                                                                      EDITED

                    // Push back the string representation of the current element into the row under construction
                    std::unique_ptr<Element> pt(new IntElement{ stoi(sr) });
                    row.push_back(std::move(pt));
                    sr = "";
                    // If row comes to an end, push the row into the elements vector
                    if (*ite == ']')
                    {
                        elements.push_back(std::move(row));
                        row.clear();
                    }
                }

                // Read current character into the string
                else sr.push_back(*ite);
            }
        }
	}

    else if (isSymbolicSquareMatrix(str_m) && (typeid(Type) == typeid(Element)))
    {
        if (str_m == "[[]]") { n = 0; }

        else
        {
            // First determine n
            // '[' or ']' increments n
            n = std::count(str_m.begin() + 1, str_m.end(), '[');

            // Initialize row container
            std::vector<std::unique_ptr<Element>> row;

            // Initialize string where the value of each integer element is read into
            std::string sr = "";
            for (auto ite = str_m.begin(); ite != str_m.end() - 1; ite++)
            {
                // Do nothing if a new row begins
                if (*ite == '[') {}

                // When current element is a variable push a pointer to row
                if (isalpha(*ite))
                {
                    std::unique_ptr<Element> ptr(new VariableElement{ *ite });
                    row.push_back(std::move(ptr));
                }

                // If the current character indicates next element or next row
                else if (*ite == ',' || *ite == ']')
                {
                    // If sr != "", then the element before *ite was an integer, so push a pointer to row
                    if (sr != "")
                    {
                        std::unique_ptr<Element> pt(new IntElement{ stoi(sr) });
                        row.push_back(std::move(pt));
                        sr = "";
                    }
                    // If row comes to an end, push the row into the elements vector
                    if (*ite == ']')
                    {
                        elements.push_back(std::move(row));
                        row.clear();
                    }
                }

                // Read current character into the string representing an integer
                else if (isdigit(*ite))
                    sr.push_back(*ite);
            }
        }
    }
    else throw std::invalid_argument("Not a square matrix");
}

template<typename Type>
ElementarySquareMatrix<Type>::ElementarySquareMatrix()
{
    if (typeid(Type) == typeid(IntElement))
        ConcreteSquareMatrix{ "[[]]" };
    else if (typeid(Type) == typeid(Element))
        SymbolicSquareMatrix{ "[[]]" };
}

// A symbolic square matrix that is the result of arithmetic
// from two matrices will not pass the isSymbolicSquareMatrix test. The problem
// is circumvented by using assignment operator in the copy constructor
// avoiding the need for testing such matrices
template<typename Type>
ElementarySquareMatrix<Type>::ElementarySquareMatrix(const ElementarySquareMatrix<Type>& m)
{
    *this = m;
}

template<typename Type>
ElementarySquareMatrix<Type>::ElementarySquareMatrix(ElementarySquareMatrix<Type>&& m)
{

    if (typeid(Type) == typeid(IntElement))
    {
        for (auto ite = m.elements.begin(); ite != m.elements.end(); ite++)
        {
            elements.push_back(std::move(*ite));
        }
        n = m.n;
        m.elements.clear();
    }
    else if (typeid(Type) == typeid(Element))
    {
        for (auto ite = m.elements.begin(); ite != m.elements.end(); ite++)
        {
            elements.push_back(std::move(*ite));
        }
        n = m.n;
        m.elements.clear();
    }
}

template<typename Type>
std::string ElementarySquareMatrix<Type>::toString() const
{
    if (typeid(Type) == typeid(IntElement))
    {
        // Initialize the string
        std::string str = "[";

        // Empty matrix case
        if (elements.empty())
            str.append("[]]");

        else
        {
            // Go through each row
            for (const auto& row : elements)
            {
                // Add the beginning of a new row
                str.push_back('[');
                // Add each element and separate them with ','
                for (const auto& c : row)
                {
                    //                                                                      EDITED
                    str.append(c->toString());
                    str.push_back(',');
                }

                // Remove last ',' and close the row
                str.pop_back();
                str.push_back(']');
            }
            // Close the matrix 
            str.push_back(']');
        }

        return str;
    }
    
    else if (typeid(Type) == typeid(Element))
    {
        // Initialize the string representation
        std::string str = "[";

        // Empty matrix case
        if (elements.empty())
            str.append("[]]");

        else
        {
            for (const auto& row : elements)
            {
                // At the beginnning of row, add '['
                str.push_back('[');

                for (const auto& c : row)
                {
                    // Add a string representation of the current element and ','
                    str.append(c->toString());
                    str.push_back(',');
                }
                // At the end, remove last ',' and add ']'
                str.pop_back();
                str.push_back(']');
            }

            // Close the matrix with ']'
            str.push_back(']');
        }

        return str;
    }
}

/**
    \brief Operator for output
    \param os stream to print in
    \param e reference to a ElementarySquareMatrix object
    \tparam Type type of the class
*/
template<typename Type>
std::ostream& operator <<(std::ostream& os, const ElementarySquareMatrix<Type>& m)
{
    return os << m.toString();
}

template<typename Type>
void ElementarySquareMatrix<Type>::print(std::ostream& os) const
{
    os << this->toString() << std::endl;
}

template<typename Type>
unsigned int ElementarySquareMatrix<Type>::getN() const { return n; }

template<typename Type>
ElementarySquareMatrix<Type> ElementarySquareMatrix<Type>::transpose()
{
    ElementarySquareMatrix<Type> m{ *this };
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            m.elements[i][j] = elements[j][i]->clone();
        }
    }

    return m;
}

template<typename Type>
bool ElementarySquareMatrix<Type>::operator ==(const ElementarySquareMatrix<Type>& rhs) const
{
    return (this->toString() == rhs.toString());
}

template<typename Type>
ElementarySquareMatrix<Type>& ElementarySquareMatrix<Type>::operator =(const ElementarySquareMatrix<Type>& m)
{
    if (m == *this)
        return *this;
    else
    {
        // Clear all elements
        this->elements.clear();

        // Initialize a row
        std::vector<std::unique_ptr<Element>> row;
        for (const auto& i : m.elements)
        {
            // Copy each row and push them to the matrix
            for (const auto& j : i)
            {
                row.push_back(std::move(j->clone()));
            }
            this->elements.push_back(std::move(row));
        }

        // Set correct n
        this->n = m.n;
        return *this;
    }
}

template<typename Type>
ElementarySquareMatrix<Type>& ElementarySquareMatrix<Type>::operator =(ElementarySquareMatrix<Type>&& m)
{
    if (m == *this)
        return *this;
    else
    {
        // Clear all elements
        this->elements.clear();

        // Move each row
        for (auto& i : m.elements)
        {
            this->elements.push_back(std::move(i));
        }

        // Set correct n
        this->n = m.n;

        // Empty the move assigned matrix and set the correct n
        m.elements.clear();
        m.n = 1;

        return *this;
    }
}

template<typename Type>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<Type>::evaluate(const Valuation& v) const
{
    // Initialize the string representation
    std::string str = "[";

    // Empty matrix case
    if (elements.empty())
        str.append("[]]");

    else
    {
        for (const auto& row : elements)
        {
            // At the beginnning of row, add '['
            str.push_back('[');

            for (const auto& c : row)
            {
                // Add a string representation of the current element and ','
                str.append(std::to_string(c->evaluate(v)));
                str.push_back(',');
            }
            // At the end, remove last ',' and add ']'
            str.pop_back();
            str.push_back(']');
        }

        // Close the matrix with ']'
        str.push_back(']');
    }
    ConcreteSquareMatrix m(str);

    return m;
}

template<typename Type>
ElementarySquareMatrix<Type>& ElementarySquareMatrix<Type>::operator +=(const ElementarySquareMatrix<Type>& rhs)
{
    // Check dimensions and type
    if (this->n != rhs.n || typeid(Type) != typeid(IntElement))
        throw std::invalid_argument("Incompatible matrices");

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            // This should be done more elegantly, but the problem is that
            // elements is a vector of uniq_ptrs to Elements rather than
            // <Type>. Fixing this at this point would require changing so much
            // and it would not be guaranteed to work
            IntElement eLhs{ std::stoi(this->elements[i][j]->toString()) };
            IntElement eRhs{ std::stoi(rhs.elements[i][j]->toString()) };
            eLhs += eRhs;
            this->elements[i][j] = eLhs.clone();
        }
    }

    return *this;
}

template<typename Type>
ElementarySquareMatrix<Type>& ElementarySquareMatrix<Type>::operator -=(const ElementarySquareMatrix<Type>& rhs)
{
    // Check dimensions and type
    if (this->n != rhs.n || typeid(Type) != typeid(IntElement))
        throw std::invalid_argument("Incompatible matrices");

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            // This should be done more elegantly, but the problem is that
            // elements is a vector of uniq_ptrs to Elements rather than
            // <Type>. Fixing this at this point would require changing so much
            // and it would not be guaranteed to work
            IntElement eLhs{ std::stoi(this->elements[i][j]->toString()) };
            IntElement eRhs{ std::stoi(rhs.elements[i][j]->toString()) };
            eLhs -= eRhs;
            this->elements[i][j] = eLhs.clone();
        }
    }

    return *this;
}

template<typename Type>
ElementarySquareMatrix<Type>& ElementarySquareMatrix<Type>::operator *=(const ElementarySquareMatrix<Type>& rhs)
{
    // Check dimensions and type
    if (this->n != rhs.n || typeid(Type) != typeid(IntElement))
        throw std::invalid_argument("Incompatible matrices");

    ElementarySquareMatrix<Type> lhs{ *this };
    auto multi = [lhs, &rhs](int i, int j, int k)
    {
        return std::stoi(lhs.elements[i][k]->toString()) * std::stoi(rhs.elements[k][j]->toString());
    };

    // This should be done more elegantly, but the problem is that
    // elements is a vector of uniq_ptrs to Elements rather than
    // <Type>. Fixing this at this point would require changing so much
    // and it would not be guaranteed to work
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            int res = 0;
            for (unsigned int k = 0; k < n; k++)
            {
                res = res + multi(i, j, k);
            }
            IntElement eRes{ res };
            this->elements[i][j] = eRes.clone();
        }
    }

    return *this;
}

template<typename Type>
ElementarySquareMatrix<Type> ElementarySquareMatrix<Type>::operator +(const ElementarySquareMatrix<Type>& rhs)
{
    // Check dimensions and type
    if (this->getN() != rhs.getN())
        throw std::invalid_argument("Incompatible matrices");

    else if (typeid(Type) == typeid(IntElement))
    {
        ElementarySquareMatrix<Type> res{ this->toString() };
        res += rhs;
        return res;
    }

    else if (typeid(Type) == typeid(Element))
    {
        ElementarySquareMatrix<Type> m;
        m.n = rhs.getN();
        for (unsigned int i = 0; i < n; ++i)
        {
            std::vector<std::unique_ptr<Element>> row;
            for (unsigned int j = 0; j < n; ++j)
            {
                row.push_back(std::move(CompositeElement(*elements[i][j], *rhs.elements[i][j], std::plus<int>(), '+').clone()));
            }
            m.elements.push_back(std::move(row));
        }

        return m;
    }
}

template<typename Type>
ElementarySquareMatrix<Type> ElementarySquareMatrix<Type>::operator -(const ElementarySquareMatrix<Type>& rhs)
{
    // Check dimensions and type
    if (this->getN() != rhs.getN())
        throw std::invalid_argument("Incompatible matrices");

    else if (typeid(Type) == typeid(IntElement))
    {
        ElementarySquareMatrix<Type> res{ this->toString() };
        res -= rhs;
        return res;
    }

    else if (typeid(Type) == typeid(Element))
    {
        ElementarySquareMatrix<Type> m;
        m.n = rhs.getN();
        for (unsigned int i = 0; i < n; ++i)
        {
            std::vector<std::unique_ptr<Element>> row;
            for (unsigned int j = 0; j < n; ++j)
            {
                row.push_back(std::move(CompositeElement(*elements[i][j], *rhs.elements[i][j], std::minus<int>(), '-').clone()));
            }
            m.elements.push_back(std::move(row));
        }

        return m;
    }
}

template<typename Type>
ElementarySquareMatrix<Type> ElementarySquareMatrix<Type>::operator *(const ElementarySquareMatrix<Type>& rhs)
{
    // Check dimensions and type
    if (this->getN() != rhs.getN())
        throw std::invalid_argument("Incompatible matrices");

    
    else if (typeid(Type) == typeid(IntElement) && isSquareMatrix(this->toString()))
    {
        ElementarySquareMatrix<Type> res{ this->toString() };
        res *= rhs;
        return res;
    }

    else if (typeid(Type) == typeid(Element))
    {
        ElementarySquareMatrix<Type> m;
        m.n = rhs.getN();
        for (unsigned int i = 0; i < n; ++i)
        {
            // Initialize a row vector
            std::vector<std::unique_ptr<Element>> row;
            for (unsigned int j = 0; j < n; j++)
            {
                // Store all integer pairs that are to be summed into a vector
                std::vector<CompositeElement> store;
                for (unsigned int k = 0; k < n; k++)
                {
                    store.push_back(CompositeElement(*elements[i][k], *rhs.elements[k][j], std::multiplies<int>(), '*'));
                }
                // Initialize a container for the resultant matrix element [i][i]
                std::vector<CompositeElement> res;

                // Initialize the element by taking the first two elements from store and put it into res
                res.push_back(CompositeElement(store[0], store[1], std::plus<int>(), '+'));
                
                // Pull from res, create a new element with the next one from store,
                // clear res and push back to res
                for (unsigned int l = 2; l < n; l++)
                {
                    CompositeElement e{ res[0] };
                    res.clear();
                    res.push_back(CompositeElement(e, store[l], std::plus<int>(), '+'));
                }
                
                // Push the element to a row
                row.push_back(std::move(res[0].clone()));
            }
            // Push the row to elements
            m.elements.push_back(std::move(row));
        }

        return m;
    }
}