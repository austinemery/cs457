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
	name = givenName;
	databaseName = givenDatabaseName;
	for( int index = 0 ; index < givenMeta.size() ; index++ )
	{
		metaData.push_back(givenMeta[index]);
	}
}
Table::Table( const Table& givenTable )
{
	if( &givenTable != this )
	{
		name = givenTable.name;
		databaseName = givenTable.databaseName;
		for (int i = 0; i < givenTable.metaData.size(); i++)
		{
			metaData.push_back(givenTable.metaData[i]);
		}
	}
}
Table::~Table()
{
	name = '\0';
	databaseName = '\0';
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
}
void Table::addMetaCol( string givenCol )
{
	metaData.push_back(givenCol);
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
}
Database::Database( const Database& givenDatabase )
{
	if( &givenDatabase != this )
	{
		name = givenDatabase.name;
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

	if( command == "ADD" )
	{
		tableData[tableIndex].addMetaCol( givenMeta );
	}
}
void Database::printTable( string tableToPrint )
{
	int tableIndex = 0;

	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		if( tableToPrint == tableData[index].getName() )
		{
			tableIndex = index;
		}
	}

	tableData[tableIndex].printData();
}
void Database::updateTableList()
{
	string filePath = "./data/" + name + "/" + "Info";
	ofstream fout;
	fout.open(filePath.c_str(), ios::app);

	if(!fout.is_open())
	{
		cout << "--ERROR: Could not open ./data" << name << "/tableList.txt to write--" << endl;
		exit(1);
	}

	for(int i = 0 ; i < tableData.size() ; i++ )
	{
		fout << tableData[i].getName() << endl;
	}

	fout.close();
}
