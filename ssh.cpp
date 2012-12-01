#include "ssh.h"

#include "log.h"

#include <string>
#include <vector>

#include <unistd.h>

namespace Ssh {


    static const std::string kScpCommand = "scp";
    static const std::string kSftpCommand = "/usr/lib/openssh/sftp-server";

    std::ostream& operator<<(std::ostream& o, 
            const std::vector<std::string>& v) {
        o << "{ ";
        for(int i = 0; i < v.size() - 1; ++i) {
            o << v[i] << ", ";
        }

        return o << v[v.size() - 1] << " }";
    }

    std::vector<std::string> mapto(int argc, char** argv) {
        std::vector<std::string> toReturn;
        toReturn.reserve(argc);
        for(int i = 0; i < argc; ++i) {
            toReturn.push_back(argv[i]);
        }

        return toReturn;
    }

    const char** tocarray(const std::vector<std::string>& v) {
        const char** toReturn = new const char*[v.size()];

        for(int i = 0; i < v.size(); ++i) {
            toReturn[i] = v[i].c_str();
        }

        return toReturn;
    }

    std::vector<std::string> unescapeCmd(const std::string& c) {
        std::vector<std::string> toReturn;
        bool quote = false;
        std::string current = "";

        for(int i = 0; i < c.size(); ++i) {
            if(c[i] == '\'') {
                quote ^= 1;
            } else if(c[i] == ' ' && !quote){
                toReturn.push_back(current);
                current = "";
            } else {
                current += c[i];
            }
        }

        toReturn.push_back(current); // last option

        return toReturn;
    }

    bool processArgs(int argc, char** argv, const std::string&) {
        std::vector<std::string> args = mapto(argc, argv);
        if(argc < 3 || args[1] != "-c") {
            Log::log() << "Not a command: " << argc << args[1] 
                << std::endl;
            return false;
        }

        std::vector<std::string> cmd = unescapeCmd(args[2]);        

        if(cmd[0] != kScpCommand && cmd[2] != kSftpCommand) {
            Log::log() << "Not an ssh command: " << args[2] << std::endl;
            return false;
        }

        const char** newargv = tocarray(cmd);

        Log::log() << "Switching to " << cmd[0] << " with arguments " <<
            cmd << std::endl;

        execvp(cmd[0].c_str(), const_cast<char**>(newargv));

        // Should not be reached.
        return true;
    }
}
