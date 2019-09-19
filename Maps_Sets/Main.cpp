#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Set.h"
#include "HashMap.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

using namespace std;

//Parsing function to take any line, pefrom the correct function and output the info to the outstream.
void parse(string line, ostream& out, HashMap<string,string>& pokemon, HashMap<string, string>& moves,
		   HashMap<string, Set<string>>& effectivities, HashMap<string, Set<string>>& ineffectivities)
{
	stringstream ss(line);
	string command;
	string output;

	ss >> command;
	if (command == "Set:")
	{
		Set<string> set;
		string item;
		while (ss >> item)
		{
			set.insert(item);
		}
		out << line << endl << "  [" << set.toString() << "]" << endl << endl;
	}
	if (command == "Pokemon:")
	{
		string key, type;
		ss >> key >> type;
		pokemon[key] = type;
		out << line << endl;
	}
	if (command == "Move:")
	{
		string move, type;
		ss >> move >> type;
		moves[move] = type;
		out << line << endl;
	}
	if (command == "Pokemon")
	{
		out << endl << "Pokemon: " << pokemon.size() << "/" << pokemon.max_size() << endl;
		out << pokemon.toString();
	}
	if (command == "Moves")
	{
		out << endl << "Moves: " << moves.size() << "/" << moves.max_size() << endl;
		out << moves.toString();
	}
	if (command == "Effective:")
	{
		string type, effectivity;
		ss >> type;
		while (ss >> effectivity)
		{
			effectivities[type].insert(effectivity);
		}
		out << line << endl;
	}
	if (command == "Ineffective:")
	{
		string type, ineffectivity;
		ss >> type;
		while (ss >> ineffectivity)
		{
			ineffectivities[type].insert(ineffectivity);
		}
		out << line << endl;
	}
	if (command == "Effectivities")
	{
		out << endl << "Effectivities: " << effectivities.size() << "/" << effectivities.max_size() << endl;
		out << effectivities.toString();
	}
	if (command == "Ineffectivities")
	{
		out << endl << "Ineffectivities: " << ineffectivities.size() << "/" << ineffectivities.max_size() << endl;
		out << ineffectivities.toString();
	}
	if (command == "Battle:")
	{
		string pokemon1, move1, pokemon2, move2;
		int p1Advantage = 0;
		ss >> pokemon1 >> move1 >> pokemon2 >> move2;
		out << endl << line << endl;
		out << "  " << pokemon1 << " (" << move1 << ") vs " << pokemon2 << " (" << move2 << ")" << endl;
		out << "  " << pokemon1 << " is a " << pokemon[pokemon1] << " type Pokemon." << endl;
		out << "  " << pokemon2 << " is a " << pokemon[pokemon2] << " type Pokemon." << endl;
		out << "  " << move1 << " is a " << moves[move1] << " type move." << endl;
		out << "  " << move2 << " is a " << moves[move2] << " type move." << endl;
		out << "  " << move1 << " is super effective against [" << effectivities[moves[move1]] << "] type Pokemon." << endl;
		out << "  " << move1 << " is ineffective against [" << ineffectivities[moves[move1]] << "] type Pokemon." << endl;
		out << "  " << pokemon1 << "'s " << move1 << " is ";
		if (ineffectivities[moves[move1]].count(pokemon[pokemon2]))
		{
			out << "ineffective";
			p1Advantage--;
		}
		else if (effectivities[moves[move1]].count(pokemon[pokemon2]))
		{
			out << "super effective";
			p1Advantage++;
		}
		else out << "effective";
		out << " against " << pokemon2 << endl;
		out << "  " << move2 << " is super effective against [" << effectivities[moves[move2]] << "] type Pokemon." << endl;
		out << "  " << move2 << " is ineffective against [" << ineffectivities[moves[move2]] << "] type Pokemon." << endl;
		out << "  " << pokemon2 << "'s " << move2 << " is ";
		if (ineffectivities[moves[move2]].count(pokemon[pokemon1]))
		{
			out << "ineffective";
			p1Advantage++;
		}
		else if (effectivities[moves[move2]].count(pokemon[pokemon1]))
		{
			out << "super effective";
			p1Advantage--;
		}
		else out << "effective";
		out << " against " << pokemon1 << endl;
		if (p1Advantage == 0)
		{
			out << "  The battle between " << pokemon1 << " and " << pokemon2 << " is a tie." << endl << endl;
		}
		else
		{
			out << "  In the battle between " << pokemon1 << " and " << pokemon2 << ", ";
			out << (p1Advantage > 0 ? pokemon1 : pokemon2) << " wins!" << endl << endl;
		}
		
	}
}

//Main
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

	HashMap<string, string> pokemon;
	HashMap<string, string> moves;
	HashMap<string, Set<string>> effectivities;
	HashMap<string, Set<string>> ineffectivities;

	while (getline(in, line))
	{
		try
		{
			parse(line, out, pokemon, moves, effectivities, ineffectivities);
		}
		catch (...)
		{
			out << "error";
		}
	}

	return 0;
}