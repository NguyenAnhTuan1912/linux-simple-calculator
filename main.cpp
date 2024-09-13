#include <iostream>

// Include core libs
#include "lib/exceptions/operator_exception.hpp"
#include "lib/exceptions/operator_exception.hpp"
#include "lib/__VERSION__.hpp"

// Include objects
#include "lib/calculator.hpp"
#include "lib/args.hpp"

std::string getVersion() {
  return APP_VERSION;
}

int main(int argc, char* argv[]) {
  Application::Calculator* calculator = new Application::Calculator();
  Application::ArgsParser* argsParser = new Application::ArgsParser(
    "tunacalc",
    "A simple bin calculator which was wrote by Nguyen Anh Tuan. Enjoy it!!"
  );

  // Add commands and options
  argsParser->addCommand("add", "To get sum of two numbers");
  argsParser->addCommand("sub", "To get difference of two numbers");
  argsParser->addCommand("div", "To get quotient of two numbers");
  argsParser->addCommand("mod", "To get a remain of division between two numbers");
  argsParser->addCommand("mul", "To get quotient of multiplication between two numbers");
  argsParser->addOption("--help", "Get description, full commands and options.");

  try {
    argsParser->parse(argc, argv);

  } catch (Application::OperatorException const& ox) {
    std::cerr << "Operator Error: " << ox.what() << "\n";
  } catch (std::exception const& ex) {
    std::cerr << "Error: " << ex.what() << "\n";
  }
}
