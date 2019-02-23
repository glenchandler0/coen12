/*
 * Glen Chandler
 * 03/29/16
 * Tuesday 5:15pm Lab
 *
 * This lab is program that counts the number of
 * characters in a file passed into the program
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[])
{
	char str[MAX_WORD_LENGTH];

	//If argc is not 2, then the incorrect format was used for using this program
	//And instructions will be given to call it correctly
	if(argc != 2)
	{
		printf("Incorrect function call. Should be [./a.out *.txt]\n");
		return -1;
	}
	
	//Create file and open it for reading using argv[1] which will be the name of the text file
	FILE *text;
	text = fopen(argv[1], "r");
	//If text is not a file, then alert user and exit program.
	if(text == NULL)
	{
		printf("File does not exist, try a different file.\n");
		return -1;
	}
	
	
	//A while loop will be used simultaneously scan the file into a string, then check that the return
	//Is not EOF, which will end loop
	int wordCounter = 0;
	while(fscanf(text, "%s", str) != EOF)
	{
		wordCounter++;
	}

	printf("Number of words: %d\n", wordCounter);

	fclose(text);
}
