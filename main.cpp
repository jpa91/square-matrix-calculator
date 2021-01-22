/**
	\file main.cpp
	\brief Implementation of the Matrix calculator user interface
*/

#define CATCH_CONFIG_RUNNER

#include "element.h"
#include "compositeelement.h"
#include "elementarymatrix.h"
#include "catch.hpp"
#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>

/**
	\brief Function for checking if a string is an integer
	\param str string
	\return Boolean value of the check
*/
bool isInt(const std::string& str)
{
	if (str.empty() || ((!isdigit(str[0])) && (str[0] != '-')))
		return false;

	char* p;
	strtol(str.c_str(), &p, 10);

	return (*p == 0);
}

int main(int argc, char** argv)
{
	int result = Catch::Session().run(argc, argv);

	std::stack<ElementarySquareMatrix<Element>> mystack;
	std::vector<ElementarySquareMatrix<Element>> mystore;
	Valuation v;
	std::string inp = "0";
	std::string delim = "=";
	
	while (inp != "quit")
	{
		std::cout << ">";
		std::cin >> inp;
		if (isSymbolicSquareMatrix(inp))
			mystack.push(SymbolicSquareMatrix{inp});

		// Adding variable values
		else if (inp[1] == '=' && isalpha(inp[0]) && isInt(inp.substr(inp.find("=") + 1)))
		{
			int val = std::stoi(inp.substr(inp.find("=") + 1));
			v[inp[0]] = val;
		}

		// Addition
		else if (inp == "+")
		{
			// Check that stack has enough operands
			if (mystack.size() > 1)
			{
				mystore.push_back(mystack.top());
				mystack.pop();
				mystore.push_back(mystack.top());
				mystack.pop();
				// Check that operands have equal dimensions
				if (mystore[0].getN() != mystore[1].getN())
				{
					std::cout << "Operation could not be executed" << std::endl;
					mystack.push(mystore[1]);
					mystack.push(mystore[0]);
					mystore.clear();
				}
				else
				{
					mystack.push(mystore[0] + mystore[1]);
					std::cout << mystack.top() << std::endl;
					mystore.clear();
				}
			}
			else std::cout << "Operation could not be executed" << std::endl;
		}

		// Subtraction
		else if (inp == "-")
		{
			// Check that stack has enough operands
			if (mystack.size() > 1)
			{
				mystore.push_back(mystack.top());
				mystack.pop();
				mystore.push_back(mystack.top());
				mystack.pop();
				// Check that operands have equal dimensions
				if (mystore[0].getN() != mystore[1].getN())
				{
					std::cout << "Operation could not be executed" << std::endl;
					mystack.push(mystore[1]);
					mystack.push(mystore[0]);
					mystore.clear();
				}
				else
				{
					mystack.push(mystore[0] - mystore[1]);
					std::cout << mystack.top() << std::endl;
					mystore.clear();
				}
			}
			else std::cout << "Operation could not be executed" << std::endl;
		}

		// Multiplication
		else if (inp == "*")
		{
			// Check that stack has enough operands
			if (mystack.size() > 1)
			{
				mystore.push_back(mystack.top());
				mystack.pop();
				mystore.push_back(mystack.top());
				mystack.pop();
				// Check that operands have equal dimensions
				if (mystore[0].getN() != mystore[1].getN())
				{
					std::cout << "Operation could not be executed" << std::endl;
					mystack.push(mystore[1]);
					mystack.push(mystore[0]);
					mystore.clear();
				}
				else
				{
					mystack.push(mystore[0] * mystore[1]);
					std::cout << mystack.top() << std::endl;
					mystore.clear();
				}
			}
			else std::cout << "Operation could not be executed" << std::endl;
		}

		// Evaluating the top matrix from stack
		else if (inp == "=")
		{
			if (!mystack.empty())
				std::cout << mystack.top().evaluate(v) << std::endl;
			else std::cout << "Operation could not be executed" << std::endl;
		}

		else if (inp == "quit") {}

		else std::cout << "Invalid input" << std::endl;
	}

	return 0;
}