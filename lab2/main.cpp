#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
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
  // std::cout<<"dupadebug"<<std::endl;
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

int main() {
  std::list<std::vector<pwd>> datalist;
  for (int i = 10; i < 21; i++) {
    std::string variable = "data." + std::to_string(i) + ":";
    datalist.push_back(read_to_vec(variable, "witi.data.txt"));
  }


}
