#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

struct data {
    /* workTime - czas obrabiania na maszynie */
    std::vector<int> work_time;
    int id=0;
    data(){}
    data(int number_of_machines, int id=0){work_time = std::vector<int>(number_of_machines); this->id = id; }
};

std::vector<data> read_to_vec(std::string data_name, std::string file_name) {
    int number_of_problems, number_of_machines;
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

int calc_cmax(std::vector<int> perm, std::vector<data>& data){
    std::vector<int> cmax = std::vector<int>(data[0].work_time.size(), 0);
    for (auto job_id: perm){
        // Wykres na pierwszej maszynie zawsze dosunięty w lewo
        cmax[0] += data[job_id-1].work_time[0];
        for (int m_id=1; m_id < cmax.size(); ++m_id){
            // Sprawdzenie czy zadanie jest jeszcze na maszynie poprzedniej
            cmax[m_id] = std::max(cmax[m_id], cmax[m_id-1]);
            // Do momentu zakończenia na poprzedniej albo obecnej maszynie
            // (zależy który czas większy) doliczamy czas przetwarzania
            // na obecnej maszynie
            cmax[m_id] += data[job_id-1].work_time[m_id];
        }
    }
    return cmax[cmax.size()-1];
}

int calculate_cmax(std::vector<int> kolej, std::vector<data> &data) {
    int machines = data[0].work_time.size();
    int jobs = kolej.size();
    std::vector<std::vector<int>> tab(machines, std::vector<int>(jobs));
    for (int j = 0; j < jobs; ++j) {
        for (int i = 0; i < machines; ++i) {
            int tmp=0;
            if (i != 0) { tmp=tab[i-1][j]; }
            if (j != 0 && i == 0) { tmp=tab[i][j-1]; }
            tab[i][j] = data[kolej[j]-1].work_time[i] + tmp;
            std::cout<< tab[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return tab[machines-1][jobs-1];
}

int main() {
    auto vec1 = read_to_vec("data.001:", "neh.data");
    // print_data(vec1);
    std::vector<int> kolejnosc = {1, 2, 3, 4};
    std::cout << calc_cmax(kolejnosc,vec1) << std::endl;
}
