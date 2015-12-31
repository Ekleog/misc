#include "Program.hpp"

#include <iostream>
#include <sstream>

void Program::run(bool debug) const {
    State s;

    while (s.ip() < opcodes_.size()) {
        if (debug) {
            std::cerr << "eip = " << s.ip() << ":\t" << opcodes_[s.ip()]->name() << "\n";
        }
        ++s.ip();
        opcodes_[s.ip() - 1]->run(s);
    }
}

std::string Program::to_string() const {
    std::ostringstream oss;
    for (size_t i = 0; i < opcodes_.size(); ++i) {
        oss << i << ":\t" << opcodes_[i]->name() << "\n";
    }
    return oss.str();
}
