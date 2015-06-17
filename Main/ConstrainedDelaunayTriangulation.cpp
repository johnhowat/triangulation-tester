#include <cstdlib>
#include <vector>
#include "Graph/Graph.h"
#include "Triangulations.h"
#include "triangle/triangle.h"

void compute_constrained_delaunay_triangulation(Graph& graph) {
	std::vector<Vertex*> vertices;
	vertices.assign(graph.vertices_begin(), graph.vertices_end());
	
	struct triangulateio in, out;
	in.numberofpoints = vertices.size();
	in.numberofpointattributes = 0;
	in.pointlist = (double*)malloc(in.numberofpoints * 2 * sizeof(double));
	for(std::size_t i = 0; i < vertices.size(); i++) {
		in.pointlist[2*i] = vertices[i]->x();
		in.pointlist[2*i + 1] = vertices[i]->y();
	}

	in.pointmarkerlist = NULL;
	in.numberofsegments = vertices.size();
	in.segmentmarkerlist = NULL;
	in.segmentlist = (int*)malloc(in.numberofpoints * 2 * sizeof(int));
	for(std::size_t i = 0; i < vertices.size(); i++) {
		in.segmentlist[2*i] = i;
		in.segmentlist[2*i + 1] = (i+1) % vertices.size();
	}
	in.numberofholes = 0;
	in.numberofregions = 0;
	in.regionlist = NULL;

  	out.pointlist = (double*) NULL;
  	out.pointmarkerlist = (int*) NULL;
  	out.trianglelist = (int *) NULL;
	out.segmentlist = (int *) NULL;
	out.segmentmarkerlist = (int *) NULL;
	out.edgelist = (int *) NULL;
	out.edgemarkerlist = (int *) NULL;

	triangulate((char*)"Qepz", &in, &out, NULL);

	for(int i = 0; i < out.numberofedges; i++) {
		graph.add_edge(vertices[out.edgelist[2*i]], vertices[out.edgelist[2*i+1]]);
	}

	free(in.pointlist);
	free(in.segmentlist);
	free(out.pointlist);
	free(out.pointmarkerlist);
	free(out.trianglelist);
	free(out.segmentlist);
	free(out.segmentmarkerlist);
	free(out.edgelist);
	free(out.edgemarkerlist);
}
