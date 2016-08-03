//////////////////////////////////////////////////////////////////////////////////
//  TypeTable.cpp -    Provides Structure to the type table				        //
//  ver 1.0                                                                     //
//  Language:          C++, Visual Studio 2105							        //
//	Platform:		   Dell Inspiron 1300, core i5 , Windows 10					//
//  Application:       Parallel Dependency Analysis						     	//
//				       CSE687 - Object Oriented Design						    //
//  Author:            Varun Jindal -Syracuse University -  vjindal@syr.edu     //
//								                                                //
//////////////////////////////////////////////////////////////////////////////////


#include"TypeTable.h"

FileTypeStore::FileTypeStore()
{

}

FileTypeStore::~FileTypeStore()
{}

TypeTable::TypeTable()
{
}

TypeTable::~TypeTable()
{
}

void TypeTable:: setValue(std::string obj, std::string type, std::string filename, std::string nameSpace)
{
	//If it's a new key
	if (lookup_map.count(obj) == 0)
	{
		FileTypeStore *typeStore = new FileTypeStore;
		typeStore->_type = type;
		std::vector<std::pair<std::string, std::string>> _pair;
		std::pair<std::string, std::string> pair = std::make_pair(filename, nameSpace);
		_pair.push_back(pair);
		typeStore->_fileNameSpace = _pair;
		lookup_map.emplace(obj, *typeStore);
	}
	// If insertion at existing key
	else {
		FileTypeStore *typeStore = &lookup_map[obj];
		std::vector<std::pair<std::string, std::string>> _pair = typeStore->_fileNameSpace;
		std::pair<std::string, std::string> pair = std::make_pair(filename, nameSpace);
		_pair.push_back(pair);
	}	
}

std::unordered_map<std::string, FileTypeStore> TypeTable::getMap()
{
	return lookup_map;
}

#ifdef TYPE_TABLE
int main() {

	FileTypeStore* x = new FileTypeStore();
	std::string key = "Test";
	x->_type = "Function";
	std::vector<std::pair<std::string, std::string>> _pair;
	std::pair<std::string, std::string> pair = std::make_pair("Test.cpp", "GNS");
	_pair.push_back(pair);
	x->_fileNameSpace = _pair;	
	//Constructing a Type Table
	TypeTable table;
	//table.lookup_map.emplace(key, *x);

}
#endif