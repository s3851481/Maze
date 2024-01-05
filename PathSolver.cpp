

#include "NodeList.h"
#include "PathSolver.h"
#include <iostream>

#include <climits>
#define DIRECTIONS_COUNT 4
int directions[DIRECTIONS_COUNT][2]
    = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
bool isValid (int row, int col);

PathSolver::PathSolver () { nodesExplored = new NodeList (); }

PathSolver::~PathSolver () { delete nodesExplored; }
// Milestone 2
void
PathSolver::forwardSearch (Env env)
{
  // Find the starting point in the environment
  int startRow = -1, startCol = -1;
  int goalRow = -1, goalCol = -1;

  for (int i = 0; i < ENV_DIM && (startRow == -1 || goalRow == -1); ++i)
    {
      for (int j = 0; j < ENV_DIM; ++j)
        {
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
      NodeList *closedList = new NodeList ();
      NodeList *openList = new NodeList ();
      Node *startNode = new Node (startCol, startRow, 0);
      openList->addElement (startNode);

      Node *goalNode = new Node (goalCol, goalRow, 0);
      std::cout << "openList Length: " << goalNode << std::endl;
      std::cout << "openList Length: " << openList->getLength () << std::endl;
      std::cout << "closedList Length: " << closedList->getLength ()
                << std::endl;

      bool goalFound = false;
      int i = 0;

      while (i < openList->getLength () && !goalFound)
        {
          Node *current = openList->getNode (i);
          std::cout << "Checking current Node - Row: " << current->getCol ()
                    << ", Col: " << current->getRow () << std::endl;

          int dir = 0;
          while (dir < DIRECTIONS_COUNT && !goalFound)
            {
              int newRow = current->getRow () + directions[dir][0];
              int newCol = current->getCol () + directions[dir][1];

              std::cout << "Checking position: Row " << newRow << ", Col "
                        << newCol << std::endl;

              if (newRow >= 0 && newRow < ENV_DIM && newCol >= 0
                  && newCol < ENV_DIM)
                {
                  bool isInClosedList = false;
                  int j = 0;

                  while (j < closedList->getLength () && !isInClosedList)
                    {
                      Node *closedListNode = closedList->getNode (j);

                      if (closedListNode->getRow () == newRow
                          && closedListNode->getCol () == newCol)
                        {
                          isInClosedList = true;
                        }
                      ++j;
                    }

                  if (!isInClosedList)
                    {
                      // std::cout << "Checking position: Row " << newRow << ",
                      // Col " << newCol << std::endl; std::cout << "Position is
                      // valid" << std::endl;

                      if (env[newRow][newCol] == env[goalRow][goalCol])
                        {
                          std::cout << "Current position: (Row " << newRow
                                    << ", Col " << newCol << ")" << std::endl;
                          std::cout << "Goal Position: (" << goalRow << ", "
                                    << goalCol << ")" << std::endl;
                          std::cout << "Goal Reached - "
                                    << env[goalRow][goalCol] << std::endl;

                          goalFound = true;
                          // You can add code here to construct the path or
                          // perform any other actions
                          // ...
                        }
                      else if (env[newRow][newCol] == SYMBOL_WALL)
                        {
                          std::cout << "Wall detected at: Row " << newRow
                                    << ", Col " << newCol << std::endl;
                        }
                      else
                        {
                          Node *neighbor
                              = new Node (newRow, newCol,
                                          current->getDistanceTraveled ()
                                              + 1); // Update distance_traveled
                          openList->addElement (neighbor);
                          std::cout << "Added neighbor: Row " << newRow
                                    << ", Col " << newCol << std::endl;
                        }
                    }
                  else
                    {
                      std::cout << "Position is invalid or already visited"
                                << std::endl;
                    }
                }
              else
                {
                  std::cout << "Position is out of bounds" << std::endl;
                }

              ++dir;
            }
          std::cout << "Distance travelled " << current->getDistanceTraveled ()
                    << std::endl;
          closedList->addElement (current);
          ++i;
        }
      if (goalFound)
        {
          Node *goalNode = new Node (goalRow, goalCol, 0);
          closedList->addElement (goalNode);
        }

      // Store the items in closedList to nodesExplored
      nodesExplored = new NodeList (*closedList);
      std::cout << "Nodes Explored: ";
      for (int i = 0; i < nodesExplored->getLength (); ++i)
        {
          Node *exploredNode = nodesExplored->getNode (i);
          std::cout << "(" << exploredNode->getRow () << ", "
                    << exploredNode->getCol () << ") ";
        }
      std::cout << std::endl;

      delete openList;
      delete closedList;
    }
}

// here
// Deep Copy Milestone 3
NodeList *
PathSolver::getNodesExplored ()
{
  return new NodeList (*nodesExplored);
}

// Milestone 3
NodeList *
PathSolver::getPath (Env env)
{
  NodeList *path = new NodeList ();
  // std::cout << length << std::endl;
  //  Find the goal position in the environment
  int startRow = -1, startCol = -1;
  int goalRow = -1, goalCol = -1;

  for (int i = 0; i < ENV_DIM && (startRow == -1 || goalRow == -1); ++i)
    {
      for (int j = 0; j < ENV_DIM; ++j)
        {
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

  if (goalRow != -1 && goalCol != -1)
    {
      // Find the goal node in nodesExplored
      Node *goalNode = nullptr;
      int i = 0;
      std::cout << nodesExplored->getLength () << std::endl;
      while (i < nodesExplored->getLength () && goalNode == nullptr)
        {
          Node *currentNode = nodesExplored->getNode (i);
          if (currentNode->getRow () == goalRow
              && currentNode->getCol () == goalCol)
            {
              goalNode = currentNode;
            }
          ++i;
        }

      while (goalNode != nullptr)
        {
          // Start from the goal node and backtrack to the start node
          path->addElement (new Node (goalNode->getRow (), goalNode->getCol (),
                                      goalNode->getDistanceTraveled ()));

          // Find the previous node by iterating through nodesExplored
          goalNode = nullptr;
          i = 0;
          while (i < nodesExplored->getLength () && goalNode == nullptr)
            {
              Node *currentNode = nodesExplored->getNode (i);
              if (currentNode->getDistanceTraveled ()
                      == goalNode->getDistanceTraveled () - 1
                  && (abs (currentNode->getRow () - goalNode->getRow ())
                          + abs (currentNode->getCol () - goalNode->getCol ())
                      == 1))
                {
                  goalNode = currentNode;
                }
              ++i;
            }
        }
    }

  return path;
}

//-----------------------------

bool
isValid (int row, int col)
{
  return false;
}
