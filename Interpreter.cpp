#include <iostream>
#include <vector>
#include "Interpreter.h"
#include "ExpressionList.h"
#include "RationalExpression.h"
#include "Operator.h"

int main()
{
    std::vector<Expression*> pass;
    pass.push_back(new RationalExpression("4"));
    pass.push_back(new RationalExpression("5"));
    pass.push_back(new RationalExpression("6"));
    pass.push_back(new Operator(OperatorToken::SUBTRACT));
    pass.push_back(new Operator(OperatorToken::ADD));
    Interpreter test = Interpreter(pass);

    return 0;
}

Interpreter::Interpreter(std::vector<Expression*>& pass)
{
    std::vector<Expression*>* input = &pass;
    std::stack<RationalExpression*> expStack;
    std::cout << "Start" << std::endl;
    interpret();
    std::cout << expStack.top()->print() << std::endl;
}

void Interpreter::interpret()
{
    for (Expression* exp : input) {
        if (exp->isOperator()) {
            auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
            expStack.pop();
            auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
            expStack.pop();
            switch (dynamic_cast<Operator*>(exp)->getType()) {
                case OperatorToken::ADD: {
                    RationalExpression added = RationalExpression::add(*exp1, *exp2);
                    expStack.push(&added);
                    break;
                }
                case OperatorToken::SUBTRACT: {
                    RationalExpression subtracted = RationalExpression::subtract(*exp1, *exp2);
                    expStack.push(&subtracted);
                    break;
                }
                case OperatorToken::MULTIPLY: {
                    RationalExpression multiplied = RationalExpression::multiply(*exp1, *exp2);
                    expStack.push(&multiplied);
                    break;
                }
                case OperatorToken::DIVIDE: {
                    RationalExpression divided = RationalExpression::divide(*exp1, *exp2);
                    expStack.push(&divided);
                    break;
                }
                case OperatorToken::FACTORIAL:break;
                case OperatorToken::L_PAREN:break;
                case OperatorToken::R_PAREN:break;
                case OperatorToken::UNKNOWN:break;
            }
        }
        else {
            std::cout << "ADD" << std::endl;
            expStack.push(dynamic_cast<RationalExpression*>(exp));
        }
    }
}
