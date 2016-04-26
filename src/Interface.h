#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include <vector>

#include "User.h"
#include "RideCenter.h"

using namespace std;

class Interface{
	vector<User*> users;
	RideCenter center;
public:
  Interface(ReaderFiles r);
  void displayMenu();
  void displayUsers();
  void newUser();
  void defineUserDeparture();
  void departure();
  Vertex<Node,Road> *findPlace(Node n) const;
  vector<User*> getUsers();
  int returnInt(string s1);
  string returnInput(string s1,string s2);
  int selectMenu(char menor, char maior);
  User *findUser(string name,unsigned long ID) const;

};

#endif
