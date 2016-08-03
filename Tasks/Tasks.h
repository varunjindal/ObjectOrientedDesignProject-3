#ifndef TASKS_H
#define TASKS_H
//////////////////////////////////////////////////////////////////////
//  TypeTable.h - Provides functionality to interface with ThreadPool/
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:       Varun Jindal - vjindal@syr.edu                    //
//////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This package contains a functionality to interface with ThreadPool

Public Interface functions:
void addTask(WorkItem<Result>* pWi, ProcessWorkItem<Result>&);
void returnResult();
void waitTask(ProcessWorkItem<Result>&);


Build Process:
==============

Build commands
- devenv Tasks.sln

Maintenance History:
====================
ver 1.0 : 8 April 16
*/
//
#pragma once
#include <conio.h>
#include <iomanip>
#include<unordered_map>
#include"../TypeTable/TypeTable.h"
#include"../ThreadPool/ThreadPool.h"


template<typename Result>
using WorkItem = std::function<Result()>;
using namespace std;
using WorkResult = std::unordered_map<std::string, FileTypeStore>;
using WorkResult1 = std::vector<std::string>;


template<typename Result>
class Tasks
{
public:
	void addTask(WorkItem<Result>* pWi, ProcessWorkItem<Result>&);
	
	void returnResult();
	void waitTask(ProcessWorkItem<Result>&);
	
};

template<typename Result>
void Tasks<Result>::addTask(WorkItem<Result>* pWi, ProcessWorkItem<Result>& processor)
{
	processor.doWork(pWi);
}



template<typename Result>
void Tasks<Result>::returnResult()
{
}

template<typename Result>
void Tasks<Result>::waitTask(ProcessWorkItem<Result>& processor)
{
	processor.wait();
}

#endif