#include "NodeList.h"
#include <iostream>

NodeList::NodeList ()
{
  for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i)
    {
      nodes[i] = nullptr;
    }
}

NodeList::~NodeList ()
{
  for (int i = 0; i < length; ++i)
    {
      delete nodes[i];
    }
}

// deep copy
//  Copy constructor for NodeList
NodeList::NodeList (NodeList &other)
{
  // Copy the length from the other NodeList
  length = other.length;
  std::cout << "Lengths is " << length << std::endl;

  // Copy each node from the other NodeList
  for (int i = 0; i < length; ++i)
    {
      // Use the copy constructor of Node to create a new node
      nodes[i] = new Node (*(other.nodes[i]));
    }
}

int
NodeList::getLength ()
{
  // Return the number of elements in the NodeList
  return length;
}

void
NodeList::addElement (Node *newPos)
{
  // Add a COPY node element to the BACK of the NodeList.
  // Check for array bounds

  if (length < NODE_LIST_ARRAY_MAX_SIZE)
    {
      nodes[length] = new Node (*newPos);
      ++length;
    }
  else
    {
      std::cerr << "NodeList is full. Cannot add more elements." << std::endl;
    }
}

Node *
NodeList::getNode (int i)
{
  // Get a pointer to the ith node in the NodeList
  // Check if the index is within valid range
  if (i >= 0 && i < length)
    {
      return nodes[i];
    }
  else
    {
      std::cerr << "Invalid index. Returning nullptr." << std::endl;
      return nullptr;
    }
}

