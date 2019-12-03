#include "TreeDB.h"
#include <iostream>
#include <string>
#include <ostream>

using namespace std;

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    this->root = NULL;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    // If root is not null (there are entities) start deleting the tree
    if(this->root!=NULL){
        deleteAll(root);
    }
    // else do nothing 
}

// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry){
    // Insert as first entry
    TreeNode *currNode = root;
    if(currNode == NULL){
        root = new TreeNode(newEntry);
        return true;
    }
    
    // Loops through until leaf node is found 
    while(true){
        // Already exists
        if(currNode->getEntry()->getName() == newEntry->getName()){
            return false;
        // Now check for greater or smaller so you know where to insert 
        } else if(currNode->getEntry()->getName() < newEntry->getName()){
            if(currNode->getRight() == NULL){
                TreeNode *temp = new TreeNode(newEntry);
                currNode->setRight(temp);
                return true;
            }
            currNode = currNode->getRight();
        } else if(currNode->getEntry()->getName() > newEntry->getName()){
            if(currNode->getLeft() == NULL){
                TreeNode *temp = new TreeNode(newEntry);
                currNode->setLeft(temp);
                return true;
            }
            currNode = currNode->getLeft();
        }
    }
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name){ 
    probesCount = 0;
    return locateNode(name, root);
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name){
    // Check if root is NULL right away, if so return false 
    if(root == NULL){
        return false;
    }
    DBentry *item = find(name);
    if(item == NULL){
        return false;
    } else {
        root = removeNode(name, root);
        return true;
    }   
}

// deletes all the entries in the database.
void TreeDB::clear(){
    deleteAll(root);
    root = NULL;
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const{
    cout << probesCount << endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{
    int count = 0;
    countActives(count, root);
    cout << count << endl;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<<(ostream& out, const TreeDB& rhs){
    if(rhs.root != NULL){
        operator<<(out, rhs.root);
    }
}

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs){
    // Using in order traversal learnt in class, we will print everything in the tree
    if(rhs != NULL){
        // In order = LNR
        operator <<(out, rhs->getLeft()); // L
        operator <<(out, *rhs->getEntry()); // N
        operator <<(out, rhs->getRight()); // R
    }
}

void TreeDB::deleteAll(TreeNode *root){
    // If there is nothing, return  
    if(root == NULL){
        return;
    } else {
        // Recursively delete the right and left entities 
        deleteAll(root->getLeft());
        deleteAll(root->getRight());
        // Prevent memory leakage
        delete(root);
    }
}

void TreeDB::countActives(int & count,TreeNode *root) const {
    // If root is null just exit function
    if(root == NULL){
        return;
    // If root has a value, get active from it and increment count 
    } else if(root->getEntry()->getActive()) {
        count++;
    }
    // Recursively check left and right subtrees for actives
    countActives(count, root->getLeft());
    countActives(count, root->getRight());
}

DBentry *TreeDB::locateNode(string name, TreeNode *node){
    // If root is NULL, there is no location 
    if(root == NULL) {
        return NULL;
    }
    
    // Increment only after checking that root != NULL
    probesCount += 1;
    
    // Check if root = name 
    if(root->getEntry()->getName() == name) {
        return root->getEntry();
    }
    // Traverse left and right nodes of BST recursively and compare
    // If the name key is less than the one pointed to by root, go left
    else if(root->getEntry()->getName() > name) {
        return locateNode(name, root->getRight());
    // else go right because name key is greater than the one pointed to by root
    } else {
        return locateNode(name, root->getLeft());
    }
}

TreeNode *TreeDB::findMaxNode(TreeNode *root){
    if(root->getRight() == NULL){
        return NULL;
    } else {
        // Traverse right side since that is where the max node will be at
        return findMaxNode(root->getRight());
    }   
}   

TreeNode* TreeDB::removeNode(string name, TreeNode *root){
    // CurrNode and temp to help keep track of nodes
    TreeNode *currNode = root;
    TreeNode *temp;
    
    if(currNode == NULL){ 
        return currNode;
        
    // If the entry to be deleted is greater, go to right subtree
    } else if(name > currNode->getEntry()->getName()){
        currNode->setRight(removeNode(name, currNode->getRight()));
    }
    // If the entry to be deleted is smaller, go to left subtree
    else if(name < currNode->getEntry()->getName()){
        currNode->setLeft(removeNode(name, currNode->getLeft()));
    }
    
    if(name == currNode->getEntry()->getName()){
        // Leaf = no children therefore delete its location (current Node)
        if((currNode->getLeft() == NULL) && (currNode->getRight() == NULL)){
            // Prevent memory leak
            delete currNode;
            return NULL;
            
        // 1 child
        // No left child but right child, delete current node and get location of right child
        } else if((currNode->getLeft() == NULL) && (currNode->getRight() != NULL)){
            temp = currNode->getRight();
            // Prevent memory leak
            delete currNode;
            return temp;
        // No right child but left child, delete current node and get location of left child
        } else if((currNode->getLeft() != NULL) && (currNode-> getRight() == NULL)){
            temp = currNode->getLeft();
            // Prevent memory leak
            delete currNode;
            return temp;
            
        // 2 children
        // Both left and right nodes are not null (have children present)
        } else if((currNode->getLeft() != NULL) && (currNode->getRight() != NULL)){
            // Get max node in left subtree
            temp = findMaxNode(currNode->getLeft());
            
            // Copy data of max node to desired node to be deleted
            currNode->getEntry()->setName(temp->getEntry()->getName());
            currNode->getEntry()->setIPaddress(temp->getEntry()->getIPaddress());
            currNode->getEntry()->setActive(temp-> getEntry()->getActive());
             
            // Keep BST Characteristics like in-class demonstration 
            currNode->setLeft(removeNode(temp->getEntry()->getName(), currNode->getLeft()));
        }
    }
    return currNode;
}
