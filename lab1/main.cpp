#include <iostream>
#include <fstream>
#include <algorithm>

struct rpq {
    int r,p,q;
};
bool q_comp(const rpq& left, const rpq& right ) { return left.q > right.q; }
bool r_comp(const rpq& left, const rpq& right ) { return left.r < right.r; }


int main(){
    std::fstream fs;
    fs.open("./rpq.data");
    int N;
    std::string str;

    while (str != "data.1") {fs >> str;}

    str = "";

    while (str != "data.1") {fs >> str;}

    fs >> N;

     rpq m_rpq[N];


    for(int i=0; i<N; ++i){
        fs >> m_rpq[i].r >> m_rpq[i].p >> m_rpq[i].q;
    }

    std::sort(m_rpq, m_rpq+N, r_comp);


    int m=m_rpq[0].r + m_rpq[0].p, c=m+m_rpq[0].q;

    for(int i=1; i<N; ++i){
        m = m_rpq[i].p + std::max(m, m_rpq[i].r);
        c = std::max(c, m+m_rpq[i].q);
    }

    std::cout << m << '\n' << c << std::endl;
}
