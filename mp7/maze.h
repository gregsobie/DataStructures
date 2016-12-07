/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include "dsets.h"
#include <vector>
#include "png.h"
#include <map>
#include <queue>
#include <stack>
using namespace std;

class SquareMaze{
public:
	SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	vector<int> solveMaze();
	PNG * drawMaze() const;
	PNG * drawMazeWithSolution();
private:
	int mazeWidth;
	int mazeHeight;
	int mazeSize;
	int exitCell;
	DisjointSets mazeCells;
	vector<int> mazeSolution;
	vector<bool> downWalls;
	vector<bool> rightWalls;
	vector<pair<pair<int,int>,int>> mazeWalls;
	int getCellX(int cellIdx);
	int getCellY(int cellIdx);
	int getNextCell(int x, int y, int dir);
};
#endif
