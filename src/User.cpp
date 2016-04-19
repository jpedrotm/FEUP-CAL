#include "User.h"

using namespace std;
User::User(string name, int age, Adress initAdress, Adress destAdress) {
  this->name = name;
  this->age = age;
  this->initAdress = initAdress;
  this->destAdress = destAdress;
}

User::User(string name, int age, Adress initAdress) {
  this->name = name;
  this->age = age;
  this->initAdress = initAdress;
}

User::User(string name,int age){
	this->name = name;
	this->age = age;
}

//------------------------------------------------------------------------------------------------
string User::getName() { return name; }

int User::getAge() { return age; }

Adress User::getUserAdress() { return initAdress; }

Adress User::getUserDestination() { return destAdress; }

//------------------------------------------------------------------------------------------------
void User::printUserAdress() { initAdress.printAdress(); }
