/*
*   Defines the Interpreter class which processes Reverse Polish postfix.
*/

//for math constants
#define _USE_MATH_DEFINES
//project headers
#include "Interpreter.h"
#include "ExpressionList.h"
#include "RationalExpression.h"
#include "Operator.h"
//standard library
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>

//Constructor sets vector to passed in vector and runs interpret() to get answer.
Interpreter::Interpreter(std::vector<Expression*> pass)
{
    input = std::move(pass);
    bool hasRationalExpression = false;
    for (Expression* exp : input)
    {
        if (exp->isNumber())
        {
            hasRationalExpression = true;
        }
    }
    if (input.empty() || (!(hasRationalExpression)))
    {
        throw invalid_argument("Cannot resolve empty expression.");
    }
    interpret();
}

//Primary Interpret function, takes in Reverse Polish notation and simplifies it, putting answer into expStack.
void Interpreter::interpret()
{
    for (Expression* exp : input)
    {
        //Checks if exp is an Operator.
        if (exp->isOperator())
        {
            switch (dynamic_cast<Operator*>(exp)->getType())
            {
                case OperatorToken::UNKNOWN:
                {
                    break;
                }

                /*
                 * Add case pops two objects from stack and applies addition operator to them
                 * It then pushes the answer from addition back onto the stack.
                 */
                case OperatorToken::ADD:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto added = RationalExpression::add(*exp1, *exp2);
                    expStack.push(added);
                    break;
                }

                /*
                 * Subtract case pops two objects from stack and applies subtraction operator to them
                 * It then pushes the answer from subtraction back onto the stack.
                 */
                case OperatorToken::SUBTRACT:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto subtracted = RationalExpression::subtract(*exp2, *exp1);
                    expStack.push(subtracted);
                    break;
                }

                /*
                * Multiply case pops two objects from stack and applies multiplication operator to them
                * It then pushes the answer from multiplication back onto the stack.
                */
                case OperatorToken::MULTIPLY:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto multiplied = RationalExpression::multiply(*exp1, *exp2);
                    expStack.push(multiplied);
                    break;
                }

                /*
                * Divide case pops two objects from stack and applies division operator to them
                * It then pushes the answer from division back onto the stack.
                */
                case OperatorToken::DIVIDE:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double checkZero = exp1->toDouble();
                    //Check for division by zero.
                    if (isnan(checkZero) || checkZero == 0)
                    {
                        throw invalid_argument("Can't divide by zero.");
                    }
                    auto divided = RationalExpression::divide(*exp2, *exp1);
                    expStack.push(divided);
                    break;
                }

                /*
                * Sin case pops one object from stack and applies sin operator to it
                * It then pushes the answer from sin operator back onto the stack.
                */
                case OperatorToken::SIN:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double simplify = exp1->toDouble();
                    double sinVal = std::sin(simplify * ( M_PI / 180));
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << sinVal;
                    std::string toString = stream.str();
                    auto sinDone = new RationalExpression(toString);
                    expStack.push(sinDone);
                    break;
                }

                /*
                * Cos case pops one object from stack and applies cos operator to it
                * It then pushes the answer from cos operator back onto the stack.
                */
                case OperatorToken::COS:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double simplify = exp1->toDouble();
                    double cosVal = std::cos(simplify * ( M_PI / 180));
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << cosVal;
                    std::string toString = stream.str();
                    auto cosDone = new RationalExpression(toString);
                    expStack.push(cosDone);
                    break;
                }

                /*
                * Tan case pops one object from stack and applies tan operator to it
                * It then pushes the answer from tan operator back onto the stack.
                */
                case OperatorToken::TAN:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double simplify = exp1->toDouble();
                    double tanVal = std::tan(simplify * ( M_PI / 180));
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << tanVal;
                    std::string toString = stream.str();
                    auto tanDone = new RationalExpression(toString);
                    expStack.push(tanDone);
                    break;
                }

                /*
                * Ln case pops one object from stack and applies ln operator to it
                * It then pushes the answer from ln operator back onto the stack.
                */
                case OperatorToken::LN:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double simplify = exp1->toDouble();
                    //Ln(0) is -infinity so check for out of bounds.
                    if (simplify <= 0)
                    {
                         throw invalid_argument("Ln out of bounds.");
                    }
                    double lnVal = std::log(simplify);
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << lnVal;
                    std::string toString = stream.str();
                    auto lnDone = new RationalExpression(toString);
                    expStack.push(lnDone);
                    break;
                }

                /*
                * Log case pops one object from stack and applies log operator to it
                * It then pushes the answer from log operator back onto the stack.
                */
                case OperatorToken::LOG:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double simplify = exp1->toDouble();
                    //Log(0) is -infinity so check for out of bounds.
                    if (simplify <= 0)
                    {
                        throw invalid_argument("Log out of bounds.");
                    }
                    double logVal = std::log10(simplify);
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << logVal;
                    std::string toString = stream.str();
                    auto logDone = new RationalExpression(toString);
                    expStack.push(logDone);
                    break;
                }

                /*
                * Exponent case pops one object from stack and applies exponent operator to it
                * It then pushes the answer from exponent operator back onto the stack.
                */
                case OperatorToken::EXPONENT:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double double1;
                    double1 = exp1->toDouble();
                    double double2;
                    double2 = exp2->toDouble();
                    double expVal = std::pow(double2, double1);
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << expVal;
                    std::string toString = stream.str();
                    auto expDone = new RationalExpression(toString);
                    expStack.push(expDone);
                    break;
                }
            }
        }
        //If exp is not an operator then push it to the stack since it must be a RationalExpression object.
        else
        {
            expStack.push(dynamic_cast<RationalExpression*>(exp));
        }
    }
}

//Returns string of answer.
std::string Interpreter::output()
{
    RationalExpression* answer = expStack.top();
    //Simplifies the fraction before returning.
    RationalExpression* simplified = RationalExpression::simplify(*answer);
    return simplified->toString();
}