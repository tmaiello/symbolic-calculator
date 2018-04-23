/*
*	Defines the Expression interface, which is used to tag classes that can be contained in the vectors in ExpressionList.
*/

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
using namespace std;

class Expression
{
	public:

	virtual string toString() const = 0;

	// returns if this Expression is of type RationalExpression
	virtual bool isNumber() const = 0;

	// returns if this Expression is of type Operator
	virtual bool isOperator() const = 0;
};

#endif