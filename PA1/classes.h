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
		void addCol( string );
	private:
		string name;
		string databaseName;
		vector<string> metaData;
};

class Database{

	public:
		Database( string );
		Database( const Database& );
		~Database();

		//Data related
		string getName();
		bool hasTable( string );
		void addTable( Table& );

	private:
		string name;
		vector<string> metaData;
		vector<Table> tableData;
};