#include "../inc/io.hpp"

std::vector<rpq> read_to_vec(std::string data_name, std::string file_name) {
    int N; std::string str;
    std::fstream fs;
    fs.open(file_name);

    while (str != data_name) {
        fs >> str;
    }

    fs >> N;
    std::vector<rpq> rpq_vec(N);
    for (auto i = 0; i < N; ++i) {
        fs >> rpq_vec[i].r >> rpq_vec[i].p >> rpq_vec[i].q;
        rpq_vec[i].id = i+1;
    }

    return rpq_vec;
}
