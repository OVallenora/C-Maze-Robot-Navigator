#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Maze.h" 
#include "Visuals.h"
#include "graphics.h" 

bool CheckCommandLineInput(int xStart, int yStart)
{
    if(xStart ==  X_HOME && yStart == Y_HOME)
    {
        return false;
    }
    else if (xStart > X_SIZE - 1|| yStart > Y_SIZE - 1) //because my labelling starts at 0 for coordinates 
    {
        return false;

    }
    return true;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int xStart = 3;
    int yStart = 4;

    if (argc == 3)
    {
        xStart = atoi(argv[1]);
        yStart = atoi(argv[2]);
    }
    if (CheckCommandLineInput(xStart, yStart) == false)
    {
        fprintf(stderr, "Please close the window there has been an error in your inputs");
        sleep(10);
    }
    Square *pSquares = AllocateMazeMemory();
    SetSquaresVariables(pSquares);
    MarkAllSquares(pSquares, xStart, yStart);
    FindShortestPathHome(pSquares);

    Coordinate robot;
    ChangeRobotCoordinates(&robot, xStart, yStart);

    setWindowSize(width, height);

    background();
    DrawGrid();
    DrawHome();
    DrawBlocks(pSquares);
    foreground();
    DrawRobot(xStart, yStart);
    sleep(1000);

    //while robot is not at the marker continue to move the robot
    do
    {
        int index = FindRobotPosition(&robot);
        if (pSquares[index].move.x == 1)
        {
            index = index + X_SIZE;
            MoveRobot(&robot, index, "eastrobot.png");
        }
        else if (pSquares[index].move.x == -1)
        {
            index = index - X_SIZE;
            MoveRobot(&robot, index, "westrobot.png");
        }
        else if (pSquares[index].move.y == 1)
        {
            index = index + 1;
            MoveRobot(&robot, index, "northrobot.png");
        }
        else if (pSquares[index].move.y == -1)
        {
            index = index - 1;
            MoveRobot(&robot, index, "southrobot.png");
        }
        else
        {
            sleep(250);
        }
        sleep(250);
    } while(RobotAtMarker(&robot) == false);
    return 0; 
}


