/*
*	Declares the OperatorToken enumerator and Operator class, for tagging and storing operator tokens.
*	
*	OperatorToken:
*	- Lists all possible operator tokens.
*
*	Operator:
*	- Stores an OperatorToken type, and contains functions to identify and manage operators as part of the string-to-token-list conversion process.
*/

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include "Expression.h"
using namespace std;

/*	[ OperatorToken ]
*	Lists all possible operator tokens.
*/
enum class OperatorToken
{
	ADD = '+',
	SUBTRACT = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	FACTORIAL = '!',
	SIN = 's',
	COS = 'c',
	TAN = 't',
	LN = 'n',
	LOG = 'l',
	L_PAREN = '(',
	R_PAREN = ')',
	UNKNOWN = '?'
};

/*
*	[ Operator ]
*	(Of type Expression so it can be stored in ExpressionList vectors)
*	Stores an OperatorToken type, and contains functions to identify and manage operators as part of the string-to-token-list conversion process.
*/
class Operator : public Expression
{
	private:
	const OperatorToken type;		// stores the type of token this operator is

	public:
	const int LEFT_ASSOC = 0;
	const int RIGHT_ASSOC = 1;

	Operator(OperatorToken type);
	OperatorToken getType() const;
	int getPrecedence() const;		// returns the precedence (lower is first) of this operator
	string print() const;

	bool isNumber() const override;
	bool isOperator() const override;
};

// Helper method
OperatorToken getOperatorToken(char raw);

#endif