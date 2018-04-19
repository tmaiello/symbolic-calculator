//
// Created by Ryan Solomon on 4/19/18.
//

#ifndef SYMBOLIC_CALCULATOR_HISTORY_H
#define SYMBOLIC_CALCULATOR_HISTORY_H

#include <iostream>
using namespace std;
#include <list>
#include "RationalExpression.h"
#include "ExpressionList.h"



class History {


    void createPair(ExpressionList object1, RationalExpression object2);
    void storePair(ExpressionList object1, RationalExpression object2);

};


#endif //SYMBOLIC_CALCULATOR_HISTORY_H
