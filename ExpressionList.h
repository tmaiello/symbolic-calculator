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

	/* fields */

	// raw string provided to this object
	const string input;

	// cleaned string without invalid chars
	string cleanedInput;

	// validated list of token representations of pieces of the input
	vector<Expression*> tokenList;

	// token list in postfix notation
	vector<Expression*> postfix;


	/* parser helper methods */

	// returns true if the test char is a numerical char
	static bool isNumber(char toTest);

	// returns true if the test char is either numerical, or is associated with one of the valid OperatorToken types
	static bool isValidChar(char toTest);
	
	
	/* construction methods */

	// cleans whitespace and invalid chars out of the input string, and simplifies functions/irrationals
	void cleanInputString();

	// turns the cleaned input string into a vector of number/operator tokens
	void processToTokens();

	// cleans and corrects common errors in calculator input
	void checkTokenSyntax();

	// resorts the token list into postfix notation
	void convertToPostfix();


	public:

	/* constructor */

	ExpressionList(string input);


	/* accessors */
	
	string getInput() const;
	
	string getCleanedInput() const;
	
	vector<Expression*> getTokenList() const;
	
	vector<Expression*> getInPostfix() const;
};

#endif