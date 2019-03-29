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

int main() {
  auto vec1 = read_to_vec("data.000:", "neh.data");
  print_data(vec1);
}
