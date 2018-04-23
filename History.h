/*Defines the History class which stores expression history. */

#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
using namespace std;
#include <list>
#include "RationalExpression.h"
#include "ExpressionList.h"
#include "Interpreter.h"


/*
 * [History]
 * -Creates a pair of objects from the two classes,
 *  ExpressionList and Interpreter.
 * -Stores that pair in a list.
 * -Returns the entire list to the Qt class.
*/

class History
{
	private:

	/* fields */
    list<pair<ExpressionList*, Interpreter*>> listOfPairs;


	public:

    pair<ExpressionList*, Interpreter*> createPair(ExpressionList *object1, Interpreter *object2);

    void storePair(pair<ExpressionList*, Interpreter*> pair1);

    list<pair<ExpressionList*, Interpreter*>> returnList();

    bool checkList();
};


#endif //SYMBOLIC_CALCULATOR_HISTORY_H