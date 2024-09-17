#ifndef ARGS_H_INCLUDED
#define ARGS_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>
#include <any>
#include <cstdlib>

namespace Application {
  class Option {
    private:
      std::string _key = "";
      std::string _desc = "";
      int _optionLength = 0;

    public:
      Option() = default;
      Option(std::string key, std::string desc): _key(key), _desc(desc) {};

      // Methods
      std::string getKey();
      void setKey(std::string key);
      std::string getDescription();
      void setDescription(std::string desc);

      void printHelp(int tabIndent = 0);

      // Static methods
      static bool isOption(std::string optionKey);
  };

  namespace Types {
    struct ParsedArgument {
      std::string command;
      std::vector<std::string> options;
      std::vector<std::string> values;
      ~ParsedArgument() {
        this->command = "";
        this->options.clear();
        this->values.clear();
      }
    };
    typedef std::vector<ParsedArgument> ParsedArguments;
    typedef std::vector<Application::Option*> CommandOptions;
    typedef std::map<std::string, Application::Option*> OptionsLibrary;
  }

  class Command {
    private:
      std::string _key;
      std::string _desc = "";
      std::string _nargn = "+";
      Application::Types::CommandOptions* _options = nullptr;

    public:
      Command() = default;
      Command(std::string key, std::string desc): _key(key), _desc(desc) {};
      Command(
        std::string key,
        std::string desc,
        std::string nargn
      ): _key(key), _desc(desc), _nargn(nargn) {};

      // Methods
      std::string getKey();
      void setKey(std::string key);
      std::string getDescription();
      void setDescription(std::string desc);
      const Application::Types::CommandOptions* getOptions();
      std::string getNArg();
      void setNArg(std::string narg);
      
      void addOption(Option c);
      void addOption(Option* c);
      void addOption(std::string optionKey, std::string optionDesc);
      bool checkOption(std::string optionKey);

      void printHelp(int tabIndent = 0);
  };

  namespace Types {
    typedef std::vector<Application::Command*> CommandGroup;
    typedef std::map<std::string, Application::Command*> CommandsLibrary;
  }
}

namespace Application {
  class ArgsGroup {
    private:
      std::string _desc = "";
      Application::Types::CommandGroup* _cgroup = nullptr;

    public:
      ArgsGroup() = default;
      ArgsGroup(std::string desc): _desc(desc) {};

      // Methods
      std::string getDescription();
      void setDescription(std::string desc);

      Command* addCommand(Command c);
      Command* addCommand(Command* c);
      Command* addCommand(std::string commandKey, std::string commandDesc);

      void printHelp(int tabIndent = 0);
  };

  namespace Types {
    typedef std::vector<ArgsGroup*> ArgsGroups;
  }

  class ArgsParser {
    private:
      std::string _prog = getenv("PWD");
      std::string _desc = "";
      Application::Types::CommandsLibrary* _clib = new Application::Types::CommandsLibrary();
      Application::Types::OptionsLibrary* _olib = new Application::Types::OptionsLibrary();
      // Application::Types::ArgsGroups* _group = nullptr;
      Application::Types::ParsedArguments* _pargs = nullptr;
    
    public:
      ArgsParser() = default;
      ArgsParser(std::string prog, std::string desc): _prog(prog), _desc(desc) {};

      // Methods
      Command* addCommand(Command c);
      Command* addCommand(Command* c);
      Command* addCommand(std::string commandKey, std::string commandDesc);
      Command* addCommand(std::string commandKey, std::string commandDesc, std::string nargs);
      void addOption(Option c);
      void addOption(Option* c);
      void addOption(std::string optionKey, std::string optionDesc);

      Application::Types::ParsedArgument* parse(int argc, char* argv[]);
      void printHelp();
  };
}

#endif // ARGS_H_INCLUDED