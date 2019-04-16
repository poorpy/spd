#include "../inc/perm.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>


std::vector<data> read_to_vec(std::string data_name, std::string file_name);
int read_neh(std::string neh, std::string file);
void print_data(std::vector<data>& vec);

int main() {
    for (int i=0; i<121; ++i){
        std::stringstream s;
        s << std::setfill('0') << std::setw(3) << i;
        std::string ind = s.str();
        auto vec = read_to_vec("data."+ind+":", "neh.data");

        std::stable_sort(vec.begin(), vec.end(), [&](auto left, auto right) -> bool{
                                              return left.weight > right.weight;
                                          });
        /* for (auto j=0; j<vec.size(); ++j){ */
        /*     if (vec[j].weight == vec[j+1].weight and vec[j].id > vec[j+1].id){ */
        /*         std::swap(vec[j], vec[j+1]); */
        /*     } */
        /* } */
        /* for (const auto& item: vec) { */
        /*     std::cout << "( " << item.id << ": " << item.weight << " )" << std::endl; */
        /* } */
        auto perm = find_perm(vec);
        auto cmax = calc_cmax(perm, vec);
        /* auto neh = read_neh("data."+ind+":", "neh.data"); */
        std::cout << "Dataset: "<< ind << " Cmax: " << cmax << "\n";
        for (auto item: perm){
            std::cout << item << " ";
        }
        std::cout << std::endl << std::endl;
    }
}

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

int read_neh(std::string neh, std::string file) {
    std::string str;
    std::fstream fs;
    int ret;
    fs.open(file);

    while (str != neh) {
        fs >> str;
    }

    while (str != "neh:") {
        fs >> str;
    }

    fs >> ret;

    return ret;
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
