//cs457
//database.cpp
//Austin Emery, Mercedes Anderson, Nickolas Johnson
//Project 4

#include "classes.h"

/*
 * Class Implementation
 *       TABLE
 */
Table::Table( string givenName , string givenDatabaseName , vector<string> givenMeta )
{
	numbTuples = 0;
	name = givenName;
	databaseName = givenDatabaseName;
	locked = false;

	for( int index = 0 ; index < givenMeta.size() ; index++ )
	{
		metaData.push_back(givenMeta[index]);
	}

	numbAtt = metaData.size();
}
Table::Table( const Table& givenTable )
{
	locked = givenTable.locked;
	for( int i = 0 ; i < givenTable.numbTuples ; i++ )
	{
		for( int j = 0 ; j < givenTable.numbAtt ; j++ )
		{
			data[i][j] = "\0";
		}
	}
	numbTuples = givenTable.numbTuples;
	numbAtt = givenTable.numbAtt;
	metaData.clear();

	if( &givenTable != this )
	{
		name = givenTable.name;
		databaseName = givenTable.databaseName;

		for ( int i = 0; i < givenTable.metaData.size(); i++)
		{
			metaData.push_back(givenTable.metaData[i]);
		}

		for( int i = 0 ; i < givenTable.numbTuples ; i++ )
		{	
			for( int j = 0 ; j < givenTable.numbAtt ; j++ )
			{
				data[i][j] = givenTable.data[i][j];
			}
		}
	}
}

Table::~Table()
{
	name = '\0';
	databaseName = '\0';
	numbTuples = 0;
	numbAtt = 0;
	metaData.clear();
}
void Table::printData()
{
	for( int index = 0 ; index < metaData.size() ; index++ )
	{
		if( index == ( metaData.size() - 1 ) )
		{
			cout << metaData[index] << endl;
		}
		else
		{
			cout << metaData[index] << " | ";			
		}
	}

	for( int index = 0 ; index < numbTuples ; index++ )
	{
		for( int jndex = 0 ; jndex < numbAtt ; jndex++ )
		{
			if( jndex == (numbAtt-1) )
			{
				cout << data[index][jndex] << endl;
			}
			else
			{
				cout << data[index][jndex] << " | ";				
			}
		}
	}
}

void Table::printQueryData( string query, string condition)
{
	//count commas
	int commaCount = 0;
	for (int i = 0; i < query.length(); i++)
	{
		if (query[i] == ',')
		{
			commaCount++;
		}
	}

	//get condition ready
	string varToFind = condition.substr(0, condition.find_first_of(" "));
	//cout << "Var to Find: " << varToFind << endl;
	
	string operation = condition.substr(condition.find_first_of(" ") + 1, condition.find_last_of(" ") - condition.find_first_of(" ") - 1);
	//cout << "Operation: " << operation << endl;

	string toFind = condition.substr(condition.find_last_of(" ") + 1, condition.length() - condition.find_last_of(" "));
	//cout << "To Find: " << toFind << endl;

	vector<int> indexVec;
	int varToFindIndex;

	for (int i = 0; i < commaCount; i++)
	{
		for (int j = 0; j < numbAtt; j++)
		{
			//see if string up untill comma is in metadata
			if (metaData[j].find(query.substr(0, query.find_first_of(','))) != string::npos)
			{
				//cout << "query before comma: " << query.substr(0, query.find_first_of(',')) << endl;
				indexVec.push_back(j);
			}
		}
		//erase part untill comma
		query.erase(0, query.find_first_of(',') + 1);
		//cout << "query after erase front: " << query << endl;
	}
	//grab last index
	for (int j = 0; j < numbAtt; j++)
	{
		if (metaData[j].find(query) != string::npos)
		{
			//cout << "last query: " << query << endl;
			indexVec.push_back(j);
		}
	}

	//grab conditional index to look for
	for (int j = 0; j < numbAtt; j++)
	{
		if (metaData[j].find(varToFind) != string::npos)
		{
			varToFindIndex = j;
		}
	}

	//print metadata
	for (int index = 0 ; index < metaData.size() ; index++)
	{
		for (int jindex = 0; jindex < indexVec.size(); jindex++)
		{
			if (index == indexVec[jindex])
			{
				if( index == ( metaData.size() - 1 ) )
				{
					cout << metaData[index] << endl;
				}
				else
				{
					cout << metaData[index] << " | ";			
				}
			}
		}
	}

	//print data. The operation is check first, to see if it is true or not, then it will query the appropriate attributes
	for (int index = 0 ; index < numbTuples ; index++)
	{
		for (int jindex = 0 ; jindex < numbAtt ; jindex++)
		{
			for (int kindex = 0; kindex < indexVec.size(); kindex++)
			{	
				if (operation == "=")
				{
					if (data[index][varToFindIndex] == toFind)
					{
						if (jindex == indexVec[kindex])
						{
							if( jindex == (numbAtt - 1) )
							{
								cout << data[index][jindex] << endl;
							}
							else
							{
								cout << data[index][jindex] << " | ";				
							}
						}
					}
				}
				else if (operation == "!=")
				{
					if (data[index][varToFindIndex] != toFind)
					{
						if (jindex == indexVec[kindex])
						{
							if( jindex == (numbAtt - 1) )
							{
								cout << data[index][jindex] << endl;
							}
							else
							{
								cout << data[index][jindex] << " | ";				
							}
						}
					}
				}
				else if (operation == ">")
				{
					if (data[index][varToFindIndex] > toFind)
					{
						if (jindex == indexVec[kindex])
						{
							if( jindex == (numbAtt - 1) )
							{
								cout << data[index][jindex] << endl;
							}
							else
							{
								cout << data[index][jindex] << " | ";				
							}
						}
					}
				}
				else if (operation == ">=")
				{
					if (data[index][varToFindIndex] >= toFind)
					{
						if (jindex == indexVec[kindex])
						{
							if( jindex == (numbAtt - 1) )
							{
								cout << data[index][jindex] << endl;
							}
							else
							{
								cout << data[index][jindex] << " | ";				
							}
						}
					}
				}
				else if (operation == "<")
				{
					if (data[index][varToFindIndex] < toFind)
					{
						if (jindex == indexVec[kindex])
						{
							if( jindex == (numbAtt - 1) )
							{
								cout << data[index][jindex] << endl;
							}
							else
							{
								cout << data[index][jindex] << " | ";				
							}
						}
					}
				}
				else if (operation == "<=")
				{
					if (data[index][varToFindIndex] <= toFind)
					{
						if (jindex == indexVec[kindex])
						{
							if( jindex == (numbAtt - 1) )
							{
								cout << data[index][jindex] << endl;
							}
							else
							{
								cout << data[index][jindex] << " | ";				
							}
						}
					}
				}
			}
		}
	}
}

ofstream& Table::printDataFile( ofstream& fout )
{
	if( locked )
	{
		fout << "L" << endl;
	}
	else
	{
		fout << "U" << endl;
	}
	for( int index = 0 ; index < metaData.size() ; index++ )
	{
		if( index == ( metaData.size() - 1 ) )
		{
			fout << metaData[index] << endl;
		}
		else
		{
			fout << metaData[index] << " | ";			
		}
	}

	for( int index = 0 ; index < numbTuples ; index++ )
	{
		for( int jndex = 0 ; jndex < numbAtt ; jndex++ )
		{
			if( jndex == (numbAtt-1) )
			{
				fout << data[index][jndex] << endl;
			}
			else
			{
				fout << data[index][jndex] << " | ";				
			}

		}
	}

	return fout;
}
void Table::addMetaCol( string givenCol )
{
	metaData.push_back(givenCol);
}

void Table::addTuple( string givenData )
{
	vector<string> parsedTuple;
	string holdData;
	string assemblingData;
	int index = 0;

	while( givenData[0] != '\0' )
	{
		while( givenData[0] != ' ' )
		{

			holdData = givenData[0];
			assemblingData += holdData;
		
			givenData.erase(0,1);
		}
		givenData.erase(0,1);
		parsedTuple.push_back(assemblingData);

		assemblingData = "\0";
	}

	data.push_back(parsedTuple);
	numbTuples++;

	//printData();
}

void Table::updateTuple( string givenData )
{
	int numbChanges = 0;

	//givenData order - varToFind, toFind, varToSet, toSet

	//parse givenData

	string varToFind, toFind, varToSet, toSet;

	varToFind = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	toFind = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	varToSet = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	toSet = givenData;

	//cout << "Floop: " << varToFind << "|" << toFind << "|" << varToSet << "|" << toSet << endl;
	
	//find index of varToFind and index of varToSet
	int findIndex, setIndex;	

	for (int i = 0; i < numbAtt; i++)
	{
		//cout << "I: " << data[0][i] << endl;

		if (metaData[i].find(varToFind) != string::npos)
		{
			findIndex = i;
		}
		if (metaData[i].find(varToSet) != string::npos)
		{
			setIndex = i;
		}
		//cout << "Indicies: " << findIndex << " " << setIndex << endl;
	}
	
	//update tuple(s)
	for (int i = 0; i < numbTuples; i++)
	{
		if (data[i][findIndex] == toFind)
		{
			data[i][setIndex] = toSet;
			numbChanges++;
			//cout << "The Data: " << data[i][setIndex] << endl;
		}
	}

	//print how many records modified
	if (numbChanges == 1)
	{
		cout << "1 record modified." << endl;
	}
	else
	{
		cout << numbChanges << " records modified." << endl;
	}
}

void Table::deleteTuple( string givenData )
{
	//givenData order - varToDelete, compSign, toDelete

	//parse givenData

	string varToDelete, compSign, toDelete, temp;

	temp = givenData;

	varToDelete = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	compSign = givenData.substr(0, givenData.find_first_of(" "));
	givenData.erase(0, givenData.find_first_of(" ") + 1);

	toDelete = givenData;

	
	//find index of varToDelete and index of varToDelete
	int setIndex = 0;
	for (int i = 0; i < numbAtt; i++)
	{
		if (metaData[i].find(varToDelete) != string::npos)
		{
			setIndex = i;
		}
	}

	//delete tuple(s)
	int deleteCount = 0;

	if(compSign == "=")	//equal to delete
	{
		for (int i = 0; i < numbTuples; i++)
		{
			if (data[i][setIndex] == toDelete)
			{
				data.erase(data.begin() + i);
				numbTuples--;
				deleteCount++;
			}
		}
	}
	else if(compSign == "!=")	//not equal to delte
	{
		for (int i = 0; i < numbTuples; i++)
		{
			if (data[i][setIndex] != toDelete)
			{
				data.erase(data.begin() + i);
				numbTuples--;
				deleteCount++;
			}
		}
	}
	else
	{
		float dataNum = stof(toDelete, NULL);	//sets to float if a number is compared
		if(compSign == ">")	//greater than delete
		{
			for (int i = 0; i < numbTuples; i++)
			{
				if (dataNum < stof(data[i][setIndex], NULL))
				{
					data.erase(data.begin() + i);
					numbTuples--;
					deleteCount++;
				}
			}
		}
		else if(compSign == ">=")	//greater than delete
		{
			for (int i = 0; i < numbTuples; i++)
			{
				if (dataNum <= stof(data[i][setIndex], NULL))
				{
					data.erase(data.begin() + i);
					numbTuples--;
					deleteCount++;
				}
			}
		}
		else if(compSign == "<")	//less than delete
		{
			for (int i = 0; i < numbTuples; i++)
			{
				if (dataNum > stof(data[i][setIndex], NULL))
				{
					data.erase(data.begin() + i);
					numbTuples--;
					deleteCount++;
				}
			}
		}
		else if(compSign == "<=")	//less than delete
		{
			for (int i = 0; i < numbTuples; i++)
			{
				if (dataNum >= stof(data[i][setIndex], NULL))
				{
					data.erase(data.begin() + i);
					numbTuples--;
					deleteCount++;
				}
			}
		}
	}
	if (deleteCount == 1)
	{
		cout << deleteCount << " record deleted." << endl;
	}
	else if (deleteCount > 1)
	{
		cout << deleteCount << " records deleted." << endl;
	}
}

string Table::getName()
{
	return name;
}
string Table::getDatabaseName()
{
	return databaseName;
}
int Table::getMetaIndex( string givenMeta )
{
	int i = 0;
	while( metaData[i].find(givenMeta) == string::npos )
	{
		i++;
	}
	return i;
}
bool Table::getLock()
{
	return locked;
}

/*
 * Class Implementation
 *       DATABASE
 */
Database::Database( string givenName )
{
	name = givenName;
	tableData.clear();
	lock = false;
}
Database::Database( const Database& givenDatabase )
{
	lock = givenDatabase.lock;
	if( &givenDatabase != this )
	{
		tableData.clear();
		name = givenDatabase.name;
		
		for( int i = 0 ; i < givenDatabase.tableData.size() ; i++ )
		{
			tableData.push_back(givenDatabase.tableData[i]);
		}
	}
}
Database::~Database()
{
	metaData.clear();
	tableData.clear();
}
string Database::getName()
{
	return name;
}
void Database::addTable( Table& givenTable )
{
	if (tableData.size() == tableData.capacity())
		tableData.reserve(tableData.size() + 10);

	tableData.push_back(givenTable);
}
void Database::deleteTable( string tableToDelete )
{
	int tableIndex = 0;

	for( tableIndex = 0 ; tableIndex < tableData.size() ; tableIndex++ )
	{
		if( tableToDelete == tableData[tableIndex].getName() )
		{
			break;
		}
	}

	tableData.erase(tableData.begin() + tableIndex);
}
bool Database::hasTable( string requestedTable )
{
	bool flag = false;

	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		if( tableData[index].getName() == requestedTable )
		{
			flag = true;
		}
	}

	return flag;
}
void Database::alterTable( string command, string whichTable , string givenMeta )
{
	int tableIndex = 0;

	for( tableIndex = 0 ; tableIndex < tableData.size() ; tableIndex++ )
	{
		if( whichTable == tableData[tableIndex].getName() )
		{
			break;
		}
	}

	//If the table is locked and I'm locked. And likewise.
	if( (tableData[tableIndex].locked && lock) || (!tableData[tableIndex].locked && !lock) )
	{
		if( command == "add" )
		{
			tableData[tableIndex].addMetaCol( givenMeta );
		}
		else if( command == "insert" )
		{
			tableData[tableIndex].addTuple( givenMeta );
		}
		else if( command == "update" )
		{
			tableData[tableIndex].updateTuple( givenMeta );
		}
		else if( command == "delete" )
		{
			tableData[tableIndex].deleteTuple( givenMeta );
		}

	}
	else
	{
		cout << "Error: Table " << whichTable << " is locked!" << endl;
	}
}
ofstream& Database::printTableFile( string tableToPrint, ofstream& fout )
{
	int tableIndex = 0;

	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		if( tableToPrint == tableData[index].getName() )
		{
			tableIndex = index;
		}
	}

	tableData[tableIndex].printDataFile(fout);

	return fout;
}
void Database::printTable( string tableToPrint , string printFlag , string queryString , string condition)
{
	int tableIndex = 0;

	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		if( tableToPrint == tableData[index].getName() )
		{
			tableIndex = index;
		}
	}
	
	if (printFlag == "all")
	{
		tableData[tableIndex].printData();
	}
	//query
	else if (printFlag == "some")
	{
		tableData[tableIndex].printQueryData(queryString, condition);
	}
}
void Database::updateTableList()
{
	string toss;
	string filePath = "./data/" + name + "/" + "Info";

	vector<string> tempStringVec;
	
	ifstream fin;
	fin.open(filePath.c_str());
	
	if(!fin.is_open())
	{
		cout << "--ERROR: Could not open ./data" << name << "/Info to write--" << endl;
		exit(1);
	}

	while (getline(fin, toss))
	{	
		tempStringVec.push_back(toss);
		if (toss.find("List") != string::npos)
		{
			break;
		}
	}
	fin.close();

	ofstream fout;
	fout.open(filePath.c_str());

	if(!fout.is_open())
	{
		cout << "--ERROR: Could not open ./data" << name << "/Info to write--" << endl;
		exit(1);
	}

	for(int i = 0 ; i < tempStringVec.size() ; i++ )
	{
		fout << tempStringVec[i] << endl;
	}

	for(int i = 0 ; i < tableData.size() ; i++ )
	{
		fout << tableData[i].getName() << endl;
	}

	fout.close();
}

void Database::listTables()
{
	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		cout << tableData[index].getName() << endl;	
	}
}
int Database::getTableIndex( string givenTable )
{
	int i = 0;
	while( givenTable != tableData[i].getName() )
	{
		i++;
	}
	return i;
}

void Database::innerJoin( string joinSelection , string leftTableName , string rightTableName , string leftAtt , string rightAtt )
{

	int indexLeftTable = getTableIndex( leftTableName );
	int indexRightTable = getTableIndex( rightTableName );
	int indexLeftAtt = tableData[indexLeftTable].getMetaIndex( leftAtt );
	int indexRightAtt = tableData[indexRightTable].getMetaIndex( rightAtt );

	for( int index = 0 ; index < tableData[indexLeftTable].numbAtt ; index++ )
	{
	
		cout << tableData[indexLeftTable].metaData[index] << "|";
	}
	for( int jndex = 0 ; jndex < tableData[indexRightTable].numbAtt ; jndex++ )
	{

		if( jndex != ( tableData[indexRightTable].numbAtt-1 ))
		{
			cout << tableData[indexRightTable].metaData[jndex] << "|";
		}else
		{
			cout << tableData[indexRightTable].metaData[jndex] << endl;
		} 
	}

	//for the attribute of interest in the left table
	for( int index = 0 ; index < tableData[indexLeftTable].numbTuples ; index++ )
	{
		//for the attribute of interest in the right table
		for( int jndex = 0 ; jndex < tableData[indexRightTable].numbTuples ; jndex++ )
		{
			//If the right tuple at the rightAtt == left tupe at the leftAtt
			if( tableData[indexLeftTable].data[index][indexLeftAtt] == tableData[indexRightTable].data[jndex][indexRightAtt] )
			{
				//Print both tuples				
				for( int leftTableTupleIndex = 0 ; leftTableTupleIndex < tableData[indexLeftTable].numbAtt ; leftTableTupleIndex++ )
				{
					cout << tableData[indexLeftTable].data[index][leftTableTupleIndex] << "|";
				}
				for( int rightTableTupleIndex = 0 ; rightTableTupleIndex < tableData[indexRightTable].numbAtt ; rightTableTupleIndex++ )
				{
					if( rightTableTupleIndex != ( tableData[indexRightTable].numbAtt-1 ))
					{
						cout << tableData[indexRightTable].data[jndex][rightTableTupleIndex] << "|";
					}
					else
					{
						cout << tableData[indexRightTable].data[jndex][rightTableTupleIndex] << endl;
					}
				}
			
			}
		}
	}
	cout << endl;
}

void Database::leftJoin( string joinSelection , string leftTableName , string rightTableName , string leftAtt , string rightAtt )
{
	int indexLeftTable = getTableIndex( leftTableName );
	int indexRightTable = getTableIndex( rightTableName );
	int indexLeftAtt = tableData[indexLeftTable].getMetaIndex( leftAtt );
	int indexRightAtt = tableData[indexRightTable].getMetaIndex( rightAtt );

	for( int index = 0 ; index < tableData[indexLeftTable].numbAtt ; index++ )
	{
	
		cout << tableData[indexLeftTable].metaData[index] << "|";
	}

	for( int jndex = 0 ; jndex < tableData[indexRightTable].numbAtt ; jndex++ )
	{

		if( jndex != ( tableData[indexRightTable].numbAtt-1 ))
		{
			cout << tableData[indexRightTable].metaData[jndex] << "|";
		}else
		{
			cout << tableData[indexRightTable].metaData[jndex] << endl;
		}
	}

	int count = 0;
	for( int index = 0 ; index < tableData[indexLeftTable].numbTuples ; index++ )
	{
		//for the attribute of interest in the right table
		for( int jndex = 0 ; jndex < tableData[indexRightTable].numbTuples ; jndex++ )
		{
			//If the right tuple at the rightAtt == left tupe at the leftAtt
			if( tableData[indexLeftTable].data[index][indexLeftAtt] == tableData[indexRightTable].data[jndex][indexRightAtt] )
			{
				//Print both tuples				
				for( int leftTableTupleIndex = 0 ; leftTableTupleIndex < tableData[indexLeftTable].numbAtt ; leftTableTupleIndex++ )
				{
					cout << tableData[indexLeftTable].data[index][leftTableTupleIndex] << "|";
				}
				for( int rightTableTupleIndex = 0 ; rightTableTupleIndex < tableData[indexRightTable].numbAtt ; rightTableTupleIndex++ )
				{
					if( rightTableTupleIndex != ( tableData[indexRightTable].numbAtt-1 ))
					{
						cout << tableData[indexRightTable].data[jndex][rightTableTupleIndex] << "|";
					}
					else
					{
						cout << tableData[indexRightTable].data[jndex][rightTableTupleIndex] << endl;
					} 
				}
				count++;
			}
		}
		if( count == 0)
		{
			for( int leftTableTupleIndex = 0 ; leftTableTupleIndex < tableData[indexLeftTable].numbAtt ; leftTableTupleIndex++ )
			{
				cout << tableData[indexLeftTable].data[index][leftTableTupleIndex] << "|";
			}
			for( int jndex = 0 ; jndex < tableData[indexRightTable].numbAtt ; jndex++ )
			{
				if( jndex != tableData[indexRightTable].numbAtt-1 )
					cout << "|";
			}
			cout << endl;
		}
		count = 0;
	}
	cout << endl;
}

void Database::lockDatabase( )
{
	ofstream fout;
	lock = true;
	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		fout.open(("./data/" + name + "/" + tableData[index].getName()).c_str());
		tableData[index].locked = true;
		tableData[index].printDataFile(fout);
		fout.close();
	}


}
void Database::unlockDatabase( )
{
	ofstream fout;
	lock = false;
	for( int index = 0 ; index < tableData.size() ; index++ )
	{
		fout.open(("./data/" + name + "/" + tableData[index].getName()).c_str());
		tableData[index].locked = false;
		tableData[index].printDataFile(fout);
		fout.close();
	}


				// ofstream fout;
				// fout.open(("./data/" + name + "/" + tableData[tableIndex].getName()).c_str());
				// printTableFile(whichTable, fout);

				// //fout << metaDataInQuestion << endl;
				// fout.close();
}

void Database::setTableLockStatus( string tableName , string lockStatus )
{
	int index = getTableIndex(tableName);

	if( lockStatus == "U" )
	{
		tableData[index].locked = false;
	}
	else
	{
		tableData[index].locked = true;
	}
}

bool Database::getTableLockStatus()
{
	if( !tableData.empty() )
	{
		return tableData[0].locked;
	}
	else
	{
		cout << "GET OUT OF MY ROOM I'M PLAYING MINECRAFT." << endl;
	}

}
bool Database::getLock()
{
	return lock;
}