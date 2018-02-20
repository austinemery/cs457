//cs457
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
		cout << "Yes" << endl;
	}
}
Table::~Table()
{
	metaData.clear();	
}
