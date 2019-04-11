#ifndef FIND_PERM
#define FIND_PERM

#include <vector>
#include <algorithm>

struct data {
    /* workTime - czas obrabiania na maszynie */
    std::vector<int> work_time;
    // addr = -1 bo nie zaincjalizowane
    int id=0, weight=0;
    data(){}
    data(int number_of_machines, int id=0){work_time =
        std::vector<int>(number_of_machines); this->id = id;}
};

int calc_cmax(const std::vector<int>& perm, const std::vector<data>& data);
int calc_cmax(const std::vector<int>& perm, const std::vector<data>& data,
        const std::vector<int>& addr);

std::vector<int> find_perm(const std::vector<data>& data);


#endif /* ifndef FIND_PERM */
