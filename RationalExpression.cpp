#include <iostream>
#include <cmath>
#include <numeric>
#include <sstream>
#include <limits>
#include "RationalExpression.h"

int main() {
    auto fracOne = new RationalExpression(564, 340);
    auto fracTwo = new RationalExpression(26, 47);
    RationalExpression::simplify(RationalExpression::add(*fracOne, *fracTwo)).print();
    RationalExpression::simplify(RationalExpression::subtract(*fracOne, *fracTwo)).print();
    RationalExpression::simplify(RationalExpression::multiply(*fracOne, *fracTwo)).print();
    RationalExpression::simplify(RationalExpression::divide(*fracOne, *fracTwo)).print();
    RationalExpression("456.2771").print();
    RationalExpression("3.14159").print();
    RationalExpression("1.414").print();
    return 0;
}

RationalExpression::RationalExpression(long num, long denom) {
    numerator = num;
    denominator = denom;
}

RationalExpression::RationalExpression(long value) {
    numerator = value;
    denominator = 1;
}

RationalExpression::RationalExpression(std::string value) {
    std::ostringstream stream;
    stream.precision(std::numeric_limits<double>::digits10);
    stream << std::fixed << value;
    std::string stringValue = value;
    long period;
    period = -1;
    unsigned long stringSize;
    stringSize = stringValue.size();
    for (unsigned long x = 0; x < stringSize; x++) {
        if (stringValue.at(x) == '.') {
            period = x;
        }
    }
    if (period != -1) {
        long beforeDecimal;
        beforeDecimal = stoi(stringValue.substr(0, static_cast<unsigned long>(period)));
        std::string afterDecimalString;
        afterDecimalString = stringValue.substr(static_cast<unsigned long>(period) + 1);
        std::string afterDecimalStringNoAppendedZero;
        afterDecimalStringNoAppendedZero.append(afterDecimalString);
        afterDecimalStringNoAppendedZero.erase(afterDecimalStringNoAppendedZero.find_last_not_of('0') + 1, std::string::npos);
        unsigned long afterDecimalNoAppendedZeroSize = afterDecimalStringNoAppendedZero.size();
        int beginningZero;
        beginningZero = 0;
        for (unsigned long x = 0; x < afterDecimalNoAppendedZeroSize; x++) {
            if (afterDecimalStringNoAppendedZero.at(x) == '0') {
                beginningZero++;
            } else {
                break;
            }
        }
        long newDenominator;
        newDenominator = 1;
        for (unsigned x = 0; x < afterDecimalNoAppendedZeroSize; x++) {
            newDenominator = newDenominator * 10;
        }
        long afterDecimal;
        afterDecimal = stoi(afterDecimalStringNoAppendedZero);
        RationalExpression integer = RationalExpression(beforeDecimal);
        RationalExpression decimal = RationalExpression(afterDecimal, newDenominator);
        RationalExpression finalAnswer = add(integer, decimal);
        numerator = finalAnswer.numerator;
        denominator = finalAnswer.denominator;
    }
}

RationalExpression RationalExpression::add(RationalExpression one, RationalExpression two) { //one + two
    long newDenom;
    newDenom = one.denominator * two.denominator;
    long oneNumerator;
    oneNumerator = one.numerator * two.denominator;
    long twoNumerator;
    twoNumerator = two.numerator * one.denominator;
    long sumNumerator;
    sumNumerator = oneNumerator + twoNumerator;
    return {sumNumerator, newDenom};
}

RationalExpression RationalExpression::subtract(RationalExpression one, RationalExpression two) { //one - two
    long newDenom;
    newDenom = one.denominator * two.denominator;
    long oneNumerator;
    oneNumerator = one.numerator * two.denominator;
    long twoNumerator;
    twoNumerator = two.numerator * one.denominator;
    long sumNumerator;
    sumNumerator = oneNumerator - twoNumerator;
    return {sumNumerator, newDenom};
}

RationalExpression RationalExpression::multiply(RationalExpression one, RationalExpression two) { //one * two
    long newDenom;
    newDenom = one.denominator * two.denominator;
    long newNumerator;
    newNumerator = one.numerator * two.numerator;
    return {newNumerator, newDenom};
}

RationalExpression RationalExpression::divide(RationalExpression one, RationalExpression two) { //one / two
    long newDenom;
    newDenom = one.denominator * two.numerator;
    long newNumerator;
    newNumerator = one.numerator * two.denominator;
    return {newNumerator, newDenom};
}


RationalExpression RationalExpression::simplify(RationalExpression input) {
    long numerator;
    numerator = input.numerator;
    long denominator;
    denominator = input.denominator;
    if (input.denominator != 0) {
        for (long base = input.maxValue(); base > 1; base--) {
            if ((numerator % base == 0) && (denominator % base == 0)) {
                numerator = numerator / base;
                denominator = denominator / base;
            }
        }
    }
	return { numerator, denominator };
}

long RationalExpression::maxValue() {
    if (numerator > denominator) {
        return numerator;
    }
    else {
        return denominator;
    }
}

void RationalExpression::print() {
    std::cout << numerator << " / " << denominator << std::endl;
}
