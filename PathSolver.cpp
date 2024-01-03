/*
The pathsolver program uses a backtracking algorithm to read an environment file and 
finds the start position and goal position. It then searches the shortest path to the 
goal position by using the manhattan equation.

Issues I encountered included segmentation faults when pointers were not initialized. 
While loops constantly running without progressing. 


*/

#include "PathSolver.h"
#include <iostream>
#include "NodeList.h"

#include <climits>
#define DIRECTIONS_COUNT 4
int directions[DIRECTIONS_COUNT][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool isValid(int row, int col);


PathSolver::PathSolver(){
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver(){
    delete nodesExplored; 
}
//Milestone 2
void PathSolver::forwardSearch(Env env) {
    // Find the starting point in the environment
    int startRow = -1, startCol = -1;
    int goalRow = -1, goalCol = -1;

    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            if (env[i][j] == SYMBOL_START) {
                startRow = i;
                startCol = j;
                std::cout << "Start Position: (" << startRow << ", " << startCol << ")" << std::endl;
            } else if (env[i][j] == SYMBOL_GOAL) {
                goalRow = i;
                goalCol = j;
                std::cout << "Goal Position: (" << goalRow << ", " << goalCol << ")" << std::endl;
            }
        }
    }

    if (startRow != -1 && goalRow != -1) {
        NodeList* closedList = new NodeList();
        NodeList* openList = new NodeList();
        Node* startNode = new Node(startCol, startRow, 0);
        openList->addElement(startNode);

        Node* goalNode = new Node(goalCol, goalRow, 0);
        std::cout << "openList Length: " << goalNode << std::endl;
        std::cout << "openList Length: " << openList->getLength() << std::endl;
        std::cout << "closedList Length: " << closedList->getLength() << std::endl;

        for (int i = 0; i < openList->getLength(); ++i) {
            Node* current = openList->getNode(i);
            std::cout << "Checking current Node - Row: " << current->getRow() << ", Col: " << current->getCol() << std::endl;

            for (int dir = 0; dir < DIRECTIONS_COUNT; ++dir) {
                int newRow = current->getRow() + directions[dir][0];
                int newCol = current->getCol() + directions[dir][1];

                //std::cout << "Checking position: Row " << newRow << ", Col " << newCol << std::endl;

                for (int dir = 0; dir < DIRECTIONS_COUNT; ++dir) {
                    int newRow = current->getRow() + directions[dir][0];
                    int newCol = current->getCol() + directions[dir][1];

                    std::cout << "Checking position: Row " << newRow << ", Col " << newCol << std::endl;

                    if (newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM) {
                        bool isInClosedList = false;

                        for (int j = 0; j < closedList->getLength(); ++j) {
                            Node* closedListNode = closedList->getNode(j);

                            if (closedListNode->getRow() == newRow && closedListNode->getCol() == newCol) {
                                isInClosedList = true;
                                break;  // No need to continue checking
                            }
                        }

                        if (!isInClosedList) {
                            std::cout << "Checking position: Row " << newRow << ", Col " << newCol << std::endl;
                            std::cout << "Position is valid" << std::endl;

                            if (env[newRow][newCol] != SYMBOL_WALL) {
                                Node* neighbor = new Node(newCol, newRow, 0);
                                openList->addElement(neighbor);

                                std::cout << "Added neighbor: Row " << newRow << ", Col " << newCol << std::endl;
                            } else {
                                std::cout << "Wall detected at: Row " << newRow << ", Col " << newCol << std::endl;
                            }
                        } else {
                            std::cout << "Position is invalid or already visited" << std::endl;
                        }
                    } else {
                        std::cout << "Position is out of bounds" << std::endl;
                    }
                }
            }

            closedList->addElement(current);
        }

        delete openList;
        delete closedList;
    }
}


//Deep Copy Milestone 2
NodeList* PathSolver::getNodesExplored(){
    return new NodeList(*nodesExplored);
}

//Milestone 3
NodeList* PathSolver::getPath(Env env){
        NodeList* path = new NodeList();
        return path;
}

//-----------------------------

bool isValid(int row, int col)
{
    return false;
}
