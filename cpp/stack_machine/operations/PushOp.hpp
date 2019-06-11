#ifndef OPERATIONS_PUSHOP_HPP_INCLUDED_
#define OPERATIONS_PUSHOP_HPP_INCLUDED_ 1

#include <sstream>

#include "../Operation.hpp"
#include "../State.hpp"

class PushOp : public Operation {
    std::size_t value_;

public:
    PushOp(std::size_t value) : value_(value) { }

    virtual std::string name() const {
        std::ostringstream oss;
        oss << "push " << value_;
        return oss.str();
    }

    virtual void run(State &s) const {
        s.push(value_);
    }
};

#endif
