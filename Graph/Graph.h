#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <fstream>
#include <string>
#include <vector>

class Vertex;
class HalfEdge;
class Edge;
class Face;
class VertexIterator;
class VertexVertexIterator;
class VertexEdgeIterator;
class VertexFaceIterator;
class EdgeIterator; 
class EdgeVertexIterator;
class EdgeEdgeIterator;
class EdgeFaceIterator;
class FaceIterator;
class FaceVertexIterator;
class FaceEdgeIterator;
class FaceFaceIterator;

#include "Vertex.h"
#include "HalfEdge.h"
#include "Edge.h"
#include "Face.h"
#include "Iterators.h"

class Graph {
	std::vector<Vertex*> vertices;
	std::vector<HalfEdge*> half_edges;
	std::vector<Edge*> edges;
	std::vector<Face*> faces;

	public:
		Graph();
		Graph(const std::string& filename);
		Graph(std::ifstream& filestream);
		~Graph();

		bool is_legal_edge(Vertex* u, Vertex* v) const;
		Edge* add_edge(Vertex* u, Vertex* v);

		void remove_edge(Edge* e);
		void remove_edge(Vertex* u, Vertex* v);

		std::size_t vertex_count() const;
		std::size_t edge_count() const;
		std::size_t face_count() const;
		
		// these should probably be random access iterators!
		VertexIterator vertices_begin(); 
		VertexIterator vertices_end();
		EdgeIterator edges_begin();
		EdgeIterator edges_end();
		FaceIterator faces_begin();
		FaceIterator faces_end();
		
		void save_image(const std::string& filename) const;

	private:
		void from_ifstream(std::ifstream& filestream);
		
		enum orientation { Left, Right, Collinear };
		bool intersects(Vertex* a, Vertex* b, Vertex* c, Vertex* d) const;
		orientation direction(Vertex* a, Vertex* b, Vertex* c) const;
		bool on_segment(Vertex* a, Vertex* b, Vertex* c) const;
		 
		Face* reference_face(Vertex* u, Vertex* v) const;
		HalfEdge* previous_half_edge(Vertex* v, Face* f) const;
		HalfEdge* previous_half_edge(HalfEdge* e) const;
};

#endif
