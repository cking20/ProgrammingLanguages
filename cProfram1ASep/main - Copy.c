#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
/*
Christoper King
Homework 1A 
Due Sept 23 2016
Description: 
	This program displays all the permutations of a user specified string.
Input: 
	the string to permute should be specified after the name of the program.
Output:
	Each permutation of the string is displayed on its own line.
Error Handleing:
	If the user inputs multiple strings, only the first is permutated
 */



static void usage();
int permutate(int , char *, int);
void permuteNoRec(int , char *);
void swap(char *, char *);
char **getPermutations(char *);

int main(int argc, char *argv[]) {
	
	char *theString = 0;
	char *theOrigString = 0;
   char *prgn = 0;
   char *options = "";//":a:b:c:d:e";
   prgn = (char *)malloc(sizeof(char)*(strlen(argv[0])+1));
   strcpy(prgn,argv[0]);
   
   if(argc >= 2){
		//get the lenght of the string
		int n = (strlen(argv[1]));
		//create an array with that argument
		theString = (char *)malloc(sizeof(char)*(strlen(argv[1])+1));
		theOrigString = theString;
		strcpy(theString, argv[1]);
		//add a terminator
		*(theString + n) = '\0';
		int aryIndx = 0;
		permutate(n, theString, aryIndx);
		//permuteNoRec(n, theString);
   
   } else if(argc == 1){
	   usage(prgn);
   }
   
   //Free memory
	free(theOrigString);
	free(prgn);
	exit(0);
}

void usage(char *prgn) {
	//This should be called if no string is supplied at runtime.
	//This displays the propper usage of this program. 
   fprintf(stderr,"usage: %s string_to_permute \n", prgn);
   
}
char **getPermutations(char *theString){
	char** perms = 0;
	return perms;
}
int permutate(int n, char *theString, int aryIndx){
	/*
	This function recursively displays all permutations of 
		a string (theString) with specified lenght (n).
	Heaps algorithm is utilized to provide an efficient solution. 
	*/
	//using Heaps Algorithm
	if(n == 1){
		aryIndx++;
		//print the final permutation AKA assign to array
		printf("%s %d\n", theString, aryIndx);
	} else {
		for(int i = 0; i < n - 1; i++){
			//print the next permutation
			aryIndx = permutate(n -1, theString, aryIndx);
			//perform a swap of the chars in the string
			if(n%2 == 0){
				swap(theString+i, theString + (n-1));
			} else{
				swap(theString, theString + (n-1));
			}
		}
		aryIndx = permutate(n-1, theString, aryIndx);
	}
	return aryIndx;
}

void permuteNoRec(int n, char *theString){
	int c[n];
	for(int i = 0; i < n; i++){
		c[i] = 0;
	}
	//Output thestring
	printf("%s\n", theString);
	for(int i = 1; i < n;){
		if(c[i] < 1){
			if(i % 2 == 0){
				swap(theString, theString + i);
			}else{
				swap(theString + c[i], theString + i);
			}	
			//output
			printf("%s\n", theString);
			c[i]++;
			i = 1;
		} else {
			c[i] = 0;
			i++;
		}
	}
	
	
}



void swap(char *firstArrayLoc, char *secondArrayLoc){
	/*
	This function swaps 2 chars in a char array at 
		the firstArrayLoc and the secondArrayLoc
	*/
	char temp;
	temp = *firstArrayLoc;
	*firstArrayLoc = *secondArrayLoc;
	*secondArrayLoc = temp;
}
