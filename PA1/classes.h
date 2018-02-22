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

		Table( string , string , vector<string> );
		Table( const Table& );
		~Table();

		//Data related
		string getName();
		string getDatabaseName();
		void printData();
		void addMetaCol( string );

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
		string getName();
		bool hasTable( string );
		void addTable( Table& );
		void deleteTable( string );
		void alterTable( string , string , string );

	private:
		string name;				//name of table
		vector<string> metaData;	//
		vector<Table> tableData;	//vector containing tables
};