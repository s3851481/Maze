#include "PathSolver.h"
#include <iostream>

//added stuff 
/*#include <climits> 
#include "NodeList.h"
#define DIRECTIONS_COUNT 4
bool isValid(int row, int col);
//added stuff
*/

PathSolver::PathSolver(){
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver(){
    delete nodesExplored; 
}
//Milestone 2
void PathSolver::forwardSearch(Env env) {
    //int directions[DIRECTIONS_COUNT][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Find the starting point in the environment
    // Read the environment from the file


    // Find the starting point in the environment
    int startRow = -1, startCol = -1;
    int goalRow = -1, goalCol = -1;

    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
           // std::cout << "" << env[i][j];
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
        // Create a test Node for the starting point
        Node* startNode = new Node(startCol, startRow, 0);

        // Print information about the starting point
        std::cout << "Starting Point Information:" << std::endl;
        std::cout << "Row: " << startNode->getRow() << std::endl;
        std::cout << "Column: " << startNode->getCol() << std::endl;
        std::cout << "Distance Traveled: " << startNode->getDistanceTraveled() << std::endl;

        // Clean up memory
        delete startNode;
    } else {
        std::cout << "Starting or goal point not found in the environment." << std::endl;
    }
    NodeList* openList = new NodeList();
    NodeList* closedList = new NodeList();

    Node* startNode = new Node(startCol, startRow, 0);
    openList->addElement(startNode);
    std::cout << "NodeList size: " << openList->getLength() << std::endl;

// Print information about nodes in the openList
for (int i = 0; i < openList->getLength(); ++i) {
    Node* currentNode = openList->getNode(i);
    std::cout << "Node " << i << " Information:" << std::endl;
    std::cout << "Row: " << currentNode->getRow() << std::endl;
    std::cout << "Column: " << currentNode->getCol() << std::endl;
    std::cout << "Distance Traveled: " << currentNode->getDistanceTraveled() << std::endl;
}



// Clean up memory
delete openList;
delete closedList; 





}




   // Node startNode(startRow, startCol, 0);
   // Node goalNode(goalRow, goalCol, 0);
   // NodeList openList;
    //NodeList closedList;
    
   
    // Print the information for verification
    //std::cout << "Start Node: (" << startNode.getRow() << ", " << startNode.getCol() << ")" << std::endl;
    //std::cout << "Goal Node: (" << goalNode.getRow() << ", " << goalNode.getCol() << ")" << std::endl;

    // Ensure there's an initial node in the open list
    //openList.addElement(&startNode);






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


//added stuff

 /*
bool isValid(int row, int col)
{
    return false;
}
 */

bool isValid(int row, int col)
{
    return false;
}
