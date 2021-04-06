#include <iostream>
#include <image.h>
#include "deque.hpp"

class PathFinder {
  private:
    Image<Pixel> input;
    std::string output;
    Deque<int> *rowFrontier, *colFrontier;
    bool **explored = nullptr;
    bool solutionFound = false;
    intmax_t row, col;
    int rowDir[4] = {-1, 1, 0, 0};
    int colDir[4] = {0, 0, 1, -1};
    int layerStepsLeft = 1, nextLayerSteps = 0;

  public:
    PathFinder(){};
    ~PathFinder(){};
    bool readImage(int argc, char *argv[]);
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
    bool iState = false; //true if an initial state exists
    for (intmax_t i = 0; i < input.width(); ++i) {
      for (intmax_t j = 0; j < input.height(); ++j) {

        if(input(i, j) != BLACK && input(i, j) != RED && input(i, j) != WHITE ) {
          success = false;
          break;
        }  
        if(input(i, j) == RED) {
          if(iState)
            success = false;
        
          iState = true;
          row = i;
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
  rowFrontier = new Deque<int>;
  colFrontier = new Deque<int>;
  rowFrontier->pushBack(row);
  colFrontier->pushBack(col);
  
  //dynamically allocate memory for 2D array of bools
  explored = new bool*[input.height()];
  for(intmax_t i = 0; i < input.width(); i++)
    explored[i] = new bool[input.width()];

  for(intmax_t i = 0; i < input.height(); i++) {
    for(intmax_t j = 0; j < input.width(); j++)
      explored[i][j] = false;
  }
  explored[row][col] = true;

  solve();

  delete rowFrontier;
  delete colFrontier;
  for(intmax_t i = 0; i < input.width(); i++) {
    delete [] explored[i];
  }
  delete explored;
  return EXIT_SUCCESS;
}

int PathFinder::solve()
{
  intmax_t rowPath, colPath, r, c;

   while(!rowFrontier->isEmpty() || !colFrontier->isEmpty()) {
     if(rowFrontier->isEmpty() || colFrontier->isEmpty())
      return EXIT_FAILURE;

      r = rowFrontier->front();
      c = colFrontier->front();
      rowFrontier->popFront();
      colFrontier->popFront();

      if(input(r, c) == WHITE && (r == 0 || r == input.height() - 1) || (c == 0 || c == input.width() - 1)) {
        solutionFound = true;
        break;
      }
        
    for(int i = 0; i < 4; i++) {
      rowPath = r + rowDir[i];
      colPath = c + colDir[i];

      if(rowPath >= 0 && colPath >= 0 && rowPath < input.height() && colPath < input.width() && input(rowPath, colPath) == WHITE) {
        if(!explored[rowPath][colPath]) {
          rowFrontier->pushBack(rowPath);
          colFrontier->pushBack(colPath);
          explored[rowPath][colPath] = true;
          nextLayerSteps++;
        }// end inner if
      }// end outer if
    }// end for
    layerStepsLeft--;
    if(layerStepsLeft == 0) {
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
  return 1;
}

int main(int argc, char *argv[])
{
  PathFinder p;

  p.readImage(argc, argv);
  p.breadthFirstSearch();

  return 0;
}