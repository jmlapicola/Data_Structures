#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "BST.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

using namespace std;

//Iterating functions
string iterate(BST<string>& bst)
{
	stringstream ss;
	BST<string>::Iterator iter = bst.begin();
	if (iter == bst.end()) return "empty";
	for (; iter != bst.end(); ++iter)
	{
		ss << *iter << " ";
	}
	return ss.str();
}
string iterate(BST<int>& bst)
{
	stringstream ss;
	BST<int>::Iterator iter = bst.begin();
	if (iter == bst.end()) return "empty";
	for (; iter != bst.end(); ++iter)
	{
		ss << *iter << " ";
	}
	return ss.str();
}


//Parsing function to take any line, pefrom the correct function and output the info to the outstream.
template<typename T>
void parse(string line, BST<T>& bst, ostream& out)
{
	stringstream ss(line);
	string command;
	T arg;
	string output;

	ss >> command;
	if (command == "add")
	{
		ss >> arg;
		out << line << (bst.addNode(arg) ? " true" : " false") << endl;
	}
	else if (command == "remove")
	{
		ss >> arg;
		out << line << (bst.removeNode(arg) ? " true" : " false") << endl;
	}
	else if (command == "clear")
	{
		out << line << (bst.clearTree() ? " true" : " false") << endl;
	}
	else if (command == "size")
	{
		out << line << " " << bst.size() << endl;
	}
	else if (command == "print")
	{
		out << line << ":" << bst << endl;
	}
	else if (command == "find")
	{
		ss >> arg;
		out << line << " " << (bst.find(arg) ? "found" : "not found") << endl;
	}
	else if (command == "tree")
	{
		out << line << ": " << iterate(bst) << endl;
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

	//Binary search tree of ints
	BST<int> ints;
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

	//Binary search tree of strings
	BST<string> strings;
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