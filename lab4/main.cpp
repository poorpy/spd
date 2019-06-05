#include <iostream>
#include <iomanip>

#include "inc/io.hpp"
#include "inc/schrage.hpp"
#include "inc/heap.hpp"

int main() {
    for (int i=0; i<9; ++i) {
        std::stringstream s;
        s << std::setfill('0') << std::setw(3) << i;

        std::string ind = s.str();
        auto vec = read_to_vec("data."+ind+":", "schr.data");
        auto ans = schrage(vec);

        std::cout << "prt Schrage: " << prt_schrage(vec) << std::endl;

        std::cout << "Schrage: " << calc_cmax(ans, vec) << std::endl;
        for (auto const& item : ans) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}
