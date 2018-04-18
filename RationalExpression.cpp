#include <iostream>
#include <cmath>
#include <numeric>
#include <sstream>
#include <limits>
#include "RationalExpression.h"

int main() {
    auto fracOne = new RationalExpression(564, 340);
    auto fracTwo = new RationalExpression(26, 47);
    std::cout << RationalExpression::simplify(RationalExpression::add(*fracOne, *fracTwo)).print() << std::endl;
    std::cout << RationalExpression::simplify(RationalExpression::subtract(*fracOne, *fracTwo)).print() << std::endl;
    std::cout << RationalExpression::simplify(RationalExpression::multiply(*fracOne, *fracTwo)).print() << std::endl;
    std::cout << RationalExpression::simplify(RationalExpression::divide(*fracOne, *fracTwo)).print() << std::endl;
    std::cout << RationalExpression("456.2771").print() << std::endl;
    std::cout << RationalExpression("3.14159").print() << std::endl;
    std::cout << RationalExpression("8").print() << std::endl;
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
    std::string stringValue = value;
    long period;
    period = -1;
    u_long stringSize;
    stringSize = stringValue.size();
    for (u_long x = 0; x < stringSize; x++) {
        if (stringValue.at(x) == '.') {
            period = x;
        }
    }
    if (period == -1) {
        long numValue = stoi(stringValue);
        numerator = numValue;
        denominator = 1;
    }
    if (period != -1) {
        long beforeDecimal;
        beforeDecimal = stoi(stringValue.substr(0, static_cast<u_long>(period)));
        std::string afterDecimalString;
        afterDecimalString = stringValue.substr(static_cast<u_long>(period) + 1);
        std::string afterDecimalStringNoAppendedZero;
        afterDecimalStringNoAppendedZero.append(afterDecimalString);
        afterDecimalStringNoAppendedZero.erase(afterDecimalStringNoAppendedZero.find_last_not_of('0') + 1, std::string::npos);
        u_long afterDecimalNoAppendedZeroSize = afterDecimalStringNoAppendedZero.size();
        int beginningZero;
        beginningZero = 0;
        for (u_long x = 0; x < afterDecimalNoAppendedZeroSize; x++) {
            if (afterDecimalStringNoAppendedZero.at(x) == '0') {
                beginningZero++;
            } else {
                break;
            }
        }
        long newDenominator;
        newDenominator = 1;
        for (int x = 0; x < afterDecimalNoAppendedZeroSize; x++) {
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
        return {numerator, denominator};
    }
}

long RationalExpression::maxValue() {
    if (numerator > denominator) {
        return numerator;
    }
    else {
        return denominator;
    }
}

std::string RationalExpression::print() const {
    return std::to_string(numerator) + " / " + std::to_string(denominator);
}
