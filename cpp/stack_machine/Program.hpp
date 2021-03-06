#ifndef PROGRAM_HPP_INCLUDED_
#define PROGRAM_HPP_INCLUDED_ 1

#include <memory>
#include <vector>

#include "Operation.hpp"
#include "State.hpp"

class Program {
    std::vector<std::unique_ptr<Operation>> opcodes_;

public:
    Program(std::vector<std::unique_ptr<Operation>> &&opcodes)
        : opcodes_(std::move(opcodes))
    { }

    void run(bool debug = false) const;

    std::string to_string() const;
};

#endif
