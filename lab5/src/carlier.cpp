#include "../inc/carlier.hpp"
#include <algorithm>
#include <numeric>
#include <optional>

typedef std::pair<rpq&, int> pri;

template <typename Iterator>
int sum_p(const rpq_vec& data, Iterator begin, Iterator end) {
    auto p = 0;
    for (auto be=begin; be != end; ++be) {
        p += data[(*be)-1].p;
    }
    return p;
}


int find_b(const ivec& perm, const rpq_vec& data) {
    auto cmax = calc_cmax(perm, data);
    int len = perm.size();
    for (auto rb=perm.rbegin(), re=perm.rend(); rb != re; ++rb, --len) {
        auto C = calc_cmax(ivec(re.base(), re.base()+len), data);
        if (C == cmax) {
            return len-1;
        }
    }
    return -1;
}

int find_a(const ivec& perm, const rpq_vec& data,const int b) {
    auto cmax = calc_cmax(perm, data);
    /* std::cout << "cmax_a: " << cmax << std::endl; */
    for (auto ind=0; ind <= b; ++ind) {
        auto val = data[perm[ind]-1].r
            + sum_p(data, perm.begin()+ind, perm.begin()+b+1)
            + data[perm[b]-1].q;
        if (val == cmax) {
            return ind;
        }
    }
    return -1;
}


std::optional<int> find_c(const ivec& perm, const rpq_vec& data,
                          const int a, const int b) {
    for (auto ind=b; ind >= a; --ind) {
        if (data[perm[ind]-1].q < data[perm[b]-1].q) {
            return ind;
        }
    }

    return std::nullopt;
}

ivec carlier(rpq_vec& data, int UB) {
    auto vec = data;
    auto pi = schrage(data); // at this point data == vec -> true
    auto U = calc_cmax(pi, data);
    ivec pi_opt = {};

    if (U < UB) {
        UB = U;
        pi_opt = pi;
    }

    auto b = find_b(pi, data);
    auto a = find_a(pi, data, b);
    auto c = find_c(pi, data, a, b);

    if (!c) {
        return pi_opt;
    }

    auto K = ivec(pi.begin()+(*c)+1, pi.begin()+b+1);

    auto r_pi_ind = *std::min_element(K.begin(), K.end(),
            [&](auto l, auto r){
                return data[l-1].r < data[r-1].r;
            });
    auto r_pi = data[r_pi_ind-1].r;

    auto q_pi_ind = *std::max_element(K.begin(), K.end(),
            [&](auto l, auto r){
                return data[l-1].q < data[r-1].q;
            });
    auto q_pi = data[q_pi_ind-1].q;

    auto p_pi = sum_p(data, K.begin(), K.end());

    auto old_r = data[pi[*c]-1].r;

    data[pi[*c]-1].r = std::max(old_r, r_pi+p_pi);

    auto LB = prt_schrage(data);

    if (LB < UB) {
        return carlier(data, UB);
    }

    data[pi[*c]-1].r = old_r;

    auto old_q = data[pi[*c]-1].q;
    data[pi[*c]-1].q = std::max(old_q, q_pi+p_pi);

    LB = prt_schrage(data);
    if (LB<UB) {
        return carlier(data, UB);
    }
    data[pi[*c]-1].q = old_q;
}
