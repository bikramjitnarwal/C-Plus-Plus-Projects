#include "TreeNode.h"

#include <iostream>
#include <string>

using namespace std;

TreeNode::TreeNode(DBentry* _entryPtr){
    this->entryPtr = _entryPtr;
    this->left = NULL;
    this->right = NULL;
}

// the destructor
TreeNode::~TreeNode(){
    delete this->entryPtr;
}

// sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft){
    this->left = newLeft;
}

// sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight){
    this->right = newRight;
}

// gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const{
    return this->left;
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const{
    return this->right;
}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry* TreeNode::getEntry() const{
    return this->entryPtr;
}
