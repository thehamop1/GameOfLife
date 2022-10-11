# Conway's Game of Life
- The rules are fairly simple for this game. There is a grid of cell's that are either
dead or alive. The cells react based on how many neighbors there are. The following are
the rules:
1. If a dead cell has less than 2 or more than 3 alive neighbors (in any of the 8 surrounding cells), it becomes dead.
2. If an alive cell has *exactly* 3 alive neighbors, it becomes alive. 

# Technologies
- The following was developed with cmake version: cmake version 3.24.1
- The following was developed with gcc version: gcc 11.3.0
- The GUI was built with QT version:
QMake version 3.1
Using Qt version 5.9.7 in /home/cristian/anaconda3/lib

# Build Process
1. Create a folder called build in the root project directory.
2. Run the following command: cmake -DCMAKE_BUILD_TYPE=Release ..
- NOTE: If you have multiple compilers you may have to specify which to use:
cmake -DCMAKE_C_COMPILER=<PATH/TO/GCC> -DCMAKE_CXX_COMPILER=<PATH/TO/G++> -DCMAKE_BUILD_TYPE=Release ..
3. The executables can be found in RIOTGAMESINTERVIEW/build/bin
