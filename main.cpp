#include <queue>
#include <vector>
#include <iostream>
#include <limits>
#include <assert.h>
#include <random>
#include <cmath>
#include <fstream>
#define NUMOFTRIALS 2000

using namespace std;

// enum Adder {adder1 = 0, adder2, adder3};
// enum Multiplier {mult1 = 0, mult2, mult3, mult4};
// enum Shifter {sht1 = 0, sht2, sht3};

class Node
{
protected:
	int optType;
	int area;
	int delay;
	int typeNum;
public:
	int getTypeNum() {
		return typeNum;
	}
	virtual void setNode(int a) = 0;
	int getArea() {
		return area;
	}
	int getDelay() {
		return delay;
	}
	int getOptType() {
		return optType;
	}
};

class Add: public Node
{

public:
	Add(int optType) {
		this->optType = optType;
		setNode(optType);
		typeNum = 3;
	}
	void setNode(int i) {
		switch(i) {
			case 0:
				this->area = 4;
				this->delay = 1;
				this->optType = 0;
				break;
			case 1:
				this->area = 2;
				this->delay = 2;
				this->optType = 1;
				break;
			case 2:
				this->area = 1;
				this->delay = 3;
				this->optType = 2;
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
	Shift(int optType) {
		this->optType = optType;
		typeNum = 3;
		setNode(optType);
	}
	void setNode(int i) {
		switch(i) {
			case 0:
				this->area = 3;
				this->delay = 1;
				this->optType = 0;
				break;
			case 1:
				this->area = 2;
				this->delay = 2;
				this->optType = 1;
				break;
			case 2:
				this->area = 1;
				this->delay = 3;
				this->optType = 2;
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
	Mult(int optType) {
		this->optType = optType;
		setNode(optType);
		typeNum = 4;
	}
	void setNode(int i) {
		switch(i) {
			case 0:
				this->area = 5;
				this->delay = 1;
				this->optType = 0;
				break;
			case 1:
				this->area = 3;
				this->delay = 2;
				this->optType = 1;
				break;
			case 2:
				this->area = 2;
				this->delay = 4;
				this->optType = 2;
				break;
			case 3:
				this->area = 1;
				this->delay = 8;
				this->optType = 3;
			default:
				assert("invalid multiplier");
				break;
		}
	}
};

class Graph
{
	int n;
	vector<Node*> vertex;
	vector< vector<int> > adj;
	vector< vector<int> > adj_rv;
public:
	Graph(int n);
	~Graph();
	void addEdge(int u, int v);
	int longestPath(int v);
	void printGraph();
	void addVertex(Node *a);
	int totalArea();
	Node* getNode(int i);
	void changeVertex(int v, Node *a);
	void printGraphInfo();
};

void Graph::changeVertex(int v, Node *a)
{
	vertex[v] = a;
}

Node* Graph::getNode(int i)
{
	return vertex[i];
}

Graph::Graph(int n) : n(n), adj(n), adj_rv(n) {}
Graph::~Graph()
{
	for(int i = 0; i < n; i++)
		delete vertex[i];
}

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

void Graph::printGraphInfo()
{
	int i = 0;
	for(auto p : vertex) {
		cout << "vertex[" << i << "]: " << "(area: " << p->getArea() << "," << "delay: " << p->getDelay() << ")" << endl;
		i++;
	}
}

void Graph::addVertex(Node *a) {
	vertex.push_back(a);
}

int Graph::totalArea() {
	int ans = 0;
	for(auto i : vertex)
		ans = ans + i->getArea();
	return ans;
}
int Graph::longestPath(int v) {
	int maxDelay1;
	int maxDelay2 = 0;
	vector<int>dist1(n);
	priority_queue<pair<int, int>, vector<pair<int, int>>> pq1;
	pq1.push(make_pair(vertex[v]->getDelay(), v));
	dist1[v] = vertex[v]->getDelay();
	maxDelay1 = dist1[v];
	while(!pq1.empty()) {
		int a = pq1.top().second;
		pq1.pop();
		for(auto b : adj[a]) {
			if(dist1[b] < dist1[a] + vertex[b]->getDelay()) {
				dist1[b] = dist1[a] + vertex[b]->getDelay();
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
			if(dist2[b] < dist2[a] + vertex[b]->getDelay()) {
				dist2[b] = dist2[a] + vertex[b]->getDelay();
				pq2.push(make_pair(dist2[b], b));
				maxDelay2 = maxDelay2 < dist2[b] ? dist2[b] : maxDelay2;
			}
		}
	}
	return maxDelay1 + maxDelay2;
}


int main()
{
	int period;
	int n;
	int opt;
	int u, v;

	ifstream infile("graph.txt");
	infile >> n;
	infile >> period;
	Graph g(n);

	for(int i = 0; i < n; i++) {
		infile >> opt;
		// cout << opt;
		switch(opt) {
			case 0:
				g.addVertex(new Add(0));
				break;
			case 1:
				g.addVertex(new Shift(0));
				break;
			case 2:
				g.addVertex(new Mult(0));
				break;
			default:
				assert("wrong operator");
				break;
		}
	}

	cout << endl;
	while(infile >> u >> v) {
		cout << "DAGedge (" << u << "," << v << ")" << endl;
		g.addEdge(u,v);

	}
	for(int i = 0; i < n; i++) {
		if(g.longestPath(i) > period) {
			cout << "impossible to achieve this clock period" << endl;
			return 1;
		}
	}

	// g.printGraph();
	// Node *p = g.getNode(4);
	cout << "starting total area: " << g.totalArea() << endl;
	// cout << g.longestPath(4) << endl;
	// cout << p->getTypeNum() << endl;
	// cout << g.getNode(4)->getTypeNum() << endl;
	int totalArea = g.totalArea();
	double T = 8.0;
	bool frozen = false;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dis(0.0,1.0);
	uniform_int_distribution<int> randomGate(0,n-1);
	uniform_int_distribution<int> randomGateType1(0,2);
	uniform_int_distribution<int> randomGateType2(0,3);

	while(!frozen) {
		int currentArea;
		for(int i = 0; i < NUMOFTRIALS; i++) {
			int indexGate = randomGate(gen);
			Node *k = g.getNode(indexGate);
			int indexType = k->getTypeNum() == 3 ? randomGateType1(gen) : randomGateType2(gen);
			int typeBeforeChange = k->getOptType();
			int AreaBeforeChange = k->getArea();
			k->setNode(indexType);
			if(g.longestPath(indexGate) > period) {
				k->setNode(typeBeforeChange);
			}else {
				double delta = k->getArea() - AreaBeforeChange;
				double x = dis(gen);
				double y = exp(-delta/T);
				if(delta > 0 && x > y) {
					k->setNode(typeBeforeChange);
				}
			}
		}
		currentArea = g.totalArea();
		if(currentArea < totalArea) {
			totalArea = currentArea;
			T = 0.8 * T;
		} else {
			frozen = true;
		}
	}
	g.printGraphInfo();
	cout << "total area after optimization: " << g.totalArea() << endl;

	return 1;
}

