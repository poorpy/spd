#include "perm.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

std::vector<data> read_to_vec(std::string data_name, std::string file_name) {
    int number_of_problems;
    int number_of_machines;
    int id = 1;
    std::string str;
    std::fstream fs;
    fs.open(file_name);

    while (str != data_name) {
        fs >> str;
    }

    fs >> number_of_problems >> number_of_machines;
    std::vector<data> data_vec(number_of_problems);
    for (auto& problem: data_vec){
        problem = data(number_of_machines, id);
        ++id;
        for (auto& machine: problem.work_time){
            fs >> machine;
            problem.weight += machine;
        }
    }

    return data_vec;
}

void print_data(std::vector<data>& vec){
    std::cout << "vec size: " << vec.size() << std::endl;
    std::cout << "machine size: " << vec[0].work_time.size() << std::endl << std::endl;
    for (auto& problem: vec){
        for (auto& machine: problem.work_time){
            std::cout << machine << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    for (int i=0; i<121; ++i){
        std::stringstream s;
        s << std::setfill('0') << std::setw(3) << i;
        std::string ind = s.str();
        auto vec = read_to_vec("data."+ind+":", "neh.data");
        std::sort(vec.begin(), vec.end(), [=](auto left, auto right) -> bool{
                return left.weight > right.weight;
                });
        auto perm = find_perm(vec);
        std::cout << "Dataset: "<< ind << " Cmax: " << calc_cmax(perm, vec) << "\nPerm: ";
        for (auto item: perm){
            std::cout << item << " ";
        }
        std::cout << std::endl << std::endl;
    }
}
