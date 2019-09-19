#include "Maze.h"

using namespace std;

/**Recursive sub-path finder from any point within the maze */
bool Maze::find_maze_subpath(int height, int width, int layer)
{	if ((height < 0) || (height >= maxHeight) || (width < 0) || (width >= maxWidth) || (layer < 0) || (layer >= maxLayer)) return false;

	if (maze[width][height][layer] != OPEN) return false; // blocked (base case #2)

	if ((height == maxHeight - 1) && (width == maxWidth - 1) && (layer == maxLayer - 1))
	{
		maze[width][height][layer] = EXIT;
		return true;
	}
	maze[width][height][layer] = PATH; // Recursive case

	if (find_maze_subpath(height, width - 1, layer)) maze[width][height][layer] = LEFT;
	else if (find_maze_subpath(height, width + 1, layer)) maze[width][height][layer] = RIGHT;
	else if (find_maze_subpath(height - 1, width, layer)) maze[width][height][layer] = UP;
	else if (find_maze_subpath(height + 1, width, layer)) maze[width][height][layer] = DOWN;
	else if (find_maze_subpath(height, width, layer - 1)) maze[width][height][layer] = OUT;
	else if (find_maze_subpath(height, width, layer + 1)) maze[width][height][layer] = IN;
	else
	{
		maze[width][height][layer] = VISITED;
		return false;
	}

	return true;
}

/** Output maze (same order as input maze)
@return string of 2D layers
*/
string Maze::toString() const
{
	stringstream out("");
	for (int z = 0; z < maxLayer; ++z)
	{
		out << "Layer " << (z + 1) << endl;
		for (int y = 0; y < maxHeight; ++y)
		{
			for (int x = 0; x < maxWidth; ++x)
			{
				out << " " << symbol(maze[x][y][z]);
			}
			out << endl;
		}
	}
	return out.str();
}

/**Returns the symbol to be outputted given a particular cell*/
char Maze::symbol(Cell cell) const
{
	switch (cell)
	{
	case OPEN: return '_';
	case BLOCKED: return 'X';
	case PATH: return '2';
	case VISITED: return '_';
	case LEFT: return 'L';
	case RIGHT: return 'R';
	case UP: return 'U';
	case DOWN: return 'D';
	case OUT: return 'O';
	case IN: return 'I';
	case EXIT: return 'E';
	}
	return ' ';
}