#include "RideCenter.h"

#include <algorithm>
#define DISTACIA_FOCAL 50;

RideCenter::RideCenter(ReaderFiles &r) {

	vector<Relation> rels = r.getRelations();
	vector<Node> nodes = r.getNodes();
	vector<Road> roads = r.getRoads();

	typename vector<Relation>::iterator it = rels.begin();
	typename vector<Relation>::iterator ite = rels.end();


	cout <<"DIST" <<endl;
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

		cout << dist << endl;
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

	double centroX = (foco1.getLat() + foco2.getLat()) / 2;
	double centroY = (foco1.getLog() + foco2.getLog()) / 2;

	Node centro_elipse = Node(centroX, centroY);
	double dx = foco1.getLat() - centroX;
	double dy = foco1.getLog() - centroY;

	double c = sqrt(pow(dx, 2) + pow(dy, 2));
	double a = c + DISTACIA_FOCAL;

	double x, y, d_f1, d_f2,comparador;
	comparador = a + c + (a - c); //este valor é a distancia de um ponto da elipse a ambos os focos

	for (int i = 0; i < I.getUsers().size(); i++) {

		x = I.getUsers()[i].getUserAdress().getLocal().getLat();
		y = I.getUsers()[i].getUserAdress().getLocal().getLog();

		dx = x - foco1.getLat();
		dy = y - foco1.getLog();
		d_f1 = sqrt(pow(dx,2)+ pow(dy,2));//distacia ao primeiro foco


		dx = x - foco2.getLat();
		dy = y - foco2.getLog();
		d_f2 = sqrt(pow(dx,2)+ pow(dy,2));//distancia ao segundo foco


		if(d_f1+d_f2 <= comparador)//se for menor ou igual esta contido na elipse
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

