# C-Maze-Robot-Navigator

A C-based grid navigation program that generates randomized obstacles and calculates the shortest path for a robot to return to a designated home coordinate. The algorithm systematically maps move vectors from the target destination outward and outputs the step-by-step traversal to a Java-based visualizer.

## Compilation and Execution
* The program contains 4 source files: `graphics.c`, `Visuals.c`, `Maze.c`, and `Main.c`.
* Compile the program by typing: `gcc graphics.c maze.c visuals.c main.c`.
* To run the compiled program with the default initial position, you do not have to type in a start position.
* To run the program with a custom starting position (e.g., x=5, y=4), pipe the output to the drawing app using: `./a.out 5 4 | java -jar drawapp-2.0.jar`.
* Grid coordinates start at `0` on both the x and y axes.

## Grid Configuration
* Variables including `X_SIZE`, `Y_SIZE`, `X_HOME`, `Y_HOME`, and the number of `BLOCKS` are defined in the `Maze.h` file.
* These values can be successfully changed and the program will still work.
* The grid needs to be a square because of the way the indexing is implemented.
* If the grid is made very large, you may need to adjust `BLOCK_WIDTH` in `Visuals.h` to fit the maximum window size.
* If you decrease the block width, you must also decrease the pixel dimensions of the home and robot images to account for this change.
* Generating too many blocks (usually around 15-20) may prevent the robot from finding a successful path home, depending on the starting locations.

## Algorithm Overview
* Most of the program logic is located in the `Maze.c` file, with `FindShortestPathHome` and `VisitUnblockedSquares` being the most important functions.
* Starting with the immediate neighbours of the home square, the algorithm sets the move vectors for each of these squares.
* If the robot is located in the North, East, South, or West neighbours, the move vectors are set to `(0,1)`, `(1,0)`, `(0,-1)`, and `(-1,0)` respectively, allowing a simple one-step move home.
* Since diagonal moves are not permitted, corner neighbours must move clockwise to an East, South, West, or North neighbour that has already been visited.
* The algorithm repeats these steps outward for each of the neighbours of the neighbours of the home square.
* Ultimately, relative to the home square and blocked squares, every unblocked square receives a move vector that guarantees the shortest possible path home.
* The `MoveRobot` function in `Visuals.c` controls the robot by moving it one step at a time in the correct direction based on these vectors.
