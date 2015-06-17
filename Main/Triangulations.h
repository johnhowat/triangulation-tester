#ifndef __TRIANGULATIONS_H__
#define __TRIANGULATIONS_H__

#include <functional>
#include "Graph/Graph.h"

void compute_constrained_delaunay_triangulation(Graph& graph);

void compute_minimum_weight_triangulation(Graph& graph, std::function<double(Vertex*,Vertex*,Vertex*)> weight);
void compute_minimum_weight_triangulation_of_vertices(Graph& graph, std::vector<Vertex*>& vertices, std::function<double(Vertex*,Vertex*,Vertex*)> weight);
double weight_by_triangle_perimeter(Vertex* a, Vertex* b, Vertex* c);

void compute_greedy_triangulation(Graph& graph);

void compute_subpolygon_heuristic_triangulation(Graph& graph, std::function<void(Graph&)> initial_triangulation, double epsilon);

#endif
