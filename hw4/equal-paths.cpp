#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int subHeight (Node* root);
bool boolHeight (Node * root);


bool equalPaths(Node * root)
{
    // Add your code below
    if (root == NULL)
        return true;
    
    int left_tree = subHeight(root->left);
    int right_tree = subHeight(root->right);
    if ((left_tree == 0 && right_tree == 1) || (left_tree == 1 && right_tree == 0))
        return true;
    return right_tree == left_tree;
}

int subHeight (Node* root){
    if (root == NULL)
        return 0;

    int rightH= subHeight(root->right);
    int leftH = subHeight(root->left);

    if (rightH > leftH)
        return rightH + 1;
    else 
        return leftH + 1;
 
}


/*bool boolHeight (Node * root) {
    if (root == NULL)
        return true;
    else {
        int num = subHeight(root->right) - subHeight(root->left);
        if (num == 0){  
            return boolHeight(root->right) && boolHeight(root->left);
        }
        return false;
    }
    
}*/

