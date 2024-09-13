#include <iomanip>
#include <iterator>
#include <cstring>

#include "../lib/args.hpp"
#include "../lib/exceptions/operator_exception.hpp"

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

void Application::ArgsParser::parse(int argc, char* argv[]) {
  try {
    // If there isn't arguments, show help
    if (argc == 1) {
      this->printHelp();
      return;
    }

    // If argv[1] is a command

    // If argv[1] is an option
    if (this->_olib->find(argv[1]) != this->_olib->end()) {
      if (std::strcmp(argv[1], "--help") == 0) {
        this->printHelp();
        return;
      }
    }
  } catch(std::invalid_argument const& ex) {

  }
}