#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled) : row(row), col(col), dist_traveled(dist_traveled)
{
    // TODO
}

Node::~Node(){
    // TODO
}

int Node::getRow()
{
    return this->row;
}

int Node::getRow() const {
    return row;
}

int Node::getCol() const {
    return col;
}

int Node::getCol()
{
     return this->col;
}

int Node::getDistanceTraveled()
{
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled) {
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    return abs(goal->getRow() - this->getRow()) + abs(goal->getCol() - this->getCol());
}


//--------------------------------                             