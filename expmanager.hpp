#pragma once

#include <string>
#include <optional>

bool balanced_parens (std::string s);

std::optional<std::string> infix_to_postfix(std::string str);
