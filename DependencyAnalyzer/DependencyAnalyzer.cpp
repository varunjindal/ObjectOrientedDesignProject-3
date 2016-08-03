//////////////////////////////////////////////////////////////////////////////////
//  DependencyAnalyzer.cpp - Computes Dependency after analyzing the file       //
//  ver 1.0                                                                     //
//  Language:          C++, Visual Studio 2105							        //
//	Platform:		   Dell Inspiron 1300, core i5 , Windows 10					//
//  Application:       Parallel Dependency Analysis						     	//
//				       CSE687 - Object Oriented Design						    //
//  Author:            Varun Jindal -Syracuse University -  vjindal@syr.edu     //
//								                                                //
//////////////////////////////////////////////////////////////////////////////////

#include "DependencyAnalyzer.h"
#include"../ThreadPool/ThreadPool.h"
#include "../Utilities/Utilities.h"
#include "../Tokenizer/Tokenizer.h"
#include "../SemiExp/SemiExp.h"
#include "../Parser/Parser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include "../Tasks/Tasks.h"

using WorkResult1 = std::vector<std::string>;
using namespace Scanner;
using namespace Utilities;

//-------------------------------<< Finding Dependency by parsing the file and matching each token in the type table >> ------------------------------------------

void DependencyAnalyzer::findDependency(std::string file, std::unordered_map<std::string, FileTypeStore> Mmap, std::vector<std::string> files, ProcessWorkItem<WorkResult1>& processor1)
{
	Tasks<WorkResult1> task;
	std::vector<std::string> Result;
	std::string a = file;
	WorkItem<WorkResult1> wi2 = [a, files, Mmap]() {
		std::cout << "\n\nDependency : working on thread " << std::this_thread::get_id() << " working on file :: " << a;
		std::unordered_map<std::string, bool> depFiles;
		for (auto file : files) {
			auto it = depFiles.find(file);
			if (it != depFiles.end())
				it->second = false;
			else
				depFiles.emplace(file, false);
		}
		std::ifstream in(a);
		Toker toker;
		toker.returnComments(false);
		toker.attach(&in);
		std::vector<std::string> deps;
		do
		{
			std::string tok = toker.getTok();
			for (auto it = Mmap.begin(); it != Mmap.end(); ++it) {
				if (tok == it->first) {
					std::vector<std::pair<std::string, std::string>> dependents = it->second._fileNameSpace;
					for (int i = 0; i < dependents.size(); i++)
					{
						if (a != dependents[i].first && !depFiles.find(dependents[i].first)->second) {
							deps.push_back(dependents[i].first);
							depFiles.find(dependents[i].first)->second = true;
						}
					}
				}
			}

		} while (in.good());
		return deps;
	};
	task.addTask(&wi2, processor1);

	deps = processor1.result();
}

std::vector<std::string> DependencyAnalyzer::returnDependency()
{
	return deps;
}

#ifdef DEBUG
int main()
{
	std::string file = "test.cpp";
	std::vector<std::string> files;
	std::unordered_map<std::string, FileTypeStore> Mmap;
	ProcessWorkItem<WorkResult1> processor1;
	DependencyAnalyzer temp;
	temp.findDependency(file, Mmap,files,processor1);
	return 0;
}
#endif // DEBUG
