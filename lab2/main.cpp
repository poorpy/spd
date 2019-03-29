#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>

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
bool calcWiti(std::vector<int> kolej, int startingC,
              std::vector<pwd> machineData) {
  for (auto &it : kolej) {
    int kara = std::max(0, startingC - machineData[it].d) * machineData[it].w;
    startingC+= machineData[it].p;
    if(kara!=0)
      return false;
  }
  return true;
}

int main() {
  for (int i = 10; i<21; ++i){
    std::string ind = std::to_string(i);
    auto vec1 = read_to_vec("data."+ind+":", "witi.data");
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
    //  std::cout << cmaxExported << std::endl;
    int maxWiti = h_vec[N - 1];

    N -= 1;
    int sum = h_vec[N]; // minimalna kara ostatnia
    int count = 0;      // jak dużo bitów w liczbie
    int tmp = N;
    while (tmp > 0) {
      tmp /= 2;
      count++;
    }

    std::vector<int> kolejnosc;
    bool witimemorise = true;
    int witiChangeIndex = 0;
    for (int range = 0; range < vec1.size(); range++) {
      for (int i = count - 1; i >= 0; --i) {
        // for (int i = 0 ; i <count; ++i) {
        if (N & 1 << i) { // jezeli 0 to nie zmieniaj w binarce
          N ^= (1 << i);
          // std::cout << "N " << N << std::endl;
          int kara = std::max(0, cmaxExported - vec1[i].d) * vec1[i].w;
          int min = h_vec[N] + kara;
          if (sum == min) {
            if (h_vec[N] != maxWiti and witimemorise) {
              witiChangeIndex = vec1.size() - range;
              witimemorise = false;
              // std::cout << "index change: " << witiChangeIndex << std::endl;
            }

            // std::cout << std::bitset<20>(N) << " " << h_vec[N] << " " << kara
                      // << " " << N << " id: " << vec1[i].id << std::endl;
            kolejnosc.push_back(vec1[i].id);
            cmaxExported -= vec1[i].p;
            sum = h_vec[N];
            break;
          } else {
            N ^= (1 << i);
          }
        }
      }
      // break;
    }
    std::for_each(kolejnosc.rbegin(),kolejnosc.rend(), [=](int ind){std::cout << ind << " ";});
    std::cout << '\n'<< std::endl;
    // void print(int x){std::cout << x << " "}
    /* kolejnosc wlasciwa */
    int czas = 0;
    std::vector<int> kolWlasciwa;
    for (int i = 0; i <= witiChangeIndex; ++i) {
      int id = kolejnosc.back();
      czas += vec1.at(id - 1).p;
      kolejnosc.pop_back();
      // std::cout << id << " ";
    }


    // std::cout <<'\n'<< witiChangeIndex << " " << kolejnosc[witiChangeIndex] << std::endl;
    // std::cout <<'\n'<< witiChangeIndex-1 << " " << vec1[witiChangeIndex-1].id << std::endl;

    // std::cout << czas << std::endl;
    std::reverse(kolejnosc.begin(), kolejnosc.end());
  
    int minimalId = *std::min_element(kolejnosc.begin(), kolejnosc.end());
    // std::cout << minimalId << std::endl;
    bool xd = calcWiti(kolejnosc,czas,vec1);
    // std::cout<<xd<<" calc witi"<<std::endl;
    
  }
}
