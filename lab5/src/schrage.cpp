#include "../inc/schrage.hpp"
#include <queue>
#include <limits>

ivec schrage(const rpq_vec &data) {
    auto t = 0; ivec pi;
    pi.reserve(data.size());
    std::priority_queue<rpq, rpq_vec, ncomp> N;
    std::priority_queue<rpq, rpq_vec, gcomp> G;

    for (auto item : data) {
        N.push(item);
    }

    while (!G.empty() or !N.empty()) {
        while (!N.empty() and N.top().r <= t) {
            G.push(N.top());
            N.pop();
        }
        if (G.empty()) {
            t = N.top().r;
        } else {
            pi.push_back(G.top().id);
            t += G.top().p;
            G.pop();
        }
    }

    return pi;
}

int prt_schrage(const rpq_vec &data) {
    int t = 0, cmax = 0;
    int q0 = std::numeric_limits<int>::max();
    rpq l = {0,0,q0,0};

    std::priority_queue<rpq, rpq_vec, ncomp> N;
    std::priority_queue<rpq, rpq_vec, gcomp> G;

    for (auto item : data) {
        N.push(item);
    }

    while (!G.empty() or !N.empty()) {
        while (!N.empty() and N.top().r <= t) {
            auto e = N.top();
            G.push(e);
            N.pop();

            if (e.q > l.q) {
                l.p = t - e.r;
                t = e.r;
                if (l.p > 0) {
                    G.push(l);
                }
            }
        }

        if (G.empty()) {
            t = N.top().r;
        } else {

            l = G.top();
            t += G.top().p;
            cmax = std::max(cmax, t+G.top().q);
            G.pop();
        }
    }

    return cmax;
}
