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



class History {

private:
    list<pair<ExpressionList, RationalExpression>> listOfPairs;

public:
    History();
    pair<ExpressionList, RationalExpression> createPair(ExpressionList *object1, RationalExpression *object2);
    void storePair(pair<ExpressionList, RationalExpression> pair1);
    pair<ExpressionList, RationalExpression> iterator(int index);
    list<pair<ExpressionList, RationalExpression>> returnList();
};


#endif //SYMBOLIC_CALCULATOR_HISTORY_H