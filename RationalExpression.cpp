#include <iostream>
#include <cmath>
#include <numeric>
#include <sstream>
#include <limits>
#include "RationalExpression.h"

RationalExpression::RationalExpression(long long num, long long denom)
{
    numerator = num;
    denominator = denom;
}

RationalExpression::RationalExpression(long long value)
{
    numerator = value;
    denominator = 1;
}

RationalExpression::RationalExpression(std::string value)
{
    std::string stringValue = std::move(value);
    long long period;
    period = -1;
    unsigned long long stringSize;
    stringSize = stringValue.size();
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
        RationalExpression *finalAnswer = NULL;
        if (decimal.second)
        {
            finalAnswer = add(integer, decimal.first);
        }
        else
        {
            finalAnswer = &integer;
        }
        numerator = finalAnswer->numerator;
        denominator = finalAnswer->denominator;
    }
}

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

RationalExpression* RationalExpression::multiply(RationalExpression one, RationalExpression two) //one * two
{
    long long newDenom;
    newDenom = one.denominator * two.denominator;
    long long newNumerator;
    newNumerator = one.numerator * two.numerator;
    auto toReturn = new RationalExpression(newNumerator, newDenom);
    return toReturn;
}

RationalExpression* RationalExpression::divide(RationalExpression one, RationalExpression two) //one / two
{
    long long newDenom;
    newDenom = one.denominator * two.numerator;
    long long newNumerator;
    newNumerator = one.numerator * two.denominator;
    auto toReturn = new RationalExpression(newNumerator, newDenom);
    return toReturn;
}

RationalExpression* RationalExpression::simplify(RationalExpression input)
{
    long long numerator;
    numerator = input.numerator;
    long long denominator;
    denominator = input.denominator;
    if (input.denominator != 0)
	{
        for (long long base = input.maxValue(); base > 1; base--)
		{
            if ((numerator % base == 0) && (denominator % base == 0))
			{
                numerator = numerator / base;
                denominator = denominator / base;
            }
        }
    }
    auto toReturn = new RationalExpression(numerator, denominator);
    return toReturn;
}

RationalExpression *RationalExpression::negate(RationalExpression input)
{
    long long negateNum = -(input.numerator);
    auto toReturn = new RationalExpression(negateNum, input.denominator);
    return toReturn;
}

double RationalExpression::toDouble() const {
    double simplify = static_cast<double>(numerator) / static_cast<double>(denominator);
    return simplify;
}

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

std::string RationalExpression::toString() const
{
	if (denominator != 1)
		return "(" + std::to_string(numerator) + " / " + std::to_string(denominator) + ") = " + std::to_string(toDouble());
	else
		return std::to_string(numerator);
}

bool RationalExpression::isNumber() const
{
	return true;
}

bool RationalExpression::isOperator() const
{
	return false;
}