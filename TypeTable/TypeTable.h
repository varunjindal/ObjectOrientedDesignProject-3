#ifndef TYPETABLE_H
#define TYPETABLE_H
//////////////////////////////////////////////////////////////////////
//  TypeTable.h - Provides Structure to the type table	            //
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
This package contains a functionality to provide structure to the type table

Public Interface functions:
FileTypeStore();
~FileTypeStore();
TypeTable();
~TypeTable();
void setValue(std::string obj,std::string type, std::string filename, std::string nameSpace)
std::unordered_map<std::string, FileTypeStore> getMap()

Required Files:
No File Required

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
#include<string>
#include<vector>
#include<unordered_map>

//Structure for Value part of the Type Table
 class FileTypeStore
{
public:
	FileTypeStore();
	~FileTypeStore();
	std::string _type;
	std::vector<std::pair<std::string, std::string>> _fileNameSpace;
 };

class TypeTable
{
public:
	TypeTable();
	~TypeTable();	
	void setValue(std::string obj,std::string type, std::string filename, std::string nameSpace);
	std::unordered_map<std::string, FileTypeStore> getMap();	
private:
	std::unordered_map<std::string, FileTypeStore> lookup_map;
};

#endif