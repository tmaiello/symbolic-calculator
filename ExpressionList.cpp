/*
*	Defines the ExpressionList class, which is processed by the Interpreter to calculate a rational numerical result for the input.
*/

// for math constants
#define _USE_MATH_DEFINES
// project headers
#include "ExpressionList.h"
#include "RationalExpression.h"
// standard library
#include <iostream>
#include <stack>
#include <cmath>

/*
*
*/
ExpressionList::ExpressionList(string input) : input(input)
{
	cleanInputString();
	processToTokens();
	checkTokenSyntax();
	convertToPostfix();
}

/* PRIVATE HELPER METHODS */

bool ExpressionList::isNumber(char toTest)
{
	return (toTest >= (int)'0' && toTest <= (int)'9');
}

bool ExpressionList::isValidChar(char toTest)
{
	return (isNumber(toTest) || (getOperatorToken(toTest) != OperatorToken::UNKNOWN));
}

void ExpressionList::cleanInputString()
{
	cleanedInput = input;

	// process trig functions
	while (cleanedInput.find("sin") != string::npos)
	{
		int index = cleanedInput.find("sin");
		cleanedInput.replace(index, 3, "s");
	}
	while (cleanedInput.find("cos") != string::npos)
	{
		int index = cleanedInput.find("cos");
		cleanedInput.replace(index, 3, "c");
	}
	while (cleanedInput.find("tan") != string::npos)
	{
		int index = cleanedInput.find("tan");
		cleanedInput.replace(index, 3, "t");
	}

	// process logs
	while (cleanedInput.find("ln") != string::npos)
	{
		int index = cleanedInput.find("ln");
		cleanedInput.replace(index, 2, "n");
	}
	while (cleanedInput.find("log") != string::npos)
	{
		int index = cleanedInput.find("log");
		cleanedInput.replace(index, 3, "l");
	}

	// process pi
	while (cleanedInput.find("pi") != string::npos)
	{
		int index = cleanedInput.find("pi");
		cleanedInput.replace(index, 2, "p");
	}

	// remove invalid chars
	for (unsigned i = 0; i < cleanedInput.length(); i++)
		if (!ExpressionList::isValidChar(cleanedInput[i]) && cleanedInput[i] != '.')	// exception is made for '.' for decimals
			cleanedInput = cleanedInput.substr(0, i) + cleanedInput.substr(i + 1);
}

void ExpressionList::processToTokens()
{
	// start processing
	for (unsigned i = 0; i < cleanedInput.length(); i++)
	{
		// process numbers
		if (isNumber(cleanedInput[i]))
		{
			// count until end of number
			int end = i;
			int periodFound = false;
			while (end != cleanedInput.length() && (isNumber(cleanedInput[end]) || cleanedInput[end] == '.'))	// designed to short circuit when out of bounds
			{
				if (cleanedInput[i] == '.')
					if (periodFound)
						throw new invalid_argument("More than one period delimiter found in a number");
					else
						periodFound = true;

				end++;
			}

			// check for invalid period at end
			if (cleanedInput[end - 1] == '.')
				throw new invalid_argument("Period delimiter found at end of number");

			// process the whole number
			tokenList.push_back(new RationalExpression(cleanedInput.substr(i, end - i)));
			i = end - 1;
		}
		// process operators
		else
		{
			if (getOperatorToken(cleanedInput[i]) == OperatorToken::PI)
				tokenList.push_back(new RationalExpression(to_string(M_PI)));
			else if (getOperatorToken(cleanedInput[i]) == OperatorToken::E)
				tokenList.push_back(new RationalExpression(to_string(M_E)));
			else if (isValidChar(cleanedInput[i]))
				tokenList.push_back(new Operator(getOperatorToken(cleanedInput[i])));
		}
	}
}

void ExpressionList::checkTokenSyntax()
{
	// Count parentheses
	int parenthesesCount = 0;

	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator())
		{
			Operator* op = (Operator*)tokenList[i];

			if (op->getType() == OperatorToken::L_PAREN)
				parenthesesCount++;
			else if (op->getType() == OperatorToken::R_PAREN)
				parenthesesCount--;
		}

		// e.g. ")("
		if (parenthesesCount < 0)
			throw new invalid_argument("Parentheses out of order");
	}

	// Look for double operators
	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator() && (i + 1) < tokenList.size() && tokenList[i + 1]->isOperator())
		{
			Operator* op1 = (Operator*)tokenList[i];
			Operator* op2 = (Operator*)tokenList[i + 1];

			if (op1->getType() == op2->getType() && (op1->getType() != OperatorToken::L_PAREN && op1->getType() != OperatorToken::R_PAREN))
			{
				if (op1->getType() != OperatorToken::SUBTRACT)
					tokenList.erase(tokenList.begin() + i);
				else
				{
					// get rid of doubles
					tokenList.erase(tokenList.begin() + i, tokenList.begin() + (i + 2));

					// go back to recheck
					i--;
				}
				
			}
		}
	}

	// Find parentheses/functions/irrationals next to numbers
	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator())
		{
			Operator* op = (Operator*)tokenList[i];

			if (op->getType() == OperatorToken::L_PAREN && i > 0 && tokenList[i - 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));
			else if (op->getType() == OperatorToken::R_PAREN && (i + 1) < tokenList.size() && tokenList[i + 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));
			else if (op->getType() == OperatorToken::SIN)
			{
				if (i > 0 && tokenList[i - 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

				if (i < tokenList.size() && tokenList[i + 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));
			}
			else if (op->getType() == OperatorToken::COS)
			{
				if (i > 0 && tokenList[i - 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

				if (i < tokenList.size() && tokenList[i + 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));
			}
			else if (op->getType() == OperatorToken::TAN)
			{
				if (i > 0 && tokenList[i - 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

				if (i < tokenList.size() && tokenList[i + 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));
			}
			else if (op->getType() == OperatorToken::LN)
			{
				if (i > 0 && tokenList[i - 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

				if (i < tokenList.size() && tokenList[i + 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));
			}
			else if (op->getType() == OperatorToken::LOG)
			{
				if (i > 0 && tokenList[i - 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

				if (i < tokenList.size() && tokenList[i + 1]->isNumber())
					tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));
			}
		}
	}

	// Add multiplication to numbers next to each other
	for (unsigned i = 0; (i + 1) < tokenList.size(); i++)
		if (tokenList[i]->isNumber() && tokenList[i + 1]->isNumber())
			tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));

	// Find numbers preceded by '-' signs
	for (unsigned i = 1; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isNumber() && tokenList[i - 1]->isOperator())
		{
			RationalExpression* num = (RationalExpression*)tokenList[i];
			Operator* op = (Operator*)tokenList[i - 1];

			if (op->getType() == OperatorToken::SUBTRACT)
			{
				// insert parentheses start
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::L_PAREN));

				// find parentheses end
				unsigned end = i + 1;
				bool foundEnd = false;

				while (!foundEnd && end < tokenList.size())
				{
					if (tokenList[end]->isOperator())
					{
						Operator* testOp = (Operator*)tokenList[end];

						if (testOp->getType() != OperatorToken::EXPONENT)
							foundEnd = true;
					}

					end++;
				}

				// insert parentheses end
				tokenList.emplace(tokenList.begin() + end - 1, new Operator(OperatorToken::R_PAREN));
			}
		}
	}

	// Fix bad subtraction
	while (!tokenList.empty() && tokenList.front()->isOperator())
	{
		Operator* op = (Operator*)tokenList.front();

		// remove minus, add [(-1)*]
		if (op->getType() == OperatorToken::SUBTRACT)
		{
			tokenList.erase(tokenList.begin());
			tokenList.emplace(tokenList.begin(), new Operator(OperatorToken::MULTIPLY));
			tokenList.emplace(tokenList.begin(), new RationalExpression(-1));
		}
		else
			break;
	}
	
	// check everything after it
	for (unsigned i = 1; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator() && (i + 1) < tokenList.size() && tokenList[i + 1]->isOperator())
		{
			Operator* op1 = (Operator*)tokenList[i];
			Operator* op2 = (Operator*)tokenList[i + 1];

			if (op1->getType() == OperatorToken::SUBTRACT && op2->getType() == OperatorToken::L_PAREN)
			{
				tokenList.erase(tokenList.begin() + i);
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));
				tokenList.emplace(tokenList.begin() + i, new RationalExpression(-1));

				// add plus if missing
				if (tokenList[i - 1]->isNumber())
					tokenList.insert(tokenList.begin() + i, new Operator(OperatorToken::ADD));
				else
				{
					Operator* prevOp = (Operator*)tokenList[i - 1];

					if (prevOp->getType() == OperatorToken::R_PAREN)
						tokenList.insert(tokenList.begin() + i, new Operator(OperatorToken::ADD));
				}
			}
		}
	}
}

void ExpressionList::convertToPostfix()
{
	stack<Operator*> operators;

	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		// Check if number or operator
		if (tokenList[i]->isNumber())
		{
			RationalExpression* number = (RationalExpression*)tokenList[i];

			postfix.push_back(number);
		}

		if (tokenList[i]->isOperator())
		{
			Operator* op = (Operator*)tokenList[i];

			// Handle normal operators
			if (op->getType() != OperatorToken::L_PAREN && op->getType() != OperatorToken::R_PAREN)
			{
				while (operators.size() > 0 && operators.top()->getPrecedence() < op->getPrecedence())
				{
					postfix.push_back(operators.top());
					operators.pop();
				}

				operators.push(op);
			}

			// Handle parentheses
			else if (op->getType() == OperatorToken::L_PAREN)
			{
				operators.push(op);
			}

			else if (op->getType() == OperatorToken::R_PAREN) 
			{
				while (operators.top()->getType() != OperatorToken::L_PAREN)
				{
					postfix.push_back(operators.top());
					operators.pop();
				}
				
				operators.pop();	// get rid of remaining left parenthesis
			}
		}
	}

	// pop remaining operators
	while (operators.size() > 0)
	{
		postfix.push_back(operators.top());
		operators.pop();
	}
}

/* PUBLIC ACCESSOR METHODS */

string ExpressionList::getInput() const
{
	return input;
}

string ExpressionList::getCleanedInput() const
{
	return cleanedInput;
}

vector<Expression*> ExpressionList::getTokenList() const
{
	return tokenList;
}

vector<Expression*> ExpressionList::getInPostfix() const
{
	return postfix;
}

int main()
{
	ExpressionList* test = new ExpressionList("ln(5+4)");
}