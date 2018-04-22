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
	virtual bool isNumber() const = 0;
	virtual bool isOperator() const = 0;
};

#endif