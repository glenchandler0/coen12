/*
 * Glen Chandler
 * Lab 02
 * 04/05/16
 * COEN 12
 * Professor Atkinson
 * Summary: Includes createSet, destroySet, numElements
 * hasElement, addElement, removeElement for an unused set,
 * using binary search, and a constantly ordered set for 
 * faster run times.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "set.h"

struct set {
    int count; //Current size of set
    int length; //Max length of set
    char **elts; //Array of strings for set
};

//Used to find an element using binary search
//O(log(n))
int findElement(SET *sp, char *elt, bool *found)
{
    //lo - bottom bound of search range
    //hi - upper range of search range
    //mid - check index, and middle of search range
    //diff - the result of strcmp() distance between two strings
    int lo, hi, mid, diff;
    
    //To begin set lo = 0, and hi = sp->count-1 to have max range on currently filled set
    //Set mid to middle of set range
    lo = 0;
    hi = sp->count - 1;
    mid = (lo + hi) / 2;
    
    //While the lower bound is less than the upper bound
    //When lo > hi, this means that the upperbound and lower bound have
    //shrunk so much as to pass eachother, indicated element is not present
    while(lo <= hi)
    {
	//As mentioned, find the difference between mid and the elt
	
	//If the difference is > 0, then elt is greater than mid
	//thus set lo = to the next one after mid, and reset a new mid
        diff = strcmp(sp->elts[mid], elt);
        if(diff > 0)
        {
            lo = mid + 1;
            mid = (lo + hi) / 2;
        }
        
	//If the difference is < 0, then elt is less than the mid
	//thus set hi = 1 minus the index previously analyzed
        else if(diff < 0)
        {
            hi = mid -1;
            mid = (lo + hi) / 2;
        }

	//If diff isn't >0 or <0, then diff == 0, which indicates no difference
	//between strings, meaning they are the same
        else
        {
	    //Set found value passed into function to true to indicate found outside function
	    //Return the index where the elt was found
            *found = true;
            return mid;
        }
    }
    //Set the found value passed into function to false to indicate not found outside function
    //Return where the index would have been if elt was found
    *found = false;
    return lo;
}

//Creates set same as unsorted.c
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
        free(sp->elts[i]);
    }
    free(sp->elts);
    free(sp);
}

//Returns t or f if has Element
//O(log(n)) because calls findElement which is O(n)
bool hasElement(SET *sp, char *elt)
{
    //Asserts that the set isn't null and the string isn't null
    //Calls find element by passing in address of boolean f to set 
    //The value in a black box manner, then returns that boolean
    assert(sp != NULL && elt != NULL);
    bool f;
    findElement(sp, elt, &f);
    
    return f; //elt is not in set
}

//returns number of elements
//O(1) simply returns the set's current count
int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

//adds Element
//O(n) because of worst case scenario for shifting
bool addElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    //Boolean to be passed to findElement() to see if element was found
    bool f;
    
    //isn't full and element isn't already present
    if(sp->count >= sp->length)
    {
        return false;
    }

    //Saves the index of either where elt would be or where it is, regardless if it was found
    int placeIndex = findElement(sp, elt, &f);
    //If it was found, do not add
    if(f == true)
    {
        return false;
    }
    
    //If it was not found, add. You will use placeIndex now
    else
    {
        //Shift over every element of the array to make room for the new element
        int i;
        for(i = sp->count - 1; i >= placeIndex; i--)
        {
            sp->elts[i+1] = sp->elts[i];
        }
	//After shifting over every element set the index to a copy of the string,
	//not the elt index.
	//Increment count since set was incremented
	//Assert that the string was added
        sp->elts[placeIndex] = strdup(elt);
        sp->count++;
        assert(sp->elts[placeIndex] != NULL);
    }
    
    return true; //Return true to indicate success
}

//Removes element
//O(n) due to shifting loop
bool removeElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    //Boolean will be used for find element
    bool f;
    
    //Will record the index of where the elt should be regardless of if it is there
    int removeIndex = findElement(sp, elt, &f);
    
    //If element isn't there, do not remove anything
    if(f == false)
        return false; //Quit function
    
    //Else, then the set has the element
    else
    {
	//First free the elt at the index
	//Then shift over (to the left) every other element
        free(sp->elts[removeIndex]);
        int i;
        for(i = removeIndex; i < sp->count-1; i++)
        {
            sp->elts[i] = sp->elts[i+1];
        }
	//Decrement count for removed elt
        sp->count--;
    }

    return true; //Return true for success
}
