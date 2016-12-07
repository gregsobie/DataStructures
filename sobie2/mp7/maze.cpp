
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include "maze.h"
#include "dsets.h"

#define RIGHT 	0
#define DOWN	1
#define LEFT 	2
#define UP 	3

/* Create an empty maze */
SquareMaze::SquareMaze(){
	mazeWidth=0;
	mazeHeight=0;
	mazeSize=0;
	mazeCells=DisjointSets();
}

/* Make a maze with specified dimensions */
void SquareMaze::makeMaze(int width, int height){
	if(width>=2 && height>=2){
		mazeWidth=width;
		mazeHeight=height;
		mazeSize=mazeWidth*mazeHeight;
		mazeCells.addelements(mazeSize);

		/* Finished maze is always a tree of corridors */
		downWalls=vector<bool>(mazeSize,true);
		rightWalls=vector<bool>(mazeSize,true);

		/* Fill maze with walls at each (x,y) position */
		for(int x=0; x<mazeWidth; x++){
			for(int y=0; y<mazeHeight; y++){
				pair<int,int> cell(x,y);
				pair<pair<int,int>,int> downWall(cell, DOWN);
				mazeWalls.push_back(downWall);
				pair<pair<int,int>,int> rightWall(cell, RIGHT);
				mazeWalls.push_back(rightWall);
			}
		}

		/* Seed random number generator */
		srand(time(NULL));
		/* Select random walls to delete without making a cycle */
		while(mazeWalls.size()>1){
			int deleteIdx=rand()%mazeWalls.size(); // 0<deleteIdx<mazeWalls.size();
			pair<pair<int,int>,int> deleteWall=mazeWalls[deleteIdx];
			mazeWalls[deleteIdx]=mazeWalls[mazeWalls.size()-1];
			mazeWalls.pop_back();

			pair<int,int> deleteCell=deleteWall.first;
			int deleteDirection=deleteWall.second;
			int cellIdx=(deleteCell.second*mazeWidth)+deleteCell.first;
			/* If downward direction and we are not in last row, check if cells differ */
			if(deleteDirection==DOWN && cellIdx+mazeWidth<mazeSize){ 
				/* Union differing cells */
				if(mazeCells.find(cellIdx) != mazeCells.find(cellIdx+mazeWidth)){
					downWalls[cellIdx]=false;
					mazeCells.setunion(cellIdx, cellIdx+mazeWidth);
				}
			/* Else if rightward direction and we are not in rightmost column, check if cells differ */
			}else if(deleteDirection==RIGHT && (cellIdx+1)%mazeWidth==0){
				/* Union differing cells */
				if(mazeCells.find(cellIdx) != mazeCells.find(cellIdx+1)){
					rightWalls[cellIdx]=false;
					mazeCells.setunion(cellIdx, cellIdx+1);
				}
			}
		}
	}
}

/* Determines whether it is possible to travel in the given direction from (x,y) */
bool SquareMaze::canTravel(int x, int y, int dir) const{
	/* If in currently valid position */
	if(x>=0 && y>=0 && x<mazeWidth && y<mazeHeight){
		/* Check if next move will be invalid */
		if((x==0 && dir==LEFT) || (y==0 && dir==UP) ||
		   (y==mazeHeight-1 && dir==DOWN) || 
		   (x==mazeWidth-1 && dir==RIGHT))
			return false;
		else 	return true;
	}

	/* Valid direction ? true : false */
	switch(dir){
		case RIGHT: return !(rightWalls[y*mazeWidth+x]); break;
		case DOWN: return !(downWalls[y*mazeWidth+x]); break;
		case LEFT: return !(rightWalls[y*mazeWidth+x-1]); break; 
		case UP: return !(downWalls[(y-1)*mazeWidth+x]); break;
		default: return false;
	}
}

/* Sets whether or not the specified wall exists */
void SquareMaze::setWall(int x, int y, int dir, bool exists){
	int cellIdx=y*mazeWidth+x;
	if(dir==DOWN)
		downWalls[cellIdx]=exists;
	else 	rightWalls[cellIdx]=exists;
}

vector<int> SquareMaze::solveMaze(){
	bool **visited = new bool* [mazeWidth];
	for(int i=0; i<mazeWidth; i++)
		visited[i] = new bool[mazeHeight];
	for(int x=0; x<mazeWidth; x++){
		for(int y=0; y<mazeHeight; y++)
			visited[x][y]=false;
	}

	/* Queue the adjacent positions */
	stack<int> steps;
	queue<int> q;
	map<int,int> mazeMap;
	q.push(0);
	visited[0][0]=true;

	/* Mark as visited and vidmap */
	while(!q.empty()){
		int currentCell=q.front();
		int currentX=getCellX(currentCell);
		int currentY=getCellY(currentCell);
		q.pop();

		/* Explore all adjacent positions for possible moves */
		for(int i=0; i<4; i++){
			int nextCell=getNextCell(currentX, currentY, i);
			int nextX=getCellX(nextCell);
			int nextY=getCellY(nextCell);
			/* If cell has not been visited and is valid move, enqueue cell */
			if(canTravel(currentX,currentY,i) && !visited[nextX][nextY]){
				q.push(nextCell);
				visited[nextX][nextY]=true;
				/* Map maze layout */
				mazeMap[nextCell] = currentCell;
			}
		}	
	}

	/* All cells visited */
	int max_length=0;
	int max_i=0;
	for(int i=0; i<mazeWidth; i++){
		int count=0;
		int end=(i*mazeWidth) + (mazeHeight-1);
		int start=0;
		while(end != start){
			end=mazeMap[end];
			count++;
		}
		if(count>max_length){
			max_length=count;
			max_i=i;
		}
	}
	exitCell=(max_i*mazeWidth)+(mazeHeight-1);
	int start=0;
	int end=exitCell;
	while(end!=start){
		int dist=end-mazeMap[end];
		if(dist==1)
			steps.push(0);
		else if(dist==mazeWidth)
			steps.push(1);
		else if(dist==-1)
			steps.push(2);
		else if(dist==(-1*mazeWidth))
			steps.push(3);
		else 	steps.push(-1);
		end=mazeMap[end];
	}

	/* Create solution return vector */
	while(!steps.empty() && steps.top()!=-1){
		mazeSolution.push_back(steps.top());
		steps.pop();
	}
	delete[] visited;
	visited=NULL;
	return mazeSolution;
}

PNG * SquareMaze::drawMaze() const{
	PNG* retVal=new PNG(0, 0);
	return retVal;
}

PNG * SquareMaze::drawMazeWithSolution(){
	if(mazeSolution.size()==0){
		return new PNG();
	}
	PNG* retVal = drawMaze();
	return retVal;
}

int SquareMaze::getCellX(int cellNum){
	return cellNum%mazeWidth;
}

int SquareMaze::getCellY(int cellNum){
	return cellNum/mazeWidth;
}

int SquareMaze::getNextCell(int x, int y, int dir){
	if(dir == RIGHT)
		return y*mazeWidth+x+1;
	else if(dir == DOWN)
		return y*mazeWidth+x+mazeWidth;
	else if(dir == LEFT)
		return y*mazeWidth+x-1;
	else if(dir == UP)
		return y*mazeWidth+x-mazeWidth;
	else 	return 0;
}
