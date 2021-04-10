#include <iostream>
#include <image.h>
#include "deque.hpp"

class PathFinder {
  private:
    Image<Pixel> input;
    std::string output;// stores output file name read in from program executable
    Deque<int> *rowFrontier, *colFrontier; 
    bool **explored = nullptr;
    bool solutionFound = false;
    intmax_t row, col, rowSize, colSize;
    int rowDir[4] = {-1, 1, 0, 0};// array to store row adjacent node directions
    int colDir[4] = {0, 0, 1, -1};// array to store col adjacent node directions
    int layerStepsLeft = 1, nextLayerSteps = 0;

  public:
    PathFinder(){};
    ~PathFinder(){};
    bool readImage(int argc, char *argv[]);// reads image file from executable
    int breadthFirstSearch();
    int solve();
};

bool PathFinder::readImage(int argc, char *argv[]) 
{
  if (argc != 3) {
    std::cout << "Usage: compare"
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  bool success = true;
  try {
    input = readFromFile(argv[1]);
    output = argv[2];
    rowSize = input.height();
    colSize = input.width();
    bool iState = false; //true if an initial state exists

    // iterates over each pixel in image 
    for (intmax_t i = 0; i < colSize; ++i) {
      for (intmax_t j = 0; j < rowSize; ++j) {
        // if an invalid color appears, bool is false
        if(input(i, j) != BLACK && input(i, j) != RED && input(i, j) != WHITE ) {
          success = false;
          break;
        }  
        if(input(i, j) == RED) {
          if(iState)// if already found an initial state bool is false
            success = false;
        
          iState = true;
          row = i;// stores row and column cooridinates of initial state
          col = j;
        }
      }
    }// end outer for
  
    if(!success){
      std::cout << "Invalid pixel colors or duplicate red pixels.\n";
      return EXIT_FAILURE;
    }
  } catch (std::exception &ex) {
    success = false;
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  return success;
}

int PathFinder::breadthFirstSearch() 
{
  rowFrontier = new Deque<int>; // allocate new memory for two queues
  colFrontier = new Deque<int>;
  rowFrontier->pushBack(row);
  colFrontier->pushBack(col);
  
  //dynamically allocate memory for 2D array of bools
  explored = new bool*[colSize];
  for(intmax_t i = 0; i < colSize; i++)
    explored[i] = new bool[colSize];

  for(intmax_t i = 0; i < colSize; i++) {
    for(intmax_t j = 0; j < colSize; j++)
      explored[i][j] = false;
  }
  explored[row][col] = true;

  solve();

  delete rowFrontier;
  delete colFrontier;
  for(intmax_t i = 0; i < colSize; i++) {
    delete [] explored[i];
  }
  delete explored;
  return EXIT_SUCCESS;
}

int PathFinder::solve()
{
  intmax_t rowPath, colPath, r, c;
  // iterate until either row or column frontiers are empty
   while(!rowFrontier->isEmpty() || !colFrontier->isEmpty()) {
     if(rowFrontier->isEmpty() || colFrontier->isEmpty())
      return EXIT_FAILURE;

      r = rowFrontier->front();
      c = colFrontier->front();
      rowFrontier->popFront();
      colFrontier->popFront();
      // if pixel is on a border and valid exit(white pixel), mark as solution is found and break early
      if(input(r, c) == WHITE && (r == 0 || r == colSize - 1) || (c == 0 || c == colSize - 1)) {
        solutionFound = true;
        break;
      }
    // iterate over adjacent node directions to check if each neighbor has been explored or is an exit   
    for(int i = 0; i < 4; i++) {
      rowPath = r + rowDir[i];
      colPath = c + colDir[i];

      // if row and column directions of adjacent nodes are valid locations then push to queue and mark as explored
      if(rowPath >= 0 && colPath >= 0 && rowPath < colSize && colPath < colSize && input(rowPath, colPath) == WHITE) {
        if(!explored[rowPath][colPath]) {
          rowFrontier->pushBack(rowPath);
          colFrontier->pushBack(colPath);
          explored[rowPath][colPath] = true; // mark corresponding coordinate as true
          nextLayerSteps++;// indicate more nodes need explored
        }// end inner if
      }// end outer if
    }// end for
    layerStepsLeft--;
    if(layerStepsLeft == 0) { // if s
      layerStepsLeft = nextLayerSteps;
      nextLayerSteps = 0;
    }
  }// end while

  if(solutionFound) {
    std::cout << "Solution Found.\n" << std::endl;
    input(r, c) = GREEN;
    writeToFile(input, output);
   }
  
  else {
    std::cout << "No Solution Found.\n" << std::endl;
    writeToFile(input, output);
  }
  return 1; // return back to caller
}

int main(int argc, char *argv[])
{
  PathFinder p;

  p.readImage(argc, argv);
  p.breadthFirstSearch();

  return 0;
}