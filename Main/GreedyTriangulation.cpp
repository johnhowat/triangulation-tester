#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
#include "Graph/Graph.h"
#include "Triangulations.h"

void compute_greedy_triangulation(Graph& graph) {
	std::vector<Vertex*> vertices;
	vertices.assign(graph.vertices_begin(), graph.vertices_end());
	
	std::vector<std::pair<Vertex*,Vertex*>> diagonals;
	for(std::size_t i = 0; i < vertices.size(); i++) {
		for(std::size_t j = i+2; j < vertices.size(); j++) {
			if(graph.is_legal_edge(vertices[i], vertices[j])) {
				diagonals.push_back(std::pair<Vertex*,Vertex*>(vertices[i], vertices[j]));
			}
		}
	}

	std::sort(diagonals.begin(), diagonals.end(), [](const std::pair<Vertex*,Vertex*>& d1, const std::pair<Vertex*,Vertex*>& d2) {
		double length1 = sqrt((d1.first->x() - d1.second->x()) * (d1.first->x() - d1.second->x()) + (d1.first->y() - d1.second->y()) * (d1.first->y() - d1.second->y()));
		double length2 = sqrt((d2.first->x() - d2.second->x()) * (d2.first->x() - d2.second->x()) + (d2.first->y() - d2.second->y()) * (d2.first->y() - d2.second->y()));
		return(length1 < length2);
	});
	
	for(std::pair<Vertex*,Vertex*> diagonal : diagonals) {
		if(graph.is_legal_edge(diagonal.first, diagonal.second)) {
			graph.add_edge(diagonal.first, diagonal.second);
		}
	}
}
