#ifndef SRC_RELATION_H_
#define SRC_RELATION_H_

class Relation{
	unsigned long roadID;
	unsigned long node1ID;
	unsigned long node2ID;
public:
	Relation(unsigned long roadID,unsigned long node1ID,unsigned long node2ID);
	unsigned long getRoadID() const;
	unsigned long getNode1ID() const;
	unsigned long getNode2ID() const;
};



#endif
