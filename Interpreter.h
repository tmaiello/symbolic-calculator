//
// Declares the Interpreter class which processes Reverse Polish postfix.
//

#ifndef SYMBOLIC_CALCULATOR_INTERPRETER_H
#define SYMBOLIC_CALCULATOR_INTERPRETER_H

#include <stack>
#include <vector>
#include "Expression.h"
#include "RationalExpression.h"

class Interpreter {
private:
    std::vector<Expression*> input;
    std::stack<RationalExpression*> expStack;

public:
    explicit Interpreter(std::vector<Expression *>&);
    void interpret();

};

#endif //SYMBOLIC_CALCULATOR_INTERPRETER_H
