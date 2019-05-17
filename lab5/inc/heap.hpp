#pragma once

#include "data.hpp"

struct RpqHeap {
    rpq_vec vec;
    std::pair<rpq&, size_t> r_child(size_t index);
    std::pair<rpq&, size_t> l_child(size_t index);
    void push(rpq);
};
