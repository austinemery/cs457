//cs457
//table.h
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include "table.h"

Table::Table( string givenName )
{
	name = givenName;
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
