#include <queue>
#include <vector>
#include <iostream>
#include <limits>
#include <assert.h>
#include <random>
#include <cmath>

using namespace std;

enum Adder {adder1 = 0, adder2, adder3};
enum Multiplier {mult1 = 0, mult2, mult3, mult4};
enum Shifter {sht1 = 0, sht2, sht3};

class Node
{
protected:
	int cnt;
	int area;
	int delay;
	int typeNum;
public:
	void resetCnt() {
		cnt = 0;
	}
	int getTypeNum() {
		return typeNum;
	}
	void setNode(int area, int delay);
	int getArea() {
		return area;
	}
	int getDelay() {
		return delay;
	}

};

class Add: public Node
{

public:
	Add(int cnt) {
		this->cnt = cnt;
		setNode(adder1);
		typeNum = 3;
	}
	void setNode(Adder i) {
		switch(i) {
			case adder1:
				this->area = 4;
				this->delay = 1;
				break;
			case adder2:
				this->area = 2;
				this->delay = 2;
				break;
			case adder3:
				this->area = 1;
				this->delay = 3;
				break;
			default:
				assert("invalid adder");
				break;
		}
	}
};

class Shift: public Node
{
public:
	Shift(int cnt) {
		this->cnt = cnt;
		typeNum = 3;
		setNode(sht1);
	}
	void setNode(Shifter i) {
		switch(i) {
			case sht1:
				this->area = 3;
				this->delay = 1;
				break;
			case sht2:
				this->area = 2;
				this->delay = 2;
				break;
			case sht3:
				this->area = 1;
				this->delay = 3;
				break;
			default:
				assert("invalid shifter");
				break;
		}
	}
};

class Mult: public Node
{
public:
	Mult(int cnt) {
		this->cnt = cnt;
		setNode(mult1);
		typeNum = 4;
	}
	void setNode(Multiplier i) {
		switch(i) {
			case mult1:
				this->area = 5;
				this->delay = 1;
				break;
			case mult2:
				this->area = 3;
				this->delay = 2;
				break;
			case mult3:
				this->area = 2;
				this->delay = 4;
				break;
			case mult4:
				this->area = 1;
				this->delay = 8;
			default:
				assert("invalid multiplier");
				break;
		}
	}
};

void Node::setNode (int area, int delay) {
	this->area = area;
	this->delay = delay;
}

class Graph
{
	int n;
	vector<Node> vertex;
	vector< vector<int> > adj;
	vector< vector<int> > adj_rv;
public:
	Graph(int n);
	void addEdge(int u, int v);
	int longestPath(int v);
	void printGraph();
	void addVertex(Node a);
	int totalArea();
	Node getNode(int i);
	void changeVertex(int v, Node a);
};

void Graph::changeVertex(int v, Node a)
{
	vertex[v] = a;
}

Node Graph::getNode(int i)
{
	return vertex[i];
}

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
void Graph::addVertex(Node a) {
	vertex.push_back(a);
}
int Graph::totalArea() {
	int ans = 0;
	for(auto i : vertex)
		ans = ans + i.getArea();
	return ans;
}
int Graph::longestPath(int v) {
	int maxDelay1 = 0;
	int maxDelay2 = 0;
	vector<int>dist1(n);
	priority_queue<pair<int, int>, vector<pair<int, int>>> pq1;
	pq1.push(make_pair(vertex[v].getDelay(), v));
	dist1[v] = vertex[v].getDelay();
	while(!pq1.empty()) {
		int a = pq1.top().second;
		pq1.pop();
		for(auto b : adj[a]) {
			if(dist1[b] < dist1[a] + vertex[b].getDelay()) {
				dist1[b] = dist1[a] + vertex[b].getDelay();
				pq1.push(make_pair(dist1[b], b));
				maxDelay1 = maxDelay1 < dist1[b] ? dist1[b] : maxDelay1;
			}
		}
	}

	vector<int>dist2(n);
	priority_queue<pair<int, int>, vector<pair<int, int>>> pq2;
	pq2.push(make_pair(0, v));
	while(!pq2.empty()) {
		int a = pq2.top().second;
		pq2.pop();
		for(auto b : adj_rv[a]) {
			if(dist2[b] < dist2[a] + vertex[b].getDelay()) {
				dist2[b] = dist2[a] + vertex[b].getDelay();
				pq2.push(make_pair(dist2[b], b));
				maxDelay2 = maxDelay2 < dist2[b] ? dist2[b] : maxDelay2;
			}
		}
	}
	return maxDelay1 + maxDelay2;
}


// int main()
// {
// 	Graph g(7);	
// 	Node a;
// 	a.setNode(3, 1);
// 	Node b;
// 	b.setNode(6, 2);
// 	Node c;
// 	c.setNode(1, 3);
// 	Node d;
// 	d.setNode(1, 3);
// 	Node e;
// 	e.setNode(1, 1);
// 	Node f;
// 	f.setNode(1, 5);
// 	Node h;
// 	h.setNode(1, 1);
// 	g.addVertex(a);
// 	g.addVertex(b);
// 	g.addVertex(c);
// 	g.addVertex(d);
// 	g.addVertex(e);
// 	g.addVertex(f);
// 	g.addVertex(h);
// 	g.addEdge(0,1);
// 	g.addEdge(1,2);
// 	g.addEdge(3,1);
// 	g.addEdge(3,4);
// 	g.addEdge(5,4);
// 	g.addEdge(5,6);
// 	g.addEdge(4,6);
// 	g.printGraph();
// 	cout << g.totalArea() << endl;
// 	cout << g.longestPath(4) << endl;
// 	return 1;
// }

// int main()
// {
// 	Graph g(7);	
// 	Add a(0);
// 	Shift b(0);
// 	Mult c(0);
// 	Add d(0);
// 	Add e(0);
// 	Mult f(0);
// 	Add h(0);
// 	g.addVertex(a);
// 	g.addVertex(b);
// 	g.addVertex(c);
// 	g.addVertex(d);
// 	g.addVertex(e);
// 	g.addVertex(f);
// 	g.addVertex(h);
// 	g.addEdge(0,1);
// 	g.addEdge(1,2);
// 	g.addEdge(3,1);
// 	g.addEdge(3,4);
// 	g.addEdge(5,4);
// 	g.addEdge(5,6);
// 	g.addEdge(4,6);
// 	g.printGraph();
// 	cout << g.totalArea() << endl;
// 	cout << g.longestPath(4) << endl;
// 	return 1;
// }

int main()
{
	int period = 8;
	int n = 7;
	Graph g(n);	
	Add a(0);
	Shift b(0);
	Mult c(0);
	Add d(0);
	Add e(0);
	Mult f(0);
	Add h(0);
	g.addVertex(a);
	g.addVertex(b);
	g.addVertex(c);
	g.addVertex(d);
	g.addVertex(e);
	g.addVertex(f);
	g.addVertex(h);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(3,1);
	g.addEdge(3,4);
	g.addEdge(5,4);
	g.addEdge(5,6);
	g.addEdge(4,6);
	g.printGraph();
	Node p = g.getNode(4);
	cout << g.totalArea() << endl;
	cout << g.longestPath(4) << endl;
	cout << p.getTypeNum() << endl;
	cout << g.getNode(4).getTypeNum() << endl;
	int totalArea = g.totalArea();
	double T = 800;
	bool frozen = false;
	while(!frozen) {
		currentArea = totalArea;
		for(int i = 0; i < n; i++) {
			Node k = g.getNode(i);
			Node tmp = k;
			for(int j = 0; j < k.getTypeNum(); j++) {
				localArea = totalArea;
				k.setNode(j);
				g.changeVertex(i, k);
				if(g.longestPath(i) > period) {
					g.changeVertex(i, tmp);
				} else {
					tmpArea = g.totalArea();
					double delta = tmpArea - localArea;
					if(delta > 0 && 
					   uniform_real_distribution<double> distribution(0.0,1.0) > exp(-delta/T)) {
						g.changeVertex(i, tmp);
					}
				}
			}
		}
		currentArea = g.totalArea();
		if(currentArea < totalArea) {
			totalArea = currentArea;
			T = 0.9 * T;
		} else {
			frozen = true;
		}
	}
	return 1;
}

