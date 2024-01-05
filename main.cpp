/*
The pathsolver program uses a backtracking algorithm to read an environment file
and finds the start position and goal position. It then searches the shortest
path to the goal position by using the manhattan equation.

Issues I encountered included segmentation faults when pointers were not
initialized. While loops constantly running without progressing.

I tried to get the third milestone done but for some reason when it got the
closedList and past it into the exploredPositions and then when it got sent to
the getPath it had some weird memory management and copied an extra value which
had a large length value which in turn caused one of the loops to not enter.

*/
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"
#include "Types.h"

// Helper test functions
void testNode ();
void testNodeList ();

// Read a environment from standard input.
void readEnvStdin (Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout (Env env, NodeList *solution);
// void printEnvStdout(Env env);

int
main (int argc, char **argv)
{

  // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
  // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
  // AS YOU GO ALONG.
  // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
  // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" <<
  // std::endl; testNode(); testNodeList(); std::cout << "DONE TESTING" <<
  // std::endl << std::endl; Load Environment
  Env env;
  readEnvStdin (env);
  // printEnvStdout(env);

  // Solve using forwardSearch
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2

  PathSolver *pathSolver = new PathSolver ();
  pathSolver->forwardSearch (env);

  NodeList *exploredPositions = nullptr;

  exploredPositions = pathSolver->getNodesExplored ();
  // Print the content of exploredPositions

  std::cout << "Explored Positions: ";
  for (int i = 0; i < exploredPositions->getLength (); ++i)
    {
      Node *exploredNode = exploredPositions->getNode (i);
      std::cout << "(" << exploredNode->getRow () << ", "
                << exploredNode->getCol () << ", "
                << exploredNode->getDistanceTraveled () << ") ";
    }
  std::cout << std::endl;

  // Get the path
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3

  NodeList *solution = pathSolver->getPath (env);

  printEnvStdout (env, solution);

  delete pathSolver;
  delete exploredPositions;
  delete solution;
}

void
readEnvStdin (Env env)
{
  // Prompt the user to enter the environment file name
  std::string fileName;
  std::cout << "Enter the environment file name (including .env extension): ";
  std::cin >> fileName;

  // Open the file for reading
  std::ifstream inputFile (fileName);

  if (!inputFile.is_open ())
    {
      std::cerr << "Error opening file: " << fileName << std::endl;
      return;
    }

  // Read characters from the file and populate the environment array
  for (int i = 0; i < ENV_DIM; ++i)
    {
      for (int j = 0; j < ENV_DIM; ++j)
        {
          inputFile >> env[i][j];
        }
    }

  // Close the file
  inputFile.close ();
}

// Print out a Environment to standard output with path.
void
printEnvStdout (Env env, NodeList *solution)
{
  std::cout << "Environment with Path:" << std::endl;

  for (int i = 0; i < ENV_DIM; ++i)
    {
      for (int j = 0; j < ENV_DIM; ++j)
        {
          // Check if the current position is in the solution path
          bool isInPath = false;
          for (int k = 0; k < solution->getLength (); ++k)
            {
              Node *pathNode = solution->getNode (k);
              if (pathNode->getRow () == i && pathNode->getCol () == j)
                {
                  isInPath = true;
                  break;
                }
            }

          // Output the appropriate symbol based on the movement in the path
          if (isInPath)
            {
              if (j < ENV_DIM - 1 && solution->getNode (i * ENV_DIM + (j + 1)))
                {
                  std::cout << ">"; // Move Right
                  continue;
                }
              if (j > 0 && solution->getNode (i * ENV_DIM + (j - 1)))
                {
                  std::cout << "<"; // Move Left
                  continue;
                }
              if (i > 0 && solution->getNode ((i - 1) * ENV_DIM + j))
                {
                  std::cout << "^"; // Move Up
                  continue;
                }
              if (i < ENV_DIM - 1 && solution->getNode ((i + 1) * ENV_DIM + j))
                {
                  std::cout << "v"; // Move Down
                  continue;
                }
            }

          // If not in path or no movement, print the environment symbol
          std::cout << env[i][j] << " ";
        }
      std::cout << std::endl;
    }
}

// void printEnvStdout(Env env) {
//     std::cout << "Environment:" << std::endl;
//     for (int i = 0; i < ENV_DIM; ++i) {
//         for (int j = 0; j < ENV_DIM; ++j) {
//             std::cout << env[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

void
testNode ()
{
  std::cout << "TESTING Node" << std::endl;

  // Read the environment from the file
  Env env;
  readEnvStdin (env);

  // Find the starting point in the environment
  int startRow = -1, startCol = -1;
  int goalRow = -1, goalCol = -1;

  for (int i = 0; i < ENV_DIM; ++i)
    {
      for (int j = 0; j < ENV_DIM; ++j)
        {
          // std::cout << "" << env[i][j];
          if (env[i][j] == SYMBOL_START)
            {
              startRow = i;
              startCol = j;
              std::cout << "Start Position: (" << startRow << ", " << startCol
                        << ")" << std::endl;
            }
          else if (env[i][j] == SYMBOL_GOAL)
            {
              goalRow = i;
              goalCol = j;
              std::cout << "Goal Position: (" << goalRow << ", " << goalCol
                        << ")" << std::endl;
            }
        }
    }

  if (startRow != -1 && goalRow != -1)
    {
      // Create a test Node for the starting point
      Node *startNode = new Node (startCol, startRow, 0);

      // Print information about the starting point
      std::cout << "Starting Point Information:" << std::endl;
      std::cout << "Row: " << startNode->getRow () << std::endl;
      std::cout << "Column: " << startNode->getCol () << std::endl;
      std::cout << "Distance Traveled: " << startNode->getDistanceTraveled ()
                << std::endl;

      // Clean up memory
      delete startNode;
    }
  else
    {
      std::cout << "Starting or goal point not found in the environment."
                << std::endl;
    }
}

void
testNodeList ()
{
  std::cout << "TESTING NodeList" << std::endl;

  // Make a simple NodeList, should be empty size
  NodeList *nodeList = new NodeList ();
  std::cout << "NodeList size: " << nodeList->getLength () << std::endl;

  // Add a Node to the NodeList, print size
  Node *b1 = new Node (1, 1, 1);
  nodeList->addElement (b1);
  std::cout << "NodeList size: " << nodeList->getLength () << std::endl;

  // Add second Nodetest
  Node *b2 = new Node (0, 0, 1);
  nodeList->addElement (b2);
  std::cout << "NodeList size: " << nodeList->getLength () << std::endl;

  // Test Get-ith - should be 0,0,1
  Node *getB = nodeList->getNode (1);
  std::cout << getB->getRow () << ",";
  std::cout << getB->getCol () << ",";
  std::cout << getB->getDistanceTraveled () << std::endl;

  // Print out the NodeList
  std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO"
            << std::endl;
}