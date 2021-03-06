//cs457
//database.h
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Table{

	public:

		Table( string , string , vector<string> );//constructor
		Table( const Table& );		//copy constructor
		~Table();					//destructor

		//Data related
		string getName();			//returns table name
		string getDatabaseName();	//returns database name
		void printData();			//prints our table data
		void addMetaCol( string );	//edits metadata on command

		bool setMeta( string );		//sets meta data and returns status

	private:
		string name;				//Name of table
		string databaseName;		//Name of associated database
		vector<string> metaData;	//vector of the column types
};

class Database{

	public:
		Database( string );			//constructor
		Database( const Database& );//copy constructor
		~Database();				//desctructor

		//Data related
		string getName();	

		bool hasTable( string );	//returns 1 if database contains a table
		void addTable( Table& );	//pushes table to tableData vector
		void updateTableList();
		void deleteTable( string );	//removes table from tableData
		void alterTable( string , string , string );	//edits table based on command
		void printTable( string );
		void listTables();

	private:
		string name;				//name of table
		vector<string> metaData;	//Name, creation time, owner, etc (info given by user)
		vector<Table> tableData;	//vector containing tables
};
