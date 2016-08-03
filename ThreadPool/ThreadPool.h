#pragma once
//////////////////////////////////////////////////////////////////////
//  ThreadPool.h - child thread processes enqueued work items       //
//  ver 1.1                                                         //
//  Language:     C++, Visual Studio 2105                           //
//	Platform:     Dell Inspiron 1300, core i5 , Windows 10	        //
//  Application:  Parallel Dependency Analysis				        //
//				  CSE687 - Object Oriented Design                   //
//  Source:		  Jim Fawcett,CSE687-Object Oriented Design,Spring 2016
//  Author:       Varun Jindal-Syracuse University- vjindal@syr.edu //
//////////////////////////////////////////////////////////////////////
/*
* A single child thread processes work items equeued by main thread
*/
/*
Module Operations:
==================
This package contains a functionality to child thread processes enqueued work items

Public Interface functions:
std::thread* start();
std::thread* start(int);
void doWork(WorkItem<Result>* pWi);
Result result();
void wait();
~ProcessWorkItem();

Required Files:
Cpp11-BlockingQueue.h

Build Process:
==============
Build commands
devenv Project3.sln /rebuild debug

Maintenance History:
====================
ver 1.1 : 8 April 16
*/
//

#include <thread>
#include <functional>
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"

template<typename Result>
using WorkItem = std::function<Result()>;

///////////////////////////////////////////////////////////////////////
// class to process work items
// - each work item is processed sequentially on a single child thread

template<typename Result>
class ProcessWorkItem
{
public:
	std::thread* start();
	std::thread* start(int);
	void doWork(WorkItem<Result>* pWi);
	Result result();
	void wait();
	~ProcessWorkItem();
	std::vector<std::thread*> _threads;
private:
	std::thread* _pThread;
	BlockingQueue<WorkItem<Result>*> _workItemQueue;
	BlockingQueue<Result> _resultsQueue;
};
//----< wait for child thread to terminate >---------------------------

template<typename Result>
void ProcessWorkItem<Result>::wait()
{
	//Set join on all threads of the pool
	for (int i = 0; i < _threads.size(); i++)
	_threads[i]->join();
}
//----< enqueue work item >--------------------------------------------

template<typename Result>
void ProcessWorkItem<Result>::doWork(WorkItem<Result>* pWi)
{
	_workItemQueue.enQ(pWi);
}
//----< retrieve results with blocking call >--------------------------

template<typename Result>
Result ProcessWorkItem<Result>::result()
{
	return _resultsQueue.deQ();
}
//----< start child thread that dequeus work items >-------------------

template<typename Result>
std::thread* ProcessWorkItem<Result>::start(int n)
{
	if (n > 5) n = 5; // Limit Number of threads to 5

	std::function<void()> threadProc =
		[&]() {
		while (true)
		{
			WorkItem<Result>* pWi = _workItemQueue.deQ();
			if (pWi == nullptr)
			{
				std::cout << "\n  shutting down work item processing";
				_workItemQueue.enQ(nullptr);
				return;
			}
			Result result = (*pWi)();
			_resultsQueue.enQ(result);
		}
	};
	for (int i = 0; i < n; i++) {
		_pThread = new std::thread(threadProc);
		_threads.push_back(_pThread);
	}
	return _pThread;
}

//----< clean up heap >------------------------------------------------

template<typename Result>
ProcessWorkItem<Result>::~ProcessWorkItem()
{
	delete _pThread;
}


