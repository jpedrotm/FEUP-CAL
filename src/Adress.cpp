#include "Adress.h"

using namespace std;
Adress::Adress(Node local,Road street) {
	this->local=local;
	this->street=street;
}

Road Adress::getStreet() {
	return street;
}

Node Adress::getLocal() {
	return local;
}

void Adress::printAdress() {
	cout << "Local node: " << local.getID() << endl;
	cout << "Street name: " << street.getName() << endl;
}
