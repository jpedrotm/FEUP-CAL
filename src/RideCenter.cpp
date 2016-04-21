#include "RideCenter.h"

#include <algorithm>
#define DISTACIA_FOCAL 50;

RideCenter::RideCenter(ReaderFiles &r) {

	this->rels = r.getRelations();
	this->nodes = r.getNodes();
	this->roads = r.getRoads();

	typename vector<Relation>::iterator it = rels.begin();
	typename vector<Relation>::iterator ite = rels.end();

	//cout <<"DIST" <<endl;
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

		//	cout << dist << endl;
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
	double a = c + DISTACIA_FOCAL
	;

	double x, y, d_f1, d_f2, comparador;
	comparador = a + c + (a - c); //este valor é a distancia de um ponto da elipse a ambos os focos

	for (int i = 0; i < I.getUsers().size(); i++) {

		x = I.getUsers()[i].getUserAdress().getLocal().getLat();
		y = I.getUsers()[i].getUserAdress().getLocal().getLog();

		dx = x - foco1.getLat();
		dy = y - foco1.getLog();
		d_f1 = sqrt(pow(dx, 2) + pow(dy, 2)); //distacia ao primeiro foco

		dx = x - foco2.getLat();
		dy = y - foco2.getLog();
		d_f2 = sqrt(pow(dx, 2) + pow(dy, 2)); //distancia ao segundo foco

		if (d_f1 + d_f2 <= comparador) //se for menor ou igual esta contido na elipse
			in.push_back(I.getUsers()[i]);
	}

	return in;
}

void RideCenter::centerGraph(Node T) {
	graph.dijkstraShortestPath(T);
}
vector<Vertex<Node, Road> *> RideCenter::getPath(const Node &Sourc,
		const Node &Dest, double &dist) {
	std::vector<Vertex<Node, Road> *> path = graph.getPath(Sourc, Dest);

	/*	for(unsigned int i = 0;i < path.size() ;i++){
	 cout << "i : " << i << " node id: " << path[i]->getInfo().getID() << " Dist: ";
	 cout << path[i]->getDist() << endl;
	 }*/

	vector<Vertex<Node, Road>*>::iterator it = path.end();
	--it;
	dist = (*it)->getDist();

	return path;
}

Node RideCenter::FindNode(unsigned long id) {
	vector<Vertex<Node, Road> *>::iterator it = graph.getVertexSet().begin();
	vector<Vertex<Node, Road> *>::iterator ite = graph.getVertexSet().end();

	while (it != ite) {
		if ((*it)->getInfo().getID() == id)
			return (*it)->getInfo();
		it++;
	}

	return NULL;
}

vector<Vertex<Node, Road> > RideCenter::BestPath(const Node &Sourc,
		const Node & Dest, const vector<Node> InterestPoints,
		unsigned int passenger_capacity) // Nao tem em conta lotação ainda
		{
	unsigned int total_points = InterestPoints.size() + 2;

	double dist[total_points - 1][total_points];

	vector<Node> points;
	vector<vector<Vertex<Node, Road>*> > paths;

	//BUILD POINTS SEQUENCE
	points.push_back(Sourc);
	for (unsigned int i = 0; i < InterestPoints.size(); i++) {
		points.push_back(InterestPoints[i]);
	}

	points.push_back(Dest);

	// CALCULATE DIST AND PATHS

	for (unsigned int i = 0; i + 1 < points.size(); i++) // DONT BUILD PATHS FROM END POINT TO OTHER POINTS
			{
		centerGraph(points[i]);
		for (unsigned int t = 0; t < points.size(); t++) {
			if (i == t) {
				dist[i][t] = 0;
				vector<Vertex<Node, Road>*> a;
				paths.push_back(a);
				cout << "dist " << dist[i][t] << endl;
				continue;
			}
			double distant;
			paths.push_back(getPath(points[i], points[t], distant));
			//cout << "distant " << distant << endl;
			dist[i][t] = distant;
			cout << "distant " << " i: " << i << "t: " << t << " " << dist[i][t]
					<< endl;
		}
	}

	///Nearest neighbour algorithm - TSP
	/// greedy algorithm

	int visited[points.size() - 1];
	for (unsigned int i = 0; i < points.size() - 1; i++) {
		visited[i] = 0;
	}

	unsigned int pos = 0;
	double total_dist = 0;
	bool allVisited = false;

	vector<int> index_order;
	index_order.push_back(0);
	cout << "TOTAL POINTS" << points.size() << endl;

	while (!allVisited) {	//cout << "inicio" << endl;

		double min = 999.99;
		int nextpos = points.size() - 1;
		for (unsigned int t = 0; t + 1 < points.size(); t++) {

			if (dist[pos][t] < min && dist[pos][t] != 0) {

				if (visited[t] == 0) {
					//			cout << "entrou" << endl;
					min = dist[pos][t];
					nextpos = t;
					cout << "troca" << endl;
				}

			}
		}
		//

		//	cout << "t" << nextpos <<endl;
		visited[pos] = 1;
		if (min != 999.99)
			total_dist += min;
		else
			total_dist += dist[pos][nextpos];
		pos = nextpos;
		index_order.push_back(pos);

		//	cout << "VISITED" << endl;
		for (unsigned int i = 0; i < points.size() - 1; i++) {

			if (visited[i] == 0) {
				//		cout << i << " FALSE " << endl;
				allVisited = false;
				break;
			}
			//		else cout << i << " True " << endl;
		}

		if (nextpos == points.size() - 1) // WHEN CANT COVER ALL POINT ( EU POSSO EXPLICAR ISTO SE TIVEREM DUVIDAS ASK xD )
				{
			allVisited = true;
		}
		if (allVisited == true) {	//index_order.push_back(points.size()-1);
			for (unsigned int t = 0; t < index_order.size(); t++) {
				cout << index_order[t] << endl;
			}

			cout << "TOTAL DIST " << total_dist << endl;
		}

		//cout << "nao sai" << endl;
	}

	//BUILD FINAL PATH
	cout << "AQUIdasdasd" << endl;
	vector<Vertex<Node, Road> *>::iterator it1 = paths[2].begin();
	vector<Vertex<Node, Road> *>::iterator ite1 = paths[2].end();

	while (it1 != ite1) {
		cout << (*it1)->getInfo().getID() << endl;
		it1++;
	}

	vector<Vertex<Node, Road> > final;

	cout << "AQUI" << endl;

	for (unsigned int i = 0; i + 1 < index_order.size(); i++) {

		int path_index = index_order[i] * (points.size()) + index_order[i + 1];
		cout << "path " << path_index << endl;
		vector<Vertex<Node, Road> *>::iterator it = paths[path_index].begin();
		vector<Vertex<Node, Road> *>::iterator ite = paths[path_index].end();
		if (i > 0)
			it++;
		while (it != ite) {
			//cout <<"ciclo" << endl;
			final.push_back(*(*it));
			it++;
		}
	}
	cout << "saiu" << endl;

	return final;
}

Adress* RideCenter::getAdress(Node N) const {
	Road street;
	bool find = false;
	Adress* A;

	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		if (graph.getVertexSet()[i]->getInfo() == N)
			if (graph.getVertexSet()[i]->getAdj().size() > 0) {
				find = true;
				street = graph.getVertexSet()[i]->getAdj()[0].getEdgeInfo();
			} else
				return NULL;

	}
	if (!find)
		return NULL;

	*A = Adress(N, street);

	return A;
}

