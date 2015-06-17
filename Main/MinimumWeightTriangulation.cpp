#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <vector>
#include "Graph/Graph.h"
#include "Triangulations.h"

double weight_by_triangle_perimeter(Vertex* a, Vertex* b, Vertex* c);
void add_triangles(Graph& graph, std::vector<Vertex*>& vertices, long* v, std::size_t i, std::size_t j);

void compute_minimum_weight_triangulation(Graph& graph, std::function<double(Vertex*,Vertex*,Vertex*)> weight) {
	std::vector<Vertex*> vertices;
	vertices.assign(graph.vertices_begin(), graph.vertices_end());
	compute_minimum_weight_triangulation_of_vertices(graph, vertices, weight);
}

void compute_minimum_weight_triangulation_of_vertices(Graph& graph, std::vector<Vertex*>& vertices, std::function<double(Vertex*,Vertex*,Vertex*)> weightfunction) {
	std::size_t n = vertices.size();
	double* weight = new double[n*n];
	long* bestvertex = new long[n*n];
	bool* visible = new bool[n*n];
	
	for(std::size_t i = 0; i < n; i++) {
		for(std::size_t j = 0; j < n; j++) {
			visible[i*n+j] = vertices[i]->is_adjacent(vertices[j]) || graph.is_legal_edge(vertices[i], vertices[j]);
		}
	}
	
	for(std::size_t i = n-1; i--;) {
		for(std::size_t j = i+1; j < n; j++) {
			if(i == j-1) {
				weight[i*n+j] = 0;
			} else if(visible[i*n+j]) {
				weight[i*n+j] = std::numeric_limits<double>::infinity();
				bestvertex[i*n+j] = -1;
				for(std::size_t k = i+1; k < j; k++) {
					if(visible[i*n+k] && visible[j*n+k]) {
						double new_weight =  weight[i*n+k] + weight[k*n+j] + weightfunction(vertices[i], vertices[j], vertices[k]);
						if(weight[i*n+j] >= new_weight) {
							weight[i*n+j] = new_weight;
							bestvertex[i*n+j] = k;
						}
					}
				}
			} else {
				weight[i*n+j] = std::numeric_limits<double>::infinity();
				bestvertex[i*n+j] = -1;
			}
		}
	}
	
	add_triangles(graph, vertices, bestvertex, 0, n-1);
	
	delete[] weight;
	delete[] bestvertex;
	delete[] visible;
}


double weight_by_triangle_perimeter(Vertex* a, Vertex* b, Vertex* c) {
	double ab_dx = a->x() - b->x();
	double ab_dy = a->y() - b->y();
	double bc_dx = b->x() - c->x();
	double bc_dy = b->y() - c->y();
	double ac_dx = a->x() - c->x();
	double ac_dy = a->y() - c->y();
	return(sqrt((ab_dx*ab_dx) + (ab_dy*ab_dy)) + sqrt((bc_dx*bc_dx) + (bc_dy*bc_dy)) + sqrt((ac_dx*ac_dx) + (ac_dy*ac_dy)));
}

void add_triangles(Graph& graph, std::vector<Vertex*>& vertices, long* bestvertex, std::size_t i, std::size_t j) {
	std::size_t n = vertices.size();
	if(bestvertex[i*n+j] == -1) { return; }
	graph.add_edge(vertices[i], vertices[j]);
	graph.add_edge(vertices[i], vertices[bestvertex[i*n+j]]);
	graph.add_edge(vertices[j], vertices[bestvertex[i*n+j]]);
	if(j - bestvertex[i*n+j] > 1) { add_triangles(graph, vertices, bestvertex, bestvertex[i*n+j], j); }
	if(bestvertex[i*n+j] - i > 1) { add_triangles(graph, vertices, bestvertex, i, bestvertex[i*n+j]); }
}
