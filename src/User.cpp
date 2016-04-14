#include "User.h"

using namespace std;
User::User(string name, int age, Adress adress, Trip trip) {
  this->name = name;
  this->age = age;
  this->adress = adress;
  this->trip = trip;
}

User::User(string name, int age, Adress adress) {
  this->name = name;
  this->age = age;
  this->adress = adress;
}

User::User(string name,int age){
	this->name = name;
	this->age = age;
}

//------------------------------------------------------------------------------------------------
string User::getName() { return name; }

int User::getAge() { return age; }

Adress User::getUserAdress() { return adress; }

Trip User::getUserTrip() { return trip; }

//------------------------------------------------------------------------------------------------
void User::printUserAdress() { adress.printAdress(); }
