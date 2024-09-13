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
  };

  namespace Types {
    typedef std::map<std::string, std::any> Arguments;
    typedef std::vector<Application::Option*> CommandOptions;
    typedef std::map<std::string, Application::Option*> OptionsLibrary;
  }

  class Command {
    private:
      std::string _key;
      std::string _desc = "";
      Application::Types::CommandOptions* _options = nullptr;

    public:
      Command() = default;
      Command(std::string key, std::string desc): _key(key), _desc(desc) {};

      // Methods
      std::string getKey();
      void setKey(std::string key);
      std::string getDescription();
      void setDescription(std::string desc);
      const Application::Types::CommandOptions* getOptions();
      
      void addOption(Option c);
      void addOption(Option* c);
      void addOption(std::string optionKey, std::string optionDesc);

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
      Application::Types::Arguments* _args = nullptr;
    
    public:
      ArgsParser() = default;
      ArgsParser(std::string prog, std::string desc): _prog(prog), _desc(desc) {};

      // Methods
      Command* addCommand(Command c);
      Command* addCommand(Command* c);
      Command* addCommand(std::string commandKey, std::string commandDesc);
      void addOption(Option c);
      void addOption(Option* c);
      void addOption(std::string optionKey, std::string optionDesc);

      void parse(int argc, char* argv[]);
      void printHelp();
  };
}

#endif // ARGS_H_INCLUDED