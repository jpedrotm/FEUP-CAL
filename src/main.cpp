
#include "Interface.h"
#include "ReaderFiles.h"
#include "RideCenter.h"

using namespace std;

int main() {

	ReaderFiles r=ReaderFiles();

	RideCenter center=RideCenter(r);


	//cout << "PRINT GRAPH" << endl;
	//center.printGraph();


	cout << "DISTRAK" << endl;
	//TEST 1 grahp.path
	//	center.centerGraph(temp);
	//	double dist;
	//	center.getPath(temp,temp2,dist);
	//	cout << "DIST" << dist << endl;

	//TEST2 BestPath Multiple Points
	Node  temp = center.FindNode(506859190);


	Node temp2 = center.FindNode(771440364);
	vector <Node> Pontos_interesse;
	Pontos_interesse.push_back(center.FindNode(768566003));
//	Pontos_interesse.push_back(center.FindNode(25632366));
//	Pontos_interesse.push_back(center.FindNode(452682268));
	//NAO TEM A LOTAÇAO A FUNCIONAR
	vector< Vertex<Node,Road> >  teste = center.BestPath(temp, temp2,Pontos_interesse, 0);

	vector< Vertex<Node,Road> >::iterator it = teste.begin();
	vector< Vertex<Node,Road> >::iterator ite = teste.end();

	while(it != ite)
	{
		cout << it->getInfo().getID() << endl;
		it++;
	}

  return 0;
}

