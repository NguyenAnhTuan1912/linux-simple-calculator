#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include <iostream>

namespace Application {
  class Calculator {
    public:
    Calculator() = default;

    float exec(float operandA, float operandB, std::string oper);
    float add(float operandA, float operandB);
    float sub(float operandA, float operandB);
    float mod(float operandA, float operandB);
    float div(float operandA, float operandB);
    float mul(float operandA, float operandB);
  };
}

#endif // CALCULATOR_H_INCLUDED