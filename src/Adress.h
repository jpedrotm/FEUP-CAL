#ifndef SRC_ADRESS_H_
#define SRC_ADRESS_H_

#include <iostream>
#include <string>

using namespace std;

class Adress {
  string street;
  string local;
  int coordX, coordY;

public:
  Adress(){};
  Adress(string street, string local, int x, int y);
  //--------------------------------------------------------------------------------------------------------
  string getStreet();
  string getLocal();
  int getCoordX();
  int getCoordY();
  //--------------------------------------------------------------------------------------------------------
  void printAdress();
};

#endif
