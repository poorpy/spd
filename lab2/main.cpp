#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>

struct pwd {
    int p, w, d, id;
};

std::vector<pwd> read_to_vec(std::string data_name, std::string file_name){
    int N; std::string str;
    std::fstream fs;
    fs.open(file_name);

    while (str != data_name) {
        fs >> str;
    }

    fs >> N;
    int id=1;
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
    for(int set=1; set<N; ++set){
        int c=0;
        for(int i=0, b=1; i<vec1.size(); ++i, b*=2)if(b&set){
            c+=vec1[i].p;
            id_vec.erase(id_vec.begin(), id_vec.end());
        }
        h_vec[set]=999999;
        for(int i=0, b=1; i<vec1.size(); ++i, b*=2)if(b&set){
            h_vec[set] = std::min(h_vec.at(set),
                    h_vec.at(set-b)+vec1.at(i).w*std::max(0, c-vec1.at(i).d));
        }
    }

    /* for(int i=N-1; i > 0; i=~i ){ */
    /*     std::cout << i << '\n'; */
    /* } */
    // x - (x&(x-1))
    /* std::cout << (uint)(111&(111-1)) << '\n'; */
    /* std::cout << std::bitset<20>()(uint)(111&(111-1)) << '\n'; */
    /* std::cout << std::bitset<11>(N) << '\n' ; */

    /* std::cout << h_vec[N-1] << '\n'; */
    /* for( auto item: id_vec ){ */
    /*     std::cout << item << " "; */
    /* } */
    /*     std::cout << '\n'; */

    return 0;
}
