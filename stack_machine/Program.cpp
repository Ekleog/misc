#include "Program.hpp"

#include <iostream>
#include <sstream>

void Program::run(bool debug) const {
    State s;

    while (s.ip() >= 0 && s.ip() < opcodes_.size()) {
        if (debug) {
            std::cerr << "eip = " << s.ip() << ":\t" << opcodes_[s.ip()]->name() << "\n";
        }
        opcodes_[s.ip()]->run(s);
    }
}

std::string Program::to_string() const {
    std::ostringstream oss;
    for (size_t i = 0; i < opcodes_.size(); ++i) {
        oss << i << ":\t" << opcodes_[i]->name() << "\n";
    }
    return oss.str();
}
