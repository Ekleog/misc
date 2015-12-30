#ifndef STATE_HPP_INCLUDED_
#define STATE_HPP_INCLUDED_ 1

#include <vector>

class State {
    std::vector<int> stack_;
    std::size_t ip_;

public:
    void push(int i) {
        stack_.push_back(i);
    }
    int pop() {
        if (stack_.empty())
            return 0;

        int ret = stack_.back();
        stack_.pop_back();
        return ret;
    }

    std::size_t &ip() {
        return ip_;
    }
    std::size_t const &ip() const {
        return ip_;
    }
};

#endif
