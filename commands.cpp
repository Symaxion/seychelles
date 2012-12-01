#include "command.h"
#include "command_registry.h"
#include "safe_exit.h"
#include "insults.h"

#include <iostream>
#include <cstdlib>

struct Help : public Command {
    std::string help() const {
        return "Show this message";
    }

    void run(const std::vector<std::string>&) {

        std::cout << 
                "\n"
                "    Seychelles v0.4 - Copyright (c) Frank Erens. "
                "All rights reserved. \n\n"
                "Available commands:\n" << std::endl;

        for(std::map<std::string, Command*>::const_iterator it = 
                CommandRegistry::commands().begin(); 
                it != CommandRegistry::commands().end();
                ++it) {
            if(!CommandRegistry::isHidden(it->first)) {
                std::cout << "    " << it->first;
                for(int i = 0; i < 16 - it->first.size(); ++i) {
                    std::cout << " ";
                }

                std::cout << " - " << it->second->help() << std::endl;
            }
        }

        std::cout << std::endl;
    }
};

REGISTER_COMMAND("help", Help);

struct Exit : public Command {
    std::string help() const {
        return "Quit Seychelles";
    }

    void run(const std::vector<std::string>&) {
        safe_exit(0);
    }
};

REGISTER_COMMAND("exit", Exit);
REGISTER_ALIAS_COMMAND("quit", Exit, 1);
REGISTER_ALIAS_COMMAND("logout", Exit, 2);

struct Passwd : public Command {
    std::string help() const {
        return "Change your password";
    }

    void run(const std::vector<std::string>&) {
        std::system("passwd");
    }
};

REGISTER_COMMAND("passwd", Passwd);

struct ScrewYou : public Command {
    std::string help() const {
        return "";
    }

    void run(const std::vector<std::string>&) {
        std::cout << randomInsult() << std::endl;
    }
};

REGISTER_HIDDEN_COMMAND(":(){ :|:& };:", ScrewYou);
REGISTER_ALIAS_COMMAND("rm -rf /", ScrewYou, 1);
REGISTER_ALIAS_COMMAND("sudo rm -rf /", ScrewYou, 2);
