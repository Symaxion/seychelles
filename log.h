#ifndef SEYCHELLES_LOG_H_
#define SEYCHELLES_LOG_H_

#include <fstream>
#include <iostream>
#include <string>

namespace Log {

    std::ostream& debug();
    std::ostream& log();
    std::string timestamp();
}

#endif /* SEYCHELLES_LOG_H_ */
