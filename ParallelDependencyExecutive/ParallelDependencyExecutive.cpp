//////////////////////////////////////////////////////////////////////
//  ParallelDependencyExecutive.cpp - Test Suite to demostrate all	//
//   requirements													//
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:      Varun Jindal - vjindal@syr.edu                     //
//////////////////////////////////////////////////////////////////////

#include "ParallelDependencyExecutive.h"
#include"../FileManager/FileManager.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../ParallelDependencyAnalyzer/ParallelDependencyAnalyzer.h"

using namespace std;

// ------- <Utility function for display > ---------
void ParallelDependencyExecutive::Print(std::string str)
{
	std::cout << std::endl << "================================================================================" << std::endl;
	std::cout << str << std::endl;
	std::cout << "================================================================================" << std::endl;	
}

// ----------- < req 1 demo > -----------
void ParallelDependencyExecutive::Req1()
{
	std::cout << "This project is developed using Visual Studio 2015 and its C++ Windows Console Projects" << std::endl;
	std::cout << std::endl;
}

// ----------- < req 2 demo > -----------
void ParallelDependencyExecutive::Req2()
{
	std::cout << "C++ standard library's is used for streams for all I/O and new and delete for all heap-based memory management" << std::endl;
	std::cout << std::endl;
}

// ----------- < req 3 demo > -----------
void ParallelDependencyExecutive::Req3()
{
	std::cout << "This project is developed in accordace to the requirements and enforces 'Single Responsibility Principle	'" << std::endl;
	std::cout << std::endl;
}

// ----------- < req 4 demo > -----------
void ParallelDependencyExecutive::Req4()
{
	std::cout << "Project provides ThreadPool package that declares and defines a ThreadPool class that executes enqueued work items asynchronously" << std::endl;
	std::cout << std::endl;
}

// ----------- < req 5 demo > -----------
void ParallelDependencyExecutive::Req5()
{
	std::cout << "Project provides Task package that declares and defines a Task class that executes a callable object on a ThreadPool thread" << std::endl;
	std::cout << std::endl;
}

// ----------- < req 6 demo > -----------
void ParallelDependencyExecutive::Req6()
{
	std::cout << "Project provides provide a TypeAnalysis package that identifies all of the types defined in a specified file developed in Project #1 & #2" << std::endl;
	std::cout << std::endl;
}

// ----------- < req 7 demo > -----------
void ParallelDependencyExecutive::Req7()
{
	std::cout << "Project provides a DependencyAnalysis package that identifies all of the dependencies between files in a specified file collection" << std::endl;
	std::cout << std::endl;
}

// ----------- < req 8 demo > -----------
void ParallelDependencyExecutive::Req8()
{
	std::cout << "Project provides ParallelDependencyAnalysis package that finds compilation dependencies between all of the files in a specified file collection using the asynchronous processing facilities provided by the Task package." << std::endl;
	std::cout << std::endl;
}

// ----------- < req 9 demo > -----------
void ParallelDependencyExecutive::Req9()
{
	std::cout << "Project provides ParallelDependencyExecutive that finds all the compilation dependencies between files in a file collection. Each of the files in the collection are found in a directory tree rooted at a specified path and whose names match one or more specified patterns" << std::endl;
	std::cout << std::endl;
}

// ----------- < req 10 demo > -----------
void ParallelDependencyExecutive::Req10()
{
	std::cout << "Project provides automated unit test suite - ParallelDependencyExecutive that demonstrates you meet all the requirements of this project" << std::endl;
	std::cout << std::endl;
}
// ----------- < File Dependency Demo > -----------
void ParallelDependencyExecutive::StartAnalyzer(std::vector<std::string>files, int n)
{	
	ParallelDependencyAnalyzer m;    // Calling Parallel Dependency Analyzer
	m.StartParallelAnalyzer(files, n);
}


int main(int argc, char* argv[])
{
	//Calling all demo functions
	ParallelDependencyExecutive::Print("Demonstrating Req 1");
	ParallelDependencyExecutive::Req1();
	ParallelDependencyExecutive::Print("Demonstrating Req 2");
	ParallelDependencyExecutive::Req2();
	ParallelDependencyExecutive::Print("Demonstrating Req 3");
	ParallelDependencyExecutive::Req3();
	ParallelDependencyExecutive::Print("Demonstrating Req 4");
	ParallelDependencyExecutive::Req4();	
	ParallelDependencyExecutive::Print("Demonstrating Req 5");
	ParallelDependencyExecutive::Req5();
	ParallelDependencyExecutive::Print("Demonstrating Req 6");
	ParallelDependencyExecutive::Req6();
	ParallelDependencyExecutive::Print("Demonstrating Req 7");
	ParallelDependencyExecutive::Req7();
	ParallelDependencyExecutive::Print("Demonstrating Req 8");
	ParallelDependencyExecutive::Req8();
	ParallelDependencyExecutive::Print("Demonstrating Req 9");
	ParallelDependencyExecutive::Req9();
	ParallelDependencyExecutive::Print("Demonstrating Req 10");
	ParallelDependencyExecutive::Req10();
	if (argc < 3 || argv[1] == "" || argv[argc-1] == "" || argv[argc-2] == "")               // checking command line arguments
	{
		std::cout<< "\n  please enter file patterns and root directory on command line\n\n";
		return 1;
	}		
	int no_of_threads = atoi(argv[argc - 1]);	
	int no_of_patterns = argc - 3;	
	FileManager fileManager;
	std::vector<std::string> patterns;
	for (int i = 1; i <= no_of_patterns; i++)
	patterns.push_back(argv[i]);
	std::vector<std::string> files = fileManager.getFiles(argv[argc-2], patterns);  // Fetching all files in to the vector
	ParallelDependencyExecutive::StartAnalyzer(files, no_of_threads); 	
	return 0;
}

