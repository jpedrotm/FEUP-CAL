#ifndef SRC_USER_H_
#define SRC_USER_H_

#include "Adress.h"

using namespace std;

class User {
  string name;
  int age;
  Adress initAdress;//adress onde se encontra o utilizador
  Adress destAdress;//adress onde deseja ir
  string horaInit,horaFim;
  bool wantDest;
  int numPassengers;

public:
  User(string name, int age, Adress initAdress, Adress destAdress,int nP);
  User(string name, int age, Adress initAdress);
  User(string name,int age);
  //----------------------------------------------------------------------------------------------------------
  string getName() const;
  int getAge() const;
  Adress getUserAdress() const;
  Adress getUserDestination() const;
  string getHoraInit() const;
  string getHoraFim() const;
  int getNumPassegers() const;
  bool getWantDest() const;
  void setHoraInit(string &h);
  void setHoraFim(string &h);
  void setDestAdress(Node n,Road r);
  void resetUser();
  //--------------------------------------------------------------------------------------------------------
  void printUserAdress();
  void printDestAdress();
  void printHoursAndNumPassengers();
};

#endif
