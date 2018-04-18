/*
*	Declares the ExpressionList class, which is processed by the Interpreter to calculate a rational numerical result for the input.
*/

#ifndef EXPRESSIONLIST_H
#define EXPRESSIONLIST_H

#include <string>
#include <vector>
#include "Operator.h"
//#include "RationalExpression.h"
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

	void ProcessToTokens();
	void CheckTokenSyntax();
	void ConvertToPostfix();

	public:
	ExpressionList(string input);

	string GetInput() const;
	vector<Expression*> GetTokenList() const;
	vector<Expression*> GetInPostfix() const;
};

#endif