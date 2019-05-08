#include <algorithm>
#include <iostream>

#include "inc/io.hpp"
#include "inc/schrage.hpp"

int main() {
    auto vec = read_to_vec("data.001:", "schr.data");
    /* auto ans = schrage(vec); */
    /* std::cout << std::endl; */
    /* std::cout << std::endl; */
    /* for (auto const& item : ans) { */
    /*     std::cout << item << " "; */
    /* } */
    /* std::cout << std::endl; */

    /* std::cout << calc_cmax(ans, vec) << std::endl; */

    std::cout << prt_schrage(vec) << std::endl;
}
