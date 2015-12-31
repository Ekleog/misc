#ifndef OPERATIONS_DIVOP_HPP_INCLUDED_
#define OPERATIONS_DIVOP_HPP_INCLUDED_ 1

#include "../Operation.hpp"
#include "../State.hpp"

class DivOp : public Operation {
public:
    virtual std::string name() const {
        return "div";
    }

    virtual void run(State &s) const {
        int rhs = s.pop();
        int lhs = s.pop();
        s.push(lhs / rhs);
    }
};

#endif
