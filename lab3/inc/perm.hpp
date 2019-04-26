#ifndef FIND_PERM
#define FIND_PERM

#include <vector>
#include <algorithm>

struct data;
typedef std::vector<int> ivec;
typedef std::vector<data> dvec;

struct data {
    /* workTime - czas obrabiania na maszynie */
    ivec work_time;
    // addr = -1 bo nie zaincjalizowane
    int id=0, weight=0;
    data(){}
    data(int number_of_machines, int id=0){
        work_time = ivec(number_of_machines);
        this->id = id;
    }
};


int calc_cmax(const ivec& perm, const dvec& data);
int calc_cmax(const ivec& perm, const dvec& data,
        const ivec& addr);

ivec find_perm(const dvec& data);


#endif /* ifndef FIND_PERM */
