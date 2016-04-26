#include "Interface.h"

using namespace std;

Interface::Interface(ReaderFiles r) {
	center=RideCenter(r);
}

void Interface::displayMenu() {
	int nOptions = 0;
	int option = 0;

	cout << "Welcome to RideSharing! Please choose a option." << endl;
	cout << "1-Insert new user." << endl;
	cout << "2-See all users." << endl;
	cout << "3-User information departure." << endl;
	cout << "4-Departure." << endl;
	cout << "5-Exit." << endl;

	option=selectMenu('1','4');

	option-='0';

	if (option == 1)
		newUser();
	else if (option == 2)
		displayUsers();
	else if (option == 3)
		defineUserDeparture();
	else if(option==4)
		departure();
	else if(option==5)
		return;
	else
		displayMenu();

	cout << endl;
}

void Interface::displayUsers() {

	if (users.size() == 0) {
		cout << "No users registered. Enter to main menu." << endl;
		string input;
		cin >> input;
		displayMenu();
	} else {
		cout << "Users registed: " << endl;
		for (unsigned int i = 0; i < users.size(); i++) {
			cout << "---------------------------------------" << endl;
			cout << users[i]->getName() << endl;
			cout << "Age: " << users[i]->getAge() << endl;
			cout << "---USER ADRESS---" << endl;
			users[i]->printUserAdress();
			cout << "---DEST ADRESS---" << endl;
			users[i]->printDestAdress();
			users[i]->printHoursAndNumPassengers();
			cout << endl;
		}
	}

	returnInput("Press any key.");

	displayMenu();
}

void Interface::newUser() {

	string name;
	int age, ID, i = 0,numP;
	Node N;
	Vertex<Node,Road> *v;

	name=returnInput("Name: ");

	age=returnInt("Age: ");

	while (true) {
		if (i == 0) {
			cout << "What is the ID of your Adress: ";
			cin >> ID;
			i++;
		} else {
			cout << "ID invalid, new ID again:";
			cin >> ID;
		}

		if((v=findPlace(Node(ID)))!=NULL)
			break;
	}

	Adress aInit = Adress(v->getInfo(), v->getAdj()[0].getEdgeInfo());

	string choice;

	while(choice!="yes" && choice!="no")
	{
		cout << "Want to go somewhere ?" << endl;
		cin >> choice;
	}

	string hI;
	string hF;

	if (choice == "yes") {
		i = 0;

		while(true){
		hI=returnInput("Hour to departure ?");
		hF=returnInput("Hour to arrive ?");
		if(hF>hI)
			break;
		else
			cout << "Not a possible choice. Please choose the hours again." << endl;
		}

		numP=returnInt("How many passengers can you transport ?");

		while (true) {
			if (i == 0) {
				cout << "What is the ID of your destiny Adress: ";
				cin >> ID;
				i++;
			} else {
				cout << "ID invalid, new ID again:";
				cin >> ID;
			}

			if ((v = findPlace(Node(ID))) != NULL)
				break;
		}

		Adress aDest = Adress(v->getInfo(), v->getAdj()[0].getEdgeInfo());

		User *u = new User(name, age, aInit, aDest,numP);
		u->setHoraInit(hI);
		u->setHoraFim(hF);

		users.push_back(u);
	}
	else{
		User *u = new User(name, age, aInit);

		users.push_back(u);
	}

	displayMenu();
}

vector<User*> Interface::getUsers() {
	vector<User*> U;

	for (unsigned int i = 0; i < users.size(); i++) {
		U.push_back(users[i]);
	}
	return U;
}

void Interface::defineUserDeparture(){

	if(users.size()==0)
	{
		cout << "No users." << endl;
		displayMenu();
	}

	string name;
	unsigned long nodeID;
	bool flag=true;
	Vertex<Node,Road> *v;
	int ID;
	int j=0;

	while (flag) {
		name=returnInput("What is the user name ?");
		nodeID=returnInt("What is the ID of the node ?");

		for (unsigned int i = 0; i < users.size(); i++) {
			if(users[i]->getName()==name && users[i]->getUserAdress().getLocal().getID()==nodeID)
			{
				string hI;
				string hF;
				cout << "Hour to departure ?" << endl;
				cin >> hI;
				cout << "Hour to arrive ?" << endl;
				cin >> hF;

				users[i]->setHoraInit(hI);
				users[i]->setHoraFim(hF);

				while (true) {
						if (j == 0) {
							cout << "What is the ID of your destiny adress: ";
							cin >> ID;
							j++;
						} else {
							cout << "ID invalid, new ID again:";
							cin >> ID;
						}

						if((v=findPlace(Node(ID)))!=NULL)
							break;
					}

				cout << v->getInfo().getID() << " | " << v->getAdj()[0].getEdgeInfo().getName() << endl;

				users[i]->setDestAdress(v->getInfo(),v->getAdj()[0].getEdgeInfo());

				flag = false;
				break;
			}
		}

	}

	displayMenu();

}

void Interface::departure(){
	string name;
	unsigned long ID;
	vector<Node> passPoints;
	bool flag=true;
	int numPassPicked=0;
	int numPass;
	User *u;

	while(flag){
	name=returnInput("What is the user ?");
	ID=returnInt("What is the user place ID ?");

	u=findUser(name,ID);

	if(!u->getWantDest())
	{
		cout << "User don't have a destiny for now." << endl;
		displayMenu();
	}

	if(u!=NULL)
		flag=false;
	else
		cout << "Invalid information. Please try again." << endl;
	}

	numPass=u->getNumPassegers();

	for(unsigned int i=0;i<users.size();i++)
	{
		if(users[i]!=u && users[i]->getWantDest() && users[i]->getNumPassegers()==0)
		{
			User *temp=users[i];
			if(temp->getHoraInit()>u->getHoraInit() && temp->getHoraFim()==u->getHoraFim() && users[i]->getUserDestination().getLocal()==u->getUserDestination().getLocal())
			{
				passPoints.push_back(users[i]->getUserAdress().getLocal());
				numPassPicked++;
			}
		}
		if(numPassPicked==numPass)
			break;
	}

	vector<Vertex<Node, Road> > teste = center.BestPath(u->getUserAdress().getLocal(),
			u->getUserDestination().getLocal(),passPoints, 0);

	center.displayGraph(teste);

	getchar();

	displayMenu();

}

Vertex<Node,Road> *Interface::findPlace(Node n) const{

	return center.getGraph().getVertex(n);
}

int Interface::returnInt(string s1)
{
	int tmp;

	bool fail = false;
	bool eof = false;

	do
	{
		std::cin.clear();

		if (fail && !eof)
			std::cin.ignore(100,'\n');

		std::cout << s1;
		std::cin >> tmp;

		fail = false;
		eof = false;

		if (std::cin.fail())
			fail = true;

		if (std::cin.eof())
			eof = true;
	} while(fail || eof);

	return tmp;
}

string Interface::returnInput(string s1)
{
	std::string tmp;
	bool valido = true;

	do
	{
		std::cin.clear();

		if (!valido)
			std::cout << "Introduza um nome nao vazio: ";
		else
			std::cout << s1;

		getline(std::cin, tmp);

		valido = false;

		for (size_t i = 0; i < tmp.size(); i++)
			if (tmp[i] != ' ')
				valido = true;
	} while(std::cin.eof() || !valido);

	for (size_t i = tmp.size() -1; i >= 0; i--)
	{
		if (tmp[i] != ' ')
		{
			tmp.resize(i+1);
			break;
		}
	}

	return tmp;
}

int Interface::selectMenu(char menor, char maior)
{
	std::string linha = "";

	while (linha.length() != 1)
	{
		getline(std::cin, linha);
		if (std::cin.eof())
			std::cin.clear();

		if (linha.length() != 1 || (linha.length() == 1 && (linha[0] < menor || linha[0] > maior)))
		{
			std::cout << "Opcao invalida. Introduza a opcao pretendida: ";
			linha = "";
		}
	}
	return linha[0];
}

User *Interface::findUser(string name,unsigned long ID) const{

	for(unsigned int i=0;i<users.size();i++)
	{
		if(users[i]->getName()==name && users[i]->getUserAdress().getLocal().getID()==ID)
			return users[i];
	}

	return NULL;
}

