/*
Maze
jmlapicola
3/13/19
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Maze.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK ;
#endif

using namespace std;

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
	//Intializing Maze
	int height, width, layers;
	in >> height >> width >> layers;
	Maze maze(height, width, layers);
	//Filling maze from input file
	for (int z = 0; z < layers; ++z)
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				int value;
				in >> value;
				maze.setValue(y, x, z, value);
			}
		}
	}

	//Output Maze
	out << "Solve Maze:" << endl;
	out << maze.toString();

	//Output Solution
	if (maze.find_maze_path())
	{
		out << endl << "Solution:" << endl;
		out << maze.toString();
	}
	else out << endl << "No Solution Exists!";

	return 0;
}