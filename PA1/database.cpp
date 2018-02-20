//cs457
//database.cpp
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include "database.h"

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
