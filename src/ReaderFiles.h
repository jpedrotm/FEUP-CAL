#ifndef SRC_READERFILES_H_
#define SRC_READERFILES_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

#include "Node.h"
#include "Road.h"
#include "Relation.h"

using namespace std;

class ReaderFiles{
	vector<Node> nodes;
	vector<Road> roads;
	vector<Relation> relations;
	double minLat,maxLat,minLon,maxLon;
public:
	ReaderFiles();
	void readFileNameNodes();
	void readFileNameRoads();
	void readFileNameRelation();
	vector<Node> getNodes() const;
	vector<Road> getRoads() const;
	vector<Relation> getRelations() const;
	double getMinLat() const;
	double getMaxLat() const;
	double getMinLon() const;
	double getMaxLon() const;
	void updateLatsAndLons(double lat,double lon);

};



#endif
