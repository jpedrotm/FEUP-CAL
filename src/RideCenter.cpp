#include "RideCenter.h"

#include <algorithm>

RideCenter::RideCenter(ReaderFiles &r){

	vector<Relation> rels=r.getRelations();
	vector<Node> nodes=r.getNodes();
	vector<Road> roads=r.getRoads();

	typename vector<Relation>::iterator it=rels.begin();
	typename vector<Relation>::iterator ite=rels.end();

	for(;it!=ite;it++)
	{

		typename vector<Road>::iterator itRoad;
		typename vector<Node>::iterator itNode1;
		typename vector<Node>::iterator itNode2;

		itRoad=find(roads.begin(),roads.end(),Road(it->getRoadID()));
		itNode1=find(nodes.begin(),nodes.end(),Node(it->getNode1ID()));
		itNode2=find(nodes.begin(),nodes.end(),Node(it->getNode2ID()));

		graph.addVertex(*itNode1);
		graph.addVertex(*itNode2);

		double dist=itNode1->distance(*itNode2);

		if(itRoad->getIsTwoWays())
		{
			graph.addEdge(*itNode1,*itNode2,*itRoad,dist);
			graph.addEdge(*itNode2,*itNode1,*itRoad,dist);
		}
		else
		{
			graph.addEdge(*itNode1,*itNode2,*itRoad,dist);
		}
	}
}

void RideCenter::printGraph() const{

	vector<Vertex<Node,Road>* >nodes=graph.getVertexSet();

	for(unsigned int i=0;i<nodes.size();i++)
	{
		cout << nodes[i]->getInfo().getID() << endl;
	}
}




