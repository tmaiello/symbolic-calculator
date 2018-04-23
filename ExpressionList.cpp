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
*	This constructor is vitally important to the project.
*	Actual processing and conversion of input strings happens inside of the methods in this constructor. This conversion and subsequent resorting into postfix notation is almost half of the work done in this project.
*	Since all of the string parsing happens in private helper methods called in this constructor, almost every possible error will be avoided or thrown here.
*
*	Four methods are called as part of this instructor:
*	- cleanInputString(): Fills the cleanedInput field with validated input from the provided input
*	- processToTokens(): Fills the tokenList field with a tokenized version of the cleaned input, with tokens for RationalExpression and Operator objects
*	- checkTokenSyntax(): Catches the vast majority of errors in the program, and handles them or throws them back. Verifies that the tokenized list is a valid expression that can be evaluated.
*	- convertToPostfix(): Resorts the tokenized list into postfix notation. At this point the postfix field should be entirely valid for Interpreter to process.
*/
ExpressionList::ExpressionList(string input) : input(input)
{
	// Validate and preparse input
	cleanInputString();

	// Tokenize cleaned input
	processToTokens();

	// Fix tokenized list syntax
	checkTokenSyntax();

	// Convert the tokenized list to postfix notation
	convertToPostfix();
}


/* PARSER HELPER METHODS */

/*
*	Returns true if the test char is a numerical char.
*/
bool ExpressionList::isNumber(char toTest)
{
	return (toTest >= (int)'0' && toTest <= (int)'9');
}

/*
*	Returns true if the test char is either numerical, or is associated with one of the valid OperatorToken types.
*/
bool ExpressionList::isValidChar(char toTest)
{
	// if the char isn't a valid operator, getOperatorToken won't find a matching operator, and will return UNKNOWN
	return (isNumber(toTest) || (getOperatorToken(toTest) != OperatorToken::UNKNOWN));
}

/* CONSTRUCTOR METHODS */

/*
*	Cleans whitespace and invalid chars out of the input string, and simplifies functions/irrationals.
*/
void ExpressionList::cleanInputString()
{
	// initialize
	cleanedInput = input;

	/* process trig functions */

	// sine
	while (cleanedInput.find("sin") != string::npos)
	{
		// store start of erase
		int index = cleanedInput.find("sin");

		// remove next 3 chars ("sin")
		cleanedInput.replace(index, 3, "s");
	}

	// cosine
	while (cleanedInput.find("cos") != string::npos)
	{
		// store start of erase
		int index = cleanedInput.find("cos");

		// remove next 3 chars ("cos")
		cleanedInput.replace(index, 3, "c");
	}

	// tangent
	while (cleanedInput.find("tan") != string::npos)
	{
		// store start of erase
		int index = cleanedInput.find("tan");

		// remove next 3 chars ("tan")
		cleanedInput.replace(index, 3, "t");
	}


	/* process logs */

	// natural log
	while (cleanedInput.find("ln") != string::npos)
	{
		// store start of erase
		int index = cleanedInput.find("ln");

		// remove next 2 chars ("ln")
		cleanedInput.replace(index, 2, "n");
	}

	// log base 10
	while (cleanedInput.find("log") != string::npos)
	{
		// store start of erase
		int index = cleanedInput.find("log");

		// remove next 3 chars ("log")
		cleanedInput.replace(index, 3, "l");
	}


	/* process pi */

	// pi
	while (cleanedInput.find("pi") != string::npos)
	{
		// store start of erase
		int index = cleanedInput.find("pi");

		// remove next 2 chars ("pi")
		cleanedInput.replace(index, 2, "p");
	}


	// handle invalid chars
	for (unsigned i = 0; i < cleanedInput.length(); i++)
		if (!ExpressionList::isValidChar(cleanedInput[i]) && cleanedInput[i] != '.')	// exception is made for '.' for decimals
			throw invalid_argument("Invalid characters in input string");
}

/*
*	Turns the cleaned input string into a vector of number/operator tokens.
*/
void ExpressionList::processToTokens()
{
	// start converting numbers/operators
	for (unsigned i = 0; i < cleanedInput.length(); i++)
	{
		/* process numbers */
		
		if (isNumber(cleanedInput[i]))
		{
			// initialize result
			string numString;

			// count until end of number
			int end = i;
			int periodFound = false;

			while (end != cleanedInput.length() && (isNumber(cleanedInput[end]) || cleanedInput[end] == '.'))	// designed to short circuit when out of bounds
			{
				if (cleanedInput[i] == '.')
					if (periodFound)	// period was already found, error
						throw invalid_argument("More than one period delimiter found in a number");
					else
						periodFound = true;

				// check next index to see if that one is the end of this number
				end++;
			}

			// check for invalid period at end
			if (cleanedInput[end - 1] == '.')
				throw invalid_argument("Period delimiter found at end of number");

			// try to handle ".5"
			if (i > 0 && cleanedInput[i - 1] == '.')
				numString = "0." + cleanedInput.substr(i, end - i);
			else
				numString = cleanedInput.substr(i, end - i);

			// process the whole number
			tokenList.push_back(new RationalExpression(numString));

			// skip to right before the end, so when i++ runs for the next iteration, i points to the space after the just-processed number
			i = end - 1;
		}

		
		/* process operators */

		else
		{
			// convert pi to its numerical representation
			if (getOperatorToken(cleanedInput[i]) == OperatorToken::PI)
				tokenList.push_back(new RationalExpression(to_string(M_PI)));

			// convert e to its numerical representation
			else if (getOperatorToken(cleanedInput[i]) == OperatorToken::E)
				tokenList.push_back(new RationalExpression(to_string(M_E)));

			// process all other operators
			else if (isValidChar(cleanedInput[i]))
				tokenList.push_back(new Operator(getOperatorToken(cleanedInput[i])));
		}
	}
}

/*
*	Cleans and corrects common errors in calculator input.
*/
void ExpressionList::checkTokenSyntax()
{
	/* Count parentheses */

	// initialize and start counting
	int parenthesesCount = 0;

	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator())
		{
			// valid cast because isOperator() must be true for this to execute
			Operator* op = (Operator*)tokenList[i];

			/* There's a strategy to using one variable to count both parenthesis types: */
			/* if the parentheses are out of order, e.g. a ')' comes before a '(', the count will necessarily fall below 0 at some point. */

			// '('
			if (op->getType() == OperatorToken::L_PAREN)
				parenthesesCount++;

			// ')'
			else if (op->getType() == OperatorToken::R_PAREN)
				parenthesesCount--;
		}

		// e.g. ")("
		if (parenthesesCount < 0)
			throw invalid_argument("Parentheses out of order");
	}

	
	/* Look for double operator errors */

	// initialize and start counting
	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		// if the current token is an operator, and the next token exists/this isn't the end of the list, and the next token is an operator as well:
		if (tokenList[i]->isOperator() && (i + 1) < tokenList.size() && tokenList[i + 1]->isOperator())
		{
			// valid casts because isOperator() must be true for this to execute
			Operator* op1 = (Operator*)tokenList[i];
			Operator* op2 = (Operator*)tokenList[i + 1];

			// if the two operators are minus signs:
			if (op1->getType() == op2->getType() && op1->getType() == OperatorToken::SUBTRACT)
			{

				// try to simplify to a single minus or just positive
				// get rid of two minus signs (valid because '--' = '+' = '')
				tokenList.erase(tokenList.begin() + i, tokenList.begin() + (i + 2));

				// go back one index to recheck, in case there are multiple doubled operators in a row
			}

			// if one operator follows a left parentheses, and it's not a valid operator for that case:
			else if (op1->getType() == OperatorToken::L_PAREN && op2->getType() != OperatorToken::SIN && op2->getType() != OperatorToken::COS && op2->getType() != OperatorToken::TAN
				&& op2->getType() != OperatorToken::LN && op2->getType() != OperatorToken::LOG && op2->getType() != OperatorToken::L_PAREN && op2->getType() != OperatorToken::R_PAREN)
				// just error out, bad input
				throw invalid_argument("Invalid operators after parentheses");

			// if the two operators are different, and neither is minus/function/parentheses:
			else if (op1->getType() != OperatorToken::SUBTRACT && op2->getType() != OperatorToken::SUBTRACT
				&& op1->getType() != OperatorToken::SIN && op2->getType() != OperatorToken::SIN
				&& op1->getType() != OperatorToken::COS && op2->getType() != OperatorToken::COS
				&& op1->getType() != OperatorToken::TAN && op2->getType() != OperatorToken::TAN
				&& op1->getType() != OperatorToken::LN && op2->getType() != OperatorToken::LN
				&& op1->getType() != OperatorToken::LOG && op2->getType() != OperatorToken::LOG
				&& op1->getType() != OperatorToken::L_PAREN && op2->getType() != OperatorToken::L_PAREN
				&& op1->getType() != OperatorToken::R_PAREN && op2->getType() != OperatorToken::R_PAREN)
				// just error out, bad input
				throw invalid_argument("Invalid double operators");
		}
	}


	/* Check for operators at beginning/end */

	// check beginning
	while (!tokenList.empty() && tokenList.front()->isOperator())
	{
		// valid cast because isOperator() must be true for this to execute
		Operator* op = (Operator*)tokenList.front();

		// if operator at beginning is not a minus/function/parentheses:
		if (op->getType() != OperatorToken::SUBTRACT && op->getType() != OperatorToken::SIN && op->getType() != OperatorToken::COS && op->getType() != OperatorToken::TAN
			&& op->getType() != OperatorToken::LN && op->getType() != OperatorToken::LOG && op->getType() != OperatorToken::L_PAREN)
			throw invalid_argument("Start of expression must be a number, function, or parenthesis");
		// otherwise break to avoid infinite loop
		else
			break;
	}

	// check end
	while (!tokenList.empty() && tokenList.back()->isOperator())
	{
		// valid cast because isOperator() must be true for this to execute
		Operator* op = (Operator*)tokenList.back();

		// if operator at end is not a parenthesis:
		if (op->getType() != OperatorToken::R_PAREN)
			throw invalid_argument("Cannot parse expression ending in an operator");
		// otherwise break to avoid infinite loop
		else
			break;
	}

	
	/* Find parentheses/functions/irrationals next to numbers, and verify multiplication */

	// begin iteration
	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i]->isOperator())
		{
			// valid cast because isOperator() must be true for this to execute
			Operator* op = (Operator*)tokenList[i];

			// if the current token is a left parenthesis that is preceded by a number
			if (op->getType() == OperatorToken::L_PAREN && i > 0 && tokenList[i - 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

			// if the current token is a right parenthesis that is followed by a number
			else if (op->getType() == OperatorToken::R_PAREN && (i + 1) < tokenList.size() && tokenList[i + 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));

			// if the current token is a sine function that is preceded by a number
			else if (op->getType() == OperatorToken::SIN && i > 0 && tokenList[i - 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

			// if the current token is a cosine function that is preceded by a number
			else if (op->getType() == OperatorToken::COS && i > 0 && tokenList[i - 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

			// if the current token is a tangent function that is preceded by a number
			else if (op->getType() == OperatorToken::TAN && i > 0 && tokenList[i - 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

			// if the current token is a natural log function that is preceded by a number
			else if (op->getType() == OperatorToken::LN && i > 0 && tokenList[i - 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));

			// if the current token is a log base 10 function that is preceded by a number
			else if (op->getType() == OperatorToken::LOG && i > 0 && tokenList[i - 1]->isNumber())
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));
		}
	}

	// add multiplication to numbers next to each other
	for (unsigned i = 0; (i + 1) < tokenList.size(); i++)
		// if the current token is a number followed by another number
		if (tokenList[i]->isNumber() && tokenList[i + 1]->isNumber())
			tokenList.emplace(tokenList.begin() + i + 1, new Operator(OperatorToken::MULTIPLY));

	
	/* Find numbers preceded by '-' signs and surround with parentheses */

	for (unsigned i = 1; i < tokenList.size(); i++)
	{
		// if the current token is a number preceded by an operator
		if (tokenList[i]->isNumber() && tokenList[i - 1]->isOperator())
		{
			// valid cast because isNumber() must be true for this to execute
			RationalExpression* num = (RationalExpression*)tokenList[i];

			// valid cast because isOperator() must be true for this to execute
			Operator* op = (Operator*)tokenList[i - 1];

			// only proceed if we have a minus followed by a number
			if (op->getType() == OperatorToken::SUBTRACT)
			{
				// insert parentheses start
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::L_PAREN));

				// find parentheses end
				unsigned end = i + 1;
				bool foundEnd = false;

				while (!foundEnd && end < tokenList.size())	// end when a valid operator is found, or when end of list is reached
				{
					// break when a non-exponent operator is found
					// this surrounds either one number or one exponent expression with parentheses
					if (tokenList[end]->isOperator())
					{
						Operator* testOp = (Operator*)tokenList[end];

						if (testOp->getType() != OperatorToken::EXPONENT)
							foundEnd = true;
					}

					// iterate to check next token to find if it should be the end
					end++;
				}

				// insert parentheses end
				tokenList.emplace(tokenList.begin() + end - 1, new Operator(OperatorToken::R_PAREN));
			}
		}
	}


	/* Fix bad subtraction */

	// check front of token list
	while (!tokenList.empty() && tokenList.front()->isOperator())
	{
		// valid cast because isOperator() must be true for this to execute
		Operator* op = (Operator*)tokenList.front();

		if (op->getType() == OperatorToken::SUBTRACT)
		{
			// get rid of the subtraction
			tokenList.erase(tokenList.begin());
			
			// add[(-1)*]
			tokenList.emplace(tokenList.begin(), new Operator(OperatorToken::MULTIPLY));
			tokenList.emplace(tokenList.begin(), new RationalExpression(-1));
		}
		else
			// break out to avoid infinite loop when token list starts with operator
			break;
	}
	
	// check everything after it
	for (unsigned i = 1; i < tokenList.size(); i++)
	{
		// if the current token is an operator followed by another operator
		if (tokenList[i]->isOperator() && (i + 1) < tokenList.size() && tokenList[i + 1]->isOperator())
		{
			// valid casts because isOperator() must be true for this to execute
			Operator* op1 = (Operator*)tokenList[i];
			Operator* op2 = (Operator*)tokenList[i + 1];

			// fix negation case
			if (op1->getType() == OperatorToken::SUBTRACT && op2->getType() == OperatorToken::L_PAREN)
			{
				// get rid of the subtraction
				tokenList.erase(tokenList.begin() + i);

				// add[(-1)*]
				tokenList.emplace(tokenList.begin() + i, new Operator(OperatorToken::MULTIPLY));
				tokenList.emplace(tokenList.begin() + i, new RationalExpression(-1));

				// add plus if missing
				// if immediately preceding token is a number:
				if (tokenList[i - 1]->isNumber())
					tokenList.insert(tokenList.begin() + i, new Operator(OperatorToken::ADD));

				// if it's an operator, check if it is a right parenthesis
				else
				{
					// valid cast because isOperator() must be true for this to execute
					Operator* prevOp = (Operator*)tokenList[i - 1];

					if (prevOp->getType() == OperatorToken::R_PAREN)
						tokenList.insert(tokenList.begin() + i, new Operator(OperatorToken::ADD));
				}
			}
		}
	}
}

/*
*	Resorts the token list into postfix notation.
*/
void ExpressionList::convertToPostfix()
{
	// initialize operator stack
	stack<Operator*> operators;

	for (unsigned i = 0; i < tokenList.size(); i++)
	{
		// Handle numbers
		if (tokenList[i]->isNumber())
		{
			// valid cast because isNumber() must be true for this to execute
			RationalExpression* number = (RationalExpression*)tokenList[i];

			// always push numbers
			postfix.push_back(number);
		}

		// Handle operators
		if (tokenList[i]->isOperator())
		{
			// valid cast because isOperator() must be true for this to execute
			Operator* op = (Operator*)tokenList[i];

			// Handle normal operators
			if (op->getType() != OperatorToken::L_PAREN && op->getType() != OperatorToken::R_PAREN)
			{
				// push based on precedence
				while (operators.size() > 0 && operators.top()->getPrecedence() < op->getPrecedence())
				{
					postfix.push_back(operators.top());
					operators.pop();
				}

				operators.push(op);
			}

			// Handle left parenthesis
			else if (op->getType() == OperatorToken::L_PAREN)
			{
				operators.push(op);
			}

			// Handle right parenthesis
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