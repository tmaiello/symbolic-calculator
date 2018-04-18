/*
*	Defines the ExpressionList class, which is processed by the Interpreter to calculate a rational numerical result for the input.
*/

#include "ExpressionList.h"

ExpressionList::ExpressionList(string input) : input(input) {};

/* PRIVATE HELPER METHODS */

void ExpressionList::processToTokens() {

}

void ExpressionList::checkTokenSyntax() {

}

void ExpressionList::convertToPostfix() {

}

/* PUBLIC ACCESSOR METHODS */

string ExpressionList::getInput() const {
	return input;
}

vector<Expression*> ExpressionList::getTokenList() const {
	return tokenList;
}

vector<Expression*> ExpressionList::getInPostfix() const {
	return postfix;
}