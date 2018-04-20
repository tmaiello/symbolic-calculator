using namespace std;
#include "RationalExpression.h"
#include "ExpressionList.h"
#include "History.h"
#include <list>
#include <iostream>

History::History() {

    list<pair<ExpressionList, RationalExpression>> listOfPairs;

}

void History::storePair(pair<ExpressionList, RationalExpression> pair1) {

    listOfPairs.push_back(pair1);

}


pair<ExpressionList, RationalExpression> History::createPair(ExpressionList object1, RationalExpression object2){

    auto pair1 = make_pair(object1, object2);
    return pair1;

}

void History::printPairs(list<pair<ExpressionList, RationalExpression>> listOfPairs){

    while (!listOfPairs.empty()) {
        listOfPairs.pop_back();
    }


}