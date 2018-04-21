/*
*	Defines the ExpressionList class, which is processed by the Interpreter to calculate a rational numerical result for the input.
*/

#include "ExpressionList.h"
#include "RationalExpression.h"
#include <iostream>
#include <stack>

ExpressionList::ExpressionList(string input) : input(input) {
	processToTokens();
	checkTokenSyntax();
	convertToPostfix();
}

/* PRIVATE HELPER METHODS */

bool ExpressionList::isNumber(char toTest) {
	return (toTest >= (int)'0' && toTest <= (int)'9');
}

bool ExpressionList::isValidChar(char toTest) {
	return (isNumber(toTest) || (getOperatorToken(toTest) != OperatorToken::UNKNOWN));
}

void ExpressionList::processToTokens() {
	// remove invalid chars
	string cleaned = input;
	for (unsigned i = 0; i < cleaned.length(); i++)
		if (!isValidChar(cleaned[i]) && cleaned[i] != '.')	// exception is made for '.' for decimals
			cleaned = cleaned.substr(0, i) + cleaned.substr(i + 1);

	// start processing
	for (unsigned i = 0; i < cleaned.length(); i++) {
		// process numbers
		if (isNumber(cleaned[i])) {
			// count until end of number
			int end = i;
			int periodFound = false;
			while (end != cleaned.length() && (isNumber(cleaned[end]) || cleaned[end] == '.')) {	// designed to short circuit when out of bounds
				if (cleaned[i] == '.')
					if (periodFound)
						throw new invalid_argument("More than one period delimiter found in a number");
					else
						periodFound = true;

				end++;
			}

			// check for invalid period at end
			if (cleaned[end - 1] == '.')
				throw new invalid_argument("Period delimiter found at end of number");

			// process the whole number
			tokenList.push_back(new RationalExpression(cleaned.substr(i, end - i)));
			i = end - 1;
		}
		// process operators
		else
			if (isValidChar(cleaned[i]))
				tokenList.push_back(new Operator(getOperatorToken(cleaned[i])));
	}
}

void ExpressionList::checkTokenSyntax() {

}

void ExpressionList::convertToPostfix() {
	stack<Operator*> operators;

	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		// Check if number or operator
		if (tokenList[i]->isNumber()) {
			RationalExpression* number = (RationalExpression*)tokenList[i];

			postfix.push_back(number);
		}

		if (tokenList[i]->isOperator()) {
			Operator* op = (Operator*)tokenList[i];

			// Handle normal operators
			if (op->getType() != OperatorToken::L_PAREN && op->getType() != OperatorToken::R_PAREN) {
				while (operators.size() > 0 && operators.top()->getPrecedence() < op->getPrecedence()) {
					postfix.push_back(operators.top());
					operators.pop();
				}

				operators.push(op);
			}

			// Handle parentheses
			else if (op->getType() == OperatorToken::L_PAREN) {
				operators.push(op);
			}

			else if (op->getType() == OperatorToken::R_PAREN) {
				while (operators.top()->getType() != OperatorToken::L_PAREN) {
					postfix.push_back(operators.top());
					operators.pop();
				}
				
				operators.pop();	// get rid of remaining left parenthesis
			}
		}
	}

	// pop remaining operators
	while (operators.size() > 0) {
		postfix.push_back(operators.top());
		operators.pop();
	}
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