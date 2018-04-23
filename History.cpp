#include "RationalExpression.h"
#include "ExpressionList.h"
#include "History.h"


/*The createPair method provides a function that takes in an object
 * from each class (ExpressionList and Interpreter) and pairs them together
 * using the 'pair' c++ implemented library. */

pair<ExpressionList*, Interpreter*> History::createPair(ExpressionList *object1, Interpreter *object2)
{
    return make_pair(object1, object2);
}

/*When the storePair function is called, it will take in the created Pair
 * and store it in the previously declared list of pairs. */

void History::storePair(pair<ExpressionList*, Interpreter*> pair1)
{
    listOfPairs.push_back(pair1);
}


/*If the user wishes to see the entire list of pairs
 *this method is called, and will return the list. */

list<pair<ExpressionList*, Interpreter*>> History::returnList()
{
    return listOfPairs;
}

/*checks if the list is empty and returns
 * corresponding boolean value. */

bool History::checkList()
{
	bool isEmpty = true;

    if (listOfPairs.empty())
	{
        isEmpty = true;
    }
    else if (!listOfPairs.empty())
	{
        isEmpty = false;
    }

	return isEmpty;
}