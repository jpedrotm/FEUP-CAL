#ifndef SRC_RIDECENTER_H_
#define SRC_RIDECENTER_H_

#include "Graph.h"
#include "Node.h"
#include "Road.h"
#include "ReaderFiles.h"
#include "User.h"
#include "Adress.h"
#include "GraphViewer.h"

/**
 * RideCenter-Class that represents all the logic of the program.
 */
class RideCenter {
	/**
	 * Private attribute that saves all the information in a graph.
	 */
	Graph<Node, Road> graph;
	/**
	 * Private attribute which stores all the relations between the nodes and the roads.
	 */
	vector<Relation> rels;
	/**
	 * Private attribute which stores all the nodes.
	 */
	vector<Node> nodes;
	/**
	 * Private attribute which stores all the roads.
	 */
	vector<Road> roads;
	/**
	 * Private attribute of type ReaderFiles.
	 */
	ReaderFiles reader;
public:
	/**
	 * Constructor of the class with no parameters.
	 */
	RideCenter(){};
	/**
	 * Constructor of the class that initialize all the private attributes.
	 * @param r.
	 */
	RideCenter(ReaderFiles &r);
	/**
	 * Function that prints all the ids's of the nodes in the graph.
	 */
	void printGraph() const;
	/**
	 * Function that calculates if a node is inside of the elipse.
	 * @param foco1.
	 * @param foco2.
	 * @param n.
	 * @return true if the node n is inside of the elipse.
	 */
	bool in_elipse(Node foco1, Node foco2, Node N);

	//VAI PARA PRIVATE MUDAR DEPOIS
	void centerGraph(Node T);
	vector<Vertex<Node,Road> *> getPath(const Node &Sourc,const Node &Dest, double &dist) ;
	//
	Node FindNode(unsigned long id);
	vector< Vertex<Node,Road> > BestPath(const Node &Sourc, const Node & Dest,const vector <Node> InterestPoints, unsigned int passenger_capacity);
	Adress* getAdress(Node N)const;
	void displayGraph(vector< Vertex<Node,Road> > passNodes);
	Graph<Node,Road> getGraph() const;

	bool SourcDestConected(Node dest, vector<Node> nodes);
    bool TestALLNodesConected(Node Sourc, Node Dest, vector<Node> Interest_Points,unsigned int &ban);
	unsigned long getEdgeID(unsigned long id_sourc, unsigned long id_dest);


};



#endif
