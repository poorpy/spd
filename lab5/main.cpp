#include <iostream>
#include <iomanip>
#include <limits>

#include "inc/io.hpp"
#include "inc/carlier.hpp"

int main() {
    for (int i=0; i<9; ++i) {
        std::stringstream s;
        s << std::setfill('0') << std::setw(3) << i;

        std::string ind = s.str();
        rpq_vec vec = read_to_vec("data."+ind+":", "carl.data");
        auto pi_opt = carlier(vec, std::numeric_limits<int>::max());

        std::cout << "Cmax: " << calc_cmax(pi_opt, vec) << std::endl;
        for (const auto& item : pi_opt) {
            std::cout << item << " ";
        }
            std::cout << std::endl;

    }

}
