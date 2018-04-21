//
// Defines the History class which stores expression history.
//

#ifndef SYMBOLIC_CALCULATOR_HISTORY_H
#define SYMBOLIC_CALCULATOR_HISTORY_H

#include <iostream>
using namespace std;
#include <list>
#include "RationalExpression.h"
#include "ExpressionList.h"



class History {

private:
    list<pair<ExpressionList, RationalExpression>> listOfPairs;

public:
    History();
    pair<ExpressionList, RationalExpression> createPair(ExpressionList object1, RationalExpression object2);
    void storePair(pair<ExpressionList, RationalExpression> pair1);
    void iterator(int index);
    list<pair<ExpressionList, RationalExpression>> returnList();
};


#endif //SYMBOLIC_CALCULATOR_HISTORY_H
