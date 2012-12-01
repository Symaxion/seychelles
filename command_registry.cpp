#include "command_registry.h"

std::map<std::string,Command*> CommandRegistry::mCommands;
std::set<std::string> CommandRegistry::mHiddenCommands;

void CommandRegistry::registerCommand(const std::string& s, Command* c) {
    mCommands.insert(std::make_pair(s, c));
}

void CommandRegistry::registerHiddenCommand(const std::string& s, Command* c) {
    registerCommand(s, c);
    mHiddenCommands.insert(s);
}

Command* CommandRegistry::commandForName(const std::string& name) {
    return mCommands.find(name) == mCommands.end() ? 0 : 
            mCommands.find(name)->second;
}

bool CommandRegistry::isHidden(const std::string& name) {
    return mHiddenCommands.find(name) != mHiddenCommands.end();
}



