#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_´

#include <string>

using namespace std;

class Road{
	unsigned long id;
	string name;
	bool isTwoWays;
public:
	Road(){};
	Road(unsigned long id);
	Road(unsigned long id,string name,bool isTwoWays);
	unsigned long getID() const;
	string getName() const;
	bool getIsTwoWays() const;
	bool operator==(const Road &r) const{return this->id==r.getID();};
};



#endif
