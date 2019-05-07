#include <algorithm>
#include <iostream>
#include <queue>

#include "inc/io.hpp"


ivec schrage(const rpq_vec& data) {
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




int main() {
    auto vec = read_to_vec("data.000:", "schr.data");
    std::cout << "Read pass" << std::endl;
    auto ans = schrage(vec);
    std::cout << std::endl;
    std::cout << std::endl;
    for (auto const& item : ans) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::cout << calc_cmax(ans, vec) << std::endl;
}
