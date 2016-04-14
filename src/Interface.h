#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include <vector>

#include "Exceptions.h"
#include "User.h"

using namespace std;

class Interface {
  vector<User> users;

public:
  Interface();

  void displayMenu();
  void displayUsers();
  void newUser();
};

#endif
