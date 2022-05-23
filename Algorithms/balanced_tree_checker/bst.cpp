#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>


bool isBalanced(Node *root) {
	//Get the heights of the left and right subtrees - helper func?
	//Determine if this node is balanced! If not ret false!

	//Check if there are subtrees under us
	//Are they balanced?

	//If all nodes are balanced return true!
    int h = 0;
    if(root == nullptr){
        return true;
    }

    return checkHeight(root, h);
}

// Recursive function to delete a given binary tree
bool checkHeight(Node* &current, int &height)
{
    int leftHeight = 0;
    int rightHeight = 0;
 
    //  l is true iff left subtree is true
    //  r is true iff right subtree is true
    int l = 0;
    int r = 0;
 
    if(current == nullptr){
        height = 0;
        return 1;
    }
 
    //  using recursive calls to obtain left and right subtree heights
    Node* left = current->left;
    Node* right = current->right;
    l = checkHeight(left, leftHeight);
    r = checkHeight(right, rightHeight);
 
    //  the height of a subtree is the max of the left or right subtree plus 1
    if(leftHeight > rightHeight){
        height = leftHeight + 1;
    }
    else{
        height = rightHeight + 1;
    }
 
    //  if difference is more than one then the tree is not balanced
    //  we return zero because anything anded with zero will always be false
    //  the false will continue until it reaches back into the isBalanced function
    if (abs(leftHeight - rightHeight) >= 2) return 0;
    else return l && r; //  else it is true
}
