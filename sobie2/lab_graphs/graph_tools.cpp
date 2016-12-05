/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

using namespace std;

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Edge> edges = graph.getEdges();
    vector<Vertex> vertices = graph.getVertices();
    queue<Vertex> q;

    for (size_t i=0; i<edges.size(); i++)
	graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    for (size_t i=0; i<vertices.size(); i++)
	graph.setVertexLabel(vertices[i], "UNEXPLORED");

    Vertex start = graph.getStartingVertex();
    vector<Vertex> adj = graph.getAdjacent(start);
    int min = graph.getEdgeWeight(start, adj[0]);
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Vertex x_min = start;
    Vertex y_min = adj[0];

    while (!q.empty()) {
	Vertex v = q.front();
	adj = graph.getAdjacent(v);
	q.pop();	
	for (size_t i=0; i<adj.size(); i++) {
	   if (graph.getEdgeWeight(v, adj[i]) < min) {
		min = graph.getEdgeWeight(v, adj[i]);
	   	x_min = v;
		y_min = adj[i];
	   }
	   if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
		graph.setVertexLabel(adj[i], "VISITED");
		graph.setEdgeLabel(v, adj[i], "DISCOVERY");
		q.push(adj[i]);
	   }		
	   else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED")
		graph.setEdgeLabel(v, adj[i], "CROSS");
	}
    }


    graph.setEdgeLabel(x_min, y_min, "MIN");

    return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */

    vector<Edge> edges = graph.getEdges();
    vector<Vertex> vertices = graph.getVertices();
    queue<Vertex> q;

    for (size_t i=0; i<edges.size(); i++)
	graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    for (size_t i=0; i<vertices.size(); i++)
	graph.setVertexLabel(vertices[i], "UNEXPLORED");

    unordered_map<Vertex, Vertex> vertexMap;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);

    while (!q.empty()) {
	Vertex v = q.front();
	vector<Vertex> adj = graph.getAdjacent(v);
	q.pop();	
	for (size_t i=0; i<adj.size(); i++) {
	   if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
		graph.setVertexLabel(adj[i], "VISITED");
		graph.setEdgeLabel(v, adj[i], "DISCOVERY");
		q.push(adj[i]);
		vertexMap[adj[i]] = v;
	   }		
	   else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED")
		graph.setEdgeLabel(v, adj[i], "CROSS");
	}
    }

    int shortest = 0;
    Vertex endTemp = end;

    while (endTemp != start) {
	graph.setEdgeLabel(vertexMap[endTemp], endTemp, "MINPATH");
	shortest++;
	endTemp = vertexMap[endTemp];
    }

    

    return shortest;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */

    vector<Edge> edges = graph.getEdges();
    vector<Vertex> vertices = graph.getVertices();
    sort(edges.begin(), edges.end(), compare);
    DisjointSets temp;
    temp.addelements(vertices.size());

    int maxEdges = vertices.size() - 1;
    int currEdges = 0;

    for (size_t i=0; i<edges.size(); i++) {

	Vertex u = edges[i].source;
	Vertex v = edges[i].dest;

	if (temp.find(u) != temp.find(v)) {
	   temp.setunion(u, v);
	   graph.setEdgeLabel(u, v, "MST");
	   currEdges++;
	}

 	if (currEdges >= maxEdges)
	   break;
    }
	
}

bool GraphTools::compare(Edge a, Edge b)
{
    return a.weight < b.weight;

}
