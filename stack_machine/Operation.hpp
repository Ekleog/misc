#ifndef OPERATION_HPP_INCLUDED_
#define OPERATION_HPP_INCLUDED_ 1

class State;

class Operation {
public:
    virtual void run(State &s) const = 0;
};

#endif
