#ifndef PDA_H
#define PDA_H
//////////////////////////////////////////////////////////////////////
//  ParallelDependencyExecutive.h - Test Suite to demostrate all	//
//   requirements													//
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:      Varun Jindal - vjindal@syr.edu                     //
//////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This package contains a test suite that demonstrates all the requirements
of project 2. The ParallelDependencyAnalyzer is called in this package.

Public Interface functions:
Title(std::string str);
Req1()
Req2()
Req3()
Req4()
Req5()
Req6()
Req7()
Req8()
Req9()
Req10()
static void StartAnalyzer(std::vector<std::string>, int)

Build Process:
==============

Build commands
devenv Project3.sln /rebuild debug

Required files
- Parser.h, Parser.cpp, ScopeStack.h, ScopeStack.cpp,
ActionsAndRules.h, ActionsAndRules.cpp, ConfigureParser.cpp,
ItokCollection.h, SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp,
MetricAnalyzer.h, MetricAnalyzer.cpp, ASTree.h, ASTree.cpp, FileManager.h, FileManager.cpp
ParallelDependencyAnalyzer.h,ParallelDependencyAnalyzer.cpp

Maintenance History:
====================
ver 1.0 : 9 April 16
- first release
*/
//


#pragma once
#include <iostream>
#include<string>
#include<vector>
#include <iosfwd>


class ParallelDependencyExecutive
{
public:
	static void Print(std::string str);
	static void Req1();
	static void Req2();
	static void Req3();
	static void Req4();
	static void Req5();
	static void Req6();
	static void Req7();
	static void Req8();
	static void Req9();
	static void Req10();
	static void StartAnalyzer(std::vector<std::string>, int);
};

#endif