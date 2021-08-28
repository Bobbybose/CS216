/*
 * Name: Bobby Bose
 * File: Graph.cpp
 * Course: CS216-007
 * Project: Project 3
 * Purpose: Provide the implementation of Graph class, which is a template class
 */
#ifndef Graph_cpp
#define Graph_cpp



#include <iostream>
#include <queue>
#include "Graph.h"

// default constructor
template <class T>
Graph<T>::Graph()
{
}

// check if an edge exists between v and w
template <class T>
bool Graph<T>::hasEdge(T v, T w) const
{
    //If vertex v is invalid
    if (adjMap.find(v) == adjMap.end())
        //Return false
        return false;
    //If w is in v's list of edges
    if (adjMap.at(v).find(w) != adjMap.at(v).end())
        //Return true    
        return true;
    else
        //Otherwise return false
        return false;
}

// add an edge between v and w to the graph
// note that it is an undirected graph
template <class T>
void Graph<T>::addEdge(T v, T w)
{
    //Adding w to v's list of edges
    adjMap[v].insert(w);

    //Adding v to w's list of edges
    adjMap[w].insert(v);
}

// Apply BFS traversal to find the shortest path from the given source s to destination t
// return the distnace from s to t
// if there is no path from s to t, return -1
// store the shortest path distance from the given source s  to vertex w in distance map<w, distance>
// store which next vertex to go through on the shortest path to the given source s in go_through map<w, v>. 
// Here a pair <w, v> in go_through map represents on the shortest path from w to the given source s, it needs to take the path: w-->v...-->s  
template <class T>
int Graph<T>::BFS(T s, T t, map<T, int>& distance, map<T, T>& go_through) const
{
    //If either vertex isn't in the map
    if ( adjMap.find(s) == adjMap.end() || adjMap.find(t) == adjMap.end())
    {
        //Notifying the user and return
        cout << "Invalid source Vertex or/and destination Vertex!" << endl;
        return INVALID_VERTEX;
    }

    // Mark all the vertices with current distance to s: -1
    for (auto it = adjMap.begin(); it != adjMap.end(); it++)
    {
        distance[it->first] = NOPATH;
    }

    // Create a queue for BFS
    queue<T> bfs;

    // Enqueue the source s
    bfs.push(s);
    // Mark the distance from the source s to s: 0
    distance[s] = 0;
    // Mark the shortest path to the given source s going through s
    go_through[s] = s;

    T current = bfs.front();
    while(!bfs.empty() && current != t)
    {
        current = bfs.front();
        // Get all adjacent vertices of current Vertex
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        set<T> adjVertices = adjMap.at(current);
        for(auto i  = adjVertices.begin(); i != adjVertices.end(); i++)
        {
            if(distance[*i] == NOPATH)
            {
                distance[*i] = distance[current]+1;
                go_through[*i] = current;
                bfs.push(*i);
            }
        }
        bfs.pop();
    }
    return distance[t];
}

#endif
