
//////////////////////////////////////////////////////////////////////
//  ParallelDependencyAnalyzer.h - This package calls all required  //
//  packages of the project, merges type tables and					//
//  display dependencies											//
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:      Varun Jindal - vjindal@syr.edu                     //
//////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This package calls all required packages of the project, merges type tables and display dependencies

Public Interface functions:
ParallelDependencyAnalyzer(){}
~ParallelDependencyAnalyzer(){}
static std::vector<std::unordered_map<std::string, FileTypeStore>> RunParallelTypeAnalysis(std::vector<std::string>, ProcessWorkItem<WorkResult>&);
static std::unordered_map<std::string, FileTypeStore> MergePartialTypeTables(std::vector<std::unordered_map<std::string, FileTypeStore>>);
std::unordered_map<string, vector<string>> RunParallelDependency(std::vector<std::string>, std::unordered_map<std::string, FileTypeStore>, ProcessWorkItem<WorkResult1>&);
void StartParallelAnalyzer(std::vector<std::string>, int);


Build Process:
==============
Required files
- Parser.h, Parser.cpp, ScopeStack.h, ScopeStack.cpp,
ActionsAndRules.h, ActionsAndRules.cpp, ConfigureParser.cpp,
ItokCollection.h, SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp,
MetricAnalyzer.h, MetricAnalyzer.cpp, ASTree.h, ASTree.cpp, FileManager.h, FileManager.cpp
TypeTable.h,ThreadPool.h,TypeAnalyzer.h,Tasks.h,FileSystem.h,DependencyAnalyzer.h

Build commands
devenv Project3.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 14 Mar 16
- first release, demonstrated 1,2,3 and 4 requirement
ver 1.1 : 9 April 16
- demonstrated 5,6,7,8,9,10 requirement


*/
//
#include <iosfwd>
#include <string>
#include "../TypeTable/TypeTable.h"
#include"../ThreadPool/ThreadPool.h"
using namespace std;
using WorkResult = std::unordered_map<std::string, FileTypeStore>;
using WorkResult1 = std::vector<std::string>;

class ParallelDependencyAnalyzer
{
public:
	ParallelDependencyAnalyzer(){}
	~ParallelDependencyAnalyzer(){}
	static std::vector<std::unordered_map<std::string, FileTypeStore>> RunParallelTypeAnalysis(std::vector<std::string>, ProcessWorkItem<WorkResult>&);
	static std::unordered_map<std::string, FileTypeStore> MergePartialTypeTables(std::vector<std::unordered_map<std::string, FileTypeStore>>);
	std::unordered_map<string, vector<string>> RunParallelDependency(std::vector<std::string>, std::unordered_map<std::string, FileTypeStore>, ProcessWorkItem<WorkResult1>&);
	void StartParallelAnalyzer(std::vector<std::string>, int);
	std::unordered_map<std::string, FileTypeStore> MergedTypeTable;
	std::vector<std::unordered_map<std::string, FileTypeStore>> PartialTypeTables;
};
