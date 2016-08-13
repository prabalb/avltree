/*
 * AVLTree.cpp
 * Author: Prabal Basu
 * Email: prabalb@aggiemail.usu.edu
 */



#include "./AVLTree.h"
#include <cassert>
#include <stdlib.h>

int AVLTree::getData(AVLNode *node) const
{
  return node->data;
}

// height increases in bottom-up fashion.
// height of a leaf node is assumed to be '1'
int AVLTree::height(AVLNode *node) const
{
  int nodeHeight = 0;
  if(node != NULL) {
    int leftHeight  = height(node->left);
    int rightHeight = height(node->right);
    nodeHeight = 1 + max(leftHeight, rightHeight);
  }
  return nodeHeight;
}

// balanceFactor(node) = height(left-subtree) - height(right-subtree)
int AVLTree::balanceFactor(AVLNode *node) const
{
  int leftHeight  = node->left  ? height(node->left)  : 0;
  int rightHeight = node->right ? height(node->right) : 0;
  return (leftHeight - rightHeight);
}

AVLNode* AVLTree::insertNode(AVLNode *lastNode, int value, bool &nodeExists, Output &cout)
{
  if(lastNode == NULL) {
    // create a new node with data = value
    lastNode = new AVLNode(value);
    return lastNode;
  }

  if(value < getData(lastNode)) {
    lastNode->left = insertNode(lastNode->left, value, nodeExists, cout);
  } else if(value > getData(lastNode)) {
    lastNode->right = insertNode(lastNode->right, value, nodeExists, cout);
  } else {
    cout << "A node with value " << value << " already exists in the tree" << "\n";
    nodeExists = true;
    return lastNode;
  }
  // inserting a node may cause imbalance
  lastNode = balanceNode(lastNode);
  return lastNode;
}

// get right most child of the left sub-tree of a node with two children
AVLNode* AVLTree::getInOrderPredecessor(AVLNode *node)
{
  AVLNode *tempNode = node->left;
  while(tempNode->right) {
    tempNode = tempNode->right;
  }
  return tempNode;
}

AVLNode* AVLTree::deleteNode(AVLNode *lastNode, int value, bool &nodeFound, Output &cout)
{
  if(!lastNode) {
    cout << "Node with value " << value << " cannot be found. Deletion cannot be performed ..." << "\n";
    nodeFound = false;
    return lastNode; // no tree exists or node with 'value' is not present in the tree
  }
  if(value < lastNode->data) {
    lastNode->left = deleteNode(lastNode->left, value, nodeFound, cout);
  } else if(value > lastNode->data) {
    lastNode->right = deleteNode(lastNode->right, value, nodeFound, cout);
  } else {
    if(lastNode->left && lastNode->right) {
      // replace lastNode with its in-order predecessor in case lastNode has two (non-null) children
      AVLNode *tempNode = getInOrderPredecessor(lastNode);
      lastNode->data = tempNode->data;
      lastNode->left = deleteNode(lastNode->left, tempNode->data, nodeFound, cout);
    } else {
      // in case of only one child, just replace lastNode with its only child
      AVLNode *tempNode = lastNode->left ? lastNode->left : lastNode->right;
      if(!tempNode) { // i.e. no child exists
        tempNode = lastNode;
        lastNode = NULL;
      } else {
        *lastNode = *tempNode;
      }
    }
  }

  if(!lastNode) return lastNode;
  // else, need to balance the tree
  lastNode = balanceNode(lastNode);
  return lastNode;
}

void AVLTree::deleteTree(AVLNode *node)
{
  if(node == NULL) return;
  if(node->left != NULL) {
    deleteTree(node->left);
  }
  if(node->right != NULL) {
    deleteTree(node->right);
  }
  delete node;
}

int AVLTree::findNode(AVLNode *lastNode, int value, Output &cout)
{
  if(lastNode == NULL) {
    return -1;
  }

  if(value < getData(lastNode)) {
    if(lastNode->left) {
      return findNode(lastNode->left, value, cout);
    }
  } else if(value > getData(lastNode)) {
    if(lastNode->right) {
      return findNode(lastNode->right, value, cout);
    }
  } else if(value == getData(lastNode)) {
    return height(lastNode);
  }
  cout << "Node with value " << value << " is not found in the tree ..." << "\n";
  return -1;
}


AVLNode* AVLTree::balanceNode(AVLNode *node)
{
  if(balanceFactor(node) > 1) {
    assert(node->left); // sanity check
    if(balanceFactor(node->left) > 0) {
      node = rotateLL(node);
    } else {
      node = rotateLR(node); 
    }
  }
  else if(balanceFactor(node) < -1) {
    assert(node->right); // sanity check
    if(balanceFactor(node->right) > 0) {
      node = rotateRL(node);
    } else {
      node = rotateRR(node);
    }
  }
  return node;
}

// single right rotation
AVLNode* AVLTree::rotateLL(AVLNode *node)
{
  AVLNode *tempNode = node->left;
  node->left = tempNode->right;
  tempNode->right = node;
  return tempNode;
}

// left rotation -> right rotation
AVLNode* AVLTree::rotateLR(AVLNode *node)
{
  AVLNode *tempNode = node->left;
  node->left = rotateRR(tempNode);
  return rotateLL(node);
}

// right rotation -> left rotation
AVLNode* AVLTree::rotateRL(AVLNode *node)
{
  AVLNode *tempNode = node->right;
  node->right = rotateLL(tempNode);
  return rotateRR(node);
}

// single left rotation
AVLNode* AVLTree::rotateRR(AVLNode *node)
{
  AVLNode *tempNode = node->right;
  node->right = tempNode->left;
  tempNode->left = node;
  return tempNode;
}

// root -> left -> right
void AVLTree::doPreOrderTraversal(AVLNode *node, Output &cout) 
{
  if(node == NULL) return;
  cout << getData(node) << " ";
  doPreOrderTraversal(node->left, cout);
  doPreOrderTraversal(node->right, cout);
}

// left -> root -> right
void AVLTree::doInOrderTraversal(AVLNode *node, Output &cout) 
{
  if(node == NULL) return;
  doInOrderTraversal(node->left, cout);
  cout << getData(node) << " ";
  doInOrderTraversal(node->right, cout);
}

// left -> right -> root
void AVLTree::doPostOrderTraversal(AVLNode *node, Output &cout) 
{
  if(node == NULL) return;
  doPostOrderTraversal(node->left, cout);
  doPostOrderTraversal(node->right, cout);
  cout << getData(node) << " ";
}
