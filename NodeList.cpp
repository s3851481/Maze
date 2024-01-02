#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
     for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i) {
        nodes[i] = nullptr;
    }
}

NodeList::~NodeList(){
    for (int i = 0; i < length; ++i) {
        delete nodes[i];
    }
}

//deep
NodeList::NodeList(NodeList& other){
     // Copy constructor implementation
    length = other.length;
    for (int i = 0; i < length; ++i) {
        nodes[i] = new Node(*other.nodes[i]);
    }
}

int NodeList::getLength(){
        // Return the number of elements in the NodeList
    return length;
}

void NodeList::addElement(Node* newPos){
    // Add a COPY node element to the BACK of the NodeList.
    // Check for array bounds 
    if (length < NODE_LIST_ARRAY_MAX_SIZE) {
        nodes[length] = new Node(*newPos);
        ++length;
    } else {
        std::cerr << "NodeList is full. Cannot add more elements." << std::endl;
    }
}

Node* NodeList::getNode(int i){
    // Get a pointer to the ith node in the NodeList
    // Check if the index is within valid range
    if (i >= 0 && i < length) {
        return nodes[i];
    } else {
        std::cerr << "Invalid index. Returning nullptr." << std::endl;
        return nullptr;
    }
}


Node* NodeList::getSmallestEstimation(Node* goalNode) {
    std::cout << "test1" << std::endl;
    if (length == 0) {
        std::cerr << "Error: NodeList is empty." << std::endl;
        return nullptr;
    }

    Node* smallestNode = nodes[0];
    int smallestEstimation = smallestNode->getEstimatedDist2Goal(goalNode);

    for (int i = 1; i < length; ++i) {
        int currentEstimation = nodes[i]->getEstimatedDist2Goal(goalNode);
        if (currentEstimation < smallestEstimation) {
            smallestNode = nodes[i];
            smallestEstimation = currentEstimation;
        }
    }

    return smallestNode;
}

Node *NodeList::findNode(int targetRow, int targetCol)
{
    return nullptr;
}

int NodeList::getManhattanDistance(int targetRow, int targetCol)
{
    return 0;
}



void NodeList::setEstimatedDist2Goal(int estimation)
{
}
