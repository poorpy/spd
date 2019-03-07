#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct rpq {
    int r, p, q;
};

bool q_comp(const rpq &left, const rpq &right) { return left.q > right.q; }
bool r_comp(const rpq &left, const rpq &right) { return left.r < right.r; }

// Optimal for data.1 and data.3
void rq_sort(std::vector<rpq> &rpq_vec) {
    for (int i = 0; i < (rpq_vec.size() / 2); ++i) {
        std::sort(rpq_vec.begin() + i, rpq_vec.end() - i, r_comp);
        std::sort(rpq_vec.begin() + i + 1, rpq_vec.end() - i, q_comp);
    }
}

// Optimal for data.4
void qr_sort(std::vector<rpq> &rpq_vec) {
    for (int i = 0; i < (rpq_vec.size() / 2); ++i) {
        std::sort(rpq_vec.begin()+i, rpq_vec.end()-i, q_comp);
        std::sort(rpq_vec.begin()+i, rpq_vec.end()-i-1, r_comp);
    }
}

int calc_cmax(std::vector<rpq> &rpq_vec) {
    int m = rpq_vec[0].r + rpq_vec[0].p, c = m + rpq_vec[0].q;

    for (int i = 1; i < rpq_vec.size(); ++i) {
        m = rpq_vec[i].p + std::max(m, rpq_vec[i].r);
        c = std::max(c, m + rpq_vec[i].q);
    }

    return c;
}

std::vector<rpq> read_to_vec(std::string data_name, std::string file_name){
    int N; std::string str;
    std::fstream fs;
    fs.open(file_name);

    while (str != data_name) {
        fs >> str;
    }

    fs >> N;
    std::vector<rpq> rpq_vec(N);
    for (int i = 0; i < N; ++i) {
        fs >> rpq_vec[i].r >> rpq_vec[i].p >> rpq_vec[i].q;
    }

    return std::move(rpq_vec);
}

int main() {
    auto rpq_vec = read_to_vec("data.3", "rpq.data");
    rq_sort(rpq_vec);
    std::cout << calc_cmax(rpq_vec) << std::endl;
}
