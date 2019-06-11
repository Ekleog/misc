#ifndef OPERATIONS_MULOP_HPP_INCLUDED_
#define OPERATIONS_MULOP_HPP_INCLUDED_ 1

#include "../Operation.hpp"
#include "../State.hpp"

class MulOp : public Operation {
public:
    virtual std::string name() const {
        return "mul";
    }

    virtual void run(State &s) const {
        s.push(s.pop() * s.pop());
    }
};

#endif
