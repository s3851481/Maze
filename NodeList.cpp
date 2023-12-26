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

/*  
bool NodeList::containsNode(Node* node) {
    if (node == nullptr) {
        return false;
    }

    for (int i = 0; i < length; ++i) {
        if (nodes[i]->getRow() == node->getRow() &&
            nodes[i]->getCol() == node->getCol()) {
            return true;
        }
    }
    return false;
}
bool NodeList::openListContains(std::priority_queue<Node*, std::vector<Node*>, CompareNodes>& openList, Node* node) {
    if (node == nullptr) {
        return false;
    }

    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> tempOpenList = openList;

    while (!tempOpenList.empty()) {
        if (tempOpenList.top()->getRow() == node->getRow() &&
            tempOpenList.top()->getCol() == node->getCol()) {
            return true;
        }
        tempOpenList.pop();
    }

    return false;
}

bool NodeList::operator()(Node *lhs, Node *rhs)
{
    return false;
}
  */