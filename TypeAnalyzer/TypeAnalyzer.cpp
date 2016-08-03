//////////////////////////////////////////////////////////////////////
//  TypeTable.cpp-Provides functionality to populate the Type Table //
//				  on parsing the file								//	
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//	Platform:     Dell Inspiron 1300, core i5 , Windows 10	        //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:       Varun Jindal-Syracuse University- vjindal@syr.edu //
//////////////////////////////////////////////////////////////////////



#include "TypeAnalyzer.h"
#include"../ThreadPool/ThreadPool.h"
#include "../Parser/ConfigureParser.h"
#include "../Parser/Parser.h"
#include "../Tokenizer/Tokenizer.h"
#include "../SemiExp/SemiExp.h"
#include "../Utilities/Utilities.h"
#include "../TypeTable/TypeTable.h"
#include <conio.h>
#include <iomanip>
#include"../Tasks/Tasks.h"


using WorkResult = std::unordered_map<std::string, FileTypeStore>;

TypeTable TypeAnalyzer::returnTypeTable()
{
	return TypeTable();
}



void TypeAnalyzer::generateTypeTable(std::vector<std::string> files, ProcessWorkItem<WorkResult>& processor)
{
	Tasks<WorkResult> task;
	for (int j = 0; j < files.size(); j++)
	{
		std::string a = files[j];
		//Constructing Workitem for every individual file
		WorkItem<WorkResult> wi1 = [a]() { 
			std::cout << "\nRunning Type Analysis on " << a;
			std::cout << "  working on thread " << std::this_thread::get_id();
			std::string fileSpec = a;
			std::string msg = "Processing file  " + fileSpec;
			ConfigParseToConsole configure;
			configure.setDisplayFilter(true);
			Parser* pParser = configure.Build(fileSpec);			
				try {
					if (pParser)// the parser is build here
					{
						if (!configure.Attach(fileSpec)) {
							std::cout << "\n  could not open file:: " << a << std::endl;
						}
					}
					else
					{
						std::cout << "\n\n  Parser not built\n\n";
					}
					while (pParser->next())// the parser is used here
					{
						pParser->parse();
					}
				}
				catch (std::exception& ex)
				{
					std::cout << "\n\n    " << ex.what() << "\n\n";
				}					
			Repository* rep = configure.getRepository();
			return rep->tt->getMap();
		};
		task.addTask(&wi1,processor); // Adding workitem to queue
		tables.push_back(processor.result());
	}
	task.addTask(nullptr,processor); // Sending Shutdown to threadpool
	task.waitTask(processor); // Waiting for the threads to end
}

std::vector<std::unordered_map<std::string, FileTypeStore>> TypeAnalyzer::returnTTvec()
{
	return tables;
}


#ifdef DEBUG
int main()
{
	TypeAnalyzer temp;
	ProcessWorkItem<WorkResult> processor;
	Tasks<WorkResult> task;
	
	std::string a = "Test.cpp";
		WorkItem<WorkResult> wi1 = [a]() {
			std::cout << "\nRunning Type Analysis on " << a;
			std::cout << "  working on thread " << std::this_thread::get_id();
			std::string fileSpec = a;
			std::string msg = "Processing file  " + fileSpec;
			ConfigParseToConsole configure;
			configure.setDisplayFilter(true);
			Parser* pParser = configure.Build(fileSpec);
			try {
				if (pParser)// the parser is build here
				{
					if (!configure.Attach(fileSpec)) {
						std::cout << "\n  could not open file:: " << a << std::endl;
					}
				}
				else
				{
					std::cout << "\n\n  Parser not built\n\n";
				}
				while (pParser->next())// the parser is used here
				{
					pParser->parse();
				}
			}
			catch (std::exception& ex)
			{
				std::cout << "\n\n    " << ex.what() << "\n\n";
			}
			Repository* rep = configure.getRepository();
			return rep->tt->getMap();
		};
		task.addTask(&wi1, processor);
		task.addTask(nullptr, processor);
		task.waitTask(processor);
		return 0;
}
#endif // DEBUG
