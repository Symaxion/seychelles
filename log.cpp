#include "log.h"

#include <ctime>

namespace Log {

    class nullstream : public std::ostream {};

    static class nullstream nullstream;

    template<class T>
    class nullstream& operator<<(class nullstream& o, const T&) {
        return o;
    }

#ifdef SEYCHELLES_DEBUG
    static std::ostream& mDebug = std::cerr;
#else
    static std::ostream& mDebug = nullstream;
#endif

    static std::ofstream mLog(".seychelles.log", std::ios_base::app);

    std::ostream& debug() {
        return mDebug;
    }

    std::ostream& log() {
        return mLog << timestamp();
    }

    std::string timestamp() {
        char* buffer = new char[23];

        std::time_t now = std::time(0);
        std::strftime(buffer, 23, "[%Y-%m-%d %H:%M:%S] ", std::localtime(&now));

        return buffer;
    }
}
