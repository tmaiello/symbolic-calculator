#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Interpreter.h"
#include "ExpressionList.h"
#include "RationalExpression.h"
#include "Operator.h"

/*int main()
{
	string testInput = "(4 * (14/2) - 32/4) / 10 + 2";
	ExpressionList* test = new ExpressionList(testInput);
	Interpreter* testInt = new Interpreter(test->getInPostfix());
    std::cout << testInt->output() << std::endl;

    return 0;
}*/


Interpreter::Interpreter(std::vector<Expression*> pass)
{
    input = pass;
    cout << "Constructed" << endl;
    interpret();
}

void Interpreter::interpret()
{
    cout << "I'm running whoop de doo" << endl;
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
                    double sinVal = std::sin(simplify);
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
                    double cosVal = std::cos(simplify);
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
                    double tanVal = std::cos(simplify);
                    std::stringstream stream;
                    stream << fixed << std::setprecision(6) << tanVal;
                    std::string toString = stream.str();
                    auto tanDone = new RationalExpression(toString);
                    expStack.push(tanDone);
                    break;
                }
                case OperatorToken::LN:
                {
                    break;
                }
                case OperatorToken::LOG:
                {
                    break;
                }
                case OperatorToken::EXPONENT:
                {
                    break;
                }
                case OperatorToken::L_PAREN:
                {
                    break;
                }
                case OperatorToken::R_PAREN: {
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