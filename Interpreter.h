/*
*   Declares the Interpreter class which processes Reverse Polish postfix.
*/

#ifndef SYMBOLIC_CALCULATOR_INTERPRETER_H
#define SYMBOLIC_CALCULATOR_INTERPRETER_H

#include <stack>
#include <vector>
#include "Expression.h"
#include "RationalExpression.h"

class Interpreter {
private:
    std::vector<Expression*> input; //Vector used to store Reverse Polish notation.
    std::stack<RationalExpression*> expStack; //Stack used to process Reverse Polish notation.

public:
    explicit Interpreter(std::vector<Expression*> input); //Constructor sets vector to passed in vector and runs interpret() to get answer.
    void interpret(); //Primary Interpret function, takes in Reverse Polish notation and simplifies it, putting answer into expStack.
    std::string output(); //Returns string of answer.
};

#endif //SYMBOLIC_CALCULATOR_INTERPRETER_H