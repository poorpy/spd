#include "../inc/heap.hpp"

std::pair<rpq&, size_t> RpqHeap::r_child(size_t index) {
    return {vec.at((index + 1)*2), (index + 1)*2};
}

std::pair<rpq&, size_t> RpqHeap::l_child(size_t index) {
    return {vec.at((index + 1)*2 - 1), ((index + 1)*2 - 1)};
}
