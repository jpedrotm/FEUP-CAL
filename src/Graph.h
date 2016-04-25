/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <iostream>
#include <list>

#define DOUBLE_INFINITY 99999.9
using namespace std;

template<class T, class A> class Edge;
template<class T, class A> class Graph;

template<class T, class A>
class Vertex {
	T info;
	vector<Edge<T, A> > adj;
	bool visited;
	double dist;
	bool processing;
public:
	Vertex(T in);
	friend class Graph<T, A> ;
	bool removeEdgeTo(Vertex<T, A> *d);
	T getInfo() const;
	double getDist() const;
	Vertex* path;
	vector<Edge<T, A> > getAdj() const;

};

template<class T, class A>
struct vertex_greater_than {
	bool operator()(Vertex<T, A> * a, Vertex<T, A> * b) const {
		return a->getDist() > b->getDist();
	}
};

template<class T, class A>
Vertex<T, A>::Vertex(T in) :
		info(in), visited(false) {
}

template<class T, class A>
T Vertex<T, A>::getInfo() const {
	return info;
}

template<class T, class A>
double Vertex<T, A>::getDist() const {
	return dist;
}

template<class T, class A>
vector<Edge<T, A> > Vertex<T, A>::getAdj() const {
	vector<Edge<T, A> > V;

	for (unsigned int i = 0; i < adj.size(); i++) {
		V.push_back(adj[i]);
	}
	return V;
}

template<class T, class A>
class Edge {
	Vertex<T, A> * dest;
	double weight;
	A edgeInfo;
public:
	Edge(Vertex<T, A> *d, A info, double w);
	friend class Graph<T, A> ;
	friend class Vertex<T, A> ;
	A getEdgeInfo();
};

template<class T, class A>
Edge<T, A>::Edge(Vertex<T, A> *d, A info, double w) :
		dest(d), edgeInfo(info), weight(w) {
}

template<class T, class A>
A Edge<T, A>::getEdgeInfo() {
	return edgeInfo;
}

template<class T, class A>
class Graph {
	vector<Vertex<T, A> *> vertexSet;
public:
	vector<Vertex<T, A> *> getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, A info, double w);
	bool removeEdge(const T &sourc, const T &dest);

	vector<Vertex<T, A> *> getPath(const T &origin, const T &dest) const;
	Vertex<T, A> * getVertex(const T &v) const;
	void dijkstraShortestPath(const T &s);

	vector<T> bfs(Vertex<T,A> *v) const;
};

template<class T, class A>
int Graph<T, A>::getNumVertex() const {
	return vertexSet.size();
}
template<class T, class A>
vector<Vertex<T, A> *> Graph<T, A>::getVertexSet() const {
	return vertexSet;
}

template<class T, class A>
bool Graph<T, A>::addVertex(const T &in) {

	typename vector<Vertex<T, A> *>::iterator it = vertexSet.begin();
	typename vector<Vertex<T, A> *>::iterator ite = vertexSet.end();

	for (; it != ite; it++) {
		if ((*it)->info == in)
			return false;
	}

	Vertex<T, A> *v = new Vertex<T, A>(in);
	vertexSet.push_back(v);

	return true;
}

template<class T, class A>
bool Graph<T, A>::removeVertex(const T &in) {
	typename vector<Vertex<T, A> *>::iterator it = vertexSet.begin();
	typename vector<Vertex<T, A> *>::iterator ite = vertexSet.end();

	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T, A> *v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T, A> *>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T, A> *>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			return true;
		}
	}

	return false;
}

template<class T, class A>
bool Graph<T, A>::addEdge(const T &sourc, const T &dest, A info, double w) {

	typename vector<Vertex<T, A> *>::iterator it = vertexSet.begin();
	typename vector<Vertex<T, A> *>::iterator ite = vertexSet.end();
	int count = 0;
	Vertex<T, A> *vp, *vd;

	for (; it != ite; it++) {
		if ((*it)->info == sourc) {
			vp = (*it);
			count++;
		}
		if ((*it)->info == dest) {
			vd = (*it);
			count++;
		}
	}

	if (count == 2) {
		Edge<T, A> e = Edge<T, A>(vd, info, w);
		vp->adj.push_back(e);
		return true;
	}

	return false;
}

template<class T, class A>
bool Vertex<T, A>::removeEdgeTo(Vertex<T, A> *d) {
	typename vector<Edge<T, A> >::iterator it = adj.begin();
	typename vector<Edge<T, A> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		} else
			it++;
	}
	return false;
}

template<class T, class A>
bool Graph<T, A>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T, A> *>::iterator it = vertexSet.begin();
	typename vector<Vertex<T, A> *>::iterator ite = vertexSet.end();

	for (; it != ite; it++) {
		Vertex<T, A>*v = *it;
		if (v->info == sourc)
			for (unsigned int i = 0; i < v->adj.size(); i++) {
				if (v->adj[i].dest->info == dest) {
					v->adj.erase(v->adj.begin() + i);
					return true;
				}
			}
	}

	return false;
}

template<class T, class A>
Vertex<T, A>* Graph<T, A>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v)
			return vertexSet[i];
	return NULL;
}

template<class T, class A>
void Graph<T, A>::dijkstraShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = DOUBLE_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T, A>* v = getVertex(s);
	v->dist = 0.0;

	vector<Vertex<T, A>*> pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());

	while (!pq.empty()) {

		//cout << "stack: " <<  pq.size() << endl;
		//cout << "arestas: " <<  pq.front()->adj.size() << endl;
		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T, A>* w = v->adj[i].dest;
			//cout << "peso da aresta " << v->adj[i].weight << endl;
			if (v->dist + v->adj[i].weight < w->dist) {

				//	cout << "V DIST" << v->dist;
				//cout << "V ADD  DISTT "  << v->adj[i].weight << endl;;

				//cout << w ->dist << endl;
				w->dist = v->dist + v->adj[i].weight;

				//cout << w ->dist << endl;
				w->path = v;

				//se j� estiver na lista, apenas a actualiza
				if (!w->processing) {
					w->processing = true;
					pq.push_back(w);
				}

				make_heap(pq.begin(), pq.end(), vertex_greater_than<T, A>());
			}
		}
	}

	/*cout<< "BUILD DIJS" << endl;
	 for(int i = 0; i < vertexSet.size(); i++)
	 {


	 cout <<" id " << vertexSet[i]->info.getID() << " dist " << vertexSet[i]->dist << endl;
	 }*/
}

template<class T, class A>
vector<Vertex<T, A> *> Graph<T, A>::getPath(const T &origin,
		const T &dest) const {

	list<Vertex<T, A> *> buffer;
	Vertex<T, A>* v = getVertex(dest);

	buffer.push_front(v);
	while (v->path != NULL && !(v->path->info == origin)) {
		v = v->path;
		buffer.push_front(v);
	}
	if (v->path != NULL)
		buffer.push_front(getVertex(v->path->info));

	vector<Vertex<T, A> *> res;
	while (!buffer.empty()) {
		res.push_back(buffer.front());
		buffer.pop_front();
	}
	return res;
}

template <class T, class A>
vector<T> Graph<T,A>::bfs(Vertex<T,A> *v) const {
	vector<T> res;
	queue<Vertex<T,A> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T,A> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T,A> >::iterator it=v1->adj.begin();
		typename vector<Edge<T,A> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T,A> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}
#endif
