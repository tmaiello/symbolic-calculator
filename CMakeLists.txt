cmake_minimum_required(VERSION 3.9)
project(symbolic-calculator)

set(CMAKE_CXX_STANDARD 11)

add_executable(symbolic-calculator RationalExpression.cpp RationalExpression.h Expression.h ExpressionList.cpp ExpressionList.h Operator.cpp Operator.h History.cpp History.h Interpreter.cpp Interpreter.h)