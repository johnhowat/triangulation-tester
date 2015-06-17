#ifndef __EDGE_H__
#define __EDGE_H__

#include <iostream>
#include "Graph.h"

class Edge {
	friend class Graph;
	friend class Vertex;
	friend class HalfEdge;
	friend class Face;
	friend class VertexIterator; friend class VertexVertexIterator; friend class VertexEdgeIterator; friend class VertexFaceIterator;
	friend class EdgeIterator; friend class EdgeVertexIterator; friend class EdgeEdgeIterator; friend class EdgeFaceIterator;
	friend class FaceIterator; friend class FaceVertexIterator; friend class FaceEdgeIterator; friend class FaceFaceIterator;

	HalfEdge* half_edge;

	public:
		Vertex* u() const;
		Vertex* v() const;
		double length() const;
		EdgeVertexIterator vertices_begin();
		EdgeVertexIterator vertices_end();
		EdgeEdgeIterator edges_begin();
		EdgeEdgeIterator edges_end();
		EdgeFaceIterator faces_begin();
		EdgeFaceIterator faces_end();

	private:
		Edge(HalfEdge* _half_edge);
};

std::ostream& operator<<(std::ostream& stream, Edge& edge);

#endif
