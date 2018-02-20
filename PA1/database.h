//cs457
//database.h
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Database{

	public:
		Database( string );
		Database( const Database& );
		~Database();

	private:
		string name;
		vector<string> metaData;
};