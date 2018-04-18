/*
*	Defines the ExpressionList class, which is processed by the Interpreter to calculate a rational numerical result for the input.
*/

#include "ExpressionList.h";

ExpressionList::ExpressionList(string input) : input(input) {};

/* PRIVATE HELPER METHODS */

void ExpressionList::ProcessToTokens() {

}

void ExpressionList::CheckTokenSyntax() {

}

void ExpressionList::ConvertToPostfix() {

}

/* PUBLIC ACCESSOR METHODS */

string ExpressionList::GetInput() const {
	return input;
}

vector<Expression*> ExpressionList::GetTokenList() const {
	return tokenList;
}

vector<Expression*> ExpressionList::GetInPostfix() const {
	return postfix;
}