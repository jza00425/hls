#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class Node
{
	int index;
	int area;
	int delay;
};

class Graph
{
	int n;
	vector<int> opt;
	vector< vector<int> > adj;
	vector< vector<int> > adj_rv;
public:
	Graph(int n);
	void addEdge(int u, int v);
	void longestPath(int v);
	void printGraph();
};

Graph::Graph(int n) : n(n), adj(n), adj_rv(n) {}

void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v);
	adj_rv[v].push_back(u);
}

void Graph::printGraph()
{
	vector<vector<int>>::iterator it;
	for(it = adj.begin(); it < adj.end(); it++){
		for(auto a : *it) {
			cout << a << " ";
		}
		cout << endl;
	}
}

int main()
{
	Graph g(3);	
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(0,2);
	g.printGraph();
}













