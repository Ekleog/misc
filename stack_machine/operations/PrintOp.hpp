#ifndef OPERATIONS_PRINTOP_HPP_INCLUDED_
#define OPERATIONS_PRINTOP_HPP_INCLUDED_ 1

// Yes, this really could be put in a separate .cpp file, but toy project rules
#include <iostream>

#include "../Operation.hpp"
#include "../State.hpp"

class PrintOp : public Operation {
public:
    virtual std::string name() const {
        return "print";
    }

    virtual void run(State &s) const {
        std::cout << s.pop() << "\n";
    }
};

#endif
