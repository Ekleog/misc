#ifndef OPERATIONS_DUPOP_HPP_INCLUDED_
#define OPERATIONS_DUPOP_HPP_INCLUDED_ 1

#include "../Operation.hpp"
#include "../State.hpp"

class DupOp : public Operation {
public:
    virtual std::string name() const {
        return "dup";
    }

    virtual void run(State &s) const {
        int i = s.pop();
        s.push(i);
        s.push(i);
    }
};

#endif
