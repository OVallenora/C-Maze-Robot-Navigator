#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define min(a,b) ({__typeof__(a) _a = (a); __typeof__(b) _b = (b); _a < _b? _a: _b;})
#define max(a,b) ({__typeof__(a) _a = (a); __typeof__(b) _b = (b); _a > _b? _a: _b;})

#define X_SIZE (10)
#define Y_SIZE (10)

#define X_HOME (9)
#define Y_HOME (7)

#define BLOCKS (10)

typedef enum States 
{
    Unblocked = 0,
    Blocked,
    Start,
    Home,
    Visited
} State;

typedef struct Coordinates 
{
    int x;
    int y;
} Coordinate;

typedef struct Moves
{
    int x;
    int y;
} Move;

typedef struct Squares
{
    Coordinate coord;
    Move move;
    State state;
} Square;

Square *AllocateMazeMemory(); //This could be wrong
void SetSquaresMoveVectors(Square *pSquares);
void SetUnblockedSquares(Square *pSquares);
void SetSquaresVariables(Square *pSquares);
void MarkStartSquare(Square *pSquares, const int xStart, const int yStart);
void UnmarkStartSquare(Square *pSquares, const int xStart, const int yStart);
void MarkHomeSquare(Square *pSquares);
int GenerateRandomInteger(const int lower, const int upper);
bool HomeOrStart(Square *pSquares, const int index);
bool CheckBlocked(Square *pSquares, const int index);
void MarkBlockedSquares(Square *pSquares);
void UndoBlockedSquares(Square *pSquares);
bool ExistsNorthSquare(Square *pSquares);
bool ExistsSouthSquare(Square *pSquares);
bool ExistsEastSquare(Square *pSquares);
bool ExistsWestSquare(Square *pSquares);
bool FreeSpaceAroundHome(Square *pSquares);
void CreateBlockedSquares(Square *pSquares);
void MarkAllSquares(Square *pSquares, int xStart, int yStart);
int CountUnblocked(Square *pSquares);
int CountLayers(Square *pSquares);
int FindNeighbourIndex(Square *pSquares, int layer, int k, int n);
bool IndexAvailability(Square *pSquares, int index);
bool UnblockedAvailability(Square *pSquares, int index);
bool AvailableIndexOrBlock(Square *pSquares, int index);
bool NeighbourAvailability(Square *pSquares, int index, int m);
int VisitUnblockedSquares(Square *pSquares, int index, int unblocked);
int LayerOneMoveVectors(Square *pSquares, int unblocked, int index, int k);
int CornerMoveVectors(Square *pSquares, int unblocked, int layer, int k);
void FindShortestPathHome(Square *pSquares);

#endif /* MAZE_H */
