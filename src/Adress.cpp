#include "Adress.h"

using namespace std;
Adress::Adress(string street, string local, int x, int y) {
  this->street = street;
  this->local = local;
  this->coordX = x;
  this->coordY = y;
}

string Adress::getStreet() { return street; }

string Adress::getLocal() { return local; }

int Adress::getCoordX() { return coordX; }

int Adress::getCoordY() { return coordY; }

void Adress::printAdress() {
  cout << street << ", " << local << " | "
       << "X: " << coordX << ", "
       << "Y: " << coordY;
}
