/*
Railroad Lab
jmlapicola
3/1/19
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Station.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK ;
#endif

using namespace std;

//Parsing command takes a command line, acts on the Railroad object and outputs the results
void parse(Station<unsigned int>& station, string line, ofstream& out)
{
	//converts line to string stream and extracts first command
	string command;
	stringstream ss(line);
	ss >> command;
	// commands
	if (command == "Add:station")
	{
		unsigned int car;
		ss >> car;
		out << line << " " << station.addStation(car) << endl;
	}
	else if (command == "Add:queue")
	{
		out << line << " " << station.addQueue() << endl;
	}
	else if (command == "Add:stack")
	{
		out << line << " " << station.addStack() << endl;
	}
	else if (command == "Remove:station")
	{
		out << line << " " << station.removeStation() << endl;
	}
	else if (command == "Remove:queue")
	{
		out << line << " " << station.removeQueue() << endl;
	}
	else if (command == "Remove:stack")
	{
		out << line << " " << station.removeStack() << endl;
	}
	else if (command == "Top:station")
	{
		out << line << " " << station.topStation() << endl;
	}
	else if (command == "Top:queue")
	{
		out << line << " " << station.topQueue() << endl;
	}
	else if (command == "Top:stack")
	{
		out << line << " " << station.topStack() << endl;
	}
	else if (command == "Size:queue")
	{
		out << line << " " << station.sizeQueue() << endl;
	}
	else if (command == "Size:stack")
	{
		out << line << " " << station.sizeStack() << endl;
	}
	else if (command == "Train:")
	{
		out << line << " " << station.toString() << endl;
	}
	else
	{
		ss = stringstream(line);
		getline(ss, command, ':');
		if (command == "Find")
		{
			unsigned int car;
			ss >> car;
			out << line << " " << station.find(car) << endl;
		}
	}
	
}

int main(int argc, char* argv[])
{
	VS_MEM_CHECK; //Memory leak check

				  //Opening input and output files
				  //Checking number of arguments
	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	//Input file
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	//Output file
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
	//Intializing Station class
	Station<unsigned int> station;

	//Repeated calling of the parse() function line by line (catching exceptions)
	string line;
	while (getline(in, line))
	{
		try
		{
			parse(station, line, out);
		}
		catch (exception& e)
		{
			out << line << " " << "ERROR: " << e.what() << endl;
		}
	}

	return 0;
}