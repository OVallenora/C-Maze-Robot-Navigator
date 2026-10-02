#ifndef VISUALS_H
#define VISUALS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "graphics.h"
#include "Maze.h"


#define BLOCK_WIDTH (50)
#define width  (BLOCK_WIDTH*X_SIZE + 100)
#define height (BLOCK_WIDTH*Y_SIZE + 100)

void DrawGrid();
void DrawHome();
void DrawBlocks(Square *pSquares);
void DrawRobot(const int xStart, const int yStart);
void ChangeRobotCoordinates(Coordinate *robot, const int x, const int y);
void MoveRobot(Coordinate *robot, const int index, char *image);
int FindRobotPosition(Coordinate *robot);
bool RobotAtMarker(Coordinate *robot); 



#endif /* VISUALS_H */