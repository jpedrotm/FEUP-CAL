#include "Adress.h"

using namespace std;
Adress::Adress(string street, string local, int latitude, int longitude) {
  this->street = street;
  this->local = local;
  this->lat = latitude;
  this->lon = longitude;
}

string Adress::getStreet() { return street; }

string Adress::getLocal() { return local; }

int Adress::getLatitude() { return lat; }

int Adress::getLongitude() { return lon; }

void Adress::printAdress() {
  cout << street << ", " << local << " | "
       << "Latitude: " << lat << ", "
       << "Longitude: " << lon;
}
