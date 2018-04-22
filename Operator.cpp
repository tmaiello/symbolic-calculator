/*
*	Defines the Operator class, for tagging and storing operator tokens.
*/

#include "Operator.h"

Operator::Operator(OperatorToken type) : type(type) {}

OperatorToken Operator::getType() const
{
	return type;
}

// Returns the precedence (lower is first) of this operator
int Operator::getPrecedence() const
{
	switch (type)
	{
	case OperatorToken::FACTORIAL:
		return 0;
		break;

	case OperatorToken::MULTIPLY:
	case OperatorToken::DIVIDE:
		return 1;
		break;

	case OperatorToken::ADD:
	case OperatorToken::SUBTRACT:
		return 2;
		break;

	case OperatorToken::L_PAREN:
	case OperatorToken::R_PAREN:
		return 3;
		break;

	case OperatorToken::UNKNOWN:
	default:
		return -1;	// error output
		break;
	}
}

string Operator::print() const
{
	return string(1, (char)type);
}

bool Operator::isNumber() const
{
	return false;
}

bool Operator::isOperator() const
{
	return true;
}

OperatorToken getOperatorToken(char raw)
{
	switch (raw)
	{
	case '+':
		return OperatorToken::ADD;
		break;
	case '-':
		return OperatorToken::SUBTRACT;
		break;
	case '*':
		return OperatorToken::MULTIPLY;
		break;
	case '/':
		return OperatorToken::DIVIDE;
		break;
	case '!':
		return OperatorToken::FACTORIAL;
		break;
	case '(':
		return OperatorToken::L_PAREN;
		break;
	case ')':
		return OperatorToken::R_PAREN;
		break;
	default:
		return OperatorToken::UNKNOWN;	// error output
		break;
	}
}