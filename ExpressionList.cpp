/*
*	Defines the ExpressionList class, which is processed by the Interpreter to calculate a rational numerical result for the input.
*/

#include "ExpressionList.h"
#include "RationalExpression.h"
#include <iostream>
#include <stack>
#include <math.h>

#include "History.h"
#include "Interpreter.h"

// Math constants
const string PI = "3.14159";
const string E = "2.71828";

ExpressionList::ExpressionList(string input) : input(input)
{
	cleanInputString();
	processToTokens();

	cout << "BEFORE CLEAN" << endl;
	for (unsigned i = 0; i < tokenList.size(); i++)
		cout << tokenList[i]->toString() << " -> ";
	cout << "END" << endl;

	checkTokenSyntax();

	cout << "AFTER CLEAN" << endl;
	for (unsigned i = 0; i < tokenList.size(); i++)
		cout << tokenList[i]->toString() << " -> ";
	cout << "END" << endl;

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
				tokenList.push_back(new RationalExpression(PI));
			else if (getOperatorToken(cleanedInput[i]) == OperatorToken::E)
				tokenList.push_back(new RationalExpression(E));
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

	// Combine subtraction forward
	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator() && (i + 1) < tokenList.size() && tokenList[i + 1]->isNumber())
		{
			Operator* op = (Operator*)tokenList[i];
			RationalExpression* num = (RationalExpression*)tokenList[i + 1];

			if (op->getType() == OperatorToken::SUBTRACT)
			{
				tokenList[i + 1] = RationalExpression::negate(*num);
				tokenList.erase(tokenList.begin() + i);

				// make sure addition precedes the new negated number
				if (i > 0)
				{
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

	// Look for double operators
	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator() && (i + 1) < tokenList.size() && tokenList[i + 1]->isOperator())
		{
			Operator* op1 = (Operator*)tokenList[i];
			Operator* op2 = (Operator*)tokenList[i + 1];

			if (op1->getType() == op2->getType())
				tokenList.erase(tokenList.begin() + i);
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
	cout << endl;
	History* testHistory = new History();
	ExpressionList* unicorns = new ExpressionList("ln(6-6)");
	//ExpressionList* unicorns = new ExpressionList("14/2");
	Interpreter* rainbows = new Interpreter(unicorns->getInPostfix());
	cout << "Result: " << rainbows->output() << endl;
	testHistory->storePair(testHistory->createPair(unicorns, rainbows));
	string input = testHistory->returnList().front().first->getInput();
	string storedResult = testHistory->returnList().front().second->output();
	cout << "Stored input: " << input << endl;
	cout << "Stored result: " << storedResult << endl;

	/*
	string historyOutput = "";
	auto historyList = testHistory->returnList();
	for (auto iter = historyList.begin(); iter != historyList.end(); iter++)
	{
		historyOutput += (*iter).first->getInput() + " = " + (*iter).second->output() + "\n";
	}

	cout << "historyOutput: " << endl << historyOutput << endl;*/
}