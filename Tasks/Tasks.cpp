//////////////////////////////////////////////////////////////////////
// TypeTable.cpp-Provides functionality to interface with ThreadPool//
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:       Varun Jindal - vjindal@syr.edu                    //
//////////////////////////////////////////////////////////////////////
#include "Tasks.h"
#include "../ThreadPool/ThreadPool.h"

using Work = std::string;
int main()
{
	ProcessWorkItem<Work> processor1;
	Tasks<Work> task;
	//Building a work item
	WorkItem<Work> wi2 = []() {
		return "Hello";
	};
	task.addTask(&wi2, processor1); // adding work item to queue
	task.waitTask(processor1); // Waiting for thread process to complete
	return 0;
}