/*
 * Glen Chandler
 * Lab 02
 * 05/01/16
 * COEN 12
 * Professor Atkinson
 * Summary: Includes createSet, destroySet, numElements
 * hasElement, addElement, removeElement for an unused set,
 * using hashing with linear probing, for a much faster big O 
 * run time for most methods.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "set.h"

#define EMPTY 'e'
#define FILLED 'f'
#define DELETED 'd'


struct set {
    int count; //Current size of set
    int length; //Max length of set
    char **elts; //Array of strings for set
    char *flags;
};

//Hash String
//O(str.length),
//Will create a hash value to be returned for indexing a string
unsigned hashString(char *str)
{
    unsigned hash = 0;
    
    while(*str != '\0')
        hash = 31 * hash + *str ++;
    
    return hash;
}

//Find
//Average: O(1)
//Worst: O(m)
int findElement(SET *sp, char *elt, bool *found)
{
    assert(sp != NULL);
    assert(elt != NULL);
    
    //Set delIndex to -1 to represent not being used yet
    //hIndex is the index where a string would hash to after going through hashString()
    int delIndex = -1;
    int hIndex = (hashString(elt) % sp->length);
    
    //Loop to end of set, and also check you haven't reached empty slot
    int i;
    for(i = 0; i < sp->count && sp->flags[hIndex] != EMPTY; i++)
    {
        //If the slot has an active item in it
        if(sp->flags[hIndex] == FILLED)
        {
            //If said active item is your item, you have found it. Done.
            if(strcmp(sp->elts[hIndex],elt) == 0)
            {
                *found = true;
                return hIndex;
            }
            //If not, keep going
        }
        
        //If the slot you reach is a deleted slot, remember it because if elt
        //is not found, you can put it here.
        else if(delIndex == -1 && sp->flags[hIndex] == DELETED)
        {
            delIndex = hIndex;
        }
        //Increment hashIndex in a circular manner
        hIndex = (hIndex + 1) % sp->length;
    }
    //If a delete was found return that index, for efficiency in the future
    if(delIndex != -1)
    {
        *found = false;
        return delIndex;
    }
    //If no delete was found in the range between hash index and empty, then return empty slot
    *found = false;
    return hIndex;
}

//Creates a set pointer then returns it
//Worst and Average: O(m)
SET *createSet(int maxElts)
{
    //Allocates the set itself, then sets the count and length
    SET *sp = malloc(sizeof(SET));
    sp->count = 0;
    sp->length = maxElts;
    
    //Allocates the array of strings, and allocates the mirrored flag array
    sp->elts = malloc(sizeof(char *) * maxElts);
    sp->flags = malloc(sizeof(char) * maxElts);
    
    //Makes sure elts and flags was allocated correctly
    assert(sp->elts != NULL && sp->flags != NULL);
    
    //Sets each of the flags to empty to begin
    int i;
    for(i = 0; i < sp->length; i++)
    {
        sp->flags[i] = EMPTY;
    }
    
    return sp;
}

//Destroys set that was already used.
//Worst and Average: O(m)
void destroySet(SET *sp)
{
    //First we free all the character arrays (strings) inside elts if the flag is not empty (null)
    //Then we free the character array, elts, itself.
    //Then we free the flags array followed by the set itself.
    int i;
    for(i = 0; i < sp->length; i++)
    {
        //Does not free DELETED elts because remove elt already does this.
        if(sp->flags[i] == FILLED)
            free(sp->elts[i]);
    }
    free(sp->elts);
    free(sp->flags);
    free(sp);
}

//Adds element to sp->elts if it is not there
//Worst: O(m) because find must run which has worst case O(m)
//Average case: O(1) because findElement() must run which has average case O(1)
bool addElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    
    //Make sure the set isn't full, don't add if it is
    if(sp->count >= sp->length)
    {
        return false;
    }
    
    //Set a boolean to see if elt was found from findElement()
    //Then set addIndex findElemtent() regardless of if elt was found
    bool found;
    int addIndex = findElement(sp, elt, &found);
    
    //If elt was found return false, don't add
    if(found == true)
        return false;
    
    //If elt was not found,
    //Set the element at the addIndex to a copy of the elt
    //Then set the flag at addIndex to filled
    sp->elts[addIndex] = strdup(elt);
    sp->flags[addIndex] = FILLED;
    sp->count++;
    
    return true;
}

//Removes element from sp->elts if it is there
//Worst: O(m) because find must run which has worst case O(m)
//Average case: O(1) because findElement() must run which has average case O(1)
bool removeElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    
    //Check to make sure the set isn't empty. Can't take something away from nothing
    if(sp->count <= 0)
        return false;
    
    //Create found to be used with findElement
    bool found;
    int removeIndex = findElement(sp, elt, &found);
    
    //If found is false, return false, cannot remove something that isn't there
    if(found == false)
        return false;
    
    //If found is true, free the string that the elts[removeIndex] is pointing to,
    //then set the flag equal to deleted.
    free(sp->elts[removeIndex]);
    sp->flags[removeIndex] = DELETED;
    sp->count--;
    
    return true;
}


//Returns if an element is in the set or not
//Uses findElement, thus
//Worst: O(m)
//Average: O(1)
bool hasElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    
    //Create boolean to be returned,
    //findElement() changes its value
    bool found;
    findElement(sp, elt, &found);
    
    return found;
}

//Returns the number of elements
//Worst and Average: O(1)
int numElements(SET *sp)
{
    //Assert that the set isn't null, then return the count of the set
    assert(sp != NULL);
    return sp->count;
}
