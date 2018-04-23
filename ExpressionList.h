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
class ExpressionList
{
	private:

	// fields
	const string input;		// raw string provided to this object
	string cleanedInput;	// cleaned string without invalid chars
	vector<Expression*> tokenList;		// validated list of token representations of pieces of the input
	vector<Expression*> postfix;		// token list in postfix notation

	// parser helper methods
	static bool isNumber(char toTest);		// returns true if the test char is a numerical char
	static bool isValidChar(char toTest);	// returns true if the test char is either numerical, or is associated with one of the valid OperatorToken types
	
	// construction methods
	void cleanInputString();	// cleans whitespace and invalid chars out of the input string, and simplifies functions/irrationals
	void processToTokens();		// turns the cleaned input string into a vector of number/operator tokens
	void checkTokenSyntax();	// cleans and corrects common errors in calculator input
	void convertToPostfix();	// resorts the token list into postfix notation

	public:

	// constructor
	ExpressionList(string input);

	// accessors
	string getInput() const;
	string getCleanedInput() const;
	vector<Expression*> getTokenList() const;
	vector<Expression*> getInPostfix() const;
};

#endif