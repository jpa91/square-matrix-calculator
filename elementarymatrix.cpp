/**
    \file elementarymatrix.cpp
    \brief Implementation of the CompositeElement class
*/

#include "elementarymatrix.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

bool isSquareMatrix(const std::string& str)
{
    int brCount = 0;        // Brace counter
    int rowCount = 0;       // Row counter
    int colCount = 0;       // Column counter or a row dimension counter
    int colCountOld = 0;    // Used to test that each row has the same dimension

    if (str[0] == '[' && str[str.length() - 1] == ']')
    {

        // Special case for "[]"
        if (str.length() == 2)
            return true;

        // General case
        for (unsigned int i = 1; i < str.length() - 1; i++)
        {

            // Check if there are characters between braces
            if (brCount == 0 && str[i] != '[')
                return false;

            // Testing when inside brackes
            if (brCount == 1)
            {

                // Test for unallowed characters
                if (!isdigit(str[i]) && str[i] != '-' && str[i] != ',' && str[i] != ']')
                    return false;

                // ',' increments the row dimension, check also that the row doesn't end after ','
                if (str[i] == ',') {
                    if (!isdigit(str[i + 1]) && str[i + 1] != '-')
                        return false;
                    colCount++;
                }

                // Minus sign usage checks
                if (str[i - 1] == '-' && !isdigit(str[i]))
                    return false;

                // Avoid beginning with ','
                if (str[i] == ',' && !isdigit(str[i - 1]))
                    return false;
            }

            // Calculate braces, rows and their dimensions
            // '[' increments the counter for the row dimension
            if (str[i] == '[')
            {
                brCount++;
                colCount++;
            }
            // ']' increments the counter for the amount of rows
            if (str[i] == ']')
            {
                brCount--;
                rowCount++;

                // A row has finished, if row counter is > 1 then check if the dimension equals the last row
                if (rowCount > 1 && colCount != colCountOld)
                {
                    return false;
                }

                // Save the row dimension and reset the counter
                colCountOld = colCount;
                colCount = 0;
            }
        }

        // Final brace check
        if (brCount != 0)
        {
            return false;
        }

        // Check that rows equal columns
        if (rowCount != colCountOld)
        {
            return false;
        }

        return true;
    }

    // The case when there are no braces
    return false;
}

// A symbolic square matrix that is the result of arithmetic
// from two matrices will not pass this test. The problem
// is circumvented by using assignment operator in the copy constructor
// avoiding the need for testing such matrices
bool isSymbolicSquareMatrix(const std::string& str)
{
    int brCount = 0;        // Brace counter
    int rowCount = 0;       // Row counter
    int colCount = 0;       // Column counter or a row dimension counter
    int colCountOld = 0;    // Used to test that each row has the same dimension

    if (str[0] == '[' && str[str.length() - 1] == ']') {

        // Special case for "[]"
        if (str.length() == 2)
            return true;

        // General case
        for (unsigned int i = 1; i < str.length() - 1; i++) {

            // Check if there are characters between braces
            if (brCount == 0 && str[i] != '[') {
                return false;
            }

            // Testing when inside brackes
            if (brCount == 1) {

                // Test for unallowed characters
                if (!isdigit(str[i]) && str[i] != '-' && str[i] != ',' && str[i] != ']' && !isalpha(str[i])) {
                    return false;
                }

                // A variable can only be represented by a single letter
                if (isalpha(str[i]))
                {
                    if (isalpha(str[i - 1]) || isalpha(str[i + 1]) || isdigit(str[i - 1]) || isdigit(str[i + 1]))
                        return false;
                }

                // ',' increments the row dimension, check also that the row doesn't end after ','
                if (str[i] == ',') {
                    if (!isdigit(str[i + 1]) && str[i + 1] != '-' && !isalpha(str[i + 1])) {
                        return false;
                    }
                    colCount++;
                }

                // Minus sign usage checks
                if (str[i - 1] == '-' && !isdigit(str[i])) {
                    return false;
                }

                // Avoid beginning with ','
                if (str[i] == ',' && !isdigit(str[i - 1]) && !isalpha(str[i - 1]))
                    return false;
            }

            // Calculate braces, rows and their dimensions
            // '[' increments the counter for the row dimension
            if (str[i] == '[') {
                brCount++;
                colCount++;
            }
            // ']' increments the counter for the amount of rows
            if (str[i] == ']') {
                brCount--;
                rowCount++;

                // A row has finished, if row counter is > 1 then check if the dimension equals the last row
                if (rowCount > 1 && colCount != colCountOld) {
                    return false;
                }

                // Save the row dimension and reset the counter
                colCountOld = colCount;
                colCount = 0;
            }

            /* Code coverage indicated that this is not needed
            // Check braces
            if (brCount < 0 || brCount > 1){
                std::cout<<"Hey"<<std::endl;
                return false;
            }
            */
        }

        // Final brace check
        if (brCount != 0) {
            return false;
        }

        // Check that rows equal columns
        if (rowCount != colCountOld) {
            return false;
        }

        return true;
    }

    // The case when there are no braces
    return false;
}
