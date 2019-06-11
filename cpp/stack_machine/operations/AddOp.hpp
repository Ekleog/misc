#ifndef OPERATIONS_ADDOP_HPP_INCLUDED_
#define OPERATIONS_ADDOP_HPP_INCLUDED_ 1

#include "../Operation.hpp"
#include "../State.hpp"

class AddOp : public Operation {
public:
    virtual std::string name() const {
        return "add";
    }

    virtual void run(State &s) const {
        s.push(s.pop() + s.pop());
    }
};

#endif
