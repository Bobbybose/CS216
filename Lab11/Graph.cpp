/*
 * File: Graph.cpp
 * Course: CS216
 * Project: Lab11
 */


#include <map>
#include <set>
#include <queue>
#include "Graph.h"

using namespace std;


//default constructor
Graph::Graph() {
}


// to check if an edge exists between v and w 
bool Graph::hasEdge(char v, char w) {

    //Cycling through all the vertices in the Graph
	for (auto i = adjMap.begin(); i != adjMap.end(); i++) {
		if (i->first == v) {    //If this is the right vertex
			if (i->second.find(w) != i->second.end())   //If w is in the list of edges
				return true;
		}
	}

	return false;


}

// to add an edge beween v and w to the graph
void Graph::addEdge(char v, char w) {
	adjMap[v];      //Making sure vertex v is in the Graph
    adjMap[w];      //Making sure vertex w is in the Graph
    
    //Cycling through the vertices
    for (auto i = adjMap.begin(); i != adjMap.end(); i++) {
		if (i->first == v)              //If i is at vertex v
			i->second.insert(w);            //Add w to the list of edges
		if (i->first == w)              //If i is at vertex w
			i->second.insert(v);            //Add v to the list of edges
	}

}


// Apply BFS traversal to find the shortest path from the given source s to destination t
// return the distnace from s to t
// if there is no path from s to t, return -1
// store the shortest path distance from the given source s  to vertex w in distance map<w,     distance>
// store which next vertex to go through on the shortest path to the given source s in          go_through map<w, v>.
// Here a pair <w, v> in go_through map represents on the shortest path from w to the given     source s, it needs to take the path: w-->v...-->s
int Graph::BFS(char s, char t, map<char, int>& distance, map<char, char>& go_through) {
	//Cycling through the vertexs 
    for (auto i = adjMap.begin(); i != adjMap.end(); i++) {
		distance[i->first] = NOPATH;    //Setting all their distances to NOPATH (-1)
	}

	queue<char> verticies;          //Queue to hold vertices we're looking at

    distance[s] = 0;                //Assuming the distance is 0 by default

	go_through[s] = s;              //Assuming the only way to s is through s

	verticies.push(s);              //Pushing the source onto the queue first

	char current = s;               //Start at the source for the search algorithm

    //Until there's no more vertices to look at, or we're currently looking at the target
	while (!verticies.empty() && current != t) {
		current = verticies.front();        //Popping the first thing from then queue
		verticies.pop();

        //Cycling through the current vertex's edges
		for (auto w = adjMap.at(current).begin(); w != adjMap.at(current).end(); w++) {
			if (distance.at(*w) == -1) {    //If distance at the current vertex is -1 (default)
                //Make the distance one larger than the current vertex's
                distance[*w] = distance[current] +1;
                
                //You have to go through the current edge path to get to the source
                go_through[*w] = current;   

                //Add the vertex connected by the current edge to the queue
                verticies.push(*w);
			}
		}
	}

    //Returning the distance to the target
	return distance.at(t);

}

//private:
//represent the mapping from a Vertex, say u (key) to a set of vertices (value) which           directly connect to u
//    map<char, set<char> > adjMap;
