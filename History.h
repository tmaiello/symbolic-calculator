//
// Defines the History class which stores expression history.
//

#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
using namespace std;
#include <list>
#include "RationalExpression.h"
#include "ExpressionList.h"
#include "Interpreter.h"




class History {

private:
    list<pair<ExpressionList, Interpreter>> listOfPairs;

public:
    History();
    pair<ExpressionList, Interpreter> createPair(ExpressionList *object1, Interpreter *object2);
    void storePair(pair<ExpressionList, Interpreter> pair1);
    list<pair<ExpressionList, Interpreter>> returnList();
    bool checkList();
};


#endif //SYMBOLIC_CALCULATOR_HISTORY_H