#pragma once

#include "base/action.h"
#include <ostream>
#include <string>

namespace base {
class Solution;

std::ostream& operator<<(std::ostream& os, const Action& a);
std::ostream& operator<<(std::ostream& os, const ActionsList& al);
std::ostream& operator<<(std::ostream& os, const Solution& s);

std::string Encode(const Action& a);
std::string Encode(const ActionsList& a);
std::string Encode(const Solution& a);
}  // namespace base
