#include "../lib/calculator.hpp"
#include "../lib/exceptions/operator_exception.hpp"

float Application::Calculator::exec(float operandA, float operandB, std::string oper) {
  if (oper == "+" || oper == "add")
    return this->add(operandA, operandB);
  if (oper == "-" || oper == "sub")
    return this->sub(operandA, operandB);
  if (oper == "%" || oper == "mod")
    return this->mod(operandA, operandB);
  if (oper == "/" || oper == "div")
    return this->div(operandA, operandB);
  if (oper == "*" || oper == "x" || oper == "mul")
    return this->mul(operandA, operandB);

  throw Application::OperatorException(oper);
}

float Application::Calculator::add(float operandA, float operandB) {
  return operandA + operandB;
}

float Application::Calculator::sub(float operandA, float operandB) {
  return operandA - operandB;
}

float Application::Calculator::mod(float operandA, float operandB) {
  return (int)operandA % (int)operandB;
}

float Application::Calculator::div(float operandA, float operandB) {
  return operandA / operandB;
}

float Application::Calculator::mul(float operandA, float operandB) {
  return operandA * operandB;
}