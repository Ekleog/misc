#ifndef OPERATIONS_JUMPOP_HPP_INCLUDED_
#define OPERATIONS_JUMPOP_HPP_INCLUDED_ 1

#include <sstream>

#include "../Operation.hpp"
#include "../State.hpp"

class JumpOp : public Operation {
    std::size_t dest_;

public:
    JumpOp(std::size_t dest) : dest_(dest) { }

    virtual std::string name() const {
        std::ostringstream oss;
        oss << "jump " << dest_;
        return oss.str();
    }

    virtual void run(State &s) const {
        s.ip() = dest_;
    }
};

#endif
