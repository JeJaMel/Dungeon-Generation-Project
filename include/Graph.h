#ifndef GRAPH_H
#define GRAPH_H

#include "Chamber.h"

#include <list>
#include <random>
#include <algorithm>
#include <queue>
#include <iostream>

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
                if (getChamber(i).getConnections().size() >= 3)
                {
                    break; // Skip to next chamber if this one already has 3 connections
                }

                int connectedChamber;
                do
                {
                    connectedChamber = dis(gen);
                } while (connectedChamber == i || connectedChamber == key || std::find(getChamber(i).getConnections().begin(), getChamber(i).getConnections().end(), connectedChamber) != getChamber(i).getConnections().end());

                if (getChamber(connectedChamber).getConnections().size() < 3)
                {
                    addEdge(i, connectedChamber);
                }
            }
        }

        // Ensure key chamber has at least two connections
        while (getChamber(key).getConnections().size() < 2)
        {
            int connectedChamber;
            do
            {
                connectedChamber = dis(gen);
            } while (connectedChamber == key || connectedChamber == exit || std::find(getChamber(key).getConnections().begin(), getChamber(key).getConnections().end(), connectedChamber) != getChamber(key).getConnections().end());

            if (getChamber(connectedChamber).getConnections().size() < 3)
            {
                addEdge(key, connectedChamber);
            }
        }
    }
    
    int *findShortestPath(int start, int end)
    {
        bool *visited = new bool[numVertices];
        int *prev = new int[numVertices];
        std::queue<int> q;

        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false;
            prev[i] = -1;
        }

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            if (current == end)
            {
                break;
            }

            for (int neighbor : getChamber(current).getConnections())
            {
                if (!visited[neighbor])
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    prev[neighbor] = current;
                }
            }
        }

        int *path = new int[numVertices];
        int at = end;
        int length = 0;
        while (at != -1)
        {
            path[length] = at;
            at = prev[at];
            length++;
        }

        for (int i = 0; i < length / 2; i++)
        {
            int temp = path[i];
            path[i] = path[length - i - 1];
            path[length - i - 1] = temp;
        }

        delete[] visited;
        delete[] prev;

        return path;
    }
};

#endif