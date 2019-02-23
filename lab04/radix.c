/*
 * Glen Chandler
 * Lab 04
 * 05/10/16
 * COEN 12
 * Professor Atkinson
 * Summary: Utilizes deque.c to implement radix sort
 * by using deques.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "deque.c"

int main(void)
{
    //Inputs and initialization--------
    
    //Create deque list to hold input numbers
    //Create deque bins to hold numbers for radix sorting
    DEQUE *inputList = createDeque();
    DEQUE *bins[10];
    int mostDigits = 0; //Will be used to determine how many times to run radix
    int listSize = 0; //Amount of numbers in list
    
    //Creates a deque for each index in bins
    for(int i = 0; i < 10; i++)
    {
        bins[i] = createDeque();
    }
    
    //Prompt user:
    printf("Enter any positive integer in any order to be sorted.\n");
    printf("Enter any negative integer to conclude list and recieve sorted list.\n\n");
    
    //Input integer used to scan in numbers into list
    int input;
    scanf("%d", &input);
    while(input >= 0)
    {
        //Largest number will naturally have the most digits
        if(input > mostDigits)
            mostDigits = input;

        addFirst(inputList, input);
        scanf("%d", &input);
        listSize++;
    }
    
    //Will be used to determine how many digits are in the largest number
    int mostDigitCount = 1;
    while(mostDigits / 10 > 0)
    {
        mostDigits /= 10;
        mostDigitCount++;
    }
    
    
    //Radix Sort process----------
    
    int place; //Variable used repeatedly to determine bin number to place a given number in
    int i,j,k; //Variables used for numerous for loops

    //The outermost loops proportionate to the amount of digits in the largest number
    for(i = 0; i < mostDigitCount; i++)
    {
        //Loops through each elt in the input deque.
        for(j = 0; j < listSize; j++)
        {
            //Places copies and manipulates a given
            //Value from input list to decide which bin to place it in
            place = getFirst(inputList);
            for(k = 0; k < i; k++) //Loop depends on current digit sorted by
            {
                place /= 10;
            }
            place %= 10; //Will tell you the right most digit, after truncating
        
            
            //Takes the first value from the inputList again and inserts at [place] bin
            //determined above.
            addFirst(bins[place],getFirst(inputList));
            
            //Increment the bin counter to keep track of how many numbers in each bin
            bins[place]->count++;
            
            //Remove the first elt from inputList because it was just inserted into a bin,
            //and so the algorithm can use getFirst() for the next elt. Also the spot is
            //now empty for radix sort to reinsert later.
            removeFirst(inputList);
        }
        
        //Loop increments from 0-9 for bins.
        //This loop will reinsert the elts from each bin in order back
        //into inputList
        for(j = 0; j < 10; j++)
        {
            //Loops through all elts in each bin
            for(k = 0; k < bins[j]->count; k++)
            {
                //Adds each elt from a bin in order back into inputList
                //then removes it in the same manner as above.
                addFirst(inputList, getFirst(bins[j]));
                removeFirst(bins[j]);
            }
            //The bin[j] is now empty, so it is sufficient to set the counter 0
            bins[j]->count = 0;
        }
    }
    
    //Printing ------
    
    //Since the sorting algorithm uses addFirst, the final sorted result is largest to smallest.
    //We print with getLast here to print smallest to largest.
    printf("\nSorted smallest to largest:\n");
    for(i = 0; i < listSize; i++)
    {
        //Print last
        printf("%d\n", getLast(inputList));
        
        //Add the elt to the beginning and delete from end, to cycle through
        //inputList without actually deleting elts.
        addFirst(inputList, getLast(inputList));
        removeLast(inputList);
    }
}

