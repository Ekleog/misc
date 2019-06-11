#ifndef OPERATIONS_POPOP_HPP_INCLUDED_
#define OPERATIONS_POPOP_HPP_INCLUDED_ 1

#include "../Operation.hpp"
#include "../State.hpp"

class PopOp : public Operation {
public:
    virtual std::string name() const {
        return "pop";
    }

    virtual void run(State &s) const {
        s.pop();
    }
};

#endif
