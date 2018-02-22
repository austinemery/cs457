//cs457
//database.cpp
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include "classes.h"

/*
 * Class Implementation
 *       TABLE
 */
Table::Table( string givenName , string givenDatabaseName )
{
	name = givenName;
	databaseName = givenDatabaseName;
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
	metaData.clear();	
}
bool Table::setMeta( string givenMeta )
{

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

}
string Database::getName()
{
	return name;
}