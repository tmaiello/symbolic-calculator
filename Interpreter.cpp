#include <vector>
#include "Interpreter.h"
#include "ExpressionList.cpp"
#include "RationalExpression.cpp"
#include "Operator.cpp"

Interpreter::Interpreter(std::vector<Expression*>& pass) {
    std::vector<Expression*>* input = &pass;
    std::stack<Expression*> expStack;
}

void Interpreter::interpret() {

    for (Expression* exp : input) {
        if (exp->isOperator()) {
            auto exp1 = dynamic_cast<RationalExpression&>(expStack.top());
            expStack.pop();
            auto exp2 = dynamic_cast<RationalExpression&>(expStack.top());
            expStack.pop();
            switch (exp->getType()) {
                case OperatorToken::ADD:
                    RationalExpression added = RationalExpression::add(exp1, exp2);
                    expStack.push(&added);
                case OperatorToken::SUBTRACT:
                    RationalExpression subtracted = RationalExpression::subtract(exp1, exp2);
                    expStack.push(&subtracted);
                case OperatorToken::MULTIPLY:
                    RationalExpression multiplied = RationalExpression::multiply(exp1, exp2);
                    expStack.push(&multiplied);
                case OperatorToken::DIVIDE:
                    RationalExpression divided = RationalExpression::divide(exp1, exp2);
                    expStack.push(&multiplied);
                default:
                    break;
            }

        }
        else {
            expStack.push(exp);
        }
    }
}
