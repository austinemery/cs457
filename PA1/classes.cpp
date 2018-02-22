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
	
}
void Table::addCol( string givenCol )
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