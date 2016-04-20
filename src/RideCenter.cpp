#include "RideCenter.h"

#include <algorithm>
#define DISTACIA_FOCAL 50;

RideCenter::RideCenter(ReaderFiles &r) {

	vector<Relation> rels = r.getRelations();
	vector<Node> nodes = r.getNodes();
	vector<Road> roads = r.getRoads();

	typename vector<Relation>::iterator it = rels.begin();
	typename vector<Relation>::iterator ite = rels.end();

	for (; it != ite; it++) {

		typename vector<Road>::iterator itRoad;
		typename vector<Node>::iterator itNode1;
		typename vector<Node>::iterator itNode2;

		itRoad = find(roads.begin(), roads.end(), Road(it->getRoadID()));
		itNode1 = find(nodes.begin(), nodes.end(), Node(it->getNode1ID()));
		itNode2 = find(nodes.begin(), nodes.end(), Node(it->getNode2ID()));

		graph.addVertex(*itNode1);
		graph.addVertex(*itNode2);

		double dist = itNode1->distance(*itNode2);

		if (itRoad->getIsTwoWays()) {
			graph.addEdge(*itNode1, *itNode2, *itRoad, dist);
			graph.addEdge(*itNode2, *itNode1, *itRoad, dist);
		} else {
			graph.addEdge(*itNode1, *itNode2, *itRoad, dist);
		}
	}
}

void RideCenter::printGraph() const {

	vector<Vertex<Node, Road>*> nodes = graph.getVertexSet();

	for (unsigned int i = 0; i < nodes.size(); i++) {
		cout << nodes[i]->getInfo().getID() << endl;
	}
}

vector<User> RideCenter::in_elipse(User U, Interface I) {
	Node foco1 = U.getUserAdress().getLocal();
	Node foco2 = U.getUserDestination().getLocal();
	vector<User> in;

	double centroX = (foco1.getX() + foco2.getX()) / 2;
	double centroY = (foco1.getY() + foco2.getY()) / 2;

	Node centro_elipse = Node(centroX, centroY);
	double dx = foco1.getX() - centroX;
	double dy = foco1.getY() - centroY;

	double c = sqrt(pow(dx, 2) + pow(dy, 2));
	double a = c + DISTACIA_FOCAL;
	double b = sqrt(pow(a, 2) + pow(b, 2));

	double x, y, primeiro_arg, segundo_arg;

	for (int i = 0; i < I.getUsers().size(); i++) {

		x = I.getUsers()[i].getUserAdress().getLocal().getX();
		y = I.getUsers()[i].getUserAdress().getLocal().getY();

		primeiro_arg = pow(x - centroX, 2) / pow(a, 2);
		segundo_arg = pow(y - centroY, 2) / pow(b, 2);

		if ((primeiro_arg + segundo_arg) <= 1)
			in.push_back(I.getUsers()[i]);
	}

	return in;
}


void RideCenter::centerGraph(Node T){
	graph.dijkstraShortestPath(T);
}
void RideCenter::getPath(const Node &Sourc,const  Node &Dest) const {
	std::vector<Vertex<Node,Road> *> path = graph.getPath(Sourc,Dest);

	for(unsigned int i = 0;i < path.size() ;i++){
		cout << "i : " << i << " node id: " << path[i]->getInfo().getID() << " Dist: ";
		cout << path[i]->getDist() << endl;
	}
}

Node RideCenter::FindNode(unsigned long id){
	vector<Vertex<Node,Road> *>:: iterator it = graph.getVertexSet().begin();
	vector<Vertex<Node,Road> *>:: iterator ite = graph.getVertexSet().end();

	while(it != ite)
	{
		if((*it)->getInfo().getID() == id)
			return (*it)->getInfo();
		it++;
	}


	return NULL;
}

