//cs457
//database.h
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Table{

	public:
		Table( string , string );	//constructor
		Table( const Table& );		//copy constructor
		~Table();					//desctructor

		//Data related
		string getName();			//returns name of table
		string getDatabaseName();	//returns name of database

		bool setMeta( string );		//

	private:
		string name;				//Name of table
		string databaseName;		//Name of associated database
		vector<string> metaData;	//
};

class Database{

	public:
		Database( string );			//constructor
		Database( const Database& );//copy constructor
		~Database();				//desctructor

		//Data related
		string getName();			//Returns name of database
		bool hasTable();			//If the database holds any table(s) return 1

	private:
		string name;				//name of table
		vector<string> metaData;	//
		vector<Table> tableData;	//vector containing tables
};