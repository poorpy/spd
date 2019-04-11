#include "perm.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <array>
#include <experimental/array>

int calc_cmax(const std::vector<int>& perm, const std::vector<data>& data){
    std::vector<int> addr(data.size()+1);
    int ind = 0;
    for (const auto& item: data) {
        addr[item.id] = ind;
        ++ind;
    }
    return calc_cmax(perm, data, addr);
}

int calc_cmax(const std::vector<int>& perm, const std::vector<data>& data,
        const std::vector<int>& addr){
    std::vector<int> cmax = std::vector<int>(data[0].work_time.size(), 0);
    for (auto job_id: perm){
        // Wykres na pierwszej maszynie zawsze dosunięty w lewo
        cmax[0] += data[addr.at(job_id)].work_time[0];
        for (unsigned long m_id=1; m_id < cmax.size(); ++m_id){
            // Sprawdzenie czy zadanie jest jeszcze na maszynie poprzedniej
            cmax[m_id] = std::max(cmax[m_id], cmax[m_id-1]);
            // Do momentu zakończenia na poprzedniej albo obecnej maszynie
            // (zależy który czas większy) doliczamy czas przetwarzania
            // na obecnej maszynie
            cmax[m_id] += data[addr.at(job_id)].work_time[m_id];
        }
    }
    return cmax[cmax.size()-1];
}

/* std::vector<int> find_perm(const std::vector<data>& data){ */
/*     std::vector<int> ind_vec(data.size()+1); */
/*     int addr = 0; */
/*     for (const auto& item: data) { */
/*         ind_vec[item.id] = addr; */
/*         ++addr; */
/*     } */
/*     std::vector<int> perm; */

/*     for (int i=0; i<data.size(); ++i){ */
/*         int opt_ind = 0, cmax=999999; */
/*         // Będzie not ok bo nie sprawdza wstawienia po ost. elemencie */
/*         { */
/*             auto perm_d = perm; */
/*             perm_d.insert(perm_d.begin(), data[i].id); */
/*             cmax = calc_cmax(perm_d, data, ind_vec); */
/*         } */

/*         for (int j=1; j<i; ++j){ */
/*             auto perm_cp = perm; */
/*             perm_cp.insert(perm_cp.begin()+j, data[i].id); */
/*             auto tmp = calc_cmax(perm_cp, data, ind_vec); */
/*             if (tmp < cmax){ */
/*                 cmax = tmp; */
/*                 opt_ind = j; */
/*             } */
/*         } */

/*         { */
/*             auto perm_d = perm; */
/*             perm_d.push_back(data[i].id); */
/*             auto tmp = calc_cmax(perm_d, data, ind_vec); */
/*             if ( tmp < cmax){ */
/*                 cmax = tmp; */
/*                 opt_ind = perm_d.size(); */
/*             } */
/*         } */
/*         if (opt_ind < perm.size()){ */
/*             perm.insert(perm.begin()+opt_ind, data[i].id); */
/*         } else { */
/*             perm.push_back(data[i].id); */
/*         } */
/*     } */
/*     return perm; */
/* } */


std::vector<int> find_perm(const std::vector<data>& data){
    std::vector<int> ind_vec(data.size()+1);
    int addr = 0;
    for (const auto& item: data) {
        ind_vec[item.id] = addr;
        ++addr;
    }
    std::vector<int> perm(data.size());
    std::vector<int> predecesor(data.size());
    auto counter = 0, opt_ind=0, cmax=999999;
    for (const auto& item: data) {
        for (int i=0; i < counter; ++i){
            predecesor[counter] = predecesor[i];
            predecesor[i] = item.id;
            while (false){}

        }
    }
    return perm;
}
