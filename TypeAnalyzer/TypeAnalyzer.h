#ifndef TYPEANALYZER_H
#define TYPEANALYZER_H
//////////////////////////////////////////////////////////////////////
//  TypeTable.h - Provides functionality to populate the Type Table //
//				  on parsing the file								//	
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//	Platform:     Dell Inspiron 1300, core i5 , Windows 10	        //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Author:       Varun Jindal-Syracuse University- vjindal@syr.edu //
//////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This package contains a functionality to populate the type tables on parsing the file

Public Interface functions:
TypeTable returnTypeTable();
void generateTypeTable(std::vector<std::string>, ProcessWorkItem<WorkResult>&);
std::vector<std::unordered_map<std::string, FileTypeStore>> returnTTvec();

Required Files:
TypeAnalyzer.h
ThreadPool.h
ConfigureParser.h
Parser.h
Tokenizer.h
SemiExp.h
Utilities.h
TypeTable.h
Tasks.h

Build commands
devenv Project3.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 8 April 16
*/
//

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include "../TypeTable/TypeTable.h"
#include"../ThreadPool/ThreadPool.h"

using WorkResult = std::unordered_map<std::string, FileTypeStore>;

class TypeAnalyzer
{
public:
	TypeTable returnTypeTable();
	void generateTypeTable(std::vector<std::string>, ProcessWorkItem<WorkResult>&);
	std::vector<std::unordered_map<std::string, FileTypeStore>> returnTTvec();
private:
	std::vector<std::unordered_map<std::string, FileTypeStore>> tables;
};

#endif