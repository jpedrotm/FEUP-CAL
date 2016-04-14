#ifndef SRC_ADRESS_H_
#define SRC_ADRESS_H_

#include <iostream>
#include <string>

using namespace std;

class Adress {
  string street;
  string local;
  int lat, lon;

public:
  Adress(){};
  Adress(string street, string local, int x, int y);
  //--------------------------------------------------------------------------------------------------------
  string getStreet();
  string getLocal();
  int getLatitude();
  int getLongitude();
  //--------------------------------------------------------------------------------------------------------
  void printAdress();
};

#endif
