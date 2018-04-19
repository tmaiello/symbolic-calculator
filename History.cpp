using namespace std;
#include "RationalExpression.h"
#include "ExpressionList.h"
#include <list>
#include <iostream>



class History{

public:
    ExpressionList object1;
    RationalExpression object2;

private:
    list<pair<ExpressionList, RationalExpression>> listOfPairs;



    void createPair(ExpressionList object1, RationalExpression object2){

        pair<ExpressionList, RationalExpression> pair1;
        pair1 = make_pair(object1, object2);
        History a;
        a.storePair(pair1);

    }

    void storePair(pair<ExpressionList, RationalExpression> pair1){

        listOfPairs.push_back(pair1);

    }

    void printPairs(list<pair<ExpressionList, RationalExpression>> listOfPairs){

        while (!listOfPairs.empty()) {
           listOfPairs.pop_back();
        }


    }


};
