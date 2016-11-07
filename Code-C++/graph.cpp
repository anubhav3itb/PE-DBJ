#include<iostream>
#include <list>
#include <stack>
#define NIL -1
#include "graph.h"

using namespace std;

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}


std::vector<int> Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[])
{

    static int time = 0;

    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;

    // Go through all vertices adjacent to this
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;  // v is current adjacent of 'u'

        // If v is not visited yet, then recur for it
        if (disc[v] == -1)
        {
            SCCUtil(v, disc, low, st, stackMember);


            low[u]  = min(low[u], low[v]);
        }


        else if (stackMember[v] == true)
            low[u]  = min(low[u], disc[v]);
    }


    int w = 0;  // To store stack extracted vertices
    std::vector<int> temp;
    if (low[u] == disc[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();
            //cout << "tests 1" << endl;
            //cout << w << " ";
            temp.push_back(w);
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        temp.push_back(w);
        //cout << w << "\n";
        stackMember[w] = false;
        st->pop();
    }
    return temp;
}

// The function to do DFS traversal. It uses SCCUtil()
std::vector<std::vector<int> > Graph::SCC()
{
    int *disc = new int[V];
    int *low = new int[V];
    bool *stackMember = new bool[V];
    stack<int> *st = new stack<int>();

    // Initialize disc and low, and stackMember arrays
    for (int i = 0; i < V; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }
    std::vector<std::vector<int> > out;

    for (int i = 0; i < V; i++)
        if (disc[i] == NIL)
            out.push_back(SCCUtil(i, disc, low, st, stackMember));
    return out;
}

