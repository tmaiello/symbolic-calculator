#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Interpreter.h"
#include "ExpressionList.h"
#include "RationalExpression.h"
#include "Operator.h"

Interpreter::Interpreter(std::vector<Expression*> pass)
{
    input = std::move(pass);
    interpret();
}

void Interpreter::interpret()
{
    for (Expression* exp : input)
    {
        if (exp->isOperator())
        {
            switch (dynamic_cast<Operator*>(exp)->getType())
            {
                case OperatorToken::UNKNOWN:
                {
                    break;
                }
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
                case OperatorToken::DIVIDE:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto divided = RationalExpression::divide(*exp2, *exp1);
                    expStack.push(divided);
                    break;
                }
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
                case OperatorToken::LN:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double simplify = exp1->toDouble();
                    if (simplify <= 0)
                    {
                         throw new invalid_argument("Ln out of bounds.");
                    }
                    double lnVal = std::log(simplify);
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << lnVal;
                    std::string toString = stream.str();
                    auto lnDone = new RationalExpression(toString);
                    expStack.push(lnDone);
                    break;
                }
                case OperatorToken::LOG:
                {
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    double simplify = exp1->toDouble();
                    if (simplify <= 0)
                    {
                        throw new invalid_argument("Log out of bounds.");
                    }
                    double logVal = std::log10(simplify);
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << logVal;
                    std::string toString = stream.str();
                    auto logDone = new RationalExpression(toString);
                    expStack.push(logDone);
                    break;
                }
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
                case OperatorToken::L_PAREN:
                {
                    break;
                }
                case OperatorToken::R_PAREN:
                {
                    break;
                }
            }
        }
        else
        {
            expStack.push(dynamic_cast<RationalExpression*>(exp));
        }
    }
}

std::string Interpreter::output()
{
    RationalExpression* answer = expStack.top();
    RationalExpression* simplified = RationalExpression::simplify(*answer);
    return simplified->toString();
}