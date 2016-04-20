#include "ReaderFiles.h"

ReaderFiles::ReaderFiles(){
	readFileNameNodes();
	readFileNameRoads();
	readFileNameRelation();
}

void ReaderFiles::readFileNameNodes(){

	ifstream myfile("files1.txt");

	if(myfile.is_open())
	{
		string line;
		char trash;
		unsigned long nodeID;
		int lat_degrees,lon_degrees,lat_rad,lon_rad;
		while(getline(myfile,line))
		{
			if(line=="\n")
				break;

			stringstream ss;

			ss.str(line);

			ss >> nodeID >> trash;
			ss >> lat_degrees >> trash;
			ss >> lon_degrees >> trash;
			ss >> lat_rad >> trash;
			ss >> lon_rad;

			double x = 6371000 * cos(lat_rad) * cos(lon_rad);
			double y = 6371000 * cos(lat_rad) * sin(lon_rad);
			double z = 6371000 * cos(lat_rad);

			nodes.push_back(Node(nodeID,x,y,z));
		}
	}

	myfile.close();

	for(unsigned int i=0;i<nodes.size();i++)
	{
		cout << nodes[i].getID() << endl;
	}
}

void ReaderFiles::readFileNameRoads(){
	ifstream myfile("files2.txt");

		if(myfile.is_open())
		{
			string line,lineTrash;
			char trash;
			unsigned long roadID;
			string roadName;
			string twoWaysName;
			bool twoWays;
			while(myfile.good())
			{
				if(line=="\n")
					break;

				myfile >> roadID >> trash;

				getline(myfile,roadName,';');
				getline(myfile,twoWaysName,'\n');

				if(twoWaysName=="True")
					twoWays=true;
				else
					twoWays=false;

				if(myfile.eof())
					break;

				roads.push_back(Road(roadID,roadName,twoWays));

			}
		}

		myfile.close();

		for(unsigned int i=0;i<roads.size();i++)
		{
			cout << roads[i].getID() << " | " << roads[i].getName() << " | " << roads[i].getIsTwoWays() << endl;
		}

}

void ReaderFiles::readFileNameRelation(){
	ifstream myfile("files3.txt");

	if (myfile.is_open()) {
		string line;
		char trash;
		unsigned long roadID,node1ID,node2ID;
		while (getline(myfile, line)) {

			if (line == "\n")
				break;

			stringstream ss;

			ss.str(line);

			ss >> roadID;
			ss >> trash;
			ss >> node1ID;
			ss >> trash;
			ss >> node2ID;

			relations.push_back(Relation(roadID,node1ID,node2ID));

		}
	}

	myfile.close();

	for(unsigned int i=0;i<relations.size();i++)
	{
		cout << relations[i].getRoadID() << " | " << relations[i].getNode1ID() << " | " << relations[i].getNode2ID() << endl;
	}
}

vector<Node> ReaderFiles::getNodes() const{
	return nodes;
}

vector<Road> ReaderFiles::getRoads() const{
	return roads;
}

vector<Relation> ReaderFiles::getRelations() const{
	return relations;
}

