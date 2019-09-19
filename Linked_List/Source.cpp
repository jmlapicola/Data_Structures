#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "LinkedListInterface.h"
#include "LinkedList.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

using namespace std;

//Iterating functions
string iterate(LinkedList<string>&list)
{
	stringstream ss;
	LinkedList<string>::Iterator iter = list.begin();
	for (; iter != list.end(); ++iter)
	{
		ss << *iter << " ";
	}
	return ss.str();
}
string iterate(LinkedList<int>&list)
{
	stringstream ss;
	LinkedList<int>::Iterator iter = list.begin();
	for (; iter != list.end(); ++iter)
	{
		ss << *iter << " ";
	}
	return ss.str();
}

//Parsing function to take any line, pefrom the correct function and output the info to the outstream.
template<typename T>
void parse(string line, LinkedList<T>& list, ostream& out)
{
	stringstream ss(line);
	string command;
	T arg1, arg2;
	size_t index;
	string output;
	bool success;

	ss >> command;
	out << line << " ";
	if (command == "insertHead")
	{
		ss >> arg1;
		out << (list.insertHead(arg1) ? "true" : "false") << endl;
	}
	else if (command == "insertTail")
	{
		ss >> arg1;
		out << (list.insertTail(arg1) ? "true" : "false") << endl;
	}
	else if (command == "insertAfter")
	{
		ss >> arg1 >> arg2;
		out << (list.insertAfter(arg1, arg2) ? "true" : "false") << endl;
	}
	else if (command == "size")
	{
		out << list.size() << endl;
	}
	else if (command == "at")
	{
		ss >> index;
		success = list.at(index, output);
		out << output << (success ? " true" : "Invalid Index") << endl;
	}
	else if (command == "remove")
	{
		ss >> arg1;
		out << (list.remove(arg1) ? "true" : "false") << endl;
	}
	else if (command == "clear")
	{
		out << (list.clear() ? "true" : "false") << endl;
	}
	else if (command == "printList")
	{
		out << list.toString() << endl;
	}
	else if (command == "iterateList")
	{
		out << iterate(list) << endl;
	}
}

int main(int argc, char* argv[])
{
	VS_MEM_CHECK; // memory leak check

	// opening input and output files
	// checking number of arguments
	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	// input file
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	// output file
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	string line; //For parsing each line seperately
	
	//Linked list of ints
	LinkedList<int> ints;
	getline(in, line);
	out << line << " true" << endl;
	while (getline(in, line) && line != "STRING")
	{
		try
		{
			parse<int>(line, ints, out);
		}
		catch (...)
		{
			out << "error";
		}
	}
	out << line << " true" << endl;

	//Linked list of strings
	LinkedList<string> strings;
	while (getline(in, line))
	{
		try
		{
			parse<string>(line, strings, out);
		}
		catch (...)
		{
			out << "error";
		}
	}

	return 0;
}