#include <iostream>
#include <vector>
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
    for (Expression* exp : input) {
        if (exp->isOperator()) {
            switch (dynamic_cast<Operator*>(exp)->getType())
            {
                case OperatorToken::UNKNOWN:
                {
                    break;
                }
                case OperatorToken::ADD:
                {
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto added = RationalExpression::add(*exp1, *exp2);
                    expStack.push(added);
                    break;
                }
                case OperatorToken::SUBTRACT:
                {
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto subtracted = RationalExpression::subtract(*exp1, *exp2);
                    expStack.push(subtracted);
                    break;
                }
                case OperatorToken::MULTIPLY:
                {
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto multiplied = RationalExpression::multiply(*exp1, *exp2);
                    expStack.push(multiplied);
                    break;
                }
                case OperatorToken::DIVIDE:
                {
                    auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
                    expStack.pop();
                    auto divided = RationalExpression::divide(*exp1, *exp2);
                    expStack.push(divided);
                    break;
                }
                case OperatorToken::FACTORIAL:
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

std::string Interpreter::output() {
    RationalExpression* answer = expStack.top();
    RationalExpression* simplified = RationalExpression::simplify(*answer);
    return simplified->toString();
}