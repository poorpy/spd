#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

struct data {
    /* workTime - czas obrabiania na maszynie */
    std::vector<int> work_time;
    // addr = -1 bo nie zaincjalizowane
    int id=0, weight=0;
    data(){}
    data(int number_of_machines, int id=0){work_time = std::vector<int>(number_of_machines); this->id = id; }
};

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

int calc_cmax(std::vector<int>& perm, std::vector<data>& data){
    std::vector<int> cmax = std::vector<int>(data[0].work_time.size(), 0);
    std::map<int, int> addr_map;
    int addr = 0;
    for (auto item: data) {
        addr_map.insert(std::pair<int, int>(item.id, addr));
        ++addr;
    }
    for (auto job_id: perm){
        // Wykres na pierwszej maszynie zawsze dosunięty w lewo
        cmax[0] += data[addr_map.at(job_id)].work_time[0];
        for (int m_id=1; m_id < cmax.size(); ++m_id){
            // Sprawdzenie czy zadanie jest jeszcze na maszynie poprzedniej
            cmax[m_id] = std::max(cmax[m_id], cmax[m_id-1]);
            // Do momentu zakończenia na poprzedniej albo obecnej maszynie
            // (zależy który czas większy) doliczamy czas przetwarzania
            // na obecnej maszynie
            cmax[m_id] += data[addr_map.at(job_id)].work_time[m_id];
        }
    }
    return cmax[cmax.size()-1];
}


std::vector<int> find_perm(std::vector<data>& data){
    std::vector<int> perm;
    for (int i=0; i<data.size(); ++i){
        int opt_ind = 0, cmax=999999;
        // Będzie not ok bo nie sprawdza wstawienia po ost. elemencie
        {
            auto perm_d = perm;
            perm_d.insert(perm_d.begin(), data[i].id);
            cmax = calc_cmax(perm_d, data);
        }

        for (int j=1; j<i; ++j){
            auto perm_cp = perm;
            perm_cp.insert(perm_cp.begin()+j, data[i].id);
            if (calc_cmax(perm_cp, data) < cmax){
                cmax = calc_cmax(perm_cp, data);
                opt_ind = j;
            }
        }

        {
            auto perm_d = perm;
            perm_d.push_back(data[i].id);
            if ( calc_cmax(perm_d, data) < cmax){
                cmax = calc_cmax(perm_d, data);
                opt_ind = perm_d.size();
            }
        }
        if (opt_ind >= perm.size()){
            perm.push_back(data[i].id);
        } else {
            perm.insert(perm.begin()+opt_ind, data[i].id);
        }
    }
    return perm;
}

int main() {
    for (int i=0; i<1; ++i){
        std::string ind = std::to_string(i);
        auto vec = read_to_vec("data.00"+ind+":", "neh.data");
        std::sort(vec.begin(), vec.end(), [=](auto left, auto right) -> bool{
                return left.weight > right.weight;
                });
        auto perm = find_perm(vec);
        std::cout << "Dataset: 00"<< ind << " Cmax: " << calc_cmax(perm, vec) << "\nPerm: ";
        for (auto item: perm){
            std::cout << item << " ";
        }
        std::cout << std::endl << std::endl;

    }
    // print_data(vec1);
    /* std::vector<int> kolejnosc = {1, 2, 3, 4}; */
    /* std::cout << calc_cmax(kolejnosc,vec1) << std::endl; */
}
