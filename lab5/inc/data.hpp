#pragma once
#include <vector>

struct rpq {
    int r, p, q, id;
};

struct ncomp {
    bool operator() (rpq a, rpq b) {
        return a.r > b.r;
    }
};

struct gcomp {
    bool operator() (rpq a, rpq b) {
        return a.q < b.q;
    }
};



typedef std::vector<rpq> rpq_vec;
typedef std::vector<int> ivec;

inline bool operator==(const rpq &left, const rpq &right) {
    return left.r == right.r && left.p == right.p && left.q == right.q;
}

int calc_cmax(const rpq_vec& data);
int calc_cmax(const ivec& perm, const rpq_vec& data);
