#include "../inc/data.hpp"

int calc_cmax(const rpq_vec& data) {
    int m = data[0].r + data[0].p, c = m + data[0].q;

    for (unsigned long i = 1; i < data.size(); ++i) {
        m = data[i].p + std::max(m, data[i].r);
        c = std::max(c, m + data[i].q);
    }

    return c;
}

int calc_cmax(const ivec& perm, const rpq_vec& data) {
    int m = 0, c = 0;
    for (const auto& item : perm) {
        m = data[item-1].p + std::max(m, data[item-1].r);
        c = std::max(c, m + data[item-1].q);
    }

    return c;
}
