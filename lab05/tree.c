/*
 * Glen Chandler
 * Lab 05
 * 05/17/16
 * COEN 12
 * Professor Atkinson
 * Summary: Includes createTree, destroyTree,
 * getData, getLeft, getRight, getParent, setLeft, and 
 * setRight, to
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "tree.h"

struct tree
{
    int data;
    struct tree *left, *right, *parent;
};

//Create Tree function that allocates memory for a pointer, sets parent, and children.
//O(1)
struct tree *createTree(int data, struct tree *left, struct tree *right)
{
    struct tree *returnTree = malloc(sizeof(struct tree));
    assert(returnTree != NULL);

    returnTree->data = data;
    returnTree->parent = NULL;
    
    if(left != NULL)
	setLeft(returnTree, left);
    if(right != NULL)
	setRight(returnTree, right);

    return returnTree;
}

//Destroys tree by deleting each node recursively
//O(nodesInTree)
void destroyTree(struct tree *root)
{
    
    if(root == NULL)
        return;
    
    if(root->left != NULL)
        destroyTree(root->left);
    
    if(root->right != NULL)
        destroyTree(root->right);
    
    //This section of code will not be reached until the left and right children are null
    //meaning that it is a child node
    free(root);
}

//Retrn the data in the root of the subtree pointed to by root
//O(1)
int getData(struct tree *root)
{
    assert(root != NULL);
    
    return root->data;
}
//Return the left pointer from the root tree
//O(1)
struct tree *getLeft(struct tree *root)
{
    assert(root != NULL);
    
    return root->left;
}

//Return the right pointer from the root tree
//O(1)
struct tree *getRight(struct tree *root)
{
    assert(root != NULL);
    
    return root->right;
}

//Return the parent pointer from root tree
//O(1)
struct tree *getParent(struct tree *root)
{
    assert(root != NULL);
    
    return root->parent;
}

//Used to 'detatch' a child from its parent
//as well as set the parent's child back to null
void cut(struct tree *child)
{
    assert(child != NULL);
    
    //If child has not parent, no need to sever it
    if(child->parent == NULL)
        return;
    
    //If the child parent points to it through left pointer
    //or if the child parent points to it through right pointer
    //Sever the bond through the appropriate avenue
    if(child->parent->left == child)
        child->parent->left = NULL;
    else
        child->parent->right = NULL;
    
    //Finally set the child's parent to null
    child->parent = NULL;
}

//Update the left subtree of root
//O(1)
void setLeft(struct tree *root, struct tree *left)
{
    assert(root != NULL);

    //First cuts left's parent, and makes sure its parent doesn't reference it
    if(left != NULL);
	cut(left);

    //Set the original left of the root to null, so it does not point to root
    if(root->left != NULL)
	root->left->parent = NULL;

    //Then set the left of the root to new left
    //Then make sure the left is pointing back to root
    root->left = left;
    root->left->parent = root;
}

//Update the right subtree of root
//O(1)
void setRight(struct tree *root, struct tree *right)
{
    assert(root != NULL);
    
    //First cuts right's parent, and makes sure its parent doesn't reference it
    if(right != NULL)
	cut(right);
    
    //Set the original right of the root to null, so it does not point to root
    if(root->right != NULL)
        root->right->parent = NULL;
    
    //Then set the right of root to new right
    //Then make sure the new right is pointing back to root
    root->right = right;
    root->right->parent = root;
}
