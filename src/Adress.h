#ifndef SRC_ADRESS_H_
#define SRC_ADRESS_H_

#include <iostream>

#include "Node.h"
#include "Road.h"

using namespace std;

class Adress {
	Node local;
	Road street;
public:
	Adress(){};
	Adress(Node local,Road street);
  //--------------------------------------------------------------------------------------------------------
  Road getStreet();
  Node getLocal();
  //--------------------------------------------------------------------------------------------------------
  void printAdress();
};

#endif
