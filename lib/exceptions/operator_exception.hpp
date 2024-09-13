#ifndef OPERATOR_EXCEPTION_H_INCLUDED
#define OPERATOR_EXCEPTION_H_INCLUDED

#include <iostream>

namespace Application {
  class OperatorException : public std::exception {
    private:
    std::string _message = "The operator is not a valid operator";

    public:
    OperatorException() = default;
    OperatorException(std::string oper) {
      this->_message = "The operator " + oper + " is not a valid operator";
    };

    char const* what() const noexcept override {
      return this->_message.c_str();
    }
  };
}

#endif // OPERATOR_EXCEPTION_H_INCLUDED