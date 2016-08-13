/*
 * AVLTree.h
 * Author: Prabal Basu
 * Email: prabalb@aggiemail.usu.edu
 */


#include "./wrapper.h"

class AVLNode {

  friend class AVLTree; // AVLTree object needs to access the private members of AVLNode class

  private:
    AVLNode *left;
    AVLNode *right;
    int data;

  public:
    AVLNode(int value) : left(NULL), right(NULL) , data(value) {}
};

class AVLTree {
  
  public:
    // to access value of a node
    int getData(AVLNode *node) const;

    // height of a node
    int height(AVLNode *node) const;

    // difference of height of left child and height of right child
    int balanceFactor(AVLNode *node) const;

    // insertion and deletion of a node (with a given value)
    AVLNode *insertNode(AVLNode *lastNode, int value, bool &nodeExists, Output &cout);
    AVLNode *deleteNode(AVLNode* lastNode, int value, bool &nodeFound, Output &cout);

    // to delete the entire tree
    void deleteTree(AVLNode* node);

    // to search a node with a given value
    int findNode(AVLNode *lastNode, int value, Output &cout);

    // given a node, get its predecessor node encountered in in-order traversal of the tree
    AVLNode *getInOrderPredecessor(AVLNode *node);

    // various rotation methods to address tree-imbalance
    AVLNode *rotateLL(AVLNode *node);
    AVLNode *rotateLR(AVLNode *node);
    AVLNode *rotateRL(AVLNode *node);
    AVLNode *rotateRR(AVLNode *node);

    // method to balance an AVL tree
    AVLNode *balanceNode(AVLNode *node);

    // traversal routines
    void doPreOrderTraversal(AVLNode *node, Output &cout);
    void doInOrderTraversal(AVLNode *node, Output &cout);
    void doPostOrderTraversal(AVLNode *node, Output &cout);
};
