/*
 * Glen Chandler
 * Lab 02
 * 04/05/16
 * COEN 12
 * Professor Atkinson
 * Summary: Includes createSet, destroySet, 
 * numElements, hasElement, addElement, removeElement
 * for an unused set, using sequential searches, and 
 * slower run times. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "set.h"

//Set that will be used in subsequent functions
struct set {
    int count; //Current size of set
    int length; //Max length of set
    char **elts; //Array of strings for set
};

//Used to find an element, using sequential search
//O(n)
int findElement(SET *sp, char *elt)
{
    int i;
    for(i=0; i < sp->count; i++)
    {
        if(strcmp(sp->elts[i],elt) == 0)
        {
            return i; //Returns index
        }
    }
    
    return -1; //Invalid index, represents not found
}

//Creates set
//O(1)
SET *createSet(int maxElts)
{
    //Creates set pointer that can be returned later
    //Then allocates appropriate memory for that set
    //Asserts that the set was actually allocated
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    
    //Sets the count for the set to 0 indicating empty set
    //Length is set to the maximum size passed in to function
    //The array of string pointer is allocated by size of char array multiplied by maxElts
    //Asserts that the array was correctly allocated
    sp->count = 0;
    sp->length = maxElts;
    sp->elts = malloc(sizeof(char *) * maxElts);
    assert(sp->elts != NULL);
    
    //Returns the set pointer so it can be initialized
    return sp;
}

//Destroy Set sequentially 
//O(n)
void destroySet(SET *sp)
{
    //Loops through set freeing each string
    //Then freeing the entire array
    //Then freeing the set
    int i;
    for(i = 0; i < sp->count; i++)
    {
	//Free each string
        free(sp->elts[i]);
    }
    //Free string array
    free(sp->elts);
    //Free the set
    free(sp);
}

//Returns t or f if has Element
//O(n) because calls findElement which is O(n)
bool hasElement(SET *sp, char *elt)
{
    //Asserts that the set isn't null and the string isn't null
    //calls find element where if a -1 is returned it was not found, thus return false
    assert(sp != NULL && elt != NULL);
    if(findElement(sp, elt) == -1)
        return false; //elt was not found
    
    return true; //elt is in set
}

//returns number of elements
//O(1)
int numElements(SET *sp)
{
    //Simply returns the set's current count
    assert(sp != NULL);
    return sp->count;
}

//adds Element
//O(1)
bool addElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    
    //If set isn't full and element isn't already present
    if(hasElement(sp, elt)|| sp->count >= sp->length)
    {
	//Return false since prerequisites are not met to add elt
        return false;
    }
    
    //Sets the element after the last index, hence sp->count, not sp->count-1
    //assert that the elt was set correctly
    //Increments count
    sp->elts[(sp->count)] = strdup(elt);
    assert(sp->elts[sp->count] != NULL);
    sp->count++;

    //Return true for success
    return true;
}

//Removes element
//O(n)
bool removeElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    
    //Makes sure that the element is there to remove
    if(hasElement(sp, elt) == true)
    {
        //Finding the index using findElement O(n)
        int i = findElement(sp, elt);
        //Assert that i >= 0, since i==-1 represents not found
        assert(i >= 0);
        
	//Free the string at the found index
	//Set the index just freed to the previous last index
	//Set the last index to null
	//Decrement cout
        free(sp->elts[i]);
        sp->elts[i] = sp->elts[sp->count-1];
        sp->elts[sp->count-1] = NULL;
        sp->count--;
        return true; //Return true for success
    }
    //Return false for failure
    return false;
}
