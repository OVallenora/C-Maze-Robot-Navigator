#include "../include/Visuals.h"

void DrawGrid()
{
    setColour(black);
    for(int i=0; i <= Y_SIZE; i++)
    {
        drawLine(50, i*BLOCK_WIDTH + 50, width-50, i*BLOCK_WIDTH + 50);
    }
    for( int j=0; j <= X_SIZE; j++)
    {
        drawLine(j*BLOCK_WIDTH + 50, 50, j*BLOCK_WIDTH + 50, width-50);
    }
}

void DrawHome()
{
    displayImage("images/home.png", 55+X_HOME*BLOCK_WIDTH, 5+(Y_SIZE-Y_HOME)*BLOCK_WIDTH);
}

void DrawRobot(const int xStart, const int yStart)
{
    displayImage("images/northrobot.png", 55+xStart*BLOCK_WIDTH, 5+(Y_SIZE-yStart)*BLOCK_WIDTH);
}

void DrawBlocks(Square *pSquares)
{
    setRGBColour(216,94,39);
    for (int i=0; i<X_SIZE*Y_SIZE; ++i)
        {
            if (pSquares[i].state == Blocked)
            {
                int xCoord = i / Y_SIZE;
                int yCoord = i % X_SIZE;
                fillRect(55+xCoord*BLOCK_WIDTH, 55+(Y_SIZE-(yCoord+1))*BLOCK_WIDTH, BLOCK_WIDTH-10, BLOCK_WIDTH-10);
            }
            else
            {
                continue;
            }
        }
}

void ChangeRobotCoordinates(Coordinate *robot, const int x, const int y)
{
    robot->x = x;
    robot->y = y;
}


void MoveRobot(Coordinate *robot, const int index, char *image)
{
    clear();
    int x = index / Y_SIZE;
    int y = index % X_SIZE;
    ChangeRobotCoordinates(robot, x, y);
    displayImage(image, 55+x*BLOCK_WIDTH, 5+(Y_SIZE-y)*BLOCK_WIDTH);
}

int FindRobotPosition(Coordinate *robot)
{
    int x = robot->x;
    int y = robot->y;
    int index = X_SIZE*x + y;
    return index;
}

bool RobotAtMarker(Coordinate *robot)
{
    int x = robot->x;
    int y = robot->y;
    if (x == X_HOME && y == Y_HOME)
    {
        return true;
    }
    return false;
}
