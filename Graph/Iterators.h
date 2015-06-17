#ifndef __ITERATORS_H__
#define __ITERATORS_H__

#include <iterator>
#include <vector>
#include "Graph.h"

class VertexIterator : public std::iterator<std::forward_iterator_tag, Vertex*> {
	friend class Graph;
	std::vector<Vertex*>::iterator container_iterator;
	VertexIterator(std::vector<Vertex*>::iterator _container_iterator);

	public:
		VertexIterator();
		VertexIterator(const VertexIterator& i);
		const VertexIterator& operator=(const VertexIterator& i);
		VertexIterator& operator++();
		VertexIterator operator++(int);
		bool operator==(const VertexIterator& rhs) const;
		bool operator!=(const VertexIterator& rhs) const;
		Vertex* operator*() const;
};

class VertexVertexIterator : public std::iterator<std::forward_iterator_tag, Vertex*> {
	friend class Vertex;
	HalfEdge* initial;
	HalfEdge* current;
	VertexVertexIterator(Vertex* v);

	public:
		VertexVertexIterator();
		VertexVertexIterator(const VertexVertexIterator& i);
		const VertexVertexIterator& operator=(const VertexVertexIterator& i);
		VertexVertexIterator& operator++();
		VertexVertexIterator operator++(int);
		bool operator==(const VertexVertexIterator& rhs) const;
		bool operator!=(const VertexVertexIterator& rhs) const;
		Vertex* operator*() const;
};

class VertexEdgeIterator : public std::iterator<std::forward_iterator_tag, Edge*> {
	friend class Vertex;
	HalfEdge* initial;
	HalfEdge* current;
	VertexEdgeIterator(Vertex* v);

	public:
		VertexEdgeIterator();
		VertexEdgeIterator(const VertexEdgeIterator& i);
		const VertexEdgeIterator& operator=(const VertexEdgeIterator& i);
		VertexEdgeIterator& operator++();
		VertexEdgeIterator operator++(int);
		bool operator==(const VertexEdgeIterator& rhs) const;
		bool operator!=(const VertexEdgeIterator& rhs) const;
		Edge* operator*() const;
};

class VertexFaceIterator : public std::iterator<std::forward_iterator_tag, Face*> {
	friend class Vertex;
	HalfEdge* initial;
	HalfEdge* current;
	VertexFaceIterator(Vertex* v);

	public:
		VertexFaceIterator();
		VertexFaceIterator(const VertexFaceIterator& i);
		const VertexFaceIterator& operator=(const VertexFaceIterator& i);
		VertexFaceIterator& operator++();
		VertexFaceIterator operator++(int);
		bool operator==(const VertexFaceIterator& rhs) const;
		bool operator!=(const VertexFaceIterator& rhs) const;
		Face* operator*() const;
};

class EdgeIterator : public std::iterator<std::forward_iterator_tag, Edge*> {
	friend class Graph;
	std::vector<Edge*>::iterator container_iterator;
	EdgeIterator(std::vector<Edge*>::iterator _container_iterator);

	public:
		EdgeIterator();
		EdgeIterator(const EdgeIterator& i);
		const EdgeIterator& operator=(const EdgeIterator& i);
		EdgeIterator& operator++();
		EdgeIterator operator++(int);
		bool operator==(const EdgeIterator& rhs) const;
		bool operator!=(const EdgeIterator& rhs) const;
		Edge* operator*() const;
};

class EdgeVertexIterator : public std::iterator<std::forward_iterator_tag, Vertex*> {
	friend class Edge;
	HalfEdge* initial;
	HalfEdge* current;
	EdgeVertexIterator(Edge* e);

	public:
		EdgeVertexIterator();
		EdgeVertexIterator(const EdgeVertexIterator& i);
		const EdgeVertexIterator& operator=(const EdgeVertexIterator& i);
		EdgeVertexIterator& operator++();
		EdgeVertexIterator operator++(int);
		bool operator==(const EdgeVertexIterator& rhs) const;
		bool operator!=(const EdgeVertexIterator& rhs) const;
		Vertex* operator*() const;
};

class EdgeEdgeIterator : public std::iterator<std::forward_iterator_tag, Edge*> {
	friend class Edge;
	HalfEdge* initial;
	HalfEdge* current;
	EdgeEdgeIterator(Edge* e);

	public:
		EdgeEdgeIterator();
		EdgeEdgeIterator(const EdgeEdgeIterator& i);
		const EdgeEdgeIterator& operator=(const EdgeEdgeIterator& i);
		EdgeEdgeIterator& operator++();
		EdgeEdgeIterator operator++(int);
		bool operator==(const EdgeEdgeIterator& rhs) const;
		bool operator!=(const EdgeEdgeIterator& rhs) const;
		Edge* operator*() const;
};

class EdgeFaceIterator : public std::iterator<std::forward_iterator_tag, Face*> {
	friend class Edge;
	HalfEdge* initial;
	HalfEdge* current;
	EdgeFaceIterator(Edge* e);

	public:
		EdgeFaceIterator();
		EdgeFaceIterator(const EdgeFaceIterator& i);
		const EdgeFaceIterator& operator=(const EdgeFaceIterator& i);
		EdgeFaceIterator& operator++();
		EdgeFaceIterator operator++(int);
		bool operator==(const EdgeFaceIterator& rhs) const;
		bool operator!=(const EdgeFaceIterator& rhs) const;
		Face* operator*() const;
};

class FaceIterator : public std::iterator<std::forward_iterator_tag, Face*> {
	friend class Graph;
	std::vector<Face*>::iterator container_iterator;
	FaceIterator(std::vector<Face*>::iterator _container_iterator);

	public:
		FaceIterator();
		FaceIterator(const FaceIterator& i);
		const FaceIterator& operator=(const FaceIterator& i);
		FaceIterator& operator++();
		FaceIterator operator++(int);
		bool operator==(const FaceIterator& rhs) const;
		bool operator!=(const FaceIterator& rhs) const;
		Face* operator*() const;
};

class FaceVertexIterator : public std::iterator<std::forward_iterator_tag, Vertex*> {
	friend class Face;
	HalfEdge* initial;
	HalfEdge* current;
	FaceVertexIterator(Face* f);

	public:
		FaceVertexIterator();
		FaceVertexIterator(const FaceVertexIterator& i);
		const FaceVertexIterator& operator=(const FaceVertexIterator& i);
		FaceVertexIterator& operator++();
		FaceVertexIterator operator++(int);
		bool operator==(const FaceVertexIterator& rhs) const;
		bool operator!=(const FaceVertexIterator& rhs) const;
		Vertex* operator*() const;
};

class FaceEdgeIterator : public std::iterator<std::forward_iterator_tag, Edge*> {
	friend class Face;
	HalfEdge* initial;
	HalfEdge* current;
	FaceEdgeIterator(Face* f);

	public:
		FaceEdgeIterator();
		FaceEdgeIterator(const FaceEdgeIterator& i);
		const FaceEdgeIterator& operator=(const FaceEdgeIterator& i);
		FaceEdgeIterator& operator++();
		FaceEdgeIterator operator++(int);
		bool operator==(const FaceEdgeIterator& rhs) const;
		bool operator!=(const FaceEdgeIterator& rhs) const;
		Edge* operator*() const;
};

class FaceFaceIterator : public std::iterator<std::forward_iterator_tag, Face*> {
	friend class Face;
	HalfEdge* initial;
	HalfEdge* current;
	FaceFaceIterator(Face* f);

	public:
		FaceFaceIterator();
		FaceFaceIterator(const FaceFaceIterator& i);
		const FaceFaceIterator& operator=(const FaceFaceIterator& i);
		FaceFaceIterator& operator++();
		FaceFaceIterator operator++(int);
		bool operator==(const FaceFaceIterator& rhs) const;
		bool operator!=(const FaceFaceIterator& rhs) const;
		Face* operator*() const;
};

#endif
