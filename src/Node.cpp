#include "Node.h"

Node::Node(unsigned long id,double x,double y,double z):id(id), x(x),y(y),z(z){}

unsigned long Node::getID() const{
	return id;
}

double Node::getX() const{
	return x;
}

double Node::getY() const{
	return y;
}

double Node::getZ() const{
	return z;
}
