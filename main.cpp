/*
 * main.cpp
 * Author: Prabal Basu
 * Email: prabalb@aggiemail.usu.edu
 */


#include "./AVLTree.h"
#include <cassert>
#include <string>
#include <stdlib.h>

int main() {

  // this file will contain the output messages of various tree operations
  string outFile = "./Basu-A02049867.txt";

  Output cout(outFile.c_str());

  AVLNode *rootNode = NULL;
  AVLTree avlTree;

  int userOption;
  bool exit = false;
  
  do {
    std::cout << "Welcome! Please select an option (e.g. 1, 2 etc.) and hit enter ..." << "\n";
    std::cout << "1. Create an AVL tree" << "\n";
    std::cout << "2. Insert a node" << "\n";
    std::cout << "3. Delete a node" << "\n";
    std::cout << "4. Search a node" << "\n";
    std::cout << "5. Traverse the tree" << "\n";
    std::cout << "6. Delete the tree" << "\n";
    std::cout << "7. Check balance of the tree" << "\n";
    std::cout << "8. Exit" << "\n";

    cin >> userOption;

    // avoid getting in to infinite loop for non-int-type inputs
    cin.clear();
    cin.ignore(100, '\n'); // asks cin to discard 100 characters from the input stream

    switch(userOption)
    {
      case 1: // create tree
      {
        string fileName = "";
        ifstream file;

        std::cout << "Please specify full path of the input file: "; 
        cin >> fileName;
        file.open(fileName.c_str());
        char content[10000];
        if(file.is_open()) {
          // always create a new AVL tree
          if(rootNode != NULL) {
            avlTree.deleteTree(rootNode);
            rootNode = NULL;
          }
          while(file >> content) {
            int nodeVal = atoi(content);
            bool nodeExists = false;
            rootNode = avlTree.insertNode(rootNode, nodeVal, nodeExists, cout);
            // sanity check
            //assert(rootNode); // rootNode will still point to NULL if the input file is empty 
          }
          cout << "Create Tree: ";
          avlTree.doPreOrderTraversal(rootNode, cout);
          cout << "\n";
          file.close();
        } else {
          std::cout << "Could not open the input file specified, please try again ..." << "\n";
        }
        break;
      }

      case 2: // insertion
      {
        int nodeVal;
        std::cout << "Please insert an integer, the program will add/create a node with that value ..." << "\n";
        cin >> nodeVal;
        bool nodeExists = false;
        rootNode = avlTree.insertNode(rootNode, nodeVal, nodeExists, cout);
        assert(rootNode); // sanity check
        if(!nodeExists) {
          cout << "Updated tree (pre-order) after inserting " << nodeVal << ": "; 
          avlTree.doPreOrderTraversal(rootNode, cout);
          cout << "\n";
        }
        break;
      }

      case 3: // deletion
      {
        if(rootNode == NULL) {
          std::cout << "Node cannot be deleted. Empty Tree!" << "\n";
        } else {
          int nodeVal;
          std::cout << "Please insert an integer, the program will delete the node with that value ..." << "\n";
          cin >> nodeVal;
          bool nodeFound = true;
          rootNode = avlTree.deleteNode(rootNode, nodeVal, nodeFound, cout);
          if(nodeFound) {
            cout << "Updated tree (pre-order) after deleting " << nodeVal << ": ";
            avlTree.doPreOrderTraversal(rootNode, cout);
            cout << "\n";
          }
        }
        break;
      }

      case 4: // search
      {
        if(rootNode == NULL) {
          std::cout << "Tree is empty!" << "\n";
        } else {
          int nodeVal;
          std::cout << "Please insert an integer, the program will print the height of the node with that value ..." << "\n";
          cin >> nodeVal;
          int height = avlTree.findNode(rootNode, nodeVal, cout);
          if(height != -1) {
            cout << "The node with value " << nodeVal << " is found at height (considering height of a leaf-node to be '1') " << height << "\n";
          }
        }
        break;
      }

      case 5: // traversal
      {
        if(rootNode == NULL) {
          std::cout << "Tree is empty!" << "\n";
          break;
        }

        std::cout << "Please choose the type (1 or 2 or 3) of traversal ..." << "\n";
        std::cout << "(1) Pre-order" << "\n";
        std::cout << "(2) Post-order" << "\n";
        std::cout << "(3) In-order" << "\n";

        int traverseType;
        cin >> traverseType;

        cin.clear();
        cin.ignore(100, '\n');

        switch(traverseType)
        {
          case 1: // pre-order
          {
            cout << "Pre-order traversal : ";
            avlTree.doPreOrderTraversal(rootNode, cout);
            cout << "\n";
            break;
          }

          case 2: // post-order
          {
            cout << "Post-order traversal : ";
            avlTree.doPostOrderTraversal(rootNode, cout);
            cout << "\n";
            break;
          }

          case 3: // in-order
          {
            cout << "In-order traversal : ";
            avlTree.doInOrderTraversal(rootNode, cout);
            cout << "\n";
            break;
          }

          default:
          {
            std::cout << "You have made an incorrect choice, please try again ..." << "\n";
          }
        }
        break;
      }

      case 6: // delete tree
      {
        avlTree.deleteTree(rootNode);
        rootNode = NULL;
        cout << "Delete tree: Tree deleted ..." << "\n";
        break;
      }

      case 7: // check balance
      {
        if(rootNode == NULL) {
          std::cout << "Tree is empty!" << "\n";
        } else {
          rootNode = avlTree.balanceNode(rootNode); // should not require this step, it should always be balanced
          cout << "Check Balance: " << avlTree.balanceFactor(rootNode) << "\n";
        }
        break;
      }

      case 8: // exit
      {
        std::cout << "Bye ...\n";
        exit = true;
        break;
      }

      default:
      {
        std::cout << "You have made an incorrect choice, please try again ..." << "\n";
      }
    }
  } while(!exit);
  return 0;
}
