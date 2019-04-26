#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct data {
  int r, p, q, id;
};

std::vector<data> read_to_vec(std::string data_name, std::string file_name) {
  int N;
  std::string str;
  std::fstream fs;
  fs.open(file_name);

  while (str != data_name) {
    fs >> str;
  }

  fs >> N;
  int id = 1;
  std::vector<data> rpq_vec(N);
  for (int i = 0; i < N; ++i) {
    fs >> rpq_vec[i].r >> rpq_vec[i].p >> rpq_vec[i].q;
    rpq_vec[i].id = id;
    ++id;
  }

  return rpq_vec;
}

int main() {
  for (int i = 1; i < 121; ++i) {
    // std::string ind = std::to_string(i);
    std::stringstream s;
    s << std::setfill('0') << std::setw(3) << i;
    std::string ind = s.str();
    std::cout << ind;
    std::vector<data> data = read_to_vec("data." + ind + ":", "neh.data");
    std::cout << std::endl;
  }
}
