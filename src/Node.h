#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <iostream>

using namespace std;

class Node{
	unsigned long id;
	double x;
	double y;
	double z;
public:
	Node(){};
	Node(unsigned long id,double x,double y,double z);
	unsigned long getID() const;
	double getX() const;
	double getY() const;
	double getZ() const;
};


#endif
