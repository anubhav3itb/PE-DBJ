#include<iostream>
#include <list>
#include <stack>
#include <vector>
#define NIL -1

using namespace std;


// A class that represents an directed graph
class Graph
{
    int V;    // No. of vertices
    list<int> *adj; // A dynamic array of adjacency lists

    // A Recursive DFS based function used by SCC()
    std::vector<int> SCCUtil(int u, int disc[], int low[],
  	stack<int> *st, bool stackMember[]);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    std::vector<std::vector<int> > SCC(); // prints strongly connected components
};
