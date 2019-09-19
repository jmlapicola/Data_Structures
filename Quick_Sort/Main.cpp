#include <iostream>
#include <fstream>
#include <sstream>
#include "QuickSort.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

using namespace std;

//Parsing function to take any line, pefrom the correct function and output the info to the outstream.
void parse(string line, QuickSort<int>& QSArray, ostream& out)
{
	stringstream ss(line);
	string command;
	ss >> command;

	if (command == "QuickSort")
	{
		size_t capacity;
		ss >> capacity;
		out << line << " " << (QSArray.createArray(capacity) ? "OK" : "Error") << endl;
	}
	if (command == "Capacity")
	{
		out << line << " " << QSArray.capacity() << endl;
	}
	if (command == "Size")
	{
		out << line << " " << QSArray.size() << endl;
	}
	if (command == "Clear")
	{
		out << command << " " << (QSArray.clear() ? "OK" : "Error") << endl;
	}
	if (command == "AddToArray")
	{
		int item;
		ss >> item;
		QSArray.addElement(item);
		out << command << "  " << item;
		while (ss >> item)
		{
			QSArray.addElement(item);
			out << "," << item;
		}
		out << " OK" << endl;
	}
	if (command == "MedianOfThree")
	{
		size_t left, right;
		ss >> left >> right;
		out << command << " " << left << "," << right << " = " << QSArray.medianOfThree(left, right) << endl;
	}
	if (command == "Partition")
	{
		int left, right, pivot;
		ss >> left >> right >> pivot;
		out << command << " " << left << "," << right << "," << pivot << " = " << QSArray.partition(left, right, pivot) << endl;
	}
	if (command == "SortAll")
	{
		out << command << " " << (QSArray.sortAll() ? "OK" : "Error") << endl;
	}
	if (command == "Sort")
	{
		size_t left, right;
		ss >> left >> right;
		out << command << " " << left << "," << right << (QSArray.sort(left, right) ? " OK" : " Error") << endl;
	}
	if (command == "PrintArray")
	{
		out << command << " " << QSArray.toString() << endl;
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
	QuickSort<int> myArray;

	while (getline(in, line))
	{
		try
		{
			parse(line, myArray, out);
		}
		catch (...)
		{
			out << "error";
		}
	}

	return 0;
}