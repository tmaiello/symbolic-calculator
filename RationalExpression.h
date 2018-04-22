/*
*	Defines the RationalExpression class, which is used to store rational forms of numbers (e.g. 7 is stored as { 7 / 1 }) and process operations on those rational forms.
*/

#ifndef RATIONALEXPRESSION_H
#define RATIONALEXPRESSION_H

#include "Expression.h"

class RationalExpression : public Expression
{
	private:

	// fields
    long long numerator;
    long long denominator;

	public:

	// constructors
    RationalExpression(long long num, long long denom);		// initializes based on a precalculated numerator/denominator pair
    explicit RationalExpression(long long value);			// converts a whole number into rational form
    explicit RationalExpression(std::string value);			// converts a string into its rational form; accepts both whole numbers and decimals

	// operator functions
	static RationalExpression* add(RationalExpression one, RationalExpression two);
	static RationalExpression* subtract(RationalExpression one, RationalExpression two);
	static RationalExpression* multiply(RationalExpression one, RationalExpression two);
	static RationalExpression* divide(RationalExpression one, RationalExpression two);
	static RationalExpression* simplify(RationalExpression input);
	static RationalExpression* negate(RationalExpression input);

	// value/constant methods
	long long maxValue();
	bool isNumber() const override;
	bool isOperator() const override;

	// utility methods
    static RationalExpression makeDecimalFraction(std::pair<std::string, long long> &value);
    std::string toString() const override;
};

#endif