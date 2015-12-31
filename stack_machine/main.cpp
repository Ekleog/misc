#include <iostream>
#include <sstream>

#include "parse.hpp"
#include "Program.hpp"

int main() {
    Program p(parse(std::istringstream(
        "read\n"
        ":loop\n"
        "   dup push 2 mod\n"
        "   jnz :not_multiple_2\n"
        "       push 2 div"
        "       jump :end_cond\n"
        "   :not_multiple_2\n"
        "       push 3 mul\n"
        "       push 1 add\n"
        "   :end_cond\n"
        "   dup print\n"
        "   dup push 1 sub\n"
        "jnz :loop\n"
    )));

    std::cout << p.to_string();

    p.run();
}
