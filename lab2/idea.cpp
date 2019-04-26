#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <utility>
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
bool mycomparer(std::pair<int, int> lhs, std::pair<int, int> rhs) {
  if (lhs.first < rhs.first) {
    return true;
  } else if (lhs.first == rhs.first && lhs.second > rhs.second) {
    return true;
  } else {
    return false;
  }
}
void szukaj_najmniejsza(std::vector<std::pair<int, int>> vec);
int main() {
  auto vec1 = read_to_vec("data.20:", "witi.data");
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
      if (b & set) {
        h_vec[set] = std::min(
            h_vec.at(set), h_vec.at(set - b) +
                               vec1.at(i).w * std::max(0, cmax - vec1.at(i).d));
      }
  }
  std::cout << h_vec[N - 1] << '\n';
  N -= 1;
  // int sum = h_vec[N]; // minimalna kara ostatnia
  int count = 0; // jak dużo bitów w liczbie
  int tmp = N;
  while (tmp > 0) {
    tmp /= 2;
    count++;
  }
  std::cout << N << std::endl;
  int n = 0;

  std::vector<int> quene;
  int cmax = 0;
  int toBit = 20;
  for (int repeat = 0; repeat < 20; ++repeat) {
    std::vector<std::pair<int, int>> temporary;
    for (int i = 0; i < toBit; i++) {
      if (!(n & 1 << i)) {
        n ^= (1 << i);
        // std::cout << h_vec[n] << " ";
        temporary.push_back(std::make_pair(h_vec[n], i));
        // std::cout << n;
        n ^= (1 << i);
      }
    }
    szukaj_najmniejsza(temporary);

    sort(temporary.begin(), temporary.end(), mycomparer);
    int var = temporary.back().second;
    // if (maxWiti == temporary.back().first) {
    // }
    toBit = var;
    quene.push_back(var + 1);
    cmax += vec1[var].p;
    std::cout << cmax << " dupa\n";
    n ^= (1 << var);
  }
  for (auto it = quene.begin(); it < quene.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

void szukaj_najmniejsza(std::vector<std::pair<int, int>> vec) {
  sort(vec.begin(), vec.end(), mycomparer);
  std::cout << "________\n";
  for (const auto &p : vec) {
    std::cout << p.first << ", " << p.second << std::endl;
  }
  std::cout << "________\n";
  // znajdz najwiekszy
  // jak się powtarza to wybierz najmniejszy drugi element
}
