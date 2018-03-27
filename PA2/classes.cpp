//cs457
//database.cpp
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include "classes.h"

/*
 * Class Implementation
 *       TABLE
 */
Table::Table( string givenName , string givenDatabaseName , vector<string> givenMeta )
{
	numbTuples = 0;
	name = givenName;
	databaseName = givenDatabaseName;

	for( int index = 0 ; index < givenMeta.size() ; index++ )
	{
		metaData.push_back(givenMeta[index]);
	}

	numbAtt = metaData.size();
}
Table::Table( const Table& givenTable )
{
	for( int i = 0 ; i < givenTable.numbTuples ; i++ )
	{
		for( int j = 0 ; j < givenTable.numbAtt ; j++ )
		{
			data[i][j] = "\0";
		}
	}
	numbTuples = givenTable.numbTuples;
	numbAtt = givenTable.numbAtt;
	metaData.clear();
	if( &givenTable != this )
	{
		name = givenTable.name;
		databaseName = givenTable.databaseName;
		for ( int i = 0; i < givenTable.metaData.size(); i++)
		{
			metaData.push_back(givenTable.metaData[i]);
		}

		for( int i = 0 ; i < givenTable.numbTuples ; i++ )
		{
			for( int j = 0 ; j < givenTable.numbAtt ; j++ )
			{
				data[i][j] = givenTable.data[i][j];
			}
		}
	}
}

Table::~Table()
{
	name = '\0';
	databaseName = '\0';
	numbTuples = 0;
	numbAtt = 0;
	metaData.clear();
}
void Table::printData()
{
	for( int index = 0 ; index < metaData.size() ; index++ )
	{
		if( index == ( metaData.size() - 1 ) )
		{
			cout << metaData[index] << endl;
		}
		else
		{
			cout << metaData[index] << " | ";			
		}
	}

	for( int index = 0 ; index < numbTuples ; index++ )
	{
		for( int jndex = 0 ; jndex < numbAtt ; jndex++ )
		{
			if( jndex == (numbAtt-1) )
			{
				cout << data[index][jndex] << endl;
			}
			else
			{
				cout << data[index][jndex] << " | ";				
			}

		}
	}
}

void Table::printQueryData( string query )
{
	//cout commas
	int commaCount = 0;
	for (int i = 0; i < query.length(); i++)
	{
		if (query[i] == ',')
		{
			commaCount++;
		}
	}

	vector<int> indexVec;

	for (int i = 0; i < commaCount; i++)
	{
		for (int j = 0; j < numbAtt; j++)
		{
			//see if string up untill comma is in metadata
			if (metaData[j].find(query.substr(0, query.find_first_of(','))) != string::npos)
			{
				cout << "query before comma: " << query.substr(0, query.find_first_of(',')) << endl;
				indexVec.push_back(j);
			}
		}
		//erase part untill comma
		query = query.substr(0, query.find_first_of(','));
		cout << "query after erase front: " << query << endl;
	}
	//grab last index
	for (int j = 0; j < numbAtt; j++)
	{
		if (metaData[j].find(query) != string::npos)
		{
			cout << "last query: " << query << endl;
			indexVec.push_back(j);
		}
	}

	//print query
	for (int index = 0 ; index < metaData.size() ; index++)
	{
		for (int jindex = 0; jindex < indexVec.size(); jindex++)
		{
			if (index == indexVec[jindex])
			{
				if( index == ( metaData.size() - 1 ) )
				{
					cout << metaData[index] << endl;
				}
				else
				{
					cout << metaData[index] << " | ";			
				}
			}
		}
	}

	for (int index = 0 ; index < numbTuples ; index++)
	{
		for (int jindex = 0 ; jindex < numbAtt ; jindex++)
		{
			for (int kindex = 0; kindex < indexVec.size(); kindex++)
			{
				if (jindex == indexVec[kindex])
				{
					if( jindex == (numbAtt - 1) )
					{
						cout << data[index][jindex] << endl;
					}
					else
					{
						cout << data[index][jindex] << " | ";				
					}
				}
			}
		}
	}
}

ofstream& Table::printDataFile( ofstream& fout )
{
	for( int index = 0 ; index < metaData.size() ; index++ )
	{
		if( index == ( metaData.size() - 1 ) )
		{
			fout << metaData[index] << endl;
		}
		else
		{
			fout << metaData[index] << " | ";			
		}
	}

	for( int index = 0 ; index < numbTuples ; index++ )
	{
		for( int jndex = 0 ; jndex < numbAtt ; jndex++ )
		{
			if( jndex == (numbAtt-1) )
			{
				fout << data[index][jndex] << endl;
			}
			else
			{
				fout << data[index][jndex] << " | ";				
			}

		}
	}

	return fout;
}
void Table::addMetaCol( string givenCol )
{
	metaData.push_back(givenCol);
}

void Table::addTuple( string givenData )
{
	vector<string> parsedTuple;
	string holdData;
	string assemblingData;
	int index = 0;

	while( givenData[0] != '\0' )
	{
		while( givenData[0] != ' ' )
		{

			holdData = givenData[0];
			assemblingData += holdData;
		
			givenData.erase(0,1);
		}
		givenData.erase(0,1);
		parsedTuple.push_back(assemblingData);

		assemblingData = "\0";
	}


	data.push_back(parsedTuple);


	numbTuples++;
}

void Table::updateTuple( string givenData )
{
	//givenData order - varToFind, toFind, varToSet, toSet

	//parse givenData

	string varToFind, toFind, varToSet, toSet;

	varToFind = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	toFind = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	varToSet = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	toSet = givenData;

	//cout << "Floop: " << varToFind << "|" << toFind << "|" << varToSet << "|" << toSet << endl;
	
	//find index of varToFind and index of varToSet
	int findIndex, setIndex;	

	for (int i = 0; i < numbAtt; i++)
	{
		//cout << "I: " << data[0][i] << endl;

		if (metaData[i].find(varToFind) != string::npos)
		{
			findIndex = i;
		}
		if (metaData[i].find(varToSet) != string::npos)
		{
			setIndex = i;
		}
		//cout << "Indicies: " << findIndex << " " << setIndex << endl;
	}
	
	//update tuple(s)
	for (int i = 0; i < numbTuples; i++)
	{
		if (data[i][findIndex] == toFind)
		{
			data[i][setIndex] = toSet;
			//cout << "The Data: " << data[i][setIndex] << endl;
		}
	}
}

void Table::deleteTuple( string givenData )
{
	//givenData order - varToDelete, compSign, toDelete

	//parse givenData

	string varToDelete, compSign, toDelete;

	varToDelete = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	compSign = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	toDelete = givenData;

	
	//find index of varToDelete and index of varToDelete
	int setIndex = 0;
	for (int i = 0; i < numbAtt; i++)
	{
		if (metaData[i].find(varToDelete) != string::npos)
		{
			setIndex = i;
		}
	}

	//delete tuple(s)
	if(compSign == "=")
	{
		for (int i = 0; i < numbTuples; i++)
		{
			if (data[i][setIndex] == toDelete)
			{
				cout << "Erasing: " << data[i][1] << endl;
				//data.erase(i);
			}
		}
	}
	else
	{
		float dataNum = stof(toDelete, NULL);
		if(compSign == ">")
		{
			for (int i = 0; i < numbTuples; i++)
			{
				if (dataNum > stof(data[i][setIndex], NULL))
				{
					cout << "Erasing: " << data[i][1] << endl;
					//data.erase(i);
				}
			}
		}
		else if(compSign == "<")
		{
			for (int i = 0; i < numbTuples; i++)
			{
				if (dataNum < stof(data[i][setIndex], NULL))
				{
					cout << "Erasing: " << data[i][1] << endl;
					//data.erase(i);
				}
			}
		}
	}
}

string Table::getName()
{
	return name;
}
string Table::getDatabaseName()
{
	return databaseName;
}


/*
 * Class Implementation
 *       DATABASE
 */
Database::Database( string givenName )
{
	name = givenName;
	tableData.clear();
}
Database::Database( const Database& givenDatabase )
{
	if( &givenDatabase != this )
	{
		tableData.clear();
		name = givenDatabase.name;
		
		for( int i = 0 ; i < givenDatabase.tableData.size() ; i++ )
		{
			tableData.push_back(givenDatabase.tableData[i]);
		}
	}
}
Database::~Database()
{
	metaData.clear();
	tableData.clear();
}
string Database::getName()
{
	return name;
}
void Database::addTable( Table& givenTable )
{
	tableData.push_back( givenTable );
}
void Database::deleteTable( string tableToDelete )
{
	int tableIndex = 0;

	for( tableIndex = 0 ; tableIndex < tableData.size() ; tableIndex++ )
	{
		if( tableToDelete == tableData[tableIndex].getName() )
		{
			break;
		}
	}

	tableData.erase(tableData.begin() + tableIndex);
}
bool Database::hasTable( string requestedTable )
{
	bool flag = false;

	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		if( tableData[index].getName() == requestedTable )
		{
			flag = true;
		}
	}

	return flag;
}
void Database::alterTable( string command, string whichTable , string givenMeta )
{
	int tableIndex = 0;

	for( tableIndex = 0 ; tableIndex < tableData.size() ; tableIndex++ )
	{
		if( whichTable == tableData[tableIndex].getName() )
		{
			break;
		}
	}

	if( command == "ADD" || command == "add" )
	{
		tableData[tableIndex].addMetaCol( givenMeta );
	}
	else if( command == "INSERT" || command == "insert" )
	{
		tableData[tableIndex].addTuple( givenMeta );
	}
	else if( command == "UPDATE" || command == "update" )
	{
		tableData[tableIndex].updateTuple( givenMeta );
	}
	else if( command == "DELETE" || command == "delete" )
	{
		tableData[tableIndex].deleteTuple( givenMeta );
	}
}
ofstream& Database::printTableFile( string tableToPrint, ofstream& fout )
{
	int tableIndex = 0;

	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		if( tableToPrint == tableData[index].getName() )
		{
			tableIndex = index;
		}
	}

	tableData[tableIndex].printDataFile(fout);

	return fout;
}
void Database::printTable( string tableToPrint , string printFlag , string queryString )
{
	int tableIndex = 0;

	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		if( tableToPrint == tableData[index].getName() )
		{
			tableIndex = index;
		}
	}
	
	if (printFlag == "all")
	{
		tableData[tableIndex].printData();
	}
	//query
	else if (printFlag == "some")
	{
		tableData[tableIndex].printQueryData(queryString);
	}
}
void Database::updateTableList()
{
	string toss;
	string filePath = "./data/" + name + "/" + "Info";

	vector<string> tempStringVec;
	
	ifstream fin;
	fin.open(filePath.c_str());
	
	if(!fin.is_open())
	{
		cout << "--ERROR: Could not open ./data" << name << "/Info to write--" << endl;
		exit(1);
	}

	while (getline(fin, toss))
	{	
		tempStringVec.push_back(toss);
		if (toss.find("List") != string::npos)
		{
			break;
		}
	}
	fin.close();

	ofstream fout;
	fout.open(filePath.c_str());

	if(!fout.is_open())
	{
		cout << "--ERROR: Could not open ./data" << name << "/Info to write--" << endl;
		exit(1);
	}

	for(int i = 0 ; i < tempStringVec.size() ; i++ )
	{
		fout << tempStringVec[i] << endl;
	}

	for(int i = 0 ; i < tableData.size() ; i++ )
	{
		fout << tableData[i].getName() << endl;
	}

	fout.close();
}

void Database::listTables()
{
	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		cout << tableData[index].getName() << endl;	
	}
}
