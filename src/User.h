#ifndef SRC_USER_H_
#define SRC_USER_H_

#include "Trip.h"

using namespace std;

class User {
  string name;
  int age;
  Adress adress;
  Trip trip;

public:
  User(string name, int age, Adress adress, Trip trip);
  User(string name, int age, Adress adress);
  //----------------------------------------------------------------------------------------------------------
  string getName();
  int getAge();
  Adress getUserAdress();
  Trip getUserTrip();
  //--------------------------------------------------------------------------------------------------------
  void printUserAdress();
};

#endif
