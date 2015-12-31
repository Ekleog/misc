#ifndef OPERATIONS_READOP_HPP_INCLUDED_
#define OPERATIONS_READOP_HPP_INCLUDED_ 1

// Yes, this really could be put in a separate .cpp file, but toy project rules
#include <iostream>

#include "../Operation.hpp"
#include "../State.hpp"

class ReadOp : public Operation {
public:
    virtual std::string name() const {
        return "read";
    }

    virtual void run(State &s) const {
        int i;
        std::cin >> i;
        s.push(i);
    }
};

#endif
