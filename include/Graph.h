#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include "Chamber.h"
#include <random>
#include <algorithm>

class Graph
{
private:
    int numVertices;      
    std::list<Chamber> *adjList;

public:
    // Constructor
    Graph(int numVertices) : numVertices(numVertices)
    {
        adjList = new std::list<Chamber>[numVertices];
    }

    // Destructor
    ~Graph()
    {
        delete[] adjList;
    }

    Chamber &getChamber(int index)
    {
        // Assuming each list in adjList contains one Chamber object
        return adjList[index].front();
    }

    void addEdge(int src, int dest)
    {
        Chamber &srcChamber = getChamber(src);
        Chamber &destChamber = getChamber(dest);

        srcChamber.addConnection(dest);
        destChamber.addConnection(src);
    }

    const std::list<Chamber> &getAdjacentVertices(int vertex) const
    {
        return adjList[vertex];
    }

    void generateDungeon(int numChambers)
    {
        // Create the chambers
        for (int i = 0; i < numChambers; i++)
        {
            Chamber chamber;
            adjList[i].push_back(chamber);
        }

        // Randomly choose the start chamber, exit chamber, and chamber with the key
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, numChambers - 1);

        int start = dis(gen);
        int exit;
        int key;

        do
        {
            exit = dis(gen);
        } while (exit == start);

        do
        {
            key = dis(gen);
        } while (key == start || key == exit);

        getChamber(start).setIsStart(true);
        getChamber(exit).setIsExit(true);
        getChamber(key).setHasKey(true);

        // Randomly add connections between chambers
        std::uniform_int_distribution<> dis1(1, 3); // for number of connections
        for (int i = 0; i < numChambers; i++)
        {
            int numConnections = dis1(gen);
            for (int j = 0; j < numConnections; j++)
            {
                int connectedChamber;
                do
                {
                    connectedChamber = dis(gen);
                } while (connectedChamber == i || std::find(getChamber(i).getConnections().begin(), getChamber(i).getConnections().end(), connectedChamber) != getChamber(i).getConnections().end());
                addEdge(i, connectedChamber);
            }
        }
    }
};

#endif