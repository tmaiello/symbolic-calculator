/*
*	Declares the ExpressionList class, which is processed by the Interpreter to calculate a rational numerical result for the input.
*/

#ifndef EXPRESSIONLIST_H
#define EXPRESSIONLIST_H

#include <vector>
#include "Operator.h"
using namespace std;

/*
*	[ ExpressionList ]
*	- Stores an input string
*	- Converts that string into a list (stored as vector) of tokens
*	- Resorts that list of tokens into postfix notation.
*/
class ExpressionList {
	private:
	const string input;
	vector<Expression*> tokenList;
	vector<Expression*> postfix;

	bool isNumber(char toTest);
	bool isValidChar(char toTest);
	void processToTokens();
	void checkTokenSyntax();
	void convertToPostfix();

	public:
	ExpressionList(string input);

	string getInput() const;
	vector<Expression*> getTokenList() const;
	vector<Expression*> getInPostfix() const;
};

#endif