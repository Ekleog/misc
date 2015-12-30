#include <iostream>
#include <sstream>

#include "parse.hpp"
#include "Program.hpp"

int main() {
    Program p(parse(std::istringstream(
        ":label\n"
        "jump :label\n"
    )));

    std::cout << p.to_string();

    p.run(true);
}
