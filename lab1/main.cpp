#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>

struct rpq {
    int r, p, q, id;
};

bool q_comp(const rpq &left, const rpq &right) { return left.q > right.q; }
bool r_comp(const rpq &left, const rpq &right) { return left.r < right.r; }
bool p_comp(const rpq &left, const rpq &right) { return left.p < right.p; }

bool rq_sum_comp(const rpq &left, const rpq &right) {
  return left.q + left.r < right.q + right.r;
}

inline bool operator==(const rpq &left, const rpq &right) {
  return left.r == right.r && left.p == right.p && left.q == right.q;
}

// Optimal for data.1 and data.3
void rq_sort(std::vector<rpq> &rpq_vec) {
    for (int i = 0; i < (rpq_vec.size() / 2); ++i) {
        std::sort(rpq_vec.begin() + i, rpq_vec.end() - i, r_comp);
        std::sort(rpq_vec.begin() + i + 1, rpq_vec.end() - i, q_comp);
    }
}

// Optimal for data.4
void qr_sort(std::vector<rpq> &rpq_vec) {
    for (int i = 0; i < (rpq_vec.size() / 2); ++i) {
        std::sort(rpq_vec.begin()+i, rpq_vec.end()-i, q_comp);
        std::sort(rpq_vec.begin()+i, rpq_vec.end()-i-1, r_comp);
    }
}

int calc_cmax(std::vector<rpq> &rpq_vec) {
    int m = rpq_vec[0].r + rpq_vec[0].p, c = m + rpq_vec[0].q;

    for (int i = 1; i < rpq_vec.size(); ++i) {
        m = rpq_vec[i].p + std::max(m, rpq_vec[i].r);
        c = std::max(c, m + rpq_vec[i].q);
    }

    return c;
}

std::vector<rpq> read_to_vec(std::string data_name, std::string file_name){
    int N; std::string str;
    std::fstream fs;
    fs.open(file_name);

    while (str != data_name) {
        fs >> str;
    }

    fs >> N;
    int id=1;
    std::vector<rpq> rpq_vec(N);
    for (int i = 0; i < N; ++i) {
        fs >> rpq_vec[i].r >> rpq_vec[i].p >> rpq_vec[i].q;
        rpq_vec[i].id = id;
        ++id;
    }

    return rpq_vec;
}

// zeby wyjsc z rekurencji tak nie ladnie po pierwszej sumie
static bool sum_found = false;
std::vector<rpq> left;
void subset_sum_recursive(std::vector<rpq> rpq_vec, int target,
                          std::vector<rpq> partial) {
  int s = 0;
  for (auto cit = partial.begin(); cit != partial.end(); cit++) {
    s += (*cit).p;
  }

  if (s == target) {
    /* std::cout << "sum(["; */

    /* for (auto cit = partial.begin(); cit != partial.end(); cit++) { */
    /*   std::cout << (*cit).p << ","; */
    /* } */

    /* std::cout << "])=" << target << std::endl; */
    sum_found = true;
    left = partial;
  }

  if (s >= target)
    return;

  rpq n;
  for (auto ai = rpq_vec.begin(); ai != rpq_vec.end(); ai++) {
    n = *ai;
    std::vector<rpq> remaining;
    for (auto aj = ai; aj != rpq_vec.end(); aj++) {
      if (aj == ai)
        continue;
      remaining.push_back(*aj);
    }
    std::vector<rpq> partial_rec = partial;
    partial_rec.push_back(n);
    if (!sum_found) {
      subset_sum_recursive(remaining, target, partial_rec);
    }
  }
}
void subset_sum(std::vector<rpq> rpq_vec, int target) {
  subset_sum_recursive(rpq_vec, target, std::vector<rpq>());
}

void opt_alg_data2(std::vector<rpq> &rpq_vec, int n) {
  std::vector<rpq> sorted_data;
  std::vector<rpq> right;

  auto tmp = std::max_element(rpq_vec.begin(), rpq_vec.end(), rq_sum_comp);
  int required_sum = (*tmp).r;
  sorted_data.push_back(*tmp);
  rpq_vec.erase(tmp);

  std::sort(rpq_vec.begin(), rpq_vec.end(), p_comp);

  /* for (auto item : rpq_vec) { */
  /*   std::cout << item.p << " "; */
  /* } */

  /* std::cout << std::endl; */
  /* std::cout << required_sum << std::endl; */
  subset_sum(rpq_vec, required_sum);
  // chuja z tym trzeba boosty includowac zeby te zipy dzialaly
  // wyjeb z wektora wejściowego te bloczki króte użyte sa w subset_sum
  rpq_vec.erase(remove_if(begin(rpq_vec), end(rpq_vec),
                          [&](auto x) {
                            return find(begin(left), end(left), x) != end(left);
                          }),
                end(rpq_vec));
  right = rpq_vec;
// dupa debug printy zakomentowane w "sexy layout"
  /* for (auto item : left) {
   *   std::cout << item.p << " ";
   * }
   * std::cout << std::endl;
   * for (auto item : right) {
   *   std::cout << item.p << " ";
   * } */

  // dodaj lewa strone bloczkow
  for (auto item : left) {
    sorted_data.push_back(item);
  }
  std::reverse(sorted_data.begin(), sorted_data.end());
  // dodaj prawa srone
  for (auto item : right) {
    sorted_data.push_back(item);
  }
  rpq_vec = sorted_data;
}

void run_parallel(std::vector<rpq>& vec){
    std::vector<rpq> v1, v2, v3;
    v1 = vec;
    v2 = vec;
    v3 = vec;


    sum_found = false;

    rq_sort(v1);
    qr_sort(v2);
    opt_alg_data2(v3, vec.size());

    /* std::thread t1(rq_sort, std::ref(v1)); */
    /* std::thread t2(qr_sort, std::ref(v2)); */
    /* std::thread t3(opt_alg_data2, std::ref(v3), v3.size()); */

    /* t1.join(); */
    /* t2.join(); */
    /* t3.join(); */

    auto c1 = calc_cmax(v1);
    auto c2 = calc_cmax(v2);
    auto c3 = calc_cmax(v3);

    auto min_c = std::min({c1, c2, c3});
    if (min_c == c1) {  vec = v1; }
    if (min_c == c2) {  vec = v2; }
    if (min_c == c3) {  vec = v3; }
}

int main() {
    auto vec1 = read_to_vec("data.1", "rpq.data");
    auto vec2 = read_to_vec("data.2", "rpq.data");
    auto vec3 = read_to_vec("data.3", "rpq.data");
    auto vec4 = read_to_vec("data.4", "rpq.data");

    run_parallel(vec1);
    run_parallel(vec2);
    run_parallel(vec3);
    run_parallel(vec4);

    auto c_sum = calc_cmax(vec1) + calc_cmax(vec2) + calc_cmax(vec3) + calc_cmax(vec4);
    std::cout << c_sum << std::endl;

    std::cout << "vec1:" << std::endl;
    for( auto item: vec1 ){
        std::cout << item.id << ' ';
    }
    std::cout << '\n';

    std::cout << "vec2:" << std::endl;
    for( auto item: vec2 ){
        std::cout << item.id << ' ';
    }
    std::cout << '\n';

    std::cout << "vec3:" << std::endl;
    for( auto item: vec3 ){
        std::cout << item.id << ' ';
    }
    std::cout << '\n';

    std::cout << "vec4:" << std::endl;
    for( auto item: vec4 ){
        std::cout << item.id << ' ';
    }
    std::cout << '\n';
}
