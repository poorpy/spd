#include "../inc/io.hpp"
#include <iostream>

vpii read_to_vec(std::string data_name, std::string file_name){
    std::fstream fs;
    std::string str;
    fs.open(file_name);

    while (str != data_name) {
        fs >> str;
    }

    int A, B, C;
    fs >> A >> B >> C;
    for (auto i = 0; i < A; ++i) {
        fs >> str;
        std::cout << str << std::endl;
    }

    return {};
}
