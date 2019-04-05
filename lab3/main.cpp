#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

struct data {
  /* workTime - czas obrabiania na maszynie */
  std::vector<int> work_time;
  // addr = -1 bo nie zaincjalizowane
  int id = 0, weight = 0;
  data() {}
  data(int number_of_machines, int id = 0) {
    work_time = std::vector<int>(number_of_machines);
    this->id = id;
  }
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
  for (auto &problem : data_vec) {
    problem = data(number_of_machines, id);
    ++id;
    for (auto &machine : problem.work_time) {
      fs >> machine;
      problem.weight += machine;
    }
  }

  return data_vec;
}

void print_data(std::vector<data> &vec) {
  std::cout << "vec size: " << vec.size() << std::endl;
  std::cout << "machine size: " << vec[0].work_time.size() << std::endl
            << std::endl;
  for (auto &problem : vec) {
    for (auto &machine : problem.work_time) {
      std::cout << machine << " ";
    }
    std::cout << std::endl;
  }
}

int calc_cmax(std::vector<int> &perm, std::vector<data> &data,
              int cur_cmax = 99999) {
  std::vector<int> cmax = std::vector<int>(data[0].work_time.size(), 0);
  std::map<int, int> addr_map;
  int addr = 0;
  for (auto item : data) {
    addr_map.insert(std::pair<int, int>(item.id, addr));
    ++addr;
  }
  for (auto job_id : perm) {
    // Wykres na pierwszej maszynie zawsze dosunięty w lewo
    cmax[0] += data[addr_map.at(job_id)].work_time[0];
    for (int m_id = 1; m_id < cmax.size(); ++m_id) {
      // Sprawdzenie czy zadanie jest jeszcze na maszynie poprzedniej
      cmax[m_id] = std::max(cmax[m_id], cmax[m_id - 1]);
      // Do momentu zakończenia na poprzedniej albo obecnej maszynie
      // (zależy który czas większy) doliczamy czas przetwarzania
      // na obecnej maszynie
      cmax[m_id] += data[addr_map.at(job_id)].work_time[m_id];
      if (cmax[m_id] > cur_cmax)
        return cur_cmax;
    }
  }
  return cmax[cmax.size() - 1];
}

std::vector<int> find_perm(std::vector<data> &data) {
  std::vector<int> perm;
  auto data_cp = data;
  std::reverse(data_cp.begin(), data_cp.end());
  while (not data_cp.empty()) {
    auto elem_to_insert = data_cp.back();
    data_cp.pop_back();
    perm.insert(perm.begin(), elem_to_insert.id);
    int cmax = calc_cmax(perm, data);
    int cmax_pos = 0;
    auto perm_cp = perm;
    for (int i = 0; i < perm.size() - 1; ++i) {
      std::swap(perm[i], perm[i + 1]);
      int tmp = calc_cmax(perm, data, cmax);
      if (tmp < cmax) {
        cmax = tmp;
        cmax_pos = i + 1;
        perm_cp = perm;
      };
    }
    perm = perm_cp;
  }
  return perm;
}

int main() {
  for (int i = 0; i < 120; ++i) {
    // std::string ind = std::to_string(i);
    std::stringstream s;
    s << std::setfill('0') << std::setw(3) << i;
    std::string ind = s.str();
    std::cout << ind;
    auto vec = read_to_vec("data." + ind + ":", "neh.data");
    std::sort(vec.begin(), vec.end(), [=](auto left, auto right) -> bool {
      return left.weight > right.weight;
    });
    auto perm = find_perm(vec);
    std::cout << "Dataset: 00" << ind << " Cmax: " << calc_cmax(perm, vec)
              << "\nPerm: ";
    for (auto item : perm) {
      std::cout << item << " ";
    }
    std::cout << std::endl << std::endl;
  }
  // print_data(vec1);
  /* std::vector<int> kolejnosc = {1, 2, 3, 4}; */
  /* std::cout << calc_cmax(kolejnosc,vec1) << std::endl; */
}
