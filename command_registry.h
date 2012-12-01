#ifndef SEYCHELLES_COMMAND_REGISTRY_H_
#define SEYCHELLES_COMMAND_REGISTRY_H_

#include "command.h"

#include <map>
#include <set>
#include <string>

class CommandRegistry {
public:
    static void registerCommand(const std::string&, Command* c);
    static void registerHiddenCommand(const std::string&, Command* c);
    static Command* commandForName(const std::string& name);
    static bool isHidden(const std::string&);
    static const std::map<std::string,Command*>& commands() {
        return mCommands;
    }
private:
    static std::map<std::string,Command*> mCommands;
    static std::set<std::string> mHiddenCommands;
};

struct RegisterHelper {
    RegisterHelper(const std::string& name, Command* c, bool hidden = false) {
        if(!hidden) {
            CommandRegistry::registerCommand(name, c);
        } else {
            CommandRegistry::registerHiddenCommand(name, c);
        }
    }

    ~RegisterHelper() {
        // TODO
    }
};

#define REGISTER_COMMAND(Name, Class) \
    static RegisterHelper Class##_RH(Name, new Class())

#define REGISTER_HIDDEN_COMMAND(Name, Class) \
    static RegisterHelper Class##_RH(Name, new Class(), true)

#define REGISTER_ALIAS_COMMAND(Name, Class, Id) \
    static RegisterHelper Class##_RH_##Id(Name, new Class(), true)

#endif /* SEYCHELLES_COMMAND_REGISTRY_H_ */
