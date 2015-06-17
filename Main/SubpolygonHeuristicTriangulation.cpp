#include <cmath>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <unordered_set>
#include "Graph/Graph.h"
#include "Triangulations.h"

class FaceTreeNode {
	Face* face;
	std::size_t size;
	std::list<FaceTreeNode*> children;
	std::list<FaceTreeNode*> former_children;
	FaceTreeNode* parent;
	
	void add_sizes_on_path_to_root(FaceTreeNode* node, int amount) {
		node->size += amount;
		if(node->parent != nullptr) { add_sizes_on_path_to_root(node->parent, amount); }
	}
	
	public:
		FaceTreeNode(Face* f) : face(f), size(1), parent(nullptr) {}
		
		Face* get_face() { return(face); }
		FaceTreeNode* get_parent() { return(parent); }
		std::size_t get_size() { return(size); }
		std::size_t get_degree() { return(parent == nullptr ? child_count() : child_count()+1); }
		std::size_t child_count() { return(children.size()); }
		typename std::list<FaceTreeNode*>::iterator children_begin() { return(children.begin()); }
		typename std::list<FaceTreeNode*>::iterator children_end() { return(children.end()); }
		typename std::list<FaceTreeNode*>::iterator former_children_begin() { return(former_children.begin()); }
		typename std::list<FaceTreeNode*>::iterator former_children_end() { return(former_children.end()); }

		void add_child(FaceTreeNode* child) {
			children.push_back(child);
			former_children.push_back(child);
			child->parent = this;
			add_sizes_on_path_to_root(this, child->get_size());
		}
		
		std::unordered_set<FaceTreeNode*> disconnect() {
			std::unordered_set<FaceTreeNode*> result;
			add_sizes_on_path_to_root(this, -size);
			result.insert(children.begin(), children.end());
			if(parent != nullptr) {
				FaceTreeNode* root = this;
				while(root->parent != nullptr) {
					root = root->parent;
				}
				result.insert(root);
				parent->children.remove(this);
			}
			for(FaceTreeNode* child : children) { child->parent = nullptr; }
			return(result);
		}
		
		void get_subtree(std::unordered_set<FaceTreeNode*>& nodes) {
			nodes.insert(this);
			for(FaceTreeNode* child : children) { child->get_subtree(nodes); }
		}
		
		FaceTreeNode* get_subtree_center() {
			int r = size;
			std::map<FaceTreeNode*,std::size_t> center_degree;
			std::unordered_set<FaceTreeNode*> nodes;
			get_subtree(nodes);
			std::unordered_set<FaceTreeNode*> s;
			for(FaceTreeNode* node : nodes) {
				center_degree[node] = node->get_degree();
				if(center_degree[node] <= 1) {
					s.insert(node);
					r--;
				}
			}
			while(r > 0) {
				std::unordered_set<FaceTreeNode*> t;
				for(FaceTreeNode* node : s) {
					std::unordered_set<FaceTreeNode*> neighbours;
					neighbours.insert(node->children.begin(), node->children.end());
					if(node->parent != nullptr) { neighbours.insert(node->parent); }
					for(FaceTreeNode* neighbour : neighbours) {
						center_degree[neighbour]--;
						if(center_degree[neighbour] == 1) {
							t.insert(neighbour);
							r--;
						}
					}
				}
				s = t;
			}
			return(*(s.begin()));
		}
};

void compute_subpolygon_heuristic_triangulation(Graph& graph, std::function<void(Graph&)> initial_triangulation, double epsilon);
void compute_face_tree(FaceTreeNode* root, std::unordered_set<Face*>& triangles, std::unordered_set<Face*>& processed);
FaceTreeNode* compute_face_tree(std::unordered_set<Face*>& triangles);
void delete_face_tree_node(FaceTreeNode* node);
void get_boundary_vertices(FaceTreeNode* root, std::unordered_set<Vertex*>& result);
void get_separating_faces(FaceTreeNode* root, std::size_t maximum_size, std::vector<Vertex*>& boundary_vertices, std::unordered_set<Face*>& separating_faces, std::vector<std::vector<Vertex*>>& subpolygons);

void compute_subpolygon_heuristic_triangulation(Graph& graph, std::function<void(Graph&)> initial_triangulation, double epsilon) {
	std::vector<Vertex*> boundary;
	boundary.assign(graph.vertices_begin(), graph.vertices_end());

	std::unordered_set<Edge*> polygon_edges;
	polygon_edges.insert(graph.edges_begin(), graph.edges_end());

	initial_triangulation(graph);

	std::unordered_set<Face*> triangles;
	triangles.insert(graph.faces_begin(), graph.faces_end());
	FaceTreeNode* root = compute_face_tree(triangles);
	std::unordered_set<Face*> separating_faces;
	std::vector<std::vector<Vertex*>> subpolygons;
	get_separating_faces(root, (int)pow(graph.vertex_count(), epsilon), boundary, separating_faces, subpolygons);

	std::unordered_set<Edge*> to_remove;
	for(auto i = graph.edges_begin(); i != graph.edges_end(); i++) {
		if(polygon_edges.count(*i) == 0) { to_remove.insert(*i); }
	}

	for(Face* f : separating_faces) {
		for(auto i = f->edges_begin(); i != f->edges_end(); i++) {
			to_remove.erase(*i);
		}
	}

	for(Edge* e : to_remove) { graph.remove_edge(e); }
	delete_face_tree_node(root);
	
	for(std::vector<Vertex*> subpolygon : subpolygons) {
		compute_minimum_weight_triangulation_of_vertices(graph, subpolygon, weight_by_triangle_perimeter);
	}
}

void compute_face_tree(FaceTreeNode* root, std::unordered_set<Face*>& triangles, std::unordered_set<Face*>& processed) {
	processed.insert(root->get_face());
	for(auto i = root->get_face()->faces_begin(); i != root->get_face()->faces_end(); i++) {
		if((processed.count(*i) == 0) && (triangles.count(*i) > 0)) {
			FaceTreeNode* child = new FaceTreeNode(*i);
			root->add_child(child);
			compute_face_tree(child, triangles, processed);
		}
	}
}

FaceTreeNode* compute_face_tree(std::unordered_set<Face*>& triangles) {
	std::unordered_set<Face*> processed;
	FaceTreeNode* root = new FaceTreeNode(*(triangles.begin()));
	compute_face_tree(root, triangles, processed);
	return(root);
}

void delete_face_tree_node(FaceTreeNode* node) {
	for(auto i = node->former_children_begin(); i != node->former_children_end(); i++) {
		delete_face_tree_node(*i);
	}
	delete node;
}

void get_boundary_vertices(FaceTreeNode* root, std::unordered_set<Vertex*>& result) {
	result.insert(root->get_face()->vertices_begin(), root->get_face()->vertices_end());
	for(auto i = root->children_begin(); i != root->children_end(); i++) {
		get_boundary_vertices(*i, result);
	}
}

void get_separating_faces(FaceTreeNode* root, std::size_t maximum_size, std::vector<Vertex*>& boundary_vertices, std::unordered_set<Face*>& separating_faces, std::vector<std::vector<Vertex*>>& subpolygons) {
	std::unordered_set<FaceTreeNode*> roots;
	roots.insert(root);
	
	bool reset = false;
	for(auto i = roots.begin(); i != roots.end(); reset ? i=roots.begin() : i++) {
		reset = false;
		FaceTreeNode* current = *i;
		if(current->get_size() > maximum_size) {
			roots.erase(current);
			FaceTreeNode* center = current->get_subtree_center();
			separating_faces.insert(center->get_face());
			std::unordered_set<FaceTreeNode*> new_roots = center->disconnect();
			roots.insert(new_roots.begin(), new_roots.end());
			reset = true;
		}
	}
	
	for(FaceTreeNode* root : roots) {
		std::vector<Vertex*> subpolygon;
		std::unordered_set<Vertex*> subpolygon_vertices;
		get_boundary_vertices(root, subpolygon_vertices);
		for(Vertex* v : boundary_vertices) {
			if(subpolygon_vertices.count(v) > 0) { subpolygon.push_back(v); }
		}
		subpolygons.push_back(subpolygon);
	}
}
