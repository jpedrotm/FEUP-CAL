
#include "Interface.h"
#include "ReaderFiles.h"
#include "RideCenter.h"

using namespace std;

int main() {

	ReaderFiles r=ReaderFiles();

	RideCenter center=RideCenter(r);


	cout << "PRINT GRAPH" << endl;
	center.printGraph();


	cout << "DISTRAK" << endl;

	Node  temp = center.FindNode(1110698243);
	Node temp2 = center.FindNode(1110698260);

	center.centerGraph(temp);
	center.getPath(temp,temp2);

  return 0;
}

