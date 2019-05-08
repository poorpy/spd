#include "../inc/perm.hpp"

std::vector<ivec> graph_right(const ivec& perm, const dvec& data) {
    const auto row = data.at(0).work_time.size();
    const auto col = perm.size();
    std::vector<ivec> arr(row, ivec(col));

    for (auto i = 0; i < col; ++i) {
        if (i == 0) {
            arr[0][i] = data[perm.at(i) - 1].work_time[0];
        }

        arr[0][i] = data[perm.at(i) - 1].work_time[0] + arr[0][i - 1];
    }

    for (auto i = 1; i < row; ++i) {
        arr[i][0] = data[perm.at(0) - 1].work_time[i] + arr[i - 1][0];
    }

    for (auto i = 1; i < row; ++i) {
        for (auto j = 1; j < col; ++j) {
            arr[i][j] = std::max(data[perm.at(j) - 1].work_time[i] + arr[i][j - 1],
                                 data[perm.at(j) - 1].work_time[i] + arr[i - 1][j]);
        }
    }

    return arr;
}

std::vector<ivec> graph_left(const ivec& perm, const dvec& data) {
    const auto row = data.at(0).work_time.size() - 1;
    const auto col = perm.size() - 1;
    std::vector<ivec> arr(row + 1, ivec(col + 1));

    for (auto i = col; i >= 0; --i) {
        if ( i != col ) {
            arr[row][i] = data[perm.at(i) - 1].work_time[row] + arr[row][i + 1];
        } else {
            arr[row][i] = data[perm.at(i) - 1].work_time[row];
        }
    }

    for (auto i = row - 1; i >= 0; --i) {
        arr[i][col] = data[perm.at(col) - 1].work_time[i] + arr[i + 1][col];
    }

    for (auto i = row - 1; i >= 0; --i) {
        for (auto j = col - 1; j >= 0; --j) {
            arr[i][j] = std::max(data[perm.at(j) - 1].work_time[i] + arr[i][j + 1],
                    data[perm.at(j) - 1].work_time[i] + arr[i + 1][j]);
        }
    }

    return arr;
}

ivec quick(const dvec& data) {
    ivec perm;
    perm.reserve(data.size());
    perm.push_back(data[0].id);
    auto cmax = calc_cmax(perm, data);
    std::swap(perm[0], perm[1]);
    if (calc_cmax(perm, data) >= cmax) {
        std::swap(perm[0], perm[1]);
    }

    for (auto iter = data.begin()+2, end = data.end(); iter != end; ++iter) {
        auto right = graph_right(perm, data);
        auto left  = graph_left(perm, data);
        std::vector<int> cmaxx;
        for (auto i = 0UL; i < perm.size() + 1; ++i) {
            if (i != 0 and i != perm.size()) {
                int tmp = 0;
                int cmax = 0;
                for (auto j = 0UL; j < iter->work_time.size(); ++j) {
                    if (j != 0) {
                        tmp = std::max(right[j][i-1], tmp) + iter->work_time[j];
                        cmax = std::max(cmax, tmp + left[j][i]);
                    } else {
                        tmp = right[j][i-1] + iter->work_time[j];
                        cmax = tmp + left[j][i];
                    }
                }
                cmaxx.push_back(cmax);
            } else if (i == 0) {
                int tmp = 0;
                int cmax = 0;
                for (auto j = 0UL; j < iter->work_time.size(); ++j) {
                    // TODO:
                    // jeśli j = 0 to tmp = 0
                    // jeśli j = 0 to cmax = 0
                    // więc oba można uprościć do ogólnej postaci
                    if (j != 0) {
                        tmp = iter->work_time[j];
                        cmax = std::max(cmax, tmp + left[j][i]);
                    } else {
                        tmp = iter->work_time[j];
                        cmax = tmp + left[j][i];
                    }
                }
                cmaxx.push_back(cmax);
            } else {
                // ostatni element
                int tmp = 0;
                for (auto j = 0UL; j < iter->work_time.size(); ++j) {
                    if (j == 0) {
                        tmp = iter->work_time[j] + right[j][i - 1];
                    } else {
                        tmp = std::max(right[j][i - 1], tmp) + iter->work_time[j];
                    }
                }
                cmaxx.push_back(tmp);
            }

        }
    }

    /* for (auto i = 0; i < perm.size(); ++i) { */
    /*     if (i != 0 and i != perm.size()) { */
    /*         int cmax = 0; */
    /*         int tmp = 0; */
    /*         for (auto j = 0; j < ) */
    /*     } */
    /* } */

    return perm;
}
