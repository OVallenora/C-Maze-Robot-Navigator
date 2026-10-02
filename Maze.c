#include "Maze.h"

//Allocate memory for the Maze's 2D squares
Square *AllocateMazeMemory()
{
    return (Square *)malloc(sizeof(Square)*(X_SIZE*Y_SIZE));
}

//Set all square's coordinates
void SetSquaresCoordinates(Square *pSquares)
{
    for (int i=0; i<X_SIZE; ++i)
    {
        int k = i*X_SIZE;
        for (int j=0; j<Y_SIZE; ++j)
        {
            pSquares[k+j].coord.x = i;
            pSquares[k+j].coord.y = j;
        }
    }
}

//Set all square's move vectors to 0,0
void SetSquaresMoveVectors(Square *pSquares)
{
    for ( int i=0; i<X_SIZE*Y_SIZE; ++i)
    {
        pSquares[i].move.x = 0;
        pSquares[i].move.y = 0;
    }
}

//Set all squares as unblocked initially
void SetUnblockedSquares(Square *pSquares)
{
    for (int i=0; i<X_SIZE*Y_SIZE; ++i)
    {
        pSquares[i].state = Unblocked;        
    }
}

void SetSquaresVariables(Square *pSquares)
{
    SetSquaresCoordinates(pSquares);
    SetSquaresMoveVectors(pSquares);
    SetUnblockedSquares(pSquares);
}
 
void MarkStartSquare(Square *pSquares, const int xStart, const int yStart)
{
    int i = xStart*X_SIZE + yStart;
    pSquares[i].state = Start;
}

void UnmarkStartSquare(Square *pSquares, const int xStart, const int yStart)
{
    int i = xStart*X_SIZE + yStart;
    pSquares[i].state = Unblocked;
}


void MarkHomeSquare(Square *pSquares)
{
    int i = X_HOME*X_SIZE + Y_HOME;
    pSquares[i].state = Home;
}


int GenerateRandomInteger(const int lower, const int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}


bool HomeOrStart(Square *pSquares, const int index)
{
    if(pSquares[index].state == Home || pSquares[index].state == Start)
    {
        return true;
    }
    return false;   
}


bool CheckBlocked(Square *pSquares, const int index)
{
    if(pSquares[index].state == Blocked)
    {
        return true;
    }
    return false;
}

void MarkBlockedSquares(Square *pSquares)
{
    int counter = 1;
    while(counter <= BLOCKS)
    {
        int index = GenerateRandomInteger(0,X_SIZE*Y_SIZE-1);
        if (HomeOrStart(pSquares, index) == true || CheckBlocked(pSquares, index) == true)
        {
            continue;
        }
        else
        {
            pSquares[index].state = Blocked;
            counter ++; 
        }
          
    }
}

void UndoBlockedSquares(Square *pSquares)
{
    for ( int i=0; i<X_SIZE*Y_SIZE; ++i)
    {
        if (CheckBlocked(pSquares, i) == true)
        {
            pSquares[i].state = Unblocked;
        }
    }
}

bool ExistsNorthSquare(Square *pSquares)
{
    int index = X_HOME*X_SIZE + Y_HOME;
    if (pSquares[index].coord.y < Y_SIZE-1)
    {
        if (pSquares[index+1].state == Unblocked && pSquares[index+2].state == Unblocked) // 2 north squares are unblocked
        {
            return true;
        }
    }
    return false;
}

bool ExistsSouthSquare(Square *pSquares)
{    int index = X_HOME*X_SIZE + Y_HOME;
    if (pSquares[index].coord.y > 0)
    {
        if (pSquares[index-1].state == Unblocked && pSquares[index-2].state == Unblocked) // 2 south squares are unblocked
        {
            return true;
        }
    }
    return false;
}

bool ExistsEastSquare(Square *pSquares)
{
    int index = X_HOME*X_SIZE + Y_HOME;
    if (pSquares[index].coord.x < X_SIZE-1)
    {
        if(pSquares[index+X_SIZE].state == Unblocked && pSquares[index+X_SIZE+2].state == Unblocked) // 2 east squares are unblocked
        {
            return true;
        }
    }
    return false;
}

bool ExistsWestSquare(Square *pSquares)
{
    int index = X_HOME*X_SIZE + Y_HOME;
    if (pSquares[index].coord.x > 0)
    {
        if(pSquares[index-X_SIZE].state == Unblocked && pSquares[index-X_SIZE-2].state == Unblocked) // 2 west squares are unblocked
        {
            return true;
        }
    }
    return false;
}


//Checks there's at least 2 blocks free around the home
bool FreeSpaceAroundHome(Square *pSquares)
{
    if (ExistsNorthSquare(pSquares) == true || ExistsSouthSquare(pSquares) == true || ExistsEastSquare(pSquares) == true || ExistsWestSquare(pSquares) == true)
    {
        return true;
    }
    return false;
}

void CreateBlockedSquares(Square *pSquares)
{
    do
    {
        UndoBlockedSquares(pSquares);
        MarkBlockedSquares(pSquares);
    } while (FreeSpaceAroundHome(pSquares) == false);
    
}

void MarkAllSquares(Square *pSquares, int xStart, int yStart)
{
    MarkStartSquare(pSquares, xStart, yStart);
    MarkHomeSquare(pSquares);
    CreateBlockedSquares(pSquares);
    UnmarkStartSquare(pSquares, xStart, yStart);
}


int CountUnblocked(Square *pSquares)
{
    int unblocked = 0;
    for (int i=0; i<X_SIZE*Y_SIZE; ++i)
    {
        if (pSquares[i].state == Unblocked)
        {
            unblocked += 1;
        }
    }
    return unblocked;
}

int CountLayers(Square *pSquares)
{
    int maxLayer = max((X_SIZE-X_HOME), (Y_SIZE-Y_HOME));
    return maxLayer;
}

int FindNeighbourIndex(Square *pSquares, int layer, int k, int n)
{
    int iIndex=0, jIndex=0, index=0;
    switch(k)
    {
        case 0:
            iIndex = n - layer + 1;
            jIndex = layer;
            break;
        case 1:
            iIndex = layer;
            jIndex = -(n - layer + 1);
            break;
        case 2:
            iIndex = -(n - layer +1);
            jIndex = -layer;
            break;
        case 3:
            iIndex = -layer;
            jIndex = n - layer + 1;
            break;
    }
    index = (X_HOME + iIndex)*X_SIZE + (Y_HOME + jIndex);
    return index;
}

bool IndexAvailability(Square *pSquares, int index)
{
    if ( index < 0 || index > (X_SIZE*Y_SIZE - 1))
    {
        return false;
    }
    return true;
}

bool UnblockedAvailability(Square *pSquares, int index)
{
    if(pSquares[index].state != Unblocked)
    {
        return false;
    }
    return true;
}

bool AvailableIndexOrBlock(Square *pSquares, int index)
{
    if (UnblockedAvailability(pSquares, index) == false || IndexAvailability(pSquares, index) == false)
    {
        return false;
    }
    return true;
}

bool NeighbourAvailability(Square *pSquares, int index, int m)
{
    int xMove[] = {0, +1, 0, -1};
    int yMove[] = {+1, 0, -1, 0};
    int xCoord = pSquares[index].coord.x;
    int yCoord = pSquares[index].coord.y;
    
    int xNeighbour = xCoord + xMove[m];
    if (xNeighbour < 0 || xNeighbour > (X_SIZE-1))
    {
        return false;
    }
    int yNeighbour = yCoord + yMove[m];
    if (yNeighbour < 0 || yNeighbour > (Y_SIZE-1))
    {
        return false;
    }
    int j = xNeighbour*X_SIZE + yNeighbour;
    if (j > (X_SIZE*Y_SIZE - 1))
    {
        return false;
    }
    if (pSquares[j].state != Visited)
    {
        return false;
    }
    return true;
}


int VisitUnblockedSquares(Square *pSquares, int index, int unblocked)
{
    int xMove[] = {0, +1, 0, -1};
    int yMove[] = {+1, 0, -1, 0};
    if (IndexAvailability(pSquares, index) == false || UnblockedAvailability(pSquares, index) == false)
    {
        return unblocked;
    }
    for (int m=0; m<4; ++m)
    {
        if (NeighbourAvailability(pSquares, index, m) == false)
        {
            continue;
        }
        pSquares[index].move.x = xMove[m];
        pSquares[index].move.y = yMove[m];
        pSquares[index].state  = Visited;
        unblocked --;
        break;
    }
    return unblocked;
}

int LayerOneMoveVectors(Square *pSquares, int unblocked, int index, int k)
{
    int xMove[] = {0, +1, 0, -1};
    int yMove[] = {+1, 0, -1, 0};
    pSquares[index].move.x = -xMove[k];
    pSquares[index].move.y = -yMove[k];
    pSquares[index].state = Visited;
    unblocked --;
    return unblocked;
}

int CornerMoveVectors(Square *pSquares, int unblocked, int layer, int k)
{
    int xCorners[] = {1, 1, -1, -1};
    int yCorners[] = {1, -1, -1, 1};
    int index = (X_HOME + xCorners[k]*layer)*X_SIZE + (Y_HOME + yCorners[k]*layer);
    unblocked = VisitUnblockedSquares(pSquares, index, unblocked);
    return unblocked; 
}

void FindShortestPathHome(Square *pSquares) //main code for my algorithm
{
    int unblocked = CountUnblocked(pSquares);
    const int maxLayer = CountLayers(pSquares);
    int layer = 0;
    while(layer < maxLayer)
    {
        layer ++;
        for (int k=0; k<4; ++k)
        {
            for(int n=0; n<layer*2-1; ++n )
            {
                int index = FindNeighbourIndex(pSquares, layer, k, n);
                if (AvailableIndexOrBlock(pSquares, index) == false)
                {
                    continue;
                }
                if (layer == 1)
                {
                    unblocked = LayerOneMoveVectors(pSquares, unblocked, index, k);
                }
                else
                {
                    unblocked = VisitUnblockedSquares(pSquares, index, unblocked);
                }
            }
        }
        for (int k=0; k<4; ++k)
        {
            unblocked = CornerMoveVectors(pSquares, unblocked, layer, k);
        }
    }
    while(unblocked > 0)
    {
        for(int i=0; i<X_SIZE*Y_SIZE-1; ++i)
        {
            unblocked = VisitUnblockedSquares(pSquares, i, unblocked);
        }
    }
}