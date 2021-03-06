#ifndef OPERATIONS_SUBOP_HPP_INCLUDED_
#define OPERATIONS_SUBOP_HPP_INCLUDED_ 1

#include "../Operation.hpp"
#include "../State.hpp"

class SubOp : public Operation {
public:
    virtual std::string name() const {
        return "sub";
    }

    virtual void run(State &s) const {
        int rhs = s.pop();
        int lhs = s.pop();
        s.push(lhs - rhs);
    }
};

#endif
