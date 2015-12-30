#ifndef OPERATION_HPP_INCLUDED_
#define OPERATION_HPP_INCLUDED_ 1

#include <string>

class State;

class Operation {
public:
    virtual std::string name() const = 0;

    virtual void run(State &s) const = 0;
};

#endif
