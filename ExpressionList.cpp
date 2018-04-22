/*
*	Defines the ExpressionList class, which is processed by the Interpreter to calculate a rational numerical result for the input.
*/

#include "ExpressionList.h"
#include "RationalExpression.h"
#include <iostream>
#include <stack>

ExpressionList::ExpressionList(string input) : input(input)
{
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
	// remove invalid chars
	string cleanedInput = input;
	for (unsigned i = 0; i < cleanedInput.length(); i++)
		if (!isValidChar(cleanedInput[i]) && cleanedInput[i] != '.')	// exception is made for '.' for decimals
			cleanedInput = cleanedInput.substr(0, i) + cleanedInput.substr(i + 1);

	while (cleanedInput.find("sin") != string::npos)
	{
		int index = cleanedInput.find("sin");
		cleanedInput.replace(index, 4, "s");
	}
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
			if (isValidChar(cleanedInput[i]))
				tokenList.push_back(new Operator(getOperatorToken(cleanedInput[i])));
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

	// Combine subtraction forward
	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator() && (i + 1) < tokenList.size() && tokenList[i + 1]->isNumber())
		{
			Operator* op = (Operator*)tokenList[i];
			RationalExpression* num = (RationalExpression*)tokenList[i + 1];

			//if (op->getType() == OperatorToken::SUBTRACT)
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
	string input = "4 * sin(cos(tan(ln(log(sin(4*26)))))";
	string cleanedInput = input;

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

	// remove invalid chars
	for (unsigned i = 0; i < cleanedInput.length(); i++)
		if (!ExpressionList::isValidChar(cleanedInput[i]) && cleanedInput[i] != '.')	// exception is made for '.' for decimals
			cleanedInput = cleanedInput.substr(0, i) + cleanedInput.substr(i + 1);
	
	cout << "Input: " << input << endl;
	cout << "CleanedInput: " << cleanedInput << endl;
}