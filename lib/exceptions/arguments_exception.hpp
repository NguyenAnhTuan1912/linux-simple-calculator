#ifndef ARGUMENTS_EXCEPTION_H_INCLUDED
#define ARGUMENTS_EXCEPTION_H_INCLUDED

#include <iostream>

namespace Application {
  class ArgumentException : public std::exception {
    private:
    std::string _message = "There is an argument exception";

    public:
    ArgumentException() = default;
    ArgumentException(std::string message) {
      this->_message = message;
    };

    char const* what() const noexcept override {
      return this->_message.c_str();
    }
  };

  class ExceedingArgumentsException : public std::exception {
    private:
    std::string _message = "The number of arguments exceed the limit";

    public:
    ExceedingArgumentsException() = default;
    ExceedingArgumentsException(std::string arg) {
      this->_message = "The number of arguments of " + arg + " exceed the limit";
    };

    char const* what() const noexcept override {
      return this->_message.c_str();
    }
  };

  class InsufficientArgumentsException : public std::exception {
    private:
    std::string _message = "The number of arguments are insufficient";

    public:
    InsufficientArgumentsException() = default;
    InsufficientArgumentsException(std::string arg) {
      this->_message = "The number of arguments of " + arg + " are insufficient";
    };

    char const* what() const noexcept override {
      return this->_message.c_str();
    }
  };

  class InvalidOptionException : public std::exception {
    private:
    std::string _message = "The option is invalid";

    public:
    InvalidOptionException() = default;
    InvalidOptionException(std::string arg) {
      this->_message = "The option " + arg + " is invalid";
    };

    char const* what() const noexcept override {
      return this->_message.c_str();
    }
  };
}

#endif // ARGUMENTS_EXCEPTION_H_INCLUDED