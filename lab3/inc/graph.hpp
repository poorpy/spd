#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "perm.hpp"

std::vector<ivec> graph_right(const ivec& perm, const dvec& data);
std::vector<ivec> graph_left(const ivec& perm, const dvec& data);
ivec quick(dvec& data);

#endif /* end of include guard: GRAPH_HPP */
