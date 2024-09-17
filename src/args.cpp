#include <iomanip>
#include <vector>
#include <iterator>
#include <cstring>
#include <typeinfo>

#include "../lib/args.hpp"
#include "../lib/exceptions/operator_exception.hpp"
#include "../lib/exceptions/arguments_exception.hpp"

// Definition of Application::Option
void Application::Option::setKey(std::string key) {
  this->_key = key;
}

std::string Application::Option::getKey() {
  return this->_key;
}

void Application::Option::setDescription(std::string desc) {
  this->_desc = desc;
}

std::string Application::Option::getDescription() {
  return this->_desc;
}

void Application::Option::printHelp(int tabIndent) {
  std::string tab = "";
  int i = 0;
  while(i < tabIndent) {
    tab += "\t";
    i++;
  }
  std::cout << tab << this->_key << "\t\t" << this->_desc << "\n";
}

bool Application::Option::isOption(std::string optionKey) {
  int i = 0;
  bool check = false;
  while(i < 2) {
    if (optionKey.at(i) == '-') check = true;
    i++;
  }

  return check;
}

// Definition of Application::Command
std::string Application::Command::getKey() {
  return this->_key;
}

void Application::Command::setKey(std::string key) {
  this->_key = key;
}

std::string Application::Command::getDescription() {
  return this->_desc;
}

void Application::Command::setDescription(std::string desc) {
  this->_desc = desc;
}

const Application::Types::CommandOptions* Application::Command::getOptions() {
  return this->_options;
}

void Application::Command::addOption(Option c) {
  if (this->_options == nullptr)
    this->_options = new Application::Types::CommandOptions();

  this->_options->push_back(new Option(c));
}

void Application::Command::addOption(Option* c) {
  if (this->_options == nullptr)
    this->_options = new Application::Types::CommandOptions();
  
  this->_options->push_back(c);
}

void Application::Command::addOption(std::string optionKey, std::string optionDesc) {
  if (this->_options == nullptr)
    this->_options = new Application::Types::CommandOptions();

  this->_options->push_back(new Option(optionKey, optionDesc));
}

std::string Application::Command::getNArg() {
  return this->_nargn;
}

void Application::Command::setNArg(std::string narg) {
  this->_nargn = narg;
}

bool Application::Command::checkOption(std::string optionKey) {
  if (this->_options == nullptr) return false;

  Application::Types::CommandOptions::iterator ito = this->_options->begin();
  for (; ito != this->_options->end(); ito++) {
    if ((*ito)->getKey() == optionKey) return true;
  }
  return false;
}

void Application::Command::printHelp(int tabIndent) {
  std::string tab = "";
  int i = 0;
  while(i < tabIndent) {
    tab += "\t";
    i++;
  }

  // Print description
  std::cout << tab << this->_key << "\t\t" << this->_desc << "\n";

  if (this->_options == nullptr) return;

  // Print options
  std::cout << tab << "Options:\n";
  for (Option* o : *(this->_options)) {
    (*o).printHelp(tabIndent + 1);
  }
}

// Definition of Application::ArgsGroup
std::string Application::ArgsGroup::getDescription() {
  return this->_desc;
}

void Application::ArgsGroup::setDescription(std::string desc) {
  this->_desc = desc;
}

Application::Command* Application::ArgsGroup::addCommand(Command c) {
  if (this->_cgroup == nullptr)
    this->_cgroup = new Application::Types::CommandGroup();

  Command* ptrC = new Command(c);
  this->_cgroup->push_back(ptrC);
  return ptrC;
}

Application::Command* Application::ArgsGroup::addCommand(Command* c) {
  if (this->_cgroup == nullptr)
    this->_cgroup = new Application::Types::CommandGroup();

  this->_cgroup->push_back(c);
  return c;
}

Application::Command* Application::ArgsGroup::addCommand(std::string commandKey, std::string commandDesc) {
  if (this->_cgroup == nullptr)
    this->_cgroup = new Application::Types::CommandGroup();

  Command* ptrC = new Command(commandKey, commandDesc);
  this->_cgroup->push_back(ptrC);
  return ptrC;
}

void Application::ArgsGroup::printHelp(int tabIndent) {
  std::string tab = "";
  int i = 0;
  while(i < tabIndent) {
    tab += "\t";
    i++;
  }

  // Print description
  std::cout << tab << this->_desc << "\n";

  if (this->_cgroup == nullptr) return;

  // Print options
  std::cout << tab << "Command:\n";
  for (Command* o : *(this->_cgroup)) {
    (*o).printHelp(tabIndent + 1);
  }
}

// Definition of Application::ArgsParser
Application::Command* Application::ArgsParser::addCommand(Application::Command c) {
  Application::Command* ptrC = new Application::Command(c);
  this->_clib->insert({ ptrC->getKey(), ptrC });
  return ptrC;
}

Application::Command* Application::ArgsParser::addCommand(Application::Command* c) {
  this->_clib->insert({ c->getKey(), c });
  return c;
}

Application::Command* Application::ArgsParser::addCommand(std::string commandKey, std::string commandDesc) {
  Application::Command* ptrC = new Application::Command(commandKey, commandDesc);
  this->_clib->insert({ ptrC->getKey(), ptrC });
  return ptrC;
}

Application::Command* Application::ArgsParser::addCommand(
  std::string commandKey,
  std::string commandDesc,
  std::string nargs
) {
  Application::Command* ptrC = new Application::Command(commandKey, commandDesc, nargs);
  this->_clib->insert({ ptrC->getKey(), ptrC });
  return ptrC;
}

void Application::ArgsParser::addOption(Application::Option o) {
  Application::Option* ptrO = new Application::Option(o);
  this->_olib->insert({ ptrO->getKey(), ptrO });
}

void Application::ArgsParser::addOption(Application::Option* o) {
  this->_olib->insert({ o->getKey(), o });
}

void Application::ArgsParser::addOption(std::string optionKey, std::string optionDesc) {
  Application::Option* ptrO = new Application::Option(optionKey, optionDesc);
  this->_olib->insert({ optionKey, ptrO });
}

void Application::ArgsParser::printHelp() {
  std::string tab = "";
  int i = 0;
  while(i < 0) {
    tab += "\t";
    i++;
  }

  bool hasOption = !this->_olib->empty(),
    hasCommands = !this->_clib->empty();

  // Print main
  std::cout << "Usage: " << this->_prog;

  if (hasOption && !hasCommands) {
    std::cout << " [OPTIONS]\n\n";
  } else if (!hasOption && hasCommands) {
    std::cout << " [COMMANDS]\n\n";
  } else if (hasOption && hasCommands) {
    std::cout << " [COMMAND] [OPTIONS] | [OPTIONS]\n\n";
  }

  // Print description
  std::cout << this->_desc << "\n\n";

  if (hasOption) {
    // Print options
    std::cout << "Options:\n";
    Application::Types::OptionsLibrary::iterator oit = this->_olib->begin();
    while(oit != this->_olib->end()) {
      oit->second->printHelp(1);
      oit++;
    }
  }

  if (hasCommands) {
    // Print commands
    std::cout << "Commands:\n";
    Application::Types::CommandsLibrary::iterator cit = this->_clib->begin();
    while(cit != this->_clib->end()) {
      cit->second->printHelp(1);
      cit++;
    }
  }
}

Application::Types::ParsedArgument* Application::ArgsParser::parse(int argc, char* argv[]) {
  // If there aren't arguments, show help
  if (argc == 1) {
    this->printHelp();
    return nullptr;
  }

  // If there are arguments, process them
  Application::Types::CommandsLibrary::iterator itc;
  Application::Command* c = nullptr;
  Application::Types::ParsedArgument* parg = new Application::Types::ParsedArgument();
  
  // The command is root by default
  parg->command = "ROOT";
  for (int i = 1; i < argc; i++) {
    // c is a nullptr
    if (c == nullptr)
      itc = this->_clib->find(argv[i]);
    
    // c is a nullptr and itc isn't a null iterator
    if (c == nullptr && itc != this->_clib->end()) {
      if (c != nullptr)
        throw Application::ExceedingArgumentsException("tunacalc");

      c = itc->second;
      // Insert command information to parg
      parg->command = argv[i];
      continue;
    }
    // If argv[i] is an option and c is nullptr
    // that mean the option belong to root command
    Application::Types::OptionsLibrary::iterator ito = this->_olib->find(argv[i]);
    bool hasOption = ito != this->_olib->end();
    if (hasOption && !Application::Option::isOption(argv[i]))
      throw Application::InvalidOptionException(argv[i]);
    if (hasOption) {
      // Print help
      // if (std::strcmp(argv[i], "--help") == 0 && parg->command == "ROOT") {
      //   this->printHelp();
      //   return nullptr;
      // }

      parg->options.push_back(argv[i]);
      continue;
    }

    parg->values.push_back(argv[i]);
  }

  // Free memories
  // delete currentCommandOptions;
  // delete currentCommandValues;

  if (parg->command == "ROOT")
    return parg;

  // Check options
  std::vector<std::string>::iterator itstr = parg->options.begin();
  while(itstr != parg->options.end()) {
    // Erase options
    // if (parg->command != "ROOT" && !c->checkOption((*itstr)))
    //   parg->options.erase(itstr);
    // else itstr++;

    // Throw error when option don't exist in command (except ROOT)
    if (parg->command != "ROOT" && !c->checkOption((*itstr)))
      throw Application::InvalidOptionException((*itstr));
    itstr++;
  }

  // Check value (number of vaules)
  std::vector<std::string>::iterator itv = parg->values.begin();
  std::string commandNArg = c->getNArg();
  if (commandNArg != "*" && commandNArg != "+") {
    if (parg->values.size() != std::stoi(commandNArg))
      throw Application::ArgumentException(
        "The command " +
        parg->command +
        " requires " +
        commandNArg +
        " arguments."
      );
  } else if (commandNArg == "+" && parg->values.size() == 0)
    throw Application::InsufficientArgumentsException(parg->command);

  return parg;
}