//cs457
//PA1.cpp
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "classes.h"

using namespace std;

int globalWorkingDirectory;

//read in the database list
void readDatabaseList(vector<Database>& databaseVec);

//updates the directory list by overiding the file
void updateDatabaseList(vector<Database>& databaseVec);

//creates a directory with the name of directoryName
void createDirectory(vector<Database>& databaseVec, string directoryName);

//deletes a directory with the name of directoryName
void deleteDirectory(vector<Database>& databaseVec, string directoryName);

//prints all directories
void listDirectories(vector<Database>& databaseVec);

//prints working directory
void printWorkingDirectory(vector<Database>& databaseVec);
//search vector to see if nameToCheck exists already, returns position in vector if ture, else returns -1
int directoryExistance(vector<Database>& databaseVec, string nameToCheck);

void changeWorkingDirectory(vector<Database>& databaseVec, string newDirectory);

void createTable(vector<Database>& databaseVec, string tableName);

int main()
{
	//general variables
	string testString = "nuke";

	string inputFromUser;

	//used to hold database list info for running the program
	vector<Database> databaseList;
	readDatabaseList(databaseList);

	cout << endl << "This is a data management program!" << endl;
	cout << "Type COMMANDS for list of commands!" << endl;

	do
	{
		cout << "Enter command: ";
		cin >> inputFromUser;

		if (inputFromUser == "COMMANDS")
		{
			cout << endl << "--Command List--" << endl;
			cout << "listDirectories - Prints all directories" << endl;
			cout << "printWorkingDirectory - Prints working directory" << endl;
			cout << "CREATE DATABASE <name> - Creates a new database" << endl;
			cout << "DROP DATABASE <name> - Deletes an existing database" << endl;
			cout << "CREATE TABLE <name> - Creates a new table in the working database" << endl;
			cout << "DROP TABLE <name> - Deletes an existing table in the working database" << endl;
			cout << "USE <name> - Changes the working directory" << endl;
			cout << "quit - ends the program" << endl;
		}
		else if (inputFromUser.find("listD") != string::npos)
		{
			listDirectories(databaseList);
		}
		else if (inputFromUser.find("printW") != string::npos)
		{
			printWorkingDirectory(databaseList);
		}
		else if (inputFromUser.find("CREATE") != string::npos)
		{
			cin >> inputFromUser;
			if (inputFromUser.find("DATABASE") != string::npos)
			{	
				cin >> inputFromUser;
				createDirectory(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
			}
			else if (inputFromUser.find("TABLE") != string::npos)
			{
				//do something
				cin >> inputFromUser;
				createTable(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
			}		
		}
		else if (inputFromUser.find("DROP") != string::npos)
		{
			cin >> inputFromUser;
			if (inputFromUser.find("DATABASE") != string::npos)
			{	
				cin >> inputFromUser;
				deleteDirectory(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
			}
			else if (inputFromUser.find("TABLE") != string::npos)
			{
				//do something
			}	
		}
		else if (inputFromUser.find("USE") != string::npos)
		{
			cin >> inputFromUser;
			changeWorkingDirectory(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
		}
		else if (inputFromUser == "quit" || inputFromUser == "exit"){}
		else 
		{
			cout << "--ERROR: Command not found, type commands for list--" << endl;
		}

	}while (inputFromUser != "exit" && inputFromUser != "quit");

	updateDatabaseList(databaseList);
}

//read in the database list
void readDatabaseList(vector<Database>& databaseVec)
{
	string tempString;

	ifstream fin;
	fin.open("./data/databaseList.txt");
	
	if (!fin.is_open())
	{
		cout << "--ERROR: Could not open data/databaseList.txt to read--" << endl;
		exit(1);
	}
	
	//if the file is not empty.
	if( !fin.eof() )
	{
		while (fin >> tempString)
		{
			Database holdDatabase(tempString);
			databaseVec.push_back( holdDatabase );
		}
	}

	fin.close();
}

//updates the directory list by overiding the file
void updateDatabaseList(vector<Database>& databaseVec)
{
	ofstream fout;
	fout.open("./data/databaseList.txt");

	if (!fout.is_open())
	{
		cout << "--ERROR: Could not open data/databaseList.txt to write--" << endl;
		exit(1);
	}

	for (int i = 0; i < databaseVec.size(); i++)
	{
		fout << databaseVec[i].getName() << endl;
	}

	fout.close();
}

//creates a directory with the name of directoryName
void createDirectory(vector<Database>& databaseVec, string directoryName)
{
	if( directoryExistance(databaseVec,directoryName) == -1 )
	{
		const int errorInt = system(("mkdir ./data/" + directoryName).c_str());
		if (errorInt == -1)
		{
			cout << "--ERROR: Could not make directory--" << endl;
			cout << "--The file path used was ./data--" << endl;
		}
		
		Database holdDatabase(directoryName);

		databaseVec.push_back(holdDatabase);

		globalWorkingDirectory = databaseVec.size()-1;

		updateDatabaseList(databaseVec);

		cout << "Database " << databaseVec[databaseVec.size()-1].getName() << " created." << endl;
	} else
	{
		cout << "!Failed to create database db_1 because it already exists." << endl;
	}

}

//deletes a directory with the name of directoryName
void deleteDirectory(vector<Database>& databaseVec, string directoryName)
{
	string filePath = "./data/";

	//check to see if it exists first
	int checkInt = directoryExistance(databaseVec, directoryName);

	if (checkInt == -1)
	{
		cout << "!Failed to delete "<< directoryName << " because it does not exist." << endl;
	}
	else
	{
		filePath.append(databaseVec[checkInt].getName()); //?
		databaseVec.erase(databaseVec.begin() + checkInt);
		const int errorInt = system(("rm -r " + filePath).c_str());
		if (errorInt == -1)
		{
			cout << "--ERROR: Could not delete database--" << endl;
		}
	}

	if (globalWorkingDirectory == checkInt || (databaseVec.size() == 0) )
	{
		globalWorkingDirectory = -1;
	}

	//update directory list file
	updateDatabaseList(databaseVec);
}

//prints all directories
void listDirectories(vector<Database>& databaseVec)
{
	cout << endl << "--Directory List--" << endl;
	for (int i = 0; i < databaseVec.size(); i++)
	{
		cout << databaseVec[i].getName() << endl;
	}
	cout << endl;
}

//prints working directory
void printWorkingDirectory(vector<Database>& databaseVec)
{
	if( databaseVec.size() != 0 )
	{
		cout << "Working Directory: " << databaseVec[globalWorkingDirectory].getName() << endl;		
	} else
	{
		cout << "!Failed, there is no working directory." << endl;
	}

}

//search vector to see if nameToCheck exists already, returns position in vector if ture, else returns -1
int directoryExistance(vector<Database>& databaseVec, string nameToCheck)
{
	for (int i = 0; i < databaseVec.size(); i++)
	{
		if (databaseVec[i].getName() == nameToCheck)
		{
			return i;
		}
	}
	
	return -1;	
}

void changeWorkingDirectory(vector<Database>& databaseVec, string newDirectory)
{
	//check if new is valid
	if (directoryExistance(databaseVec, newDirectory) != -1)
	{
		globalWorkingDirectory = directoryExistance(databaseVec, newDirectory);
	}
	else
	{
		cout << "!Failed, no such database." << endl;
	}
	
}

void createTable(vector<Database>& databaseVec, string tableName)
{
	if( globalWorkingDirectory != -1 )
	{

		ofstream fout;
		fout.open(("./data/" + databaseVec[globalWorkingDirectory].getName() + "/" + tableName + ".txt").c_str());

		if (!fout.is_open())
		{
			cout << "--ERROR: Could not create table--" << endl;
		}

		fout.close();		
	} else
	{
		cout << "!Failed, there is no working database." << endl;
	}

}
