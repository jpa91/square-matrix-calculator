/**
	\file element.h
	\brief Header for the Element and Valuation classes and TElement class template
*/

#pragma once

#include <string>
#include <map>
#include <memory>
#include <stdexcept>

// Is this the correct place for this?
using Valuation = std::map<char, int>;

/**
	\class Element
	\brief An interface class for an integer value or a variable
*/
class Element
{
	public:
		/**
			\brief Destructor
		*/
		virtual ~Element() = default;

		/**
			\brief Virtual method for creating a string representation of the integer
			\return string that is the string representation of the attribute val
		*/
		virtual std::string toString() const = 0;

		/**
			\brief Virtual method for determining the value of the integer
			\param v Valuation object
			\return string that is the string representation of the attribute val
		*/
		virtual int evaluate(const Valuation& v) const = 0;

		/**
			\brief Virtual method for creating a copy of the object and returning a smart pointer to it
			\return unique_ptr to the created Element object
		*/
		virtual std::unique_ptr<Element> clone() const = 0;
};

/**
	\brief Operator for output
	\param os stream to print in
	\param e reference to an Element object
*/
std::ostream& operator <<(std::ostream&, const Element& e);

/**
	\brief Operator for comparison
	\param lhs reference to an Element object that is the left-hand side of the comparison
	\param rhs reference to an Element object that is the right-hand side of the comparison
	\return Boolean value of the comparison
*/
bool operator ==(const Element& lhs, const Element& rhs);

/**
	\class TElement
	\brief Defines a class for an integer value or a variable
	\tparam Type type of the class
*/
template<typename Type> class TElement: public Element
{
	public:
		/**
			\brief Default constructor
			\tparam Type type of the class
		*/
		TElement<Type>();

		/**
			\brief Copy constructor
			\param e TElement object that is copied
			\tparam Type type of the class
		*/
		TElement<Type>(const TElement<Type>& e);

		/**
			\brief Parametric constructor for the integer type
			\param v int
			\tparam Type type of the class
		*/
		TElement<Type>(int v) : val(v) {};

		/**
			\brief Parametric constructor for the character type
			\param v char
			\tparam Type type of the class
		*/
		TElement<Type>(char v) : val(v) {};

		/**
			\brief Destructor
		*/
		virtual ~TElement() = default;

		/**
			\brief Getter for the attribute val
			\return Type value of the attribute val
		*/
		Type getVal() const;

		/**
			\brief Setter for the attribute val
			\param v Type
		*/
		void setVal(Type v);

		/**
			\brief Method for creating a string representation of the integer variable
			\return string that is the string representation of the attribute val
		*/
		std::string toString() const;

		/**
			\brief Method for determining the value of the integer
			\param v valuation object
			\return int value of the attribute val
		*/
		int evaluate(const Valuation& v) const;

		/**
			\brief Method for creating a copy of the object and returning a smart pointer to it
			\return unique_ptr to the createdElement object
		*/
		std::unique_ptr<Element> clone() const;

		/**
			\brief Operator for addition
			\param rhs reference to a TElement object that is the element to add
			\tparam Type type of the class
			\return Reference to a TElement object that is the result of the addition
		*/
		TElement<Type>& operator +=(const TElement<Type>& rhs);

		/**
			\brief Operator for subtraction
			\param rhs reference to a TElement object that is the element to subtract
			\tparam Type type of the class
			\return Reference to a TElement object that is the result of the subtraction
		*/
		TElement<Type>& operator -=(const TElement<Type>& rhs);

		/**
			\brief Operator for multiplication
			\param rhs reference to a TElement object that is the element to multiply with
			\tparam Type type of the class
			\return Reference to a TElement object that is the result of the multiplication
		*/
		TElement<Type>& operator *=(const TElement<Type>& rhs);

	private:
		Type val;
};

/**
	\class IntElement
	\brief Class for integer values
*/
using IntElement = TElement<int>;

/**
	\class VariableElement
	\brief Class for integer variables
*/
using VariableElement = TElement<char>;

template<typename Type>
TElement<Type>::TElement()
{
	if (typeid(Type) == typeid(int))
		val = 0;
	else if (typeid(Type) == typeid(char))
		val = 'x';
}

template<typename Type>
TElement<Type>::TElement(const TElement<Type>& e)
{
	val = e.val;
}

template<typename Type>
Type TElement<Type>::getVal() const
{
	return val;
}

template<typename Type>
void TElement<Type>::setVal(Type v)
{
	val = v;
}

template<typename Type>
std::string TElement<Type>::toString() const
{
	if (typeid(Type) == typeid(int))
		return std::to_string(val);
	else if (typeid(Type) == typeid(char))
		return std::string(1, val);
}

template<typename Type>
int TElement<Type>::evaluate(const Valuation& v) const
{
	if (typeid(Type) == typeid(int))
		return val;
	else if (typeid(Type) == typeid(char))
	{
		if (v.count(val))   // Check if val is found from v
			return v.at(val);
		else
			throw std::invalid_argument("No value specified for the variable element");
	}
}

template<typename Type>
std::unique_ptr<Element> TElement<Type>::clone() const
{
	return std::unique_ptr<Element>(new TElement<Type>{*this});
}

template<typename Type>
TElement<Type>& TElement<Type>::operator +=(const TElement<Type>& rhs)
{
	if (typeid(Type) == typeid(int))
	{
		val += rhs.val;
		return *this;
	}
}

template<typename Type>
TElement<Type>& TElement<Type>::operator -=(const TElement<Type>& rhs)
{
	if (typeid(Type) == typeid(int))
	{
		val -= rhs.val;
		return *this;
	}
}

template<typename Type>
TElement<Type>& TElement<Type>::operator *=(const TElement<Type>& rhs)
{
	if (typeid(Type) == typeid(int))
	{
		val *= rhs.val;
		return *this;
	}
}

/**
	\brief Operator for addition
	\param lhs reference to a TElement object that is the left hand side of the addition
	\param rhs reference to a TElement object that is the right hand side of the addition
	\return Reference to a TElement object that is the result of the addition
*/
template<typename Type>
TElement<Type> operator +(const TElement<Type>& lhs, const TElement<Type>& rhs)
{
	if (typeid(Type) == typeid(int))
	{
		TElement<Type> res{lhs};
		res += rhs;
		return res;
	}
}

/**
	\brief Operator for subtraction
	\param lhs reference to a TElement object that is the left hand side of the subtraction
	\param rhs reference to a TElement object that is the right hand side of the subtraction
	\return Reference to a TElement object that is the result of the subtraction
*/
template<typename Type>
TElement<Type> operator -(const TElement<Type>& lhs, const TElement<Type>& rhs)
{
	if (typeid(Type) == typeid(int))
	{
		TElement<Type> res{ lhs };
		res -= rhs;
		return res;
	}
}

/**
	\brief Operator for multiplication
	\param lhs reference to a TElement object that is the left hand side of the multiplication
	\param rhs reference to a TElement object that is the right hand side of the multiplication
	\return Reference to a TElement object that is the result of the multiplication
*/
template<typename Type>
TElement<Type> operator *(const TElement<Type>& lhs, const TElement<Type>& rhs)
{
	if (typeid(Type) == typeid(int))
	{
		TElement<Type> res{ lhs };
		res *= rhs;
		return res;
	}
}