//////////////////////////////////////////////////////////////////////////////////
//  DependencyAnalyzer.h   - Computes Dependency after analyzing the file       //
//  ver 1.0                                                                     //
//  Language:          C++, Visual Studio 2105							        //
//	Platform:		   Dell Inspiron 1300, core i5 , Windows 10					//
//  Application:       Parallel Dependency Analysis						     	//
//				       CSE687 - Object Oriented Design						    //
//  Author:            Varun Jindal -Syracuse University -  vjindal@syr.edu     //
//								                                                //
//////////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
Computes Dependency after analyzing the file

Public Interface functions:
void findDependency(std::string, std::unordered_map<std::string, FileTypeStore>, std::vector<std::string>, ProcessWorkItem<WorkResult1>&);
std::vector<std::string> returnDependency();

Required Files:
ThreadPool.h,Utilities.h,Tokenizer.h,SemiExp.h
Parser.h,ActionsAndRules.h,ConfigureParser.h,Tasks.h

Build Process:
==============

Build commands
devenv Project3.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 8 April 16
*/
//

#pragma once
#include<iostream>
#include<unordered_map>
#include"../TypeTable/TypeTable.h"
#include"../ThreadPool/ThreadPool.h"

using WorkResult1 = std::vector<std::string>;

class DependencyAnalyzer
{
public:
	void findDependency(std::string, std::unordered_map<std::string, FileTypeStore>, std::vector<std::string>, ProcessWorkItem<WorkResult1>&);
	std::vector<std::string> returnDependency();
private:
	std::vector<std::string> deps;
};
