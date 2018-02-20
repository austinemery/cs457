//cs457
//table.h
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 1

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Table{

	public:
		Table(string);
		Table(const Table&);
		~Table();

		//Data related


	private:
		string name;
		vector<string> metaData;
};