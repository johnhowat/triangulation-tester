#ifndef __HALFEDGE_H__
#define __HALFEDGE_H__

#include "Graph.h"

class HalfEdge {
	friend class Graph;
	friend class Vertex;
	friend class Edge;
	friend class Face;
	friend class VertexIterator; friend class VertexVertexIterator; friend class VertexEdgeIterator; friend class VertexFaceIterator;
	friend class EdgeIterator; friend class EdgeVertexIterator; friend class EdgeEdgeIterator; friend class EdgeFaceIterator;
	friend class FaceIterator; friend class FaceVertexIterator; friend class FaceEdgeIterator; friend class FaceFaceIterator;

	Edge* edge;
	Vertex* origin;
	HalfEdge* twin;
	HalfEdge* next;
	Face* face;

	public:

	private:
		HalfEdge();
		HalfEdge* previous_half_edge() const;
};

#endif
