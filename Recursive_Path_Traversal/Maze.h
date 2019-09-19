#ifndef MAZE_H
#define MAZE_H
#include <string>
#include <sstream>
#include "MazeInterface.h"

using namespace std;

class Maze : public MazeInterface
{
private:
	enum Cell { OPEN, BLOCKED, PATH, VISITED, LEFT, RIGHT, UP, DOWN, OUT, IN, EXIT };
	int maxHeight;
	int maxWidth;
	int maxLayer;
	Cell*** maze;

	/**Returns the symbol to be outputted given a particular cell*/
	char symbol(Cell cell) const;

	/**Recursive sub-path finder from any point within the maze */
	virtual bool find_maze_subpath(int height, int width, int layer);

public:
	/**Constructor*/
	Maze(int height, int width, int layer) : maxHeight(height), maxWidth(width), maxLayer(layer)
	{
		maze = new Cell**[width];
		for (int x = 0; x < width; ++x)
		{
			maze[x] = new Cell*[height];
			for (int y = 0; y < height; ++y)
			{
				maze[x][y] = new Cell[layer];
			}
		}
	}
	/**Destructor*/
	~Maze(void)
	{
		for (int x = 0; x < maxWidth; ++x)
		{
			for (int y = 0; y < maxHeight; ++y)
			{
				delete[] maze[x][y];
			}
			delete[] maze[x];
		}
		delete[] maze;
	}

	/** Set maze value
	@parm height
	@parm width
	@parm layer
	@parm value
	*/
	virtual void setValue(int height, int width, int layer, int value)
	{
		if (value == 0) maze[width][height][layer] = OPEN;
		else if (value == 1) maze[width][height][layer] = BLOCKED;
	}

	/** Solve maze
	@return true if solveable, else false
	*/
	virtual bool find_maze_path()
	{
		return find_maze_subpath(0, 0, 0);
	}

	/** Output maze (same order as input maze)
	@return string of 2D layers
	*/
	virtual string toString() const;
};
#endif // MAZE_INTERFACE_H