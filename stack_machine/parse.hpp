#ifndef PARSE_HPP_INCLUDED_
#define PARSE_HPP_INCLUDED_ 1

#include <istream>
#include <memory>
#include <vector>

#include "Operation.hpp"

std::vector<std::unique_ptr<Operation>> parse(std::istream &&stream);

#endif
