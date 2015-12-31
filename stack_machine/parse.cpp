#include "parse.hpp"

#include <string>
#include <unordered_map>

#include "operations/JumpOp.hpp"
#include "operations/PushOp.hpp"
#include "operations/PopOp.hpp"
#include "operations/PrintOp.hpp"

// This only serves as a hack to postpone label resolution.
//
// No operation of this class shall be left in the returned vector
class DelayedOp : public Operation {
public:
    virtual ~DelayedOp();

    virtual std::string name() const {
        return "DelayedOp -- IF YOU READ THIS THERE IS A BUG IN parse";
    }

    virtual void run(State &s) const { }

    virtual std::unique_ptr<Operation> resolve(std::unordered_map<std::string, std::size_t> const &labels) const = 0;
};
DelayedOp::~DelayedOp() { }

class DelayedJumpOp : public DelayedOp {
    std::string label_;

public:
    DelayedJumpOp(std::string label) : label_(label) { }

    virtual std::unique_ptr<Operation> resolve(std::unordered_map<std::string, std::size_t> const &labels) const {
        return std::make_unique<JumpOp>(labels.at(label_));
    }
};

std::vector<std::unique_ptr<Operation>> parse(std::istream &&is) {
    std::vector<std::unique_ptr<Operation>> opcodes;

    std::unordered_map<std::string, std::size_t> labels;

    while (!is.eof()) {
        std::string s; is >> s;
        if (is.eof())
            break;
        if (s.size() == 0)
            throw "Not going to worry for this toy";

        if (s[0] == ':') {
            labels.emplace(s, opcodes.size());
        } else if (s == "jump") {
            std::string l; is >> l;
            if (l.size() > 0 && l[0] == ':')
                opcodes.emplace_back(new DelayedJumpOp(l));
            else
                throw "Too lazy to put a real exception class for this toy "
                      "sample, but there is an error in the input";
        } else if (s == "push") {
            int i; is >> i;
            opcodes.emplace_back(new PushOp(i));
        } else if (s == "pop") {
            opcodes.emplace_back(new PopOp());
        } else if (s == "print") {
            opcodes.emplace_back(new PrintOp());
        } else {
            throw "Too lazy to but a real exception class for this toy sample, "
                  "but you used an invalid opcode";
        }
    }

    // Resolve delayed operations
    for (std::size_t i = 0; i < opcodes.size(); ++i) {
        DelayedOp *o = dynamic_cast<DelayedOp *>(opcodes[i].get());
        if (o) // If it was actually a DelayedOp
            opcodes[i] = o->resolve(labels);
    }

    return opcodes;
}
