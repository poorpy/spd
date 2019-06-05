#include "../inc/carlier.hpp"
#include <limits>
#include <algorithm>
#include <numeric>
#include <optional>

typedef std::pair<rpq&, int> pri;

/* int find_b(const ivec& perm, const rpq_vec& data) { */
/*     ivec addr(data.size()+1); */
/*     int ind = 0; */
/*     for (const auto& item: data) { */
/*         addr[item.id] = ind; */
/*         ++ind; */
/*     } */

/*     auto cmax = calc_cmax(perm, data); */

/*     for (auto ind = perm.size()-1; ind >= 0; --ind) { */
/*         auto len = ind-1; */
/*         ivec p_perm = ivec(perm.begin(), perm.begin()+len); */
/*         if (calc_cmax(p_perm, data)+data[addr[perm[ind]]].q == cmax) { */
/*             return ind; */
/*         } */
/*     } */

/*     return -1; */
/* } */

/* int find_a(const ivec& perm, const rpq_vec& data, int b) { */
/*     ivec addr(data.size()+1); */
/*     int ind = 0; */
/*     for (const auto& item: data) { */
/*         addr[item.id] = ind; */
/*         ++ind; */
/*     } */

/*     auto cmax = calc_cmax(perm, data); */

/*     for (auto i = 0; i < b; ++i) { */
/*         auto vec = ivec(perm.begin()+i+1, perm.begin()+b); */
/*         if (data[addr[perm[i]]].r + calc_cmax(vec, data) + data[addr[perm[i]]].q == cmax) { */
/*             return i; */
/*         } */
/*     } */

/*     return -1; */
/* } */

/* int find_c(const ivec& perm, const rpq_vec& data, int a, int b) { */
/*     ivec addr(data.size()+1); */
/*     int ind = 0; */
/*     for (const auto& item: data) { */
/*         addr[item.id] = ind; */
/*         ++ind; */
/*     } */


/*     for (auto ind = b; ind >= a; --ind) { */
/*         auto len = ind-1; */
/*         if (data[addr[perm[ind]]].q < data[addr[perm[b]]].q) { */
/*             return ind; */
/*         } */
/*     } */
/*     return -1; */
/* } */

/* int min_r_k(const ivec& perm, const rpq_vec& data) { */
/* } */

/* ivec carlier(const rpq_vec &data) { */
/*     /1* ivec addr(data.size()+1); *1/ */
/*     /1* int ind = 0; *1/ */
/*     /1* for (const auto& item: data) { *1/ */
/*     /1*     addr[item.id] = ind; *1/ */
/*     /1*     ++ind; *1/ */
/*     /1* } *1/ */
/*     /1* int UB = std::numeric_limits<int>::max(); *1/ */
/*     /1* ivec pi_opt = {}; *1/ */
/*     /1* auto pi = schrage(data); *1/ */
/*     /1* auto U = calc_cmax(pi, data); *1/ */

/*     /1* if (U < UB) { *1/ */
/*     /1*     UB = U; *1/ */
/*     /1*     pi_opt = pi; *1/ */
/*     /1* } *1/ */

/*     /1* auto b = find_b(pi, data); *1/ */
/*     /1* auto a = find_a(pi, data, b); *1/ */
/*     /1* auto c = find_c(pi, data, a, b); *1/ */

/*     /1* if (c < 0) { *1/ */
/*     /1*     return pi_opt; *1/ */
/*     /1* } *1/ */

/*     /1* auto K = ivec(pi.begin()+c+1, pi.begin()+b); *1/ */
/*     /1* int r = *std::min(K.begin(), K.end(), *1/ */
/*     /1*         [&](auto left, auto right){ *1/ */
/*     /1*             return data[addr[*left]].r < data[addr[*right]].r; *1/ */
/*     /1*         }); *1/ */

/*     /1* int q = *std::min(K.begin(), K.end(), *1/ */
/*     /1*         [&](auto left, auto right){ *1/ */
/*     /1*             return data[addr[*left]].q < data[addr[*right]].q; *1/ */
/*     /1*         }); *1/ */

/*     /1* int p = std::accumulate(K.begin(), K.end(), 0, *1/ */
/*     /1*         [&](auto left, auto right){ *1/ */
/*     /1*         return data[addr[left]].p + data[addr[right]].p; *1/ */
/*     /1*         }); *1/ */

/*     /1* int r_pi = std::max(r+p, data[addr[c]].r); *1/ */

/*     /1* auto LB = prt_schrage(data); *1/ */

/*     /1* int h = std::accumulate(K.begin(), K.end(), 0, *1/ */
/*     /1*         [&](auto left, auto right){ *1/ */
/*     /1*         return data[addr[left]].q + data[addr[right]].q; *1/ */
/*     /1*         }); *1/ */

/*     /1*     h = std::accumulate(K.begin(), K.end(), h, *1/ */
/*     /1*         [&](auto left, auto right){ *1/ */
/*     /1*         return data[addr[left]].p + data[addr[right]].p; *1/ */
/*     /1*         }); *1/ */

/*     /1*     h = std::accumulate(K.begin(), K.end(), h, *1/ */
/*     /1*         [&](auto left, auto right){ *1/ */
/*     /1*         return data[addr[left]].r + data[addr[right]].r; *1/ */
/*     /1*         }); *1/ */

/*     /1*     h = std::max(h, h+data[addr[c]].r+data[addr[c]].p+data[addr[c]].q); *1/ */
/*     /1*     LB = std::max(h, LB); *1/ */
/*     /1*     if (LB < UB) { *1/ */
/*     /1*         carlier(data); *1/ */
/*     /1*     } *1/ */
/*     /1* return {}; *1/ */
/* } */

std::optional<int> find_b(const ivec& perm, const rpq_vec& data) {
    auto cmax = calc_cmax(perm, data);
    auto len = perm.size()-1;
    for (auto rb=perm.rbegin(), re=perm.rend(); rb != re; ++rb, --len) {
        auto C = calc_cmax(ivec(re.base(), re.base()+len), data);
        if (C + data[*rb-1].q  == cmax) {
            return len;
        }
    }
    return std::nullopt;
}


std::optional<int> find_c(const ivec& perm, const rpq_vec& data) {
    return std::nullopt;
}

ivec carlier(const rpq_vec& data) {
    auto vec = data;
    auto pi = schrage(data); // at this point data == vec -> true
    auto U = calc_cmax(pi, data);
    auto UB = std::numeric_limits<int>::max();
    ivec pi_opt = {};

    if (U < UB) {
        UB = U;
        pi_opt = pi;
    }

    auto maybe_b = find_b(pi, data);
    int b;
    if (maybe_b) {
        b = *maybe_b;
    }


}
