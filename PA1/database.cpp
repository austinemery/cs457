/*TODO:

reading the databaseList.txt is only reading the last element, need to fix that

make it so that the program get current working directory, instead of hardcoding the file path. We could use getcwd() while including unistd.h

add table functionality



*/

//cs457
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

void readDatabaseList(vector<string>&);

void updateDatabaseList(vector<string>&);

void createDirectory(vector<string>&, string);

void deleteDirectory(vector<string>&, string);

int directoryExistance(vector<string>&, string);

int main()
{
	//general variables
	string testString = "nuke";

	//used to hold databast list info for running the program
	vector<string> directoryList;

	readDatabaseList(directoryList);
/*
	if (directoryExistance(directoryList, testString) != -1)
	{
		cout << "--ERROR: Directory " << testString << " already exists--" << endl; 
	}
	else
	{
		createDirectory(directoryList, testString);
	}
*/
	cout << endl << directoryList.size() << endl;

	//print vector for testing
	for (int i = 0; i < directoryList.size(); i++)
	{
		cout << directoryList[i] << endl;
	}
	

	//deleteDirectory(directoryList, testString);

	//testString = "inbound";

	//createDirectory(directoryList, testString);
	
}

//read in the database list
void readDatabaseList(vector<string>& directoryVec)
{
	string tempString;

	ifstream fin;
	fin.open("data/databaseList.txt", ifstream::in);
	
	if (!fin.is_open())
	{
		cout << "--ERROR: Could not open data/databaseList.txt to read--" << endl;
		exit(1);
	}
	
	while(fin >> tempString);
	{
		directoryVec.push_back(tempString);
		cout << tempString << endl;
	}

	fin.close();
}

//updates the directory list by overiding the file
void updateDatabaseList(vector<string>& directoryVec)
{
	ofstream fout;
	fout.open("data/databaseList.txt", ofstream::out);

	if (!fout.is_open())
	{
		cout << "--ERROR: Could not open data/databaseList.txt to write--" << endl;
		exit(1);
	}

	for (int i = 0; i < directoryVec.size(); i++)
	{
		fout << directoryVec[i] << endl;
	}

	fout.close();
}

//creates a directory with the name of directoryName
void createDirectory(vector<string>& directoryVec, string directoryName)
{
	const int errorInt = system(("mkdir ~/cs457/PA1/data/" + directoryName).c_str());
	if (errorInt == -1)
	{
		cout << "--ERROR: Could not make directory--" << endl;
		cout << "--The file path used was ~/cs457/PA1/data--" << endl;
		exit(1);
	}
	
	directoryVec.push_back(directoryName);

	updateDatabaseList(directoryVec);
}

//deletes a directory with the name of directoryName
void deleteDirectory(vector<string>& directoryVec, string directoryName)
{
	string filePath = "~/cs457/PA1/data/";

	//check to see if it exists first
	int checkInt = directoryExistance(directoryVec, directoryName);

	if (checkInt == -1)
	{
		cout << "--ERROR: Cannot delete, directory does not exist--" << endl;
		exit(1); 
	}
	else
	{
		filePath.append(directoryVec[checkInt]);
		directoryVec.erase(directoryVec.begin() + checkInt);
		const int errorInt = system(("rm -r " + filePath).c_str());
		if (errorInt == -1)
		{
			cout << "--ERROR: Could not delete directory--" << endl;
			exit(1);
		}
	}

	//update directory list file
	updateDatabaseList(directoryVec);
}

//search vector to see if nameToCheck exists already, returns position in vector if ture, else returns -1
int directoryExistance(vector<string>& directoryVec, string nameToCheck)
{
	for (int i = 0; i < directoryVec.size(); i++)
	{
		if (directoryVec[i] == nameToCheck)
		{
			return i;
		}
	}
	
	return -1;	
}




