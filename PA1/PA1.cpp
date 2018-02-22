//cs457
//PA1.cpp
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

//hoopla test boi

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "classes.h"

using namespace std;

int globalWorkingDatabase;	//int denoting database currently in use



/**	@fn void readDatabaseList
*	@brief read in the database list
*	@pre requires existing database(s)
*	@post no change
*	@return void
*/
void readDatabaseList(vector<Database>& databaseVec);

/**	@fn void updateDatabaseList
*	@brief updates the database list by overiding the file
*	@pre no requirments
*	@post overwrites database vector
*	@return void
*/
void updateDatabaseList(vector<Database>& databaseVec);

/**	@fn void createDatabase
*	@brief creates a database with the name of databaseName
*	@pre no requirments
*	@post adds to database vector
*	@return void
*/
void createDatabase(vector<Database>& databaseVec, string databaseName);

/**	@fn void deleteDatabase
*	@brief deletes a database with the name of databaseName
*	@pre requires existing database(s)
*	@post clears database vector
*	@return void
*/
void deleteDatabase(vector<Database>& databaseVec, string databaseName);

/**	@fn void listDatabases
*	@brief prints all directories
*	@pre requires existing database(s)
*	@post no change
*	@return void
*/
void listDatabases(vector<Database>& databaseVec);

/**	@fn void printWorkingDatabase
*	@brief prints working database
*	@pre requires existing database(s)
*	@post no change
*	@return void
*/
void printWorkingDatabase(vector<Database>& databaseVec);

/**	@fn int databaseExistance
*	@brief search vector to see if nameToCheck exists already, returns position in vector if ture, else returns -1
*	@pre requires existing database(s)
*	@post no change 
*	@return int
*/
int databaseExistance(vector<Database>& databaseVec, string nameToCheck);

/**	@fn void changeWorkingDatabase
*	@brief changes current database and updates global variable
*	@pre requires existing database(s)
*	@post changes global and moves frame
*	@return void
*/
void changeWorkingDatabase(vector<Database>& databaseVec, string newDatabase);

/**	@fn void createTable
*	@brief creates new table
*	@pre no requirements
*	@post adds to table vector
*	@return void
*/
void createTable(vector<Database>& databaseVec, string tableName, vector<string> givenMetaData);

/**	@fn void deleteTable
*	@brief deletes current table
*	@pre requires existing table(s)
*	@post removes table from vector
*	@return void
*/
void deleteTable( vector<Database>& databaseVec , string tableName );

/**	@fn void alterTable
*	@brief edits table based on command
*	@pre requires existing table(s)
*	@post edits table metadata in vector
*	@return void
*/
void alterTable( vector<Database>& databaseVec , string nameOfTable , string command , string metaDataInQuestion );

int main()
{
	//general variables
	string testString = "nuke";

	string inputFromUser;

	string tempTableName;

	//used to hold database list info for running the program
	vector<Database> databaseList;
	readDatabaseList(databaseList);

	cout << endl << "This is a data management program!" << endl;
	cout << "Type COMMANDS for list of commands!" << endl;

	do
	{
		cin >> inputFromUser;

		if (inputFromUser == "COMMANDS")
		{
			cout << endl << "--Command List--" << endl;
			cout << "listDatabases - Prints all directories" << endl;
			cout << "printWorkingDatabase - Prints working database" << endl;
			cout << "CREATE DATABASE <name> - Creates a new database" << endl;
			cout << "DROP DATABASE <name> - Deletes an existing database" << endl;
			cout << "CREATE TABLE <name> - Creates a new table in the working database" << endl;
			cout << "DROP TABLE <name> - Deletes an existing table in the working database" << endl;
			cout << "USE <name> - Changes the working database" << endl;
			cout << "quit - ends the program" << endl;
		}
		else if (inputFromUser.find("listD") != string::npos)
		{
			listDatabases(databaseList);
		}
		else if (inputFromUser.find("printW") != string::npos)
		{
			printWorkingDatabase(databaseList);
		}
		else if (inputFromUser.find("CREATE") != string::npos)
		{
			cin >> inputFromUser;
			
			if (inputFromUser.find("DATABASE") != string::npos)
			{	
				cin >> inputFromUser;
				createDatabase(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
			}
			else if (inputFromUser.find("TABLE") != string::npos) //CREATE TABLE tbl_1 (a1 int, a2 varchar(20)); 
			{
				cin >> tempTableName;
				
				vector<string> userGivenMetaData;
				int commaCount = 0;

				getline(cin, inputFromUser);

				//find how many commas exist
				for (int i = 0; i < inputFromUser.size(); ++i)
				{
					if (inputFromUser[i] == ',')
					{
						commaCount++;
					}
				}

				//get data parsed
				inputFromUser = inputFromUser.substr(1);
				for (int i = 0; i < commaCount; ++i)
				{
					userGivenMetaData.push_back(inputFromUser.substr(1, inputFromUser.find(",") - 1));
					inputFromUser = inputFromUser.substr(inputFromUser.find(",") + 1);
				}

				userGivenMetaData.push_back(inputFromUser.substr(1, inputFromUser.find(")")));

				createTable(databaseList, tempTableName , userGivenMetaData);
			}		
		}
		else if (inputFromUser.find("DROP") != string::npos)
		{
			cin >> inputFromUser;
			if (inputFromUser.find("DATABASE") != string::npos)
			{	
				cin >> inputFromUser;
				deleteDatabase(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
			}
			else if (inputFromUser.find("TABLE") != string::npos)
			{
				//do something
				cin >> inputFromUser;
				deleteTable(databaseList, inputFromUser.substr(0,inputFromUser.length()-1));
			}	
		}
		else if (inputFromUser.find("SELECT") != string::npos)
		{
			cin >> inputFromUser; // toss * we'll use this later
			cin >> inputFromUser; // toss FROM we'll use this later
			cin >> inputFromUser; // Name of table

			if( databaseList[globalWorkingDatabase].hasTable(inputFromUser))
			{
				databaseList[globalWorkingDatabase].printTable(inputFromUser);
			}
			else
			{
				cout << "--!Failed table " << inputFromUser << " does not exist." << endl;
			}
		}
		else if (inputFromUser.find("USE") != string::npos)
		{
			cin >> inputFromUser;
			changeWorkingDatabase(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
		}
		else if (inputFromUser.find("ALTER") != string::npos)
		{
			cin >> inputFromUser;
			if( inputFromUser.find("TABLE") != string::npos)
			{
				string nameOfTable;
				string command;
				string metaDataInQuestion;
				//ALTER TABLE tbl_1 ADD a3 float;
				cin >> nameOfTable;
				cin >> command;
				cin >> metaDataInQuestion;
				cin >> inputFromUser;

				metaDataInQuestion = metaDataInQuestion + " " + inputFromUser.substr(0, inputFromUser.length()-1);

				alterTable( databaseList , nameOfTable , command , metaDataInQuestion );
			}
		}
		else if ( inputFromUser == ".EXIT" )
		{
			//not supposed to do anything! this way we can leave the loop without an issue.
			cout << "All done." << endl;
		}
		else 
		{
			cout << "--ERROR: Command not found, type commands for list--" << endl;
		}

	}while ( inputFromUser != ".EXIT" );

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
	
	while (fin >> tempString)
	{
		Database holdDatabase(tempString);
		databaseVec.push_back( holdDatabase );
	}
	
	fin.close();
}

//updates the database list by overiding the file
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

//creates a database with the name of databaseName
void createDatabase(vector<Database>& databaseVec, string databaseName)
{
	if( databaseExistance(databaseVec,databaseName) == -1 )
	{
		const int errorInt = system(("mkdir ./data/" + databaseName).c_str());
		if (errorInt == -1)
		{
			cout << "--ERROR: Could not make database--" << endl;
			cout << "--The file path used was ./data--" << endl;
		}
		
		Database holdDatabase(databaseName);

		databaseVec.push_back(holdDatabase);

		globalWorkingDatabase = databaseVec.size()-1;

		updateDatabaseList(databaseVec);

		cout << "Database " << databaseVec[databaseVec.size()-1].getName() << " created." << endl;
	} else
	{
		cout << "--!Failed to create database db_1 because it already exists." << endl;
	}

}

//deletes a database with the name of databaseName
void deleteDatabase(vector<Database>& databaseVec, string databaseName)
{
	string filePath = "./data/";

	//check to see if it exists first
	int checkInt = databaseExistance(databaseVec, databaseName);

	if (checkInt == -1)
	{
		cout << "--!Failed to delete "<< databaseName << " because it does not exist." << endl;
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

		cout << "--Database " << databaseName << " deleted." << endl;
	}

	if (globalWorkingDatabase == checkInt || (databaseVec.size() == 0) )
	{
		globalWorkingDatabase = -1;
	}

	//update database list file
	updateDatabaseList(databaseVec);
}

//prints all directories
void listDatabases(vector<Database>& databaseVec)
{
	cout << endl << "--Database List--" << endl;
	for (int i = 0; i < databaseVec.size(); i++)
	{
		cout << databaseVec[i].getName() << endl;
	}
	cout << endl;
}

//prints working database
void printWorkingDatabase(vector<Database>& databaseVec)
{
	if( databaseVec.size() != 0 )
	{
		cout << "Working Database: " << databaseVec[globalWorkingDatabase].getName() << endl;		
	} 
	else
	{
		cout << "--!Failed, there is no working database." << endl;
	}

}

//search vector to see if nameToCheck exists already, returns position in vector if ture, else returns -1
int databaseExistance(vector<Database>& databaseVec, string nameToCheck)
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

void changeWorkingDatabase(vector<Database>& databaseVec, string newDatabase)
{
	//check if new is valid
	if (databaseExistance(databaseVec, newDatabase) != -1)
	{
		globalWorkingDatabase = databaseExistance(databaseVec, newDatabase);
	}
	else
	{
		cout << "--!Failed, no such database." << endl;
	}
	
}
void deleteTable( vector<Database>& databaseVec , string tableName )
{
	if( databaseVec[globalWorkingDatabase].hasTable(tableName) )
	{
		databaseVec[globalWorkingDatabase].deleteTable(tableName);
		system(("rm -r ./data/" + databaseVec[globalWorkingDatabase].getName() + "/" + tableName).c_str());
		cout << "-- Table " << tableName << " deleted." << endl;
	}
	else
	{
		cout << "--!Failed to delete " << tableName << " because it does not exist." << endl;
	}
}
void createTable(vector<Database>& databaseVec, string tableName, vector<string> givenMetaData)
{

	if( globalWorkingDatabase != -1 )
	{
		if( !databaseVec[globalWorkingDatabase].hasTable(tableName) )
		{
			ofstream fout;
			fout.open(("./data/" + databaseVec[globalWorkingDatabase].getName() + "/" + tableName).c_str());

			if (!fout.is_open())
			{
				cout << "--ERROR: Could not create table--" << endl;
			}

			//output data to table	
			for (int i = 0; i < givenMetaData.size(); ++i)
			{
				fout << givenMetaData[i] << endl;
			}

			fout.close();
		
			Table holdTable( tableName , databaseVec[globalWorkingDatabase].getName() , givenMetaData );
			databaseVec[globalWorkingDatabase].addTable( holdTable );

			databaseVec[globalWorkingDatabase].printTable(tableName);
			cout << "Table " << tableName << " created." << endl;
		}
		else
		{
			cout << "--!Failed to create table " << tableName << " because it already exists." << endl;
		}
		
	} 
	else
	{
		cout << "--!Failed, there is no working database." << endl;
	}

}
void alterTable( vector<Database>& databaseVec , string nameOfTable , string command , string metaDataInQuestion )
{
	if( databaseVec[globalWorkingDatabase].hasTable(nameOfTable) )
	{
		databaseVec[globalWorkingDatabase].alterTable( command , nameOfTable , metaDataInQuestion );

		cout << "Table " << nameOfTable << " has been altered." << endl;
	}
	else
	{
		cout << "-- !Failed to query table " << nameOfTable << " because it does not exist." << endl;
	}
}
