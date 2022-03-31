#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool equalPathsHelper(Node* root, int &height);

bool equalPaths(Node * root)
{
    int height = 0;
    return equalPathsHelper(root, height); //   using the helper function to obtain result
}

bool equalPathsHelper(Node * root, int &height){

    int leftHeight = 0;
    int rightHeight = 0;
    
    // base case leaf node
    if(root == nullptr){
        height = 0;
        return 1;
    }

    int l = 0; //   left sub-tree
    int r = 0; //   right sub-tree

    //  recursive call to obtain height of subtrees until a leaf
    l = equalPathsHelper(root->left, leftHeight);
    r = equalPathsHelper(root->right, rightHeight);

    // updates the larger height of the two subtrees in case one side is a null
    if(leftHeight > rightHeight){
        height = leftHeight + 1;
    }
    else height = rightHeight + 1;

    //  will not count a subtree with a 0 height on one side, a side must be at least 1 in height
    if((rightHeight != leftHeight) && (rightHeight != 0) && (leftHeight != 0)) return 0;
    else return l && r;

}

