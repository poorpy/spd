#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct pwd {
  int p, w, d, id;
};

std::vector<pwd> read_to_vec(std::string data_name, std::string file_name) {
  int N;
  std::string str;
  std::fstream fs;
  fs.open(file_name);

  while (str != data_name) {
    fs >> str;
  }

  fs >> N;
  int id = 1;
  std::vector<pwd> pwd_vec(N);
  for (int i = 0; i < N; ++i) {
    fs >> pwd_vec[i].p >> pwd_vec[i].p >> pwd_vec[i].d;
    pwd_vec[i].id = id;
    ++id;
  }

  return pwd_vec;
}

int main() { auto vec1 = read_to_vec("data.10:", "witi.data.txt"); }
