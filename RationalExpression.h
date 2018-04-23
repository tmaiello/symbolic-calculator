/*
*	Declares the RationalExpression class, which is used to store rational forms of numbers (e.g. 7 is stored as { 7 / 1 }) and process operations on those rational forms.
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
	static RationalExpression* add(RationalExpression one, RationalExpression two);         // static method that adds two RationalExpression objects and returns a pointer to a new RationalExpression
	static RationalExpression* subtract(RationalExpression one, RationalExpression two);    // static method that subtracts two RationalExpression objects and returns a pointer to a new RationalExpression
	static RationalExpression* multiply(RationalExpression one, RationalExpression two);    // static method that multiplies two RationalExpression objects and returns a pointer to a new RationalExpression
	static RationalExpression* divide(RationalExpression one, RationalExpression two);      // static method that divides two RationalExpression objects and returns a pointer to a new RationalExpression
	static RationalExpression* simplify(RationalExpression input);                          // static method that simplifies a RationalExpression object and returns a pointer to a new RationalExpression
	static RationalExpression* negate(RationalExpression input);                            // static method that flips sign of numerator and returns a pointer to a new RationalExpression

	// value/constant methods
	long long maxValue();             // returns either numerator or denominator, the bigger one gets returned
	bool isNumber() const override;   // returns true since RationalExpression is a RationalExpression
	bool isOperator() const override; // returns false since RationalExpression is not Operator

	// utility methods
    static std::pair<RationalExpression, bool> makeDecimalFraction(std::pair<std::string, long long> &value); // used in string constructor
    long long gcd();                        // returns greatest common denominator, useful for simplify function
    std::string toString() const override;  // returns string representation of RationalExpression
	double toDouble() const;                // returns a double made by dividing numerator by denominator
};

#endif