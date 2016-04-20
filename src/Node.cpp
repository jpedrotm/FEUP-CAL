#include "Node.h"

Node::Node(unsigned long id): id(id){}

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

double Node::distance(Node &n){
	return sqrt((this->x-n.getX())*(this->x-n.getX())+(this->y-n.getY())*(this->y-n.getY())+(this->z-n.getZ())*(this->z-n.getZ()));
}
