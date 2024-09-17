#include <iostream>
#include <iterator>
#include <vector>

// Include core libs
#include "lib/exceptions/arguments_exception.hpp"
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
  argsParser->addCommand("add", "To get sum of two numbers", "2");
  argsParser->addCommand("sub", "To get difference of two numbers", "2");
  argsParser->addCommand("div", "To get quotient of two numbers", "2");
  argsParser->addCommand("mod", "To get a remain of division between two numbers", "2");
  argsParser->addCommand("mul", "To get quotient of multiplication between two numbers", "2");
  argsParser->addOption("--help", "Get description, full commands and options.");
  argsParser->addOption("--version", "Get the current version of the application.");

  try {
    Application::Types::ParsedArgument* parg = argsParser->parse(argc, argv);
    if (parg == nullptr) {
      argsParser->printHelp();
      return 0;
    }

    std::vector<std::string>::iterator ito = parg->options.begin();
    while(ito != parg->options.end()) {
      if ((*ito) == "--help") {
        argsParser->printHelp();
        return 0;
      }

      if ((*ito) == "--version") {
        std::cout << "Version: " << getVersion() << "\n";
        return 0;
      }
      ito++;
    }

    float result = calculator->exec(
      std::stof(parg->values[0]),
      std::stof(parg->values[1]),
      parg->command
    );

    std::cout << result << "\n";

  } catch (Application::InvalidOperatorException const& ox) {
    std::cerr << "Operator Error: " << ox.what() << "\n";
    return 1;
  } catch (std::exception const& ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return 1;
  }
}
