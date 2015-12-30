#include "Program.hpp"

#include "operations/JumpOp.hpp"

int main() {
    std::vector<std::unique_ptr<Operation>> opcodes;

    opcodes.emplace_back(new JumpOp(0));

    Program p(std::move(opcodes));

    p.run();
}
