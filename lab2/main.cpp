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

  int N = 1 << vec1.size();
  std::vector<int> h_vec(N);
  std::vector<int> id_vec(vec1.size());
  h_vec[0] = 0;
  for (int set = 1; set < N; ++set) {
    int cmax = 0;
    for (unsigned long int i = 0, b = 1; i < vec1.size(); ++i, b *= 2)
      if (b & set)
        cmax += vec1[i].p;
    h_vec[set] = 999999;
    for (unsigned long int i = 0, b = 1; i < vec1.size(); ++i, b *= 2)
      if (b & set)
        h_vec[set] = std::min(
            h_vec.at(set), h_vec.at(set - b) +
                               vec1.at(i).w * std::max(0, cmax - vec1.at(i).d));
  }

  std::cout << h_vec[N - 1] << '\n';
  std::cout << N - 1 << '\n';
  N -= 1; // z 100.. zrob 0111..
  // N rowna się teraz 1111111111
  N = N ^ (1 << 9); // zamien 10 bit na 0 (iterowane od 0 dlatego 9)
  // N = 0111111111 czyli powinno byc 511 dziesietnie
  std::cout << N << '\n';
  // zgadza się
  // teraz trzeba zrobić 1011111111 czyli 767
  N = N ^ (1 << 9); // zamien spowrotem 10 bit
  N = N ^ (1 << 8);
  std::cout << N << '\n'; // printuje 767 czyli dziala;
  N = N ^ (1 << 8);

  std::cout << '\n' << "pętla co przestawia pokoleii bit na 0:\n";

  // to teraz pętla żeby kazdy zamieniło z 0
  for (int bitToReplace = 9; bitToReplace >= 0; --bitToReplace) {
    /* if (N & 1 << bitToReplace) {
     *   std::cout << "bit equeal 1 \n";
     * } */

    N ^= (1 << bitToReplace);
    std::cout << N << '\n'; // printuje 767 czyli dziala;
    /* if (!(N & 1 << bitToReplace)) {
     *   std::cout << "bit equeal 0 \n";
     * } */

    N ^= (1 << bitToReplace);
  }
  // trzeba odwracać spowrotem kiedy ta wartośc nie równa się naszej
  // jeżeli się równa ten F(0111) + error naszemu optymalnemu
  // to tego 0 na początku już nie odwracamy tylko wchodzimy
  // do kolejnego czyli F(0111) i zmieniamy już tylko te 1

  // trzeba wymyślić jak zamieniać tylko jedynki na 0 po kolei
  // mam taki pomysł (zwykla lopata)
  // W tej pętli sprawdzać przed zamianą bitu czy równa się 1
  // jeżeli tak to zamień na 0 jeżeli nie to przejdz do następnego
  // bitu
  // temp & (1 << N)
  // to co zakomentowane w pętli jest git i dobrze sprawdza czy bit jest jedynka
  // GG teraz zaimplementowac
}
