#ifndef SRC_RIDECENTER_H_
#define SRC_RIDECENTER_H_

#include "Graph.h"
#include "Node.h"
#include "Road.h"
#include "ReaderFiles.h"
#include "User.h"
#include "Interface.h"

class RideCenter{
	Graph<Node,Road> graph;
public:
	RideCenter(ReaderFiles &r);
	void printGraph() const;
	vector<User> in_elipse(User U,Interface I);

};



#endif
