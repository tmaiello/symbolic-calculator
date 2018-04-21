#ifndef RATIONALEXPRESSION_RATIONALEXPRESSION_H
#define RATIONALEXPRESSION_RATIONALEXPRESSION_H

#include "Expression.h"

class RationalExpression : public Expression {
private:
    long numerator;
    long denominator;
public:
    RationalExpression(long num, long denom);
    explicit RationalExpression(long value);
    explicit RationalExpression(std::string value);
    static RationalExpression makeDecimalFraction(std::pair<std::string, long> &value);
    static RationalExpression add(RationalExpression one, RationalExpression two);
    static RationalExpression subtract(RationalExpression one, RationalExpression two);
    static RationalExpression multiply(RationalExpression one, RationalExpression two);
    static RationalExpression divide(RationalExpression one, RationalExpression two);
    static RationalExpression simplify(RationalExpression input);
    long maxValue();
    std::string print() const override;
	bool isNumber() const override;
	bool isOperator() const override;
};

#endif //RATIONALEXPRESSION_RATIONALEXPRESSION_H
