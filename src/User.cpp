#include "User.h"

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

//------------------------------------------------------------------------------------------------
string User::getName() { return name; }

int User::getAge() { return age; }

Adress User::getUserAdress() { return adress; }

Trip User::getUserTrip() { return trip; }

//------------------------------------------------------------------------------------------------
void User::printUserAdress() { adress.printAdress(); }