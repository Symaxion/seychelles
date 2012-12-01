#ifndef SEYCHELLES_SAFE_EXIT_H_
#define SEYCHELLES_SAFE_EXIT_H_

struct ExitException {
    ExitException(int i) : status(i) {}
    int status;
};

inline void safe_exit(int i) {
    throw ExitException(i);
}

#endif /* SEYCHELLES_SAFE_EXIT_H_ */
