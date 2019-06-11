#ifndef OPERATIONS_JNZOP_HPP_INCLUDED_
#define OPERATIONS_JNZOP_HPP_INCLUDED_ 1

#include <sstream>

#include "../Operation.hpp"
#include "../State.hpp"

class JnzOp : public Operation {
    std::size_t dest_;

public:
    JnzOp(std::size_t dest) : dest_(dest) { }

    virtual std::string name() const {
        std::ostringstream oss;
        oss << "jnz " << dest_;
        return oss.str();
    }

    virtual void run(State &s) const {
        if (s.pop() != 0)
            s.ip() = dest_;
    }
};

#endif
