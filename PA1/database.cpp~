/*TODO:

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

string globalWorkingDirectory;

void readDatabaseList(vector<string>&);

void updateDatabaseList(vector<string>&);

void createDirectory(vector<string>&, string);

void deleteDirectory(vector<string>&, string);

void listDirectories(vector<string>&);

void printWorkingDirectory();

int directoryExistance(vector<string>&, string);

void changeWorkingDirectory(vector<string>&, string);

void createTable(string);

int main()
{
	//general variables
	string testString = "nuke";

	string inputFromUser;

	//used to hold database list info for running the program
	vector<string> directoryList;

	readDatabaseList(directoryList);

	cout << endl << "This is a data management program!" << endl;
	cout << "Type commands for list of commands!" << endl;

	do
	{
		cout << "Enter command: ";
		cin >> inputFromUser;

		if (inputFromUser == "commands")
		{
			cout << endl << "--Command List--" << endl;
			cout << "listDirectories - Prints all directories" << endl;
			cout << "printWorkingDirectory - Prints working directory" << endl;
			cout << "createDirectory <name> - Creates a new directory" << endl;
			cout << "deleteDirectory <name> - Deletes a existing directory" << endl;
			cout << "changeDirectory <name> - Changes the working directory" << endl;
			cout << "createTable <name> - Creates a new table in the working directory" << endl;
			cout << "deleteTable <name> - Deletes a exiting table in the working directory" << endl;
			cout << "quit - ends the program" << endl;
		}
		else if (inputFromUser.find("listD") != string::npos)
		{
			listDirectories(directoryList);
		}
		else if (inputFromUser.find("printW") != string::npos)
		{
			printWorkingDirectory();
		}
		else if (inputFromUser.find("createD") != string::npos)
		{
			cin >> inputFromUser;
			createDirectory(directoryList, inputFromUser);
		}
		else if (inputFromUser.find("deleteD") != string::npos)
		{
			cin >> inputFromUser;
			deleteDirectory(directoryList, inputFromUser);
		}
		else if (inputFromUser.find("changeD") != string::npos)
		{
			cin >> inputFromUser;
			changeWorkingDirectory(directoryList, inputFromUser);
		}
		else 
		{
			cout << "--ERROR: Command not found, type commands for list--" << endl;
		}

	}while (inputFromUser != "exit" && inputFromUser != "quit");

	updateDatabaseList(directoryList);
	
}

//read in the database list
void readDatabaseList(vector<string>& directoryVec)
{
	string tempString;

	ifstream fin;
	fin.open("./data/databaseList.txt");
	
	if (!fin.is_open())
	{
		cout << "--ERROR: Could not open data/databaseList.txt to read--" << endl;
		exit(1);
	}
	
	while (fin >> tempString)
	{
		directoryVec.push_back(tempString);
	}

	fin.close();
}

//updates the directory list by overiding the file
void updateDatabaseList(vector<string>& directoryVec)
{
	ofstream fout;
	fout.open("./data/databaseList.txt");

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
	const int errorInt = system(("mkdir ./data/" + directoryName).c_str());
	if (errorInt == -1)
	{
		cout << "--ERROR: Could not make directory--" << endl;
		cout << "--The file path used was ./data--" << endl;
		exit(1);
	}
	
	directoryVec.push_back(directoryName);

	globalWorkingDirectory = directoryName;

	updateDatabaseList(directoryVec);
}

//deletes a directory with the name of directoryName
void deleteDirectory(vector<string>& directoryVec, string directoryName)
{
	string filePath = "./data/";

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

//prints all directories
void listDirectories(vector<string>& directoryVec)
{
	cout << endl << "--Directory List--" << endl;
	for (int i = 0; i < directoryVec.size(); i++)
	{
		cout << directoryVec[i] << endl;
	}
	cout << endl;
}

//prints working directory
void printWorkingDirectory()
{
	cout << globalWorkingDirectory;
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

void changeWorkingDirectory(vector<string>& directoryVec, string newDirectory)
{
	//check if new is valid
	if (directoryExistance(directoryVec, newDirectory) != -1)
	{
		globalWorkingDirectory = newDirectory;
	}
	else
	{
		cout << "--ERROR: Could not change working directory, new directory invalid--" << endl;
		exit(1);
	}
	
}

void createTable(string tableName)
{
	ofstream fout;
	fout.open(("./data/" + globalWorkingDirectory + "/" + tableName + ".txt").c_str());

	if (!fout.is_open())
	{
		cout << "--ERROR: Could not create table--" << endl;
		exit(1);
	}

	fout.close();
}












