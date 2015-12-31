#include <iostream>
#include <sstream>

#include "parse.hpp"
#include "Program.hpp"

int main() {
    Program p(parse(std::istringstream(
        "read\n"
        ":loop\n"
        "   dup add\n"
        "   push 1 add\n"
        "   dup print\n"
        "jump :loop\n"
    )));

    std::cout << p.to_string();

    p.run();
}
