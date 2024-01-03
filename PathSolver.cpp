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
        std::cout << goalNode << std::endl;
        // Main loop
std::cout << "openList Length: " << openList->getLength() << std::endl;
std::cout << "closedList Length: "<< closedList->getLength() << std::endl;
      

      
// bool goalReached = false;
// while (openList->getLength() > 0 && !goalReached) {
    // Get the starting point 
    
    //std::cout << smallestNode << std::endl;
    // Iterate through the openList to find the node with the smallest estimated distance
    
   
    
for (int i = 0; i < openList->getLength(); ++i) {
    std::cout << i << std::endl;
    std::cout << "Estimated distance of Node " << i << " to goal: " << openList->getNode(i)->getEstimatedDist2Goal(goalNode) << std::endl;
    Node* current = openList->getNode(i);
    std::cout << "Checking current Node - Row: " << current->getRow() << ", Col: " << current->getCol() << std::endl;

    // Iterate through the directions
    for (int dir = 0; dir < DIRECTIONS_COUNT; ++dir) {
        int newRow = current->getRow() + directions[dir][0];
        int newCol = current->getCol() + directions[dir][1];

        // Print information about the current position
        std::cout << "start: " << startRow << startCol << std::endl;
        std::cout << "Checking position: Row " << newRow << ", Col " << newCol << std::endl;
        std::cout << "goal: " << goalRow << goalCol << std::endl;

// Inside the inner loop (for directions)
for (int dir = 0; dir < DIRECTIONS_COUNT; ++dir) {
    int newRow = current->getRow() + directions[dir][0];
    int newCol = current->getCol() + directions[dir][1];

    // Print information about the current position
    std::cout << "start: " << startRow << startCol << std::endl;
    std::cout << "Checking position: Row " << newRow << ", Col " << newCol << std::endl;
    std::cout << "goal: " << goalRow << goalCol << std::endl;

    // Check if the new position is valid
    if (newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM) {
        // Check if the new position is in the closedList
        bool isInClosedList = false;

        // Iterate through the nodes in the closedList
        for (int j = 0; j < closedList->getLength(); ++j) {
            Node* closedListNode = closedList->getNode(j);
            if (closedListNode->getRow() == newRow && closedListNode->getCol() == newCol) {
                // The node at the new position is in the closedList
                isInClosedList = true;
                break;  // No need to continue checking
            }
        }

        if (!isInClosedList) {
            // Mark the position as visited
            closedList->addElement(new Node(newCol, newRow, 0));
            std::cout << "Position added to closedList" << std::endl;

            // Print information about the validity of the position
            std::cout << "Position is valid" << std::endl;

            // Check if the new position is a wall
            if (env[newRow][newCol] != SYMBOL_WALL) {
                // Create a new node for the neighbor and add it to the openList
                Node* neighbor = new Node(newCol, newRow, 0);
                openList->addElement(neighbor);

                // Print information about the added neighbor
                std::cout << "Added neighbor: Row " << newRow << ", Col " << newCol << std::endl;
            } else {
                // Print information about the wall
                std::cout << "Wall detected at: Row " << newRow << ", Col " << newCol << std::endl;
            }
        } else {
            // Print information about an invalid position or a visited position
            std::cout << "Position is invalid or already visited" << std::endl;
        }
    } else {
        // Print information about an invalid position (newRow or newCol is -1)
        std::cout << "Position is out of bounds" << std::endl;
    }
}
    // After checking all neighbors, add the current node to the closedList
    closedList->addElement(current);
}
}
// Proper cleanup
delete openList;
delete closedList;




}}



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
