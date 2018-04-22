/*
*	Defines the Operator class, for tagging and storing operator tokens.
*/

#include "Operator.h"

/*
*	Create a new operator with the provided OperatorToken type.
*/
Operator::Operator(OperatorToken type) : type(type)
{
}

/*
*	Return the OperatorToken type of this object.
*/
OperatorToken Operator::getType() const
{
	return type;
}

/*
*	Return the precedence (lower is first) of this Operator object.
*/
int Operator::getPrecedence() const
{
	switch (type)
	{
	case OperatorToken::EXPONENT:
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
		// error output
		return -1;
		break;
	}
}

/*
*	Return the char/string representation of this operator.
*/
string Operator::toString() const
{
	return string(1, (char)type);
}

/*
*	Always returns false, as Operator is not of type RationalExpression.
*/
bool Operator::isNumber() const
{
	return false;
}

/*
*	Always returns true, as Operator is always of type Operator.
*/
bool Operator::isOperator() const
{
	return true;
}

/*
*	Get the OperatorToken type associated with this char.
*	For example, '+' returns OperatorToken::ADD, and 's' returns OperatorToken::SIN.
*	Also returns OperatorToken::UNKOWN if the char is not associated with a valid operator.
*	Used to quickly and easily parse the raw input string into Operator tokens wherever they show up.
*/
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
	case '^':
		return OperatorToken::EXPONENT;
		break;
	// to ease parsing later, trig functions are reduced to single char representations
	case 's':
		return OperatorToken::SIN;
		break;
	case 'c':
		return OperatorToken::COS;
		break;
	case 't':
		return OperatorToken::TAN;
		break;
	// same thing with logs
	case 'n':
		return OperatorToken::LN;
		break;
	case 'l':
		return OperatorToken::LOG;
		break;
	// constants aren't really operators, but including them simplifies string cleaning for preparsing
	case 'p':
		return OperatorToken::PI;
		break;
	case 'e':
		return OperatorToken::E;
		break;
	case '(':
		return OperatorToken::L_PAREN;
		break;
	case ')':
		return OperatorToken::R_PAREN;
		break;
	default:
		// error output
		return OperatorToken::UNKNOWN;
		break;
	}
}