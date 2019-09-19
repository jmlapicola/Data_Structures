/*
Expressions Lab
jmlapicola
3/1/19
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include "Expression.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

using namespace std;

//Parsing command takes a command line, acts on a expression object and outputs the results
void parse(Expression& expression, string line, ofstream& out)
{
	//converts line to string stream and extracts first command
	string command;
	stringstream ss(line);
	ss >> command;
	//Expression command
	if (command == "Expression:")
	{
		string expString;
		ss.get();
		getline(ss, expString);
		expression = Expression(expString);
		out << endl << line << endl;
	}
	//Infix command
	else if (command == "Infix:")
	{
		out << line << " ";
		out << expression.infix() << endl;
	}
	//Postfix command
	else if (command == "Postfix:")
	{
		out << line << " ";
		out << expression.postfix() << endl;
	}
	//Prefix command
	else if (command == "Prefix:")
	{
		out << line << " ";
		out << expression.prefix() << endl;
	}
	//Value command
	else if (command == "Value:")
	{
		out << line << " ";
		out << expression.value() << endl;
	}
	//Exception
	else
	{
		throw "Unknown command";
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

	//Intializing expression class
	Expression expression("");

	//Repeated calling of the parse() function line by line (catching exceptions)
	string line;
	while (getline(in,line))
	{
		try
		{
			parse(expression, line, out);
		}
		catch (exception& e)
		{
			out << line << e.what() << endl;
		}
		catch (int err)
		{
			switch (err)
			{
			case ILLEGAL_OPERATOR:
				out << "Illegal Operator" << endl;
				break;
			case MISSING_OPERAND:
				out << "Missing Operand" << endl;
				break;
			case MISSING_OPERATOR:
				out << "Missing Operator" << endl;
				break;
			case UNBALANCED:
				out << "Unbalanced" << endl;
				break;
			}
		}
	}

	return 0;
}