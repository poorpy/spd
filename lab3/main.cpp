#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

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

std::vector<std::vector<int>> graph_right(std::vector<int> &perm,
                                          std::vector<data> &data) {
  int wiersz = data.at(0).work_time.size();
  int kol = perm.size();
  std::vector<std::vector<int>> arr(wiersz, std::vector<int>(kol));
  for (int j = 0; j < kol; j++) {
    if (j == 0)
      arr[0][j] = data[perm.at(j) - 1].work_time[0];
    arr[0][j] = data[perm.at(j) - 1].work_time[0] + arr[0][j - 1];
  }
  for (int i = 1; i < wiersz; i++) {
    arr[i][0] = data[perm.at(0) - 1].work_time[i] + arr[i - 1][0];
  }
  for (int i = 1; i < wiersz; ++i) {
    for (int j = 1; j < kol; ++j) {
      arr[i][j] = std::max(data[perm.at(j) - 1].work_time[i] + arr[i][j - 1],
                           data[perm.at(j) - 1].work_time[i] + arr[i - 1][j]);
      // std::cout << arr[i][j] << " ";
    }
  }
  return arr;
}

std::vector<std::vector<int>> graph_left(std::vector<int> &perm,
                                         std::vector<data> &data) {
  int wiersz = data.at(0).work_time.size();
  int kol = perm.size();
  std::vector<std::vector<int>> arr(wiersz, std::vector<int>(kol));
  wiersz -= 1;
  kol -= 1;
  for (int j = kol; j >= 0; j--) {
    if (j == kol) {
      arr[wiersz][j] = data[perm.at(j) - 1].work_time[wiersz];
    } else {
      arr[wiersz][j] =
          data[perm.at(j) - 1].work_time[wiersz] + arr[wiersz][j + 1];
    }
    // std::cout << arr[wiersz][j + 1] << " ";
  }
  for (int i = wiersz - 1; i >= 0; i--) {
    arr[i][kol] = data[perm.at(kol) - 1].work_time[i] + arr[i + 1][kol];
  }

  for (int i = wiersz - 1; i >= 0; i--) {
    for (int j = kol - 1; j >= 0; j--) {
      arr[i][j] = std::max(data[perm.at(j) - 1].work_time[i] + arr[i][j + 1],
                           data[perm.at(j) - 1].work_time[i] + arr[i + 1][j]);
      // std::cout << arr[i][j] << " ";
    }
  }

  return arr;
}

void print_graph(std::vector<std::vector<int>> &tab) {
  for (auto vec : tab) {
    for (auto x : vec)
      std::cout << x << ", ";
    std::cout << std::endl;
  }
}

std::vector<int> quick(std::vector<data> &data) {
  std::vector<struct data> sorted = data;
  std::stable_sort(sorted.begin(), sorted.end(),
                   [](const struct data &x, const struct data &y) {
                     return (x.weight > y.weight);
                   });
  // std::vector<int> perm = {1, 4, 3, 2};
  std::vector<int> perm;
  perm.push_back(sorted[0].id);
  // pierwsze dwa elementy
  std::vector<int> temp = perm;
  temp.insert(temp.begin(), sorted[1].id);
  int cmax = calc_cmax(temp, data);
  std::swap(temp[0], temp[1]);
  if (calc_cmax(temp, data) < cmax)
    perm = temp;
  else
    perm.insert(perm.begin(), sorted[1].id);

  // cała reszta
  for (int i = 2; i < data.size(); i++) {
    auto to_insert = sorted[i];
    auto right = graph_right(perm, data);
    auto left = graph_left(perm, data);
    // cmax = left[0][0];
    // po wszystkich miejscach
    std::vector<int> cmaxx;
    for (int j = 0; j < perm.size() + 1; j++) {
      // pierwszy element
      if (j == 0) {
        // z gory na dol w grafie iteracja
        int tmp = 0;
        int cmax = 0;
        for (int k = 0; k < to_insert.work_time.size(); k++) {
          if (k == 0) {
            tmp = to_insert.work_time[k];
            cmax = tmp + left[k][j];
          } else {
            tmp = to_insert.work_time[k] + tmp;
            if (tmp + left[k][j] > cmax)
              cmax = tmp + left[k][j];
          }
        }
        cmaxx.push_back(cmax);
        // ostatni element
      } else if (j == perm.size()) {
        // ostatni element
        int tmp = 0;
        for (int k = 0; k < to_insert.work_time.size(); k++) {
          if (k == 0) {
            tmp = to_insert.work_time[k] + right[k][j - 1];
          } else {
            tmp = std::max(right[k][j - 1], tmp) + to_insert.work_time[k];
          }
        }
        cmaxx.push_back(tmp);
      } else {
        int cmax = 0;
        int tmp = 0;
        for (int k = 0; k < to_insert.work_time.size(); k++) {
          if (k == 0) {
            tmp = right[k][j - 1] + to_insert.work_time[k];
            cmax = tmp + left[k][j];
          } else {
            tmp = std::max(right[k][j - 1], tmp) + to_insert.work_time[k];
            if (tmp + left[k][j] > cmax)
              cmax = tmp + left[k][j];
          }
        }
        cmaxx.push_back(cmax);
      }
    }

    int maxElementIndex =
        std::min_element(cmaxx.begin(), cmaxx.end()) - cmaxx.begin();
    perm.insert(perm.begin() + maxElementIndex, to_insert.id);

    // std::cout << std::endl;
    // print_graph(right);
    // std::cout << std::endl;
    // print_graph(left);
    // std::cout << "cmax:\n";
    //
    // for (auto item : cmaxx) {
    //   std::cout << item << " ";
    // }
    // std::cout << "\n";
    // std::cout << "perm:\n";
    //
    // for (auto item : perm) {
    //   std::cout << item << " ";
    // }
    // std::cout << "\n";
  }
  // for ilosc maszyn
  // policz prawą stronę
  // policz lewą strone

  // przechodź po kolumnach
  // wstawiaj zadanie
  // sprawdz cmax w wierszach z zadaniem

  // wybierz najlepszą kolumnę (cmax najniższy)
  std::cout << "perm end:\n";
  for (auto item : perm) {
    std::cout << item << " ";
  }
  return perm;
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
    for (unsigned long int i = 0; i < perm.size() - 1; ++i) {
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
  for (int i = 1; i < 121; ++i) {
    // std::string ind = std::to_string(i);
    std::stringstream s;
    s << std::setfill('0') << std::setw(3) << i;
    std::string ind = s.str();
    std::cout << ind;
    std::vector<data> data = read_to_vec("data." + ind + ":", "neh.data");
    // std::sort(sorted.begin(), sorted.end(), [=](auto left, auto right) ->
    // bool {
    //   return left.weight > right.weight;
    // });

    std::vector<int> dupa = quick(data);
    std::cout << std::endl;
    // std::vector<int> perm = {0, 3, 2, 1};
    // auto perm = find_perm(vec);
    // std::cout << "Dataset: 00" << ind << " Cmax: " << calc_cmax(perm, vec)
    //           << "\nPerm: ";
    // for (auto item : perm) {
    //   std::cout << item << " ";
    // }
    // std::cout << std::endl << std::endl;
  }
  // print_data(vec1);
  /* std::vector<int> kolejnosc = {1, 2, 3, 4}; */
  /* std::cout << calc_cmax(kolejnosc,vec1) << std::endl; */
}
