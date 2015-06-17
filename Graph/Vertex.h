#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <iostream>
#include "Graph.h"

class Vertex {
	friend class Graph;
	friend class HalfEdge;
	friend class Edge;
	friend class Face;
	friend class VertexIterator; friend class VertexVertexIterator; friend class VertexEdgeIterator; friend class VertexFaceIterator;
	friend class EdgeIterator; friend class EdgeVertexIterator; friend class EdgeEdgeIterator; friend class EdgeFaceIterator;
	friend class FaceIterator; friend class FaceVertexIterator; friend class FaceEdgeIterator; friend class FaceFaceIterator;

	double x_coordinate;
	double y_coordinate;
	HalfEdge* leaving;

	public:
		double x() const;
		double y() const;
		Edge* get_edge_to(Vertex* v) const;
		bool is_adjacent(Vertex* v) const;


		VertexVertexIterator vertices_begin();
		VertexVertexIterator vertices_end();
		VertexEdgeIterator edges_begin();
		VertexEdgeIterator edges_end();
		VertexFaceIterator faces_begin();
		VertexFaceIterator faces_end();

	private:
		Vertex(double _x_coordinate, double _y_coordinate);
};

std::ostream& operator<<(std::ostream& stream, Vertex& v);

#endif
