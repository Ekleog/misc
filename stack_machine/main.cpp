#include <iostream>
#include <sstream>

#include "parse.hpp"
#include "Program.hpp"

int main() {
    Program p(parse(std::istringstream(
        "push 3\n"
        "push 42\n"
        "read\n"
        "jump :label\n"
        "  pop\n"
        ":label\n"
        "print\n"
        "print\n"
    )));

    std::cout << p.to_string();

    p.run();
}
