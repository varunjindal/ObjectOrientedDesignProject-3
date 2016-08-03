//////////////////////////////////////////////////////////////////////
//  ParallelDependencyAnalyzer.cpp - This package calls all required//
//  packages of the project, merges type tables and					//
//  display dependencies											//
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:      Varun Jindal - vjindal@syr.edu                     //
//////////////////////////////////////////////////////////////////////


#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "../Utilities/Utilities.h"
#include "../Tokenizer/Tokenizer.h"
#include "../SemiExp/SemiExp.h"
#include "../Parser/Parser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../MetricAnalyzer/MetricAnalyzer.h"
#include "../FileManager/FileManager.h"
#include"ParallelDependencyAnalyzer.h"
#include <conio.h>
#include <iomanip>
#include "../TypeTable/TypeTable.h"
#include"../ThreadPool/ThreadPool.h"
#include "../TypeAnalyzer/TypeAnalyzer.h"
#include <unordered_set>
#include "../Tasks/Tasks.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include"../DependencyAnalyzer/DependencyAnalyzer.h"

using namespace Scanner;
using namespace Utilities;
using namespace std;

using Util = Utilities::StringHelper;
//using WorkResult1 = std::string;
using WorkResult1 = std::vector<std::string>;
using WorkResult = std::unordered_map<std::string, FileTypeStore>;

#include <queue>
#include <string>
#define Util StringHelper

//----------<Calling Type Analyser on each file> ----------------
std::vector<std::unordered_map<std::string, FileTypeStore>> ParallelDependencyAnalyzer::RunParallelTypeAnalysis(std::vector<std::string> files, ProcessWorkItem<WorkResult>& processor)
{
	TypeAnalyzer temp;
	temp.generateTypeTable(files, processor);
	std::vector<std::unordered_map<std::string, FileTypeStore>> table;
	table = temp.returnTTvec();
	return table;
}
//----------<Merging all type tables> ----------------
std::unordered_map<std::string, FileTypeStore> ParallelDependencyAnalyzer::MergePartialTypeTables(std::vector<std::unordered_map<std::string, FileTypeStore>> tables)
{
	std::unordered_map<std::string, FileTypeStore> table;
	for (int x = 0; x < tables.size(); x++) {
		std::unordered_map<std::string, FileTypeStore> map = tables[x];
		for (auto it = map.begin(); it != map.end(); it++) {
			if (table.find(it->first) == table.end()) {
				table.emplace(it->first, it->second);
			}
			else {
				std::vector<std::pair<std::string, std::string>> _mergedPair = table.find(it->first)->second._fileNameSpace;
				std::vector<std::pair<std::string, std::string>> _pair = it->second._fileNameSpace;
				for (std::pair<std::string, std::string> p : _pair) {
					_mergedPair.push_back(p);
				}
				table.find(it->first)->second._fileNameSpace=_mergedPair;
			}
		}
	}
	
	FILE *file = fopen("TypeTable_Thread_Output.txt", "a");
	for (auto it = table.begin(); it != table.end(); ++it) {
		std::vector<std::pair<std::string, std::string>> output = it->second._fileNameSpace;
		for (int i = 0; i < output.size(); i++)
		{
			/*std::cout << "\n" << std::left << std::setw(20) << it->first << std::setw(20) << it->second._type;
			std::cout << std::setw(80) << output[i].first;
			std::cout << std::setw(20) << output[i].second << std::endl;*/
			fputs(("Key: " + it->first + "\t" + "	Type: " + it->second._type + "\t" + "	file ::" + output[i].first + "\t" + "	name ::" + output[i].second + "\n").c_str(), file);
		}		
	}
	return table;
}


//----------<Checking dependency of each file> ----------------
std::unordered_map<string, vector<string>> ParallelDependencyAnalyzer::RunParallelDependency(std::vector<std::string> files, std::unordered_map<std::string, FileTypeStore> table, ProcessWorkItem<WorkResult1>& processor1)
{
	Tasks<WorkResult1> task;
	std::unordered_map<string, vector<string>> Result;
	for (int j = 0; j < files.size(); j++)
	{
		DependencyAnalyzer dep;
		dep.findDependency(files[j], table, files, processor1);
		std::vector<std::string> t = dep.returnDependency();
		Result.emplace(files[j], t);
	}
	task.addTask(nullptr, processor1);
	task.waitTask(processor1);
	return Result;
}

//----------<Starting dependency analyser> ----------------
void ParallelDependencyAnalyzer::StartParallelAnalyzer(std::vector<std::string> files, int n)
{
	ParallelDependencyAnalyzer m;
	ProcessWorkItem<WorkResult> processor;
	//Starting Thread pool with n threads
	processor.start(n);
	cout << endl<<"================================="<<endl;
	cout << "Files under analysis are : " << endl;
	for (auto file : files)
		cout << endl << file << endl;
	//Call to type analyser
	m.PartialTypeTables = m.RunParallelTypeAnalysis(files, processor);
	//cout << "Tables size :: " << m.PartialTypeTables.size() << endl;

	//Merging type typles
	m.MergedTypeTable = m.MergePartialTypeTables(m.PartialTypeTables);
	//cout << "Merged Tables size :: " << m.MergedTypeTable.size() << endl;

	//Starting Thread pool with n threads
	ProcessWorkItem<WorkResult1> processor1;
	processor1.start(n);

	// Call to dependency analyzer
	std::unordered_map<string, vector<string>> Result = m.RunParallelDependency(files, m.MergedTypeTable, processor1);

	//Displaying Dependencies
	for (auto it = Result.begin(); it != Result.end(); ++it) {
		cout << "\n\n File ::" << it->first << "  depends upon:" << endl;
		vector<string> files = it->second;
		if (files.size() > 0) {
			for (int i = 0; i < files.size(); i++)
				cout << "	" << files[i] << endl;
		}
		else
			cout << "	" << "No Dependencies found" << endl;
	}
}



#ifdef TEST_PDA
int main(int argc, char* argv[])
{
	cout << "bkjbkjb";

	FileManager fileManager;
	vector<string> patterns;
	patterns.push_back(argv[1]);
	patterns.push_back(argv[2]);
	vector<string> files = fileManager.getFiles(argv[3], patterns);  // Fetching files
	ParallelDependencyAnalyzer m;
	ProcessWorkItem<WorkResult> processor;
	processor.start(4);				// starting thread pool
	for (auto file : files)
		cout << endl << file << endl;	
	m.PartialTypeTables = m.RunParallelTypeAnalysis(files, processor);  // type analyis
	//cout << "Tables size :: " << m.PartialTypeTables.size() << endl;
	m.MergedTypeTable = m.MergePartialTypeTables(m.PartialTypeTables);
	//cout << "Merged Tables size :: " << m.MergedTypeTable.size() << endl; // merging type tables
	ProcessWorkItem<WorkResult1> processor1;
	processor1.start(4);
	std::unordered_map<string, vector<string>> Result = m.RunParallelDependency(files, m.MergedTypeTable, processor1);   // Finding dependencies
	for (auto it = Result.begin(); it != Result.end(); ++it) {
		cout << "\n\n File ::" << it->first << "  depends upon:" << endl;   // printing dependencies
		vector<string> files = it->second;
		for (int i = 0; i < files.size(); i++)
			cout << "	" << files[i] << endl;
	}
	return 0;
}

#endif