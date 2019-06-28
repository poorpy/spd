#pragma once

#include <fstream>
#include "data.hpp"
typedef std::pair<int, int> pii;
typedef std::vector<pii> vpii;
vpii read_to_vec(std::string data_name, std::string file_name);
