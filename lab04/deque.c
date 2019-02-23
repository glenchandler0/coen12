/*
 * Glen Chandler
 * Lab 04
 * 05/03/16
 * COEN 12
 * Professor Atkinson
 * Summary: Includes createDeque, destroyDeque,
 * numItems, addFirst, addLast, removeFirst, removeLast,
 * getFirst, getLast to be used in maze.c and solve a maze.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "deque.h"

struct node
{
    struct node * next;
    struct node * prev;
    int data;
};

struct deque
{
    int count;
    struct node * dummy;
};

//Allocates a starting deque, then returns it
//O(1)
DEQUE *createDeque(void)
{
    //Allocates the dummy node and the deque then asserts that
    //they are not null.
    struct node * pDummy = malloc(sizeof(struct node));
    struct deque * pDeque = malloc(sizeof(struct deque));
    assert(pDummy != NULL && pDeque != NULL);
    
    //Sets the dummy node, and count before returning the pointer to the deque
    pDeque->dummy = pDummy;
    pDeque->dummy->next = pDeque->dummy;
    pDeque->dummy->prev = pDeque->dummy;
    pDeque->count = 0;
    
    return pDeque;
}

//Destroys the entire deque, freeing it completely from memory
//O(1)
void destroyDeque(DEQUE *dp)
{
    //Assert dp!=NUL to avoid segmentation fault
    assert(dp != NULL);
    
    //Starts with a current pointer to traverse the deque
    struct node * pCurrent = dp->dummy->next;
    
    //While loop to traverse the deque
    //As long as the next node isn't the dummy, move on,
    //and free the node just passed (prev)
    while(pCurrent->next != dp->dummy)
    {
        pCurrent = pCurrent->next;
        free(pCurrent->prev);
    }
    
    //Once pCurrent->next == dp->dummy, then we are
    //in a situation where there is only pCurrent and dp->dummy left
    //Free these two, then free the entire deque itself.
    free(pCurrent);
    free(dp->dummy);
    free(dp);
}

//Return the amount of items in a deque
//O(1)
int numItems(DEQUE *dp)
{
    //Assert dp!=NULL to avoid segmentation fault
    assert(dp != NULL);
    
    return dp->count;
}

//Add element x to the beginning of the deque
//O(1)
void addFirst(DEQUE *dp, int x)
{
    //Assert dp!=NULL to avoid segmentation fault
    assert(dp != NULL);
    
    //Create pAdd, assert that it was allocated, then set relevent data
    struct node * pAdd = malloc(sizeof(struct node));
    assert(pAdd != NULL);
    pAdd->data = x;
    
    //Make pAdd point to what dummy was originally pointing forwards to,
    //Then make it point back to pAdd
    pAdd->next = dp->dummy->next;
    pAdd->next->prev = pAdd;
    
    //Have pAdd point back to dummy
    //Then make dummy point towards pAdd
    pAdd->prev = dp->dummy;
    dp->dummy->next = pAdd;
    
    //dp->count++;
}

//Add element x to the end of the deque
//O(1)
void addLast(DEQUE *dp, int x)
{
    //Assert dp!=NULL to avoid segmentation fault
    assert(dp != NULL);
    
    //Create pAdd, assert that it was allocated, then set relevent data
    struct node * pAdd = malloc(sizeof(struct node));
    assert(pAdd != NULL);
    pAdd->data = x;
    
    //Made pAdd point to what dummy was originally pointing backwards to,
    //Then make it point forward to pAdd
    pAdd->prev = dp->dummy->prev;
    pAdd->prev->next = pAdd;
    
    //Have pAdd point back to dummy
    //Then make dummy point backwards to pAdd
    pAdd->next = dp->dummy;
    dp->dummy->prev = pAdd;
    
    //dp->count++;
}

//Removes and frees whatever element is in the beginning of the deque
//O(1)
int removeFirst(DEQUE *dp)
{
    //Assert dp!=NULL to avoid segmentation fault
    assert(dp != NULL);
    
    int returnVal = dp->dummy->next->data;
    
    //Have dummy skip over and point to the next's next
    //pDummy->next (which now poitns to the old pDummy->next->next) still points back to the original pDummy->next (which we want to free)
    //So this allows you to still free it.
    //After freeing this element, have pDummy->next->prev point back to pDummy
    dp->dummy->next = dp->dummy->next->next;
    free(dp->dummy->next->prev);
    dp->dummy->next->prev = dp->dummy;
    
    //dp->count--;
    
    return returnVal;
}

//Removes and frees whatever element is in the end of the deque
//O(1)
int removeLast(DEQUE *dp)
{
    //Assert dp!=NULL to avoid segmentation fault
    assert(dp != NULL);
    
    int returnVal = dp->dummy->prev->data;
    
    //Have dummy skip over and point to the prev's prev
    //pDummy->prev (which now points to the old pDummy->prev->prev) still points forwar to the original pDummy->prev(which we want to free)
    //So this allows you to still free it.
    //After freeing this element, have pDummy->prev->next point forward to pDummy
    dp->dummy->prev = dp->dummy->prev->prev;
    free(dp->dummy->prev->next);
    dp->dummy->prev->next = dp->dummy;
    
    //dp->count--;
    
    return returnVal;
}

//Returns the data of the first element of the deque
//O(1)
int getFirst(DEQUE *dp)
{
    //Assert dp!=NULL to avoid segmentation fault
    assert(dp != NULL);
    
    return dp->dummy->next->data;
}

//Returns the data of the last element of the deque
//O(1)
int getLast(DEQUE *dp)
{
    //Assert dp!=NULL to avoid segmentation fault
    assert(dp != NULL);
    
    return dp->dummy->prev->data;
}