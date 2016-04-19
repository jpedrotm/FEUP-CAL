#ifndef SRC_USER_H_
#define SRC_USER_H_

#include "Adress.h"

using namespace std;

class User {
  string name;
  int age;
  Adress initAdress;//adress onde se encontra o utilizador
  Adress destAdress;//adress onde deseja ir

public:
  User(string name, int age, Adress initAdress, Adress destAdress);
  User(string name, int age, Adress initAdress);
  User(string name,int age);
  //----------------------------------------------------------------------------------------------------------
  string getName();
  int getAge();
  Adress getUserAdress();
  Adress getUserDestination();
  //--------------------------------------------------------------------------------------------------------
  void printUserAdress();
};

#endif
