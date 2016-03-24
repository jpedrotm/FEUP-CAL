#include "Interface.h"

Interface::Interface() {}

void Interface::displayMenu() {
  int nOptions = 0;
  int option = 0;

  cout << "Welcome to RideSharing! Please choose a option." << endl;
  nOptions++;
  cout << "1-Insert new user." << endl;
  nOptions++;
  cout << "2-See all users." << endl;
  nOptions++;
  cout << "3-Exit." << endl;
  cin >> option;
  try {
    if (option < 1 || option > nOptions)
      throw IlegalOptionException();
  } catch (IlegalOptionException &e) {
    cout << "Not a possible option. Please choose other." << endl;
    return;
  }
  this->option = option;
  cout << endl;
}

void Interface::displayUsers() {

  if (users.size() == 0) {
    cout << "No users registered. Enter to main menu." << endl;
    string input;
    cin >> input;
    displayMenu();
  } else {
    for (unsigned int i = 0; i < users.size(); i++) {
      cout << users[i].getName() << endl;
      cout << "Age: " << users[i].getAge() << endl;
      cout << "Adress: ";
      users[i].printUserAdress();
      cout << endl;
    }
  }
}
