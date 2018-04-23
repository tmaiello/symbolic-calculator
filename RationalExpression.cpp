/*
*	Defines the RationalExpression class, which is used to store rational forms of numbers (e.g. 7 is stored as { 7 / 1 }) and process operations on those rational forms.
*/

//project headers
#include "RationalExpression.h"
//standard library
#include <iostream>
#include <cmath>
#include <numeric>
#include <sstream>
#include <limits>

// initializes based on a precalculated numerator/denominator pair
RationalExpression::RationalExpression(long long num, long long denom)
{
    numerator = num;
    denominator = denom;
}

// converts a whole number into rational form
RationalExpression::RationalExpression(long long value)
{
    numerator = value;
    denominator = 1;
}

// converts a string into its rational form; accepts both whole numbers and decimals
RationalExpression::RationalExpression(std::string value)
{
    std::string stringValue = std::move(value);
    long long period;
    period = -1;
    unsigned long long stringSize;
    stringSize = stringValue.size();
    bool sign = false;
    char stringFirst = stringValue.at(0);
    if (stringFirst == '-')
    {
        sign = true;
    }
    for (unsigned long long x = 0; x < stringSize; x++)
	{
        if (stringValue.at(x) == '.')
		{
            period = x;
        }
    }
    if (period == -1)
	{
        long long numValue = stoll(stringValue);
        numerator = numValue;
        denominator = 1;
    }
    if (period != -1)
	{
        long long beforeDecimal;
        beforeDecimal = stoll(stringValue.substr(0, static_cast<unsigned long long>(period)));
        auto integer = RationalExpression(beforeDecimal);
        auto pair = std::make_pair(stringValue , period);
        auto decimal = makeDecimalFraction(pair);
        RationalExpression *finalAnswer = nullptr;
        if (decimal.second)
        {
            finalAnswer = add(integer, decimal.first);
        }
        else
        {
            finalAnswer = &integer;
        }
        if (sign)
        {
            numerator = -(finalAnswer->numerator);
        }
        else
        {
            numerator = finalAnswer->numerator;
        }
        denominator = finalAnswer->denominator;
    }
}

// used in string constructor
std::pair<RationalExpression, bool> RationalExpression::makeDecimalFraction(std::pair<std::string, long long> &value)
{
    std::string afterDecimalString;
    afterDecimalString = value.first.substr(static_cast<unsigned long long>(value.second) + 1);
    std::string removedZeros;
    removedZeros.append(afterDecimalString);
    removedZeros.erase(removedZeros.find_last_not_of('0') + 1, std::string::npos);
    unsigned long long removedZerosSize = removedZeros.size();
    long long newDenominator = 1;
    long long afterDecimal = 1;
    bool isGood = false;
    if (removedZerosSize != 0)
    {
        isGood = true;
        newDenominator = 1;
        for (unsigned long long x = 0; x < removedZerosSize; x++)
        {
            newDenominator = newDenominator * 10;
        }
        afterDecimal = stoll(removedZeros);
    }
    auto toReturn = std::make_pair(RationalExpression(afterDecimal, newDenominator), isGood);
    return toReturn;
}

// static method that adds two RationalExpression objects and returns a pointer to a new RationalExpression
RationalExpression* RationalExpression::add(RationalExpression one, RationalExpression two) //one + two
{
    long long newDenom;
    newDenom = one.denominator * two.denominator;
    long long oneNumerator;
    oneNumerator = one.numerator * two.denominator;
    long long twoNumerator;
    twoNumerator = two.numerator * one.denominator;
    long long sumNumerator;
    sumNumerator = oneNumerator + twoNumerator;
    auto toReturn = new RationalExpression(sumNumerator, newDenom);
    return toReturn;
}

// static method that subtracts two RationalExpression objects and returns a pointer to a new RationalExpression
RationalExpression* RationalExpression::subtract(RationalExpression one, RationalExpression two) //one - two
{
    long long newDenom;
    newDenom = one.denominator * two.denominator;
    long long oneNumerator;
    oneNumerator = one.numerator * two.denominator;
    long long twoNumerator;
    twoNumerator = two.numerator * one.denominator;
    long long sumNumerator;
    sumNumerator = oneNumerator - twoNumerator;
    auto toReturn = new RationalExpression(sumNumerator, newDenom);
    return toReturn;
}

// static method that multiplies two RationalExpression objects and returns a pointer to a new RationalExpression
RationalExpression* RationalExpression::multiply(RationalExpression one, RationalExpression two) //one * two
{
    long long newDenom;
    newDenom = one.denominator * two.denominator;
    long long newNumerator;
    newNumerator = one.numerator * two.numerator;
    auto toReturn = new RationalExpression(newNumerator, newDenom);
    return toReturn;
}

// static method that divides two RationalExpression objects and returns a pointer to a new RationalExpression
RationalExpression* RationalExpression::divide(RationalExpression one, RationalExpression two) //one / two
{
    long long newDenom;
    newDenom = one.denominator * two.numerator;
    long long newNumerator;
    newNumerator = one.numerator * two.denominator;
    auto toReturn = new RationalExpression(newNumerator, newDenom);
    return toReturn;
}

// static method that simplifies a RationalExpression object and returns a pointer to a new RationalExpression
RationalExpression* RationalExpression::simplify(RationalExpression input)
{
    long long numerator;
    numerator = input.numerator;
    long long denominator;
    denominator = input.denominator;
    long long toDivideBy;
    toDivideBy = input.gcd();
    numerator = numerator / toDivideBy;
    denominator = denominator / toDivideBy;
    auto toReturn = new RationalExpression(numerator, denominator);
    return toReturn;
}

// static method that flips sign of numerator and returns a pointer to a new RationalExpression
RationalExpression *RationalExpression::negate(RationalExpression input)
{
    long long negateNum = -(input.numerator);
    auto toReturn = new RationalExpression(negateNum, input.denominator);
    return toReturn;
}

// returns a double made by dividing numerator by denominator
double RationalExpression::toDouble() const {
    double simplify = static_cast<double>(numerator) / static_cast<double>(denominator);
    return simplify;
}

// returns either numerator or denominator, the bigger one gets returned
long long RationalExpression::maxValue()
{
    if (numerator > denominator)
	{
        return numerator;
    }
    else
	{
        return denominator;
    }
}

// returns string representation of RationalExpression
std::string RationalExpression::toString() const
{
	if (denominator != 1)
		return "(" + std::to_string(numerator) + " / " + std::to_string(denominator) + ") = " + std::to_string(toDouble());
	else
		return std::to_string(numerator);
}

// returns greatest common denominator, useful for simplify function
long long RationalExpression::gcd()
{
    long long num1;
    num1 = numerator;
    long long num2;
    num2 = denominator;
    long long tmp;
    while (num2 != 0) {
        tmp = num2;
        num2 = num1 % num2;
        num1 = tmp;
    }
    return num1;
}

// returns true since RationalExpression is a RationalExpression
bool RationalExpression::isNumber() const
{
	return true;
}

// returns false since RationalExpression is not Operator
bool RationalExpression::isOperator() const
{
	return false;
}