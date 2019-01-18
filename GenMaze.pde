// This is the interface that facilitates the generation of the maze. 

interface GenMaze {
 void generate();
 void displayMaze();
 boolean generated();
 void makeExit();
 cell[][] getMaze();
 cell getExit();
}
