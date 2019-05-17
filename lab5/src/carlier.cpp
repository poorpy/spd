#include "../inc/carlier.hpp"
#include <limits>
#include <algorithm>

ivec carlier(const rpq_vec &data) {
    int UB = std::numeric_limits<int>::max();
    ivec pi_opt = {};
    auto pi = schrage(data);
    auto U = calc_cmax(pi, data);

    if (U < UB) {
        UB = U;
        pi_opt = pi;
    }

    auto c = -1;
    if (c < 0) {
        return pi_opt;
    } 




}


