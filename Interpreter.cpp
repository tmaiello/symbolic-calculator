#include <iostream>
#include <vector>
#include "Interpreter.h"
#include "ExpressionList.h"
#include "RationalExpression.h"
#include "Operator.h"

int main()
{
	/*
    std::vector<Expression*> pass;
    pass.push_back(new RationalExpression("4"));
    pass.push_back(new RationalExpression("5"));
    pass.push_back(new RationalExpression("6"));
    pass.push_back(new Operator(OperatorToken::SUBTRACT));
    pass.push_back(new Operator(OperatorToken::ADD));
    Interpreter test = Interpreter(pass);
	*/

	string testInput = "(4 * (14/2) - 32/4) / 10 + 2";
	ExpressionList* test = new ExpressionList(testInput);
	Interpreter* testInt = new Interpreter(test->getInPostfix());
    std::cout << testInt->output() << std::endl;

    return 0;
}

Interpreter::Interpreter(std::vector<Expression*> pass)
{
    input = pass;
    //std::cout << "Start" << std::endl;
    interpret();
}

void Interpreter::interpret()
{
    for (Expression* exp : input) {
        if (exp->isOperator()) {
            auto exp2 = dynamic_cast<RationalExpression*>(expStack.top());
            expStack.pop();
            auto exp1 = dynamic_cast<RationalExpression*>(expStack.top());
            expStack.pop();
            switch (dynamic_cast<Operator*>(exp)->getType()) {
                case OperatorToken::ADD: {
                    RationalExpression added = RationalExpression::add(*exp1, *exp2);
					//cout << "pushing: " << added.print() << endl;
                    expStack.push(&added);
                    break;
                }
                case OperatorToken::SUBTRACT: {
                    RationalExpression subtracted = RationalExpression::subtract(*exp1, *exp2);
					//cout << "pushing: " << subtracted.print() << endl;
                    expStack.push(&subtracted);
                    break;
                }
                case OperatorToken::MULTIPLY: {
                    RationalExpression multiplied = RationalExpression::multiply(*exp1, *exp2);
					//cout << "pushing: " << multiplied.print() << endl;
                    expStack.push(&multiplied);
                    break;
                }
                case OperatorToken::DIVIDE: {
                    RationalExpression divided = RationalExpression::divide(*exp1, *exp2);
					//cout << "pushing: " << divided.print() << endl;
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

	/*cout << "expStack size is: " << expStack.size() << endl;
	RationalExpression* answer = expStack.top();
	RationalExpression simplified = RationalExpression::simplify(*answer);
	cout << "Answer: " << simplified.print() << std::endl;*/
}

std::string Interpreter::output() {
    RationalExpression* answer = expStack.top();
    RationalExpression simplified = RationalExpression::simplify(*answer);
    return simplified.print();
}
