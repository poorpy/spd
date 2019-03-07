#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct rpq {
  int r, p, q;
};

bool q_comp(const rpq &left, const rpq &right) { return left.q > right.q; }
bool r_comp(const rpq &left, const rpq &right) { return left.r < right.r; }

void opt_alg_data13(std::vector<rpq> &rpq_vec) {
  // Algorytm dla 1 datasetu optymalny
  for (int i = 0; i < (rpq_vec.size() / 2); ++i) {
    std::sort(rpq_vec.begin() + i, rpq_vec.end() - i, r_comp);
    std::sort(rpq_vec.begin() + i + 1, rpq_vec.end() - i, q_comp);
  }
}

int main() {
  std::fstream fs;
  fs.open("./rpq.data");
  int N;
  std::string str;

  while (str != "data.3") {
    fs >> str;
  }

  fs >> N;

  std::vector<rpq> rpq_vec(N);

  for (int i = 0; i < N; ++i) {
    fs >> rpq_vec[i].r >> rpq_vec[i].p >> rpq_vec[i].q;
  }

  opt_alg_data13(rpq_vec);
  int m = rpq_vec[0].r + rpq_vec[0].p, c = m + rpq_vec[0].q;

  for (int i = 1; i < N; ++i) {
    m = rpq_vec[i].p + std::max(m, rpq_vec[i].r);
    c = std::max(c, m + rpq_vec[i].q);
  }

  std::cout << c << std::endl;
}
