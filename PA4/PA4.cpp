//cs457
//PA4.cpp
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 4

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <cctype>
#include "classes.h"

using namespace std;

int globalWorkingDatabase;	//int denoting database currently in use
bool globalProcessKey = false;

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
*	@return int - position of database if it does exist
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

/**	@fn void undercased
*	@brief causes all the letters in a string to be undercase
*	@pre requires existing string
*	@post editted string with all letters undercase
*	@return void
*/
void undercased(string& givenString);

int main()
{
	//general variables
	string testString = "nuke";

	string inputFromUser;

	string tempTableName;

	string nameOfTable;
	string command;
	string metaDataInQuestion;

	//used to hold database list info for running the program
	vector<Database> databaseList;

	readDatabaseList(databaseList);

	cout << endl << "This is a data management program!" << endl;
	cout << "Type COMMANDS for list of commands!" << endl;

	do
	{
		cin >> inputFromUser;

		undercased(inputFromUser);

		if (inputFromUser == "commands")
		{
			cout << endl << "--Command List--" << endl;
			cout << "listDatabases - Prints all directories" << endl;
			cout << "printWorkingDatabase - Prints working database" << endl;
			cout << "CREATE DATABASE <name>; - Creates a new database" << endl;
			cout << "DROP DATABASE <name>; - Deletes an existing database" << endl;
			cout << "CREATE TABLE <name>; - Creates a new table in the working database" << endl;
			cout << "DROP TABLE <name>; - Deletes an existing table in the working database" << endl;
			cout << "USE <name>; - Changes the working database" << endl;
			cout << "ALTER TABLE <name> <command> <alteration>; - Alter metadata of table" << endl;
			cout << "SELECT * FROM <name>; - Prints data of table" << endl;
			cout << ".EXIT - ends the program" << endl;
		}
		else if (inputFromUser.find("listd") != string::npos)
		{
			listDatabases(databaseList);
		}
		else if (inputFromUser.find("--") != string::npos)
		{
			getline(cin, inputFromUser);
		}
		else if (inputFromUser.find("printw") != string::npos)
		{
			printWorkingDatabase(databaseList);
		}
		else if ((inputFromUser.find("create") != string::npos))
		{
			cin >> inputFromUser;
			undercased(inputFromUser);

			if ((inputFromUser.find("database") != string::npos))
			{	
				cin >> inputFromUser;
				undercased(inputFromUser);
				createDatabase(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
				updateDatabaseList(databaseList);

			}
			else if ((inputFromUser.find("table") != string::npos))//CREATE TABLE tbl_1 (a1 int, a2 varchar(20)); 
			{
				//need to read until parenthesis here
				char tempChar = 'a';
				string reallyReallyTempString;
				tempTableName.erase(tempTableName.begin(), tempTableName.end());

				getchar();

				while (tempChar = getchar())
				{
					if (tempChar == '(')
					{
						break;
					}
					reallyReallyTempString = tempChar;
					tempTableName.append(reallyReallyTempString);
				}

				undercased(tempTableName);

				//cout << "TEST: |" << tempTableName << "|" << endl;

				vector<string> userGivenMetaData;
				int commaCount = 0;

				getline(cin, inputFromUser);

				//cout << "REEE: |" << inputFromUser << "|" << endl;

				//find how many commas exist
				for (int i = 0; i < inputFromUser.size(); ++i)
				{
					if (inputFromUser[i] == ',')
					{
						commaCount++;
					}
				}

				//get data parsed
				//inputFromUser = inputFromUser.substr(1);
				for (int i = 0; i < commaCount; ++i)
				{
					userGivenMetaData.push_back(inputFromUser.substr(0, inputFromUser.find(",")));
					inputFromUser = inputFromUser.substr(inputFromUser.find(",") + 1);
				}

				if (inputFromUser.find_first_of(")") != inputFromUser.find_last_of(")")) //if there are 2 ')'
				{
					userGivenMetaData.push_back(inputFromUser.substr(1, inputFromUser.find(")")));
				}
				else
				{
					userGivenMetaData.push_back(inputFromUser.substr(1, inputFromUser.find(")") - 1));
				}
				createTable(databaseList, tempTableName , userGivenMetaData);
			}		
		}
		else if ((inputFromUser.find("drop") != string::npos))
		{
			cin >> inputFromUser;
			undercased(inputFromUser);

			if ((inputFromUser.find("database") != string::npos))
			{	
				cin >> inputFromUser;
				undercased(inputFromUser);

				deleteDatabase(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
			}
			else if ((inputFromUser.find("table") != string::npos))
			{
				//do something
				cin >> inputFromUser;
				undercased(inputFromUser);

				deleteTable(databaseList, inputFromUser.substr(0,inputFromUser.length()-1));
			}	
		}
		else if ((inputFromUser.find("select") != string::npos))
		{
			databaseList.clear();
			readDatabaseList(databaseList);
			
			string stringsToQuery, tableName;
			string tempString;
			string printFlag = "all";
			string joinFlag = "none";
			string condition;

			cin >> inputFromUser;
			undercased(inputFromUser);
			if (inputFromUser.find("*") == string::npos)
			{
				stringsToQuery = inputFromUser;
				while (stringsToQuery.find("from") == string::npos)
				{
					cin >> tempString;
					stringsToQuery += tempString;
				}

				//remove "from" from stringsToQuery
				stringsToQuery = stringsToQuery.substr(0, stringsToQuery.length() - 4);
				printFlag = "some";
			}
			else
			{
				cin >> inputFromUser; // toss FROM we'll use this later
			}
			
			cin >> tableName; // Name of table
			undercased(tableName);
			string joinString;
			if (tableName.find(";") != string::npos)
			{
				tableName.erase(tableName.length() - 1, 1);
				databaseList[globalWorkingDatabase].printTable(tableName, printFlag, stringsToQuery, condition);
			}
			//there is more to parse
			else
			{
				cin >> inputFromUser;
				joinString = tableName;
				if (inputFromUser == "where")
				{
					//grab whole condition
					while (condition.find(';') == string::npos)
					{
						cin >> inputFromUser;

						condition += (inputFromUser + " ");
					}
					condition.erase(condition.find_last_of(';'));
					//cout << "condition after erase: " << condition << endl;

					if( databaseList[globalWorkingDatabase].hasTable(tableName))
					{
						databaseList[globalWorkingDatabase].printTable(tableName, printFlag, stringsToQuery, condition);
					}
					else
					{
						cout << "--!Failed to query table " << inputFromUser << " because it does not exist." << endl;
					}
				}
				//Join parsing
				else
				{
					//cout << "Join String at start: " << joinString << endl;

					while (inputFromUser.find("where") == string::npos && inputFromUser.find("on") == string::npos)
					{
						joinString.append(" " + inputFromUser);
						cin >> inputFromUser;
						//cout << "Join String inside loop: " << joinString << endl;
					}
					//cout << "Join String after loop: " << joinString << endl;

					//grab whole condition
					while (condition.find(';') == string::npos)
					{
						cin >> inputFromUser;

						condition += (inputFromUser + " ");
					}
					condition.erase(condition.find_last_of(';'));
					//cout << "condition after erase: " << condition << endl;

					//determine what join and print

					//inner join
					if (joinString.find(",") != string::npos || joinString.find("inner") != string::npos)
					{
						//cout << "INNER" << endl;
						string newStringWithoutLastChar = joinString.substr(0, joinString.find_last_of(" "));
		
						string leftTable = joinString.substr(0, joinString.find_first_of(" "));
						string rightTable = newStringWithoutLastChar.substr(newStringWithoutLastChar.find_last_of(" ") + 1, (newStringWithoutLastChar.length() - newStringWithoutLastChar.find_last_of(" ")));
						string leftAttribute = condition.substr(condition.find_first_of(".") + 1, (condition.find_first_of(" ") - condition.find_first_of(".") - 1));
						string rightAttribute = condition.substr(condition.find_last_of(".") + 1, (condition.length() - condition.find_last_of(".")));

						undercased(leftTable);
						undercased(rightTable);

						//cout << "|" << leftTable << "|" << rightTable << "|" << leftAttribute << "|" << rightAttribute << "|" << endl;

						databaseList[globalWorkingDatabase].innerJoin("*", leftTable, rightTable, leftAttribute, rightAttribute);
					}
					//outer join
					else if (joinString.find("outer") != string::npos)
					{
						//cout << "OUTER" << endl;
						string newStringWithoutLastChar = joinString.substr(0, joinString.find_last_of(" "));
		
						string leftTable = joinString.substr(0, joinString.find_first_of(" "));
						string rightTable = newStringWithoutLastChar.substr(newStringWithoutLastChar.find_last_of(" ") + 1, (newStringWithoutLastChar.length() - newStringWithoutLastChar.find_last_of(" ")));
						string leftAttribute = condition.substr(condition.find_first_of(".") + 1, (condition.find_first_of(" ") - condition.find_first_of(".") - 1));
						string rightAttribute = condition.substr(condition.find_last_of(".") + 1, (condition.length() - condition.find_last_of(".")));

						undercased(leftTable);
						undercased(rightTable);

						//cout << "|" << leftTable << "|" << rightTable << "|" << leftAttribute << "|" << rightAttribute << "|" << endl;

						databaseList[globalWorkingDatabase].leftJoin("*", leftTable, rightTable, leftAttribute, rightAttribute);
					}
				}
			}
		}
		else if ((inputFromUser.find("use") != string::npos))
		{
			databaseList.clear();
			readDatabaseList(databaseList);
			
			cin >> inputFromUser;
			undercased(inputFromUser);
			changeWorkingDatabase(databaseList, inputFromUser.substr(0, inputFromUser.length() - 1));
		}
		else if ((inputFromUser.find("alter") != string::npos))
		{
			cin >> inputFromUser;
			undercased(inputFromUser);
			if((inputFromUser.find("table") != string::npos))
			{
				//ALTER TABLE tbl_1 ADD a3 float;
				undercased(nameOfTable);
				cin >> command;
				cin >> metaDataInQuestion;
				cin >> inputFromUser;

				metaDataInQuestion = metaDataInQuestion + " " + inputFromUser.substr(0, inputFromUser.length()-1); 
				databaseList[globalWorkingDatabase].alterTable( command , nameOfTable , metaDataInQuestion );
				alterTable( databaseList , nameOfTable , command , metaDataInQuestion );
			}
		}
		else if ((inputFromUser.find("insert") != string::npos) )
		{
			string grab;
			string holdData = "\0";
			string assemblingData;
			metaDataInQuestion.clear();
			// insert into Product values(1, 'Gizmo', 19.99);
			command = inputFromUser;
			cin >> inputFromUser; //toss 'into'
			cin >> nameOfTable;
			undercased(nameOfTable);

			do
			{
				cin >> grab;
				metaDataInQuestion += grab;
			}while( !(grab.find(";") != string::npos) );

			grab = "\0";
			//Parse this


			metaDataInQuestion.erase( 0 , 7 );

			while( metaDataInQuestion[0] != ';' )
			{
				while( metaDataInQuestion[0] != ',' )
				{
					if( metaDataInQuestion[0] == '\'' || metaDataInQuestion[0] == '\"' )
					{
						metaDataInQuestion.erase(0,1);
						continue;
					} else if( metaDataInQuestion[0] == ')' )
					{
						break;
					}
					holdData = metaDataInQuestion[0];
					assemblingData += holdData;

					metaDataInQuestion.erase(0,1);
				}

				metaDataInQuestion.erase(0,1);

				grab += assemblingData + " ";
				assemblingData = "\0";		
			}

			databaseList[globalWorkingDatabase].alterTable( command , nameOfTable , grab );
			alterTable( databaseList , nameOfTable , command , grab );		
			cout << "1 new record inserted." << endl;
		}
		else if ((inputFromUser.find("update") != string::npos) )
		{
			string moreInput, tableName, toFind, toSet, varToFind, varToSet;
			cin >> tableName;
			undercased(tableName);
			cin >> moreInput;
			undercased(moreInput);

			//parse the command
			if (moreInput == "set")
			{
				cin >> varToSet;
				//for equal sign
				cin >> moreInput;
				cin >> toSet;
			
				//get rid of quotes if needed
				if (toSet.find("'") != string::npos)
				{
					toSet = toSet.substr(1, toSet.length() - 2);
				}

				cin >> moreInput;
				undercased(moreInput);
				if (moreInput == "where")
				{
					cin >> varToFind;
					//for equal sign
					cin >> moreInput;
					cin >> toFind;
	
					//remove ';' if needed
					if (toFind.find(";") != string::npos)
					{
						toFind = toFind.substr(0, toFind.length() - 1);				
					}
					//get rid of quotes if needed
					if (toFind.find("'") != string::npos)
					{
						toFind = toFind.substr(1, toFind.length() - 2);
					}
				}
			}
			string metaData = varToFind + " " + toFind + " " + varToSet + " " + toSet;

			databaseList[globalWorkingDatabase].alterTable( inputFromUser , tableName , metaData );
			alterTable( databaseList , tableName , inputFromUser , metaData );
		}		
		else if ((inputFromUser.find("delete") != string::npos) )
		{
			string moreInput, tableName, toDelete, varToDelete;
			cin >> moreInput;
			cin >> tableName;
			undercased(tableName);
			cin >> moreInput;
			undercased(moreInput);
			//parse the command
			if (moreInput == "where")
			{
				cin >> varToDelete;
				cin >> moreInput;	//for equal sign
				cin >> toDelete;
			
				//get rid of quotes if needed
				if (toDelete.find("'") != string::npos)
				{
					toDelete = toDelete.substr(1, toDelete.length() - 3);
				}
			}

			string metaData = varToDelete + " " + moreInput + " " + toDelete;
			//update table
			databaseList[globalWorkingDatabase].alterTable( inputFromUser , tableName , metaData );
			alterTable( databaseList , tableName , inputFromUser , metaData );
		}
		//***********************//
		//******BEGIN LOCKS******//
		//***********************//
		else if ((inputFromUser.find("begin") != string::npos) )
		{
			getline(cin, inputFromUser);
			cout << "Transaction starts." << endl;

			if(databaseList[globalWorkingDatabase].getTableLockStatus() == false) //check to make sure a table is locked
			{
				databaseList[globalWorkingDatabase].lockDatabase();
				globalProcessKey = true;
			}
		}
		else if ((inputFromUser.find("commit") != string::npos) )
		{
			getline(cin, inputFromUser);
			if(globalProcessKey == true)
			{
				databaseList[globalWorkingDatabase].unlockDatabase();
				globalProcessKey = false;

				cout << "Transaction committed." << endl;
			}
			else
			{
				cout << "Transaction abort." << endl;
			}
		}
		//***********************//
		//*******END LOCKS*******//
		//***********************//
		else if (inputFromUser == ".exit")
		{
			//not supposed to do anything! this way we can leave the loop without an issue.
			cout << "All done." << endl;
		}
		else 
		{
			cout << "--ERROR: Command not found, type commands for list--" << endl;
		}

	}while ( inputFromUser != ".exit" );

	updateDatabaseList(databaseList);
}
//change keyword to UPPERCASE
void undercased(string& givenString)
{
	for (int i=0; givenString[i]; i++) 
	{
		//handle '.exit'
		if( givenString[i] != '.' )
		{
			givenString[i] = tolower(givenString[i]);
		}
	}
}
//read in the database list
void readDatabaseList(vector<Database>& databaseVec)
{
	string tempString;
	string tempDataBaseName;
	string tempTableName;
	vector<string> dataFromFile;

	ifstream fin;
	ifstream tableIn;
	ifstream tableMetaIn;

	//notify user that data is being read from disk
	//cout << endl << "Reading data from Disk." << endl;

	fin.open("./data/databaseList.txt");
	
	if (!fin.is_open())
	{
		cout << "--ERROR: Could not open ./data/databaseList.txt to read--" << endl;
		exit(1);
	}

	vector<string> tempMetaData;
	string tempTableNames;
	int databaseIndex = 0;

	//while there are databases to read	
	while (fin >> tempDataBaseName)
	{
		tempMetaData.clear();

		Database holdDatabase(tempDataBaseName);
		databaseVec.push_back(holdDatabase);
		
		//read the tables as well
		tableIn.open(("./data/" + tempDataBaseName + "/Info").c_str());		
		
		if (!tableIn.is_open())
		{
			cout << "--ERROR: Could not open ./data/" << tempDataBaseName << "/Info to read--" << endl;
			exit(1);
		}

		while (tableIn >> tempTableName)
		{
			if (tempTableName.find("Tables-") != string::npos)
			{
				break;
			}
		}
		while (tableIn >> tempTableName)
		{
			tableMetaIn.open(("./data/" + tempDataBaseName + "/" + tempTableName).c_str());

			if (!tableMetaIn.is_open())
			{
				cout << "--ERROR: Could not open ./data/" << tempDataBaseName << "/Info to read--" << endl;
				exit(1);
			}


			//Read in the lock status.
			string getLock;
			getline(tableMetaIn , getLock);
			//Read in all data from file
			while (getline(tableMetaIn, tempString))
			{
				dataFromFile.push_back(tempString);
			}

			string assembleString;
			//Grab metadata
			while ( dataFromFile[0][0] != '\0' )
			{
				if( dataFromFile[0][0] != '|')
				{
					assembleString += dataFromFile[0][0];
				}
				else
				{
					if( assembleString[0] == ' ')
					{
						assembleString.erase(0,1);
					}
					if( assembleString[assembleString.length() - 1] == ' ')
					{
						assembleString.erase(assembleString.length() - 1, 1);
					}
					tempMetaData.push_back(assembleString);
					assembleString.clear();
				}

				dataFromFile[0].erase(0,1);
			}
			if( assembleString[0] == ' ')
			{
				assembleString.erase(0,1);
			}
			//push last string
			tempMetaData.push_back(assembleString);
			
			//create table with pulled meta
			Table tempTable(tempTableName, tempDataBaseName, tempMetaData);

			databaseVec[databaseIndex].addTable(tempTable);

			for( int i = 1 ; i < dataFromFile.size() ; i++ )
			{
				//Clean string to no longer have |
				for( int j = 0 ; j < dataFromFile[i].size() ; j++ )
				{
					if( dataFromFile[i][j] == '|' )
					{
						dataFromFile[i].erase(j,2);
					}
				}

				dataFromFile[i] += ' ';
				databaseVec[globalWorkingDatabase].alterTable( "insert" , tempTableName , dataFromFile[i] );
			}

			databaseVec[globalWorkingDatabase].setTableLockStatus( tempTableName , getLock );
			tempMetaData.clear();
			dataFromFile.clear();
			tableMetaIn.close();
		}
		tableIn.close();
		databaseIndex++;
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
		//physical side
		const int errorInt = system(("mkdir ./data/" + databaseName).c_str());
		if (errorInt == -1)
		{
			cout << "--ERROR: Could not make database--" << endl;
			cout << "--The file path used was ./data--" << endl;
		}
		
		//create database info file
		time_t rawtime;
  		struct tm * timeinfo;

		time (&rawtime);
		timeinfo = localtime (&rawtime);

		ofstream fout;
		fout.open(("./data/" + databaseName + "/Info").c_str());

		fout << "Database Name: " << databaseName << endl;
		fout << "Author: User" << endl;
		fout << "Date Created: " << asctime(timeinfo);
		fout << endl << "--List of Tables--" << endl;
		fout.close();

		//program side
		Database holdDatabase(databaseName);

		databaseVec.push_back(holdDatabase);

		globalWorkingDatabase = databaseVec.size()-1;

		updateDatabaseList(databaseVec);
		cout << "Database " << databaseVec[databaseVec.size()-1].getName() << " created." << endl;
	} 
	else
	{
		cout << "--!Failed to create database " << databaseName << " because it already exists." << endl;
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
		filePath.append(databaseVec[checkInt].getName());
		databaseVec.erase(databaseVec.begin() + checkInt);
		const int errorInt = system(("rm -r " + filePath).c_str());
		if (errorInt == -1)
		{
			cout << "--ERROR: Could not delete database--" << endl;
		}

		cout << "Database " << databaseName << " deleted." << endl;
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
		cout << "Using database " << newDatabase << "." << endl;
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
		cout << "Table " << tableName << " deleted." << endl;
	}
	else
	{
		cout << "--!Failed to delete " << tableName << " because it does not exist." << endl;
	}
	databaseVec[globalWorkingDatabase].updateTableList();
}
void createTable(vector<Database>& databaseVec, string tableName, vector<string> givenMetaData)
{
	undercased(tableName);

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
			
			int i;

			//output data to table	
			for (i = 0; i < givenMetaData.size() - 1; ++i)
			{
				fout << givenMetaData[i] << " | ";
			}
			fout << givenMetaData[i] << endl;
			fout.close();
		
			Table holdTable( tableName , databaseVec[globalWorkingDatabase].getName() , givenMetaData );
			databaseVec[globalWorkingDatabase].addTable( holdTable );

			//databaseVec[globalWorkingDatabase].printTable(tableName);
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
	databaseVec[globalWorkingDatabase].updateTableList();

}
void alterTable( vector<Database>& databaseVec , string nameOfTable , string command , string metaDataInQuestion )
{
	if( databaseVec[globalWorkingDatabase].hasTable(nameOfTable) )
	{
		// just make sure that 
	}
	else
	{
		cout << "--!Failed to query table " << nameOfTable << " because it does not exist." << endl;
	}
}




