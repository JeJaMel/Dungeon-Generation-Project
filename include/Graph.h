#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include "Chamber.h"

/*
std::list is used to create an adjacency list for the graph.
Each element in the list represents a node that is connected to the node
represented by the index of the list.
*/

class Graph
{
private:
    int numVertices;      
    std::list<int> *adjList;

public:
    // Constructor
    Graph(int numVertices) : numVertices(numVertices)
    {
        adjList = new std::list<int>[numVertices];
    }

    // Destructor
    ~Graph()
    {
        delete[] adjList;
    }

    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    const std::list<int> &getAdjacentVertices(int vertex) const
    {
        return adjList[vertex];
    }
};

#endif