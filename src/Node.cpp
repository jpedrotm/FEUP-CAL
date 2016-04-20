#include "Node.h"

#include <cmath>
#define EARTH_RAD 6378.137


Node::Node(unsigned long id): id(id){}

Node::Node(unsigned long id,double lat,double log):id(id), latitude(lat),longitude(log){}

Node::Node(double lat,double log): latitude(lat),longitude(log){}

unsigned long Node::getID() const{
	return id;
}

double Node::getLat() const{
	return latitude;
}

double Node::getLog() const{
	return longitude;
}


double Node::distance(Node &n){
	double dLat=(n.getLat()- latitude);
	double dLon=(n.getLog() -longitude);
	double a = sin(dLat/2)*sin(dLat/2)+
			cos(latitude)* cos(n.getLat())
			*sin(dLon/2)*sin(dLon/2);
	double c = 2 * atan2(sqrt(a),sqrt(1-a));
	double d = EARTH_RAD * c;
	return d;
}
