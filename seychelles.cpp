#include <iostream>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <signal.h>
#include <cmath>
#include <ctime>

#include "libedit.h"
#include "safe_exit.h"
#include "command_registry.h"
#include "ssh.h"
#include "log.h"

std::string gUsername;

void repl(const std::string& command) {
    Command* c = CommandRegistry::commandForName(command);
    if(c != 0) {
        Log::log() << "Running: " << command;
        c->run(std::vector<std::string>());
    } else { 
        Log::log() << "Unknown command: " << command;
        std::cout << "Unknown command: " << command << std::endl;
    }
}


void setUsername() {
    gUsername = getenv("USER");
}

std::string prompt(Edit::EditLine& e) {
    return gUsername+"@synthi.net$ ";
}

int main(int argc, char *argv[]) {

    std::ostream& log = Log::log();

    log << "Starting seychelles";

    if(argc > 1) {
        log << " with arguments ";
        for(int i = 0; i < argc; ++i) {
            log << argv[i] << " ";
        }
    }

    log << std::endl;

    setUsername();
    if(Ssh::processArgs(argc, argv, gUsername)) {
        return 0;
    } 

    try {
        std::srand(std::time(0));

        CommandRegistry::commandForName("help")->run(
                std::vector<std::string>());
        setUsername();

        Edit::EditLine el(argv[0]);
        Edit::History hist;

        el.setPrompt(prompt);
        el.setHistory(hist);

        while(true) {
            std::string line = el.gets();
            
            if(line.size() > 0) { 
                hist.add(line);
                repl(line);
            }
        }

    } catch(const ExitException& ex) {
        Log::log() << "Quitting seychelles" << std::endl;
        std::cout << "Thank you for using SynthiNet!" << std::endl;
        return ex.status;
    }
}

