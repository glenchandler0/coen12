/*
 * Glen Chandler
 * Lab 05
 * 05/17/16
 * COEN 12
 * Professor Atkinson
 * Summary: This file will lead to the excecution
 * of a program that takes in a text file, and uses
 * Huffman Coding to compress it into the shortest
 * total length of bits using binary trees
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

#include "tree.h"
#include "pack.h"

//Built in functions to find the percieved
#define p(x) ((x - 1) / 2)
#define l(x) ((x * 2) + 1)
#define r(x) ((x * 2) + 2)

//These will be globally defined for ease of use
int counts[257];

static struct tree * heap[257];
static int heapSize;
static struct tree * leaves[257];


void printHeap()
{
    int i;
    for(i = 0; i < heapSize; i++)
    {
        printf("%d ", getData(heap[i]));
    }
    printf("\n");
}
 

//Traverse to the top of the tree by recursively calling parent
//And printing either a 0 or 1 following the recursive calls
//O(h) runtime
void printHuf(struct tree * leaf)
{
    if(getParent(leaf) != NULL)
    {
        printHuf(getParent(leaf));
        if(getLeft(getParent(leaf)) == leaf)
        {
            printf("0");
        }
        else
        {
            printf("1");
        }
    }
}

//Inserts a tree into the heap, and resorts the heap for usability
//O(h) run time
void heapInsert(struct tree *ins)
{
    //Sets the next biggest in the heap to ins
    //Then increment heap size
    heap[heapSize] = ins;
    heapSize++;

    //Set the current index to the index just filled with ins
    //Then create a temporary tree variable for swapping
    int curIndex = heapSize - 1;
    struct tree * temp;
    
    //The inserted value will move towards the top of the tree, and stop when it has found its spot
    //If the current value is less than its parent, they should swap
    //Loop stops once calculated parent index is less than 0
    while((getData(heap[curIndex]) < getData(heap[p(curIndex)])) && p(curIndex) >= 0)
    {
        temp = heap[curIndex];
        heap[curIndex] = heap[p(curIndex)];
        curIndex = p(curIndex);
    }
}


//Removes the smallest value of the heap that is on top of the tree, and returns it
//While maintaining min heap integrity
struct tree * heapRemove()
{
    struct tree * returnTree = heap[0];
    
    //After the pointer to the top was saved in another variable, set the top of tree to last index
    //Then set the last value to null, and decrement size
    heap[0] = heap[heapSize - 1];
    heap[heapSize - 1] = NULL;
    heapSize--;
    
    //Set curIndex to 0 for decrementing
    int curIndex = 0;
    struct tree * temp;
    
    //If the left child of the current index is in bounds, this is all needed to traverse
    while(l(curIndex) < heapSize)
    {
        //If right child is out of bounds, and left is greater than current
        if(r(curIndex) >= heapSize)
        {
            if(getData(heap[l(curIndex)]) >= getData(heap[curIndex]))
                break;
            else
            {
                temp = heap[curIndex];
                heap[curIndex] = heap[l(curIndex)];
                heap[l(curIndex)] = temp;
                curIndex = l(curIndex);
            }
        }
        
        //Else, must be in bounds
        else if(r(curIndex) < heapSize)
        {
            if(getData(heap[l(curIndex)]) <= getData(heap[r(curIndex)]))
            {
                temp = heap[curIndex];
                heap[curIndex] = heap[l(curIndex)];
                heap[l(curIndex)] = temp;
                curIndex = l(curIndex);
            }
            else
            {
                temp = heap[curIndex];
                heap[curIndex] = heap[r(curIndex)];
                heap[r(curIndex)] = temp;
                curIndex = r(curIndex);
            }
        }
    }
    
    return returnTree; //Finally return original top of heap
}

int main(int argc, char **argv)
{
    //Initializing global tree arrays
    FILE *fp = fopen(argv[1], "r");
    heapSize = 0;

    //Count the occurances of characters by reading in values
    int c;
    while((c = getc(fp)) != EOF)
    {
        counts[c]++;
    }
    fclose(fp);
    
    //Insert and create tree for special case
    leaves[256] = createTree(0, NULL, NULL);
    heapInsert(leaves[256]);
    
    int i;
    for(i = 0; i < 256; i++)
    {
        if(counts[i] > 0)
        {
            leaves[i] = createTree(counts[i], NULL, NULL);
            heapInsert(leaves[i]);
            //printf("Index: %d\tCount(data): %d\n", i, leaves[i]->data);
        }
    }
    
    struct tree * subTree1, * subTree2, * newTree;
    while(heapSize > 1)
    {
        subTree1 = heapRemove();
        subTree2 = heapRemove();
        
        newTree = createTree(getData(subTree1) + getData(subTree2), subTree1, subTree2);
        heapInsert(newTree);
    }

    char printC;
    for(i = 0; i <= 256; i++)
    {
        if(leaves[i] != NULL)
        {
            printC = i;
            if(isprint(printC))
                printf("leaves %c %d: ", printC, counts[i]);
            else
                printf("leaves %d %d: ", i, counts[i]);
            printHuf(leaves[i]);
            printf("\n");
        }
    }
    
    pack(argv[1], argv[2], leaves);
}
