#pragma once

#include <iomanip>
#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

#include <unordered_map>
#include <variant>
#include <vector>

#include <algorithm>
#include <stdexcept>

namespace funk
{

using String = std::string;

template <typename T> using Vector = std::vector<T>;
template <typename K, typename V> using HashMap = std::unordered_map<K, V>;

} // namespace funk
