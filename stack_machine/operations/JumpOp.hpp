#ifndef OPERATIONS_JUMPOP_HPP_INCLUDED_
#define OPERATIONS_JUMPOP_HPP_INCLUDED_ 1

#include "../Operation.hpp"
#include "../State.hpp"

class JumpOp : public Operation {
    std::size_t dest_;

public:
    JumpOp(std::size_t dest) : dest_(dest) { }

    virtual void run(State &s) const {
        s.ip() = dest_;
    }
};

#endif
