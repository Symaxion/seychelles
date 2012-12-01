#ifndef SEYCHELLES_COMMAND_H_
#define SEYCHELLES_COMMAND_H_

#include <vector>
#include <string>

class Command {
public:
    virtual std::string help() const = 0;
    virtual void run(const std::vector<std::string>& v) = 0;
};

#endif /* SEYCHELLES_COMMAND_H_ */
