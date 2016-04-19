/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
using namespace std;

template <class T,class A> class Edge;
template <class T,class A> class Graph;

template <class T,class A>
class Vertex {
	T info;
	vector<Edge<T,A>  > adj;
	bool visited;
public:
	Vertex(T in);
	friend class Graph<T,A>;
	bool removeEdgeTo(Vertex<T,A> *d);
};


template <class T,class A>
Vertex<T,A>::Vertex(T in): info(in), visited(false){}


template <class T,class A>
class Edge {
	Vertex<T,A> * dest;
	double weight;
	A edgeInfo;
public:
	Edge(Vertex<T,A> *d, double w);
	friend class Graph<T,A>;
	friend class Vertex<T,A>;
};

template <class T,class A>
Edge<T, A>::Edge(Vertex<T,A> *d, double w): dest(d), weight(w){}

template <class T,class A>
class Graph {
	vector<Vertex<T,A> *> vertexSet;
public:
	vector<Vertex<T,A> * > getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
};

template <class T,class A>
int Graph<T,A>::getNumVertex() const {
	return vertexSet.size();
}
template <class T,class A>
vector<Vertex<T,A> * > Graph<T,A>::getVertexSet() const {
	return vertexSet;
}

template<class T,class A>
bool Graph<T,A>::addVertex(const T &in){

	typename vector<Vertex<T,A> *>::iterator it=vertexSet.begin();
	typename vector<Vertex<T,A> *>::iterator ite=vertexSet.end();

	for(;it!=ite;it++)
	{
		if((*it)->info==in)
			return false;
	}

	Vertex<T,A> *v=new Vertex<T,A>(in);
	vertexSet.push_back(v);

	return true;
}

template<class T,class A>
bool Graph<T,A>::removeVertex(const T &in)
{
	typename vector<Vertex<T,A> *>::iterator it=vertexSet.begin();
	typename vector<Vertex<T,A> *>::iterator ite=vertexSet.end();

	for(;it!=ite;it++)
	{
		if((*it)->info==in)
		{
			Vertex<T,A> *v=*it;
			vertexSet.erase(it);
			typename vector<Vertex<T,A> *>::iterator it1=vertexSet.begin();
			typename vector<Vertex<T,A> *>::iterator it1e=vertexSet.end();
			for(;it1!=it1e;it1++)
			{
				(*it1)->removeEdgeTo(v);
			}

			return true;
		}
	}

	return false;
}

template<class T,class A>
bool Graph<T,A>::addEdge(const T &sourc, const T &dest, double w){

	typename vector<Vertex<T,A> *>::iterator it=vertexSet.begin();
	typename vector<Vertex<T,A> *>::iterator ite=vertexSet.end();
	int count=0;
	Vertex<T,A> *vp,*vd;

	for(;it!=ite;it++){
		if((*it)->info==sourc)
			{
			vp=(*it);
			count++;
			}
		if((*it)->info==dest)
		{
			vd=(*it);
			count++;
		}
	}

	if(count==2)
	{
		Edge<T,A> e=Edge<T,A>(vd,w);
		vp->adj.push_back(e);
		return true;
	}

	return false;
}

template <class T,class A>
bool Vertex<T,A>::removeEdgeTo(Vertex<T,A> *d) {
	typename vector<Edge<T,A> >::iterator it= adj.begin();
	typename vector<Edge<T,A> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template<class T,class A>
bool Graph<T,A>::removeEdge(const T &sourc, const T &dest){
	typename vector<Vertex<T,A> *>::iterator it=vertexSet.begin();
	typename vector<Vertex<T,A> *>::iterator ite=vertexSet.end();

	for(;it!=ite;it++)
	{
		Vertex<T,A>*v=*it;
		if(v->info==sourc)
			for(unsigned int i=0;i<v->adj.size();i++)
			{
				if(v->adj[i].dest->info==dest)
				{
					v->adj.erase(v->adj.begin()+i);
					return true;
				}
			}
	}

	return false;
}
