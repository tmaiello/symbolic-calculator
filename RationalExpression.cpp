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
        auto finalAnswer = add(integer, decimal);
        numerator = finalAnswer->numerator;
        denominator = finalAnswer->denominator;
    }
}

RationalExpression RationalExpression::makeDecimalFraction(std::pair<std::string, long long> &value)
{
    std::string afterDecimalString;
    afterDecimalString = value.first.substr(static_cast<unsigned long long>(value.second) + 1);
    std::string removedZeros;
    removedZeros.append(afterDecimalString);
    removedZeros.erase(removedZeros.find_last_not_of('0') + 1, std::string::npos);
    unsigned long long removedZerosSize = removedZeros.size();
    long long newDenominator;
    newDenominator = 1;
    for (unsigned long long x = 0; x < removedZerosSize; x++) {
        newDenominator = newDenominator * 10;
    }
    long long afterDecimal;
    afterDecimal = stoll(removedZeros);
    return {afterDecimal, newDenominator};
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
    return std::to_string(numerator) + " / " + std::to_string(denominator);
}

bool RationalExpression::isNumber() const
{
	return true;
}

bool RationalExpression::isOperator() const
{
	return false;
}