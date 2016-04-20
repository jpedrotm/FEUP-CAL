#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <iostream>
#include <cmath>

using namespace std;

class Node{
	unsigned long id;
	double latitude;
	double longitude;

public:
	Node(){};
	Node(unsigned long id);
	Node(unsigned long id,double lat,double log);
	Node(double x,double y);
	unsigned long getID() const;
	double getLat() const;
	double getLog() const;
	bool operator==(const Node &n) const{return this->id==n.getID();};
	double distance(Node &n);
};


#endif
