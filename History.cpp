#include "RationalExpression.h"
#include "ExpressionList.h"
#include "History.h"


//History class constructor that declares the list of pairs.
// The pairs will consist of an object from the ExpressionList class
//and an object from the RationalExpression class.
History::History()
{
    list<pair<ExpressionList, RationalExpression>> listOfPairs;
}

//The createPair method provides a function that takes in an object
//from each class (ExpressionList and RationalExpression) and
//pairs them together using the 'pair' c++ implemented library.
pair<ExpressionList, RationalExpression> History::createPair(ExpressionList *object1, RationalExpression *object2)
{
    pair<ExpressionList, RationalExpression> pair1 = make_pair(*object1, *object2);
    return pair1;
}

//When the storePair function is called, it will take in the created Pair
//and store it in the previsouly declared list of pairs.
void History::storePair(pair<ExpressionList, RationalExpression> pair1)
{
    listOfPairs.push_back(pair1);
}


//If the user wishes to see the entire list of pairs
//this method is called, and will return the list.
list<pair<ExpressionList, RationalExpression>> History::returnList()
{
    return listOfPairs;
}