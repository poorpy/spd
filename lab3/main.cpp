#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

struct data {
  std::vector<int> workTime;
  /* workTime - czas obrabiania na maszynie */
  int id;
};

std::vector<data> read_to_vec(std::string data_name, std::string file_name) {
  int N, machineNumber;
  std::string str;
  std::fstream fs;
  fs.open(file_name);

  while (str != data_name) {
    fs >> str;
  }

  fs >> N >> machineNumber;
  int id = 1;
  std::vector<data> data_vec(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < machineNumber; ++j) {
      int tmp;
      fs >> tmp;
      data_vec[i].workTime.push_back(tmp);
    }
    data_vec[i].id = id;
    ++id;
  }

  return data_vec;
}

void print_data(std::vector<data> &vec1) {
  for (auto &iter : vec1) {
    std::cout << "id: " << iter.id << std::endl;
    for (int i = 0; i < iter.workTime.size(); ++i) {
      std::cout << iter.workTime.at(i) << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  auto vec1 = read_to_vec("data.000:", "neh.data");
  print_data(vec1);
}
