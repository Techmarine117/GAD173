#include "save.h"
using namespace std;

void  save::Saved(std::string fileName, std::string Filecontents)
{

	ofstream myfile;
	myfile.open(fileName + ".txt");
	myfile << Filecontents;

	myfile.close();


}

std::string save::Load(std::string fileName)
{

	fstream myfile;
	myfile.open(fileName + ".txt");
	std::string data;
	myfile >> data;


	myfile.close();
	return data;
}

