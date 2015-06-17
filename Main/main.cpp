#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include "Graph/Graph.h"
#include "Triangulations.h"

void output_graph(const std::string& filename, Graph& graph);

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "Usage: " << argv[0] << " POLYGON-FILE" << std::endl;
		return(1);
	}
	std::string filename(argv[1]);

	std::unordered_map<std::string, std::function<void(Graph&)>> algorithms;
	algorithms["Greedy triangulation"] = compute_greedy_triangulation;
	algorithms["Constrained Delaunay triangulation"] = compute_constrained_delaunay_triangulation;
	algorithms["Minimum-weight triangulation"] = std::bind(compute_minimum_weight_triangulation, std::placeholders::_1, weight_by_triangle_perimeter);
	algorithms["Subpolygon heuristic triangulation (Delaunay, epsilon=0.25)"] = std::bind(compute_subpolygon_heuristic_triangulation, std::placeholders::_1, compute_constrained_delaunay_triangulation, 0.25);
	algorithms["Subpolygon heuristic triangulation (Delaunay, epsilon=0.5)"] = std::bind(compute_subpolygon_heuristic_triangulation, std::placeholders::_1, compute_constrained_delaunay_triangulation, 0.5);
	algorithms["Subpolygon heuristic triangulation (Delaunay, epsilon=0.75)"] = std::bind(compute_subpolygon_heuristic_triangulation, std::placeholders::_1, compute_constrained_delaunay_triangulation, 0.75);
	algorithms["Subpolygon heuristic triangulation (Greedy, epsilon=0.25)"] = std::bind(compute_subpolygon_heuristic_triangulation, std::placeholders::_1, compute_greedy_triangulation, 0.25);
	algorithms["Subpolygon heuristic triangulation (Greedy, epsilon=0.5)"] = std::bind(compute_subpolygon_heuristic_triangulation, std::placeholders::_1, compute_greedy_triangulation, 0.5);
	algorithms["Subpolygon heuristic triangulation (Greedy, epsilon=0.75)"] = std::bind(compute_subpolygon_heuristic_triangulation, std::placeholders::_1, compute_greedy_triangulation, 0.75);

	std::string name_template((std::max_element(algorithms.begin(), algorithms.end(), [](std::pair<std::string,std::function<void(Graph&)>> lhs, std::pair<std::string,std::function<void(Graph&)>> rhs) { return(lhs.first.length() < rhs.first.length()); }))->first.length() + 3, '.');	
	std::multimap<double,std::string> weights;
	for(auto i = algorithms.begin(); i != algorithms.end(); i++) {
		Graph graph(filename);
		if(i == algorithms.begin()) {
			std::cout << "Polygon \"" << filename << "\" has " << graph.vertex_count() << " vertices." << std::endl;
		}
		(i->second)(graph);
		std::string name_template_copy(name_template);
		//weights.insert(std::pair<double,std::string>(std::accumulate(graph.edges_begin(), graph.edges_end(), 0.0, [](double& sum, Edge* e) { return(sum += e->length()); }), name_template_copy.replace(0, i->first.length(), i->first)));
		weights.insert(std::pair<double,std::string>(std::accumulate(graph.faces_begin(), graph.faces_end(), 0.0, [](double& sum, Face* f) { return(sum += f->perimeter()); }), name_template_copy.replace(0, i->first.length(), i->first)));

		graph.save_image((filename + "_" + i->first + ".png").c_str());
	}
	
	int width = std::to_string((int)std::max_element(weights.begin(), weights.end(), [](std::pair<double,std::string> lhs, std::pair<double,std::string> rhs) { return(std::to_string((int)lhs.first).length() < std::to_string((int)rhs.first).length()); })->first).length();
	for(auto i = weights.begin(); i != weights.end(); i++) {
		std::cout << i->second << " " << std::fixed << std::setw(width+2) << std::setprecision(1) << i->first << std::setprecision(5) << " [" << (i->first / weights.begin()->first) << "]" << std::endl;
	}
	return 0;
}
