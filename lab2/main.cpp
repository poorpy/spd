#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct pwd {
  int p, w, d, id;
  /* p- czas trwania
   * w- waga
   * d- porzadany termin zakonczenia */
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
  std::vector<pwd> rpq_vec(N);
  for (int i = 0; i < N; ++i) {
    fs >> rpq_vec[i].p >> rpq_vec[i].w >> rpq_vec[i].d;
    rpq_vec[i].id = id;
    ++id;
  }

  return rpq_vec;
}

int main() {
  auto vec1 = read_to_vec("data.10:", "witi.data");
  /* auto vec2 = read_to_vec("data.2", "witi.data"); */
  /* auto vec3 = read_to_vec("data.3", "witi.data"); */
  /* auto vec4 = read_to_vec("data.4", "witi.data"); */
  int cmaxExported = 0;

  int N = 1 << vec1.size();
  std::vector<int> h_vec(N);
  std::vector<int> id_vec(vec1.size());
  h_vec[0] = 0;
  for (int set = 1; set < N; ++set) {
    int cmax = 0;
    cmaxExported = 0;
    for (unsigned long int i = 0, b = 1; i < vec1.size(); ++i, b *= 2)
      if (b & set)
        cmax += vec1[i].p;
    cmaxExported = cmax;
    h_vec[set] = 999999;
    for (unsigned long int i = 0, b = 1; i < vec1.size(); ++i, b *= 2)
      if (b & set)
        h_vec[set] = std::min(
            h_vec.at(set), h_vec.at(set - b) +
                               vec1.at(i).w * std::max(0, cmax - vec1.at(i).d));
  }

  std::cout << h_vec[N - 1] << '\n';

  N -= 1;
  int sum = h_vec[N]; // minimalna kara ostatnia
  int count = 0;      // jak dużo bitów w liczbie
  int tmp = N;
  while (tmp > 0) {
    tmp /= 2;
    count++;
  }
  std::vector<int> kolejnosc;
  for (int i = 0; i < vec1.size(); i++) {
    for (int i = count - 1; i >= 0; --i) {
      if (N & 1 << i) { // jezeli 0 to nie zmieniaj w binarce
        N ^= (1 << i);
        // std::cout << "N " << N << std::endl;
        int kara = std::max(0, cmaxExported - vec1[i].d) * vec1[i].w;
        int min = h_vec[N] + kara;
        if (sum == min) {
          // std::cout << h_vec[N] << " " << kara << " " << N
          // << " id: " << vec1[i].id << std::endl;
          kolejnosc.push_back(vec1[i].id);
          cmaxExported -= vec1[i].p;
          sum = h_vec[N];
          break;
        } else {
          N ^= (1 << i);
        }
      }
    }
  }
  std::cout << "kolejnosc:\n";
  for (auto it = kolejnosc.end()-1; it >= kolejnosc.begin(); it--)
    std::cout << " " << *it;

  std::cout << std::endl;
}
