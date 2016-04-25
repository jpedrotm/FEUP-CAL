#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <iostream>
#include <cmath>

using namespace std;

class Node{
	unsigned long id;
	double latRad;
	double lonRad;
	double latDeg;
	double lonDeg;

public:
	Node(){};
	Node(unsigned long id);
	Node(unsigned long id,double latR,double lonR,double latD,double lonD);
	Node(double x,double y);
	unsigned long getID() const;
	double getLatRad() const;
	double getLonRad() const;
	double getLatDeg() const;
	double getLonDeg() const;
	bool operator==(const Node &n) const{return this->id==n.getID();};
	double distance(Node &n);
};


#endif
