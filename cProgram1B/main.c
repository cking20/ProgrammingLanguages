#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
/*
Christoper King
Homework 1B 
Due Sept 23 2016
Description: 
	This program produces random numbers for the user. 
	By default, it creates 10 random numbers in the range 
	1 to 100, unless the user opts to change one of these 
	values. 
Input: 
	run the program with any of the options l,n, or u 
	in any order, with a respective argument.
	No input is handled while the program is running.
Output:
	The program displays random numbers each on their own line.
Error Handleing:
	Missing values and unkown opperators are caught and a 
	respective message displayed. 
 */

static char *prgn = 0;

int main(int argc, char *argv[]) {
   int num = 10;
   int lower = 1;
   int upper = 100;
   int c = 0;
   int error = 0;
   char *options = ":n:l:u:";
   prgn = (char *)malloc(sizeof(char)*(strlen(argv[0])+1));
   strcpy(prgn,argv[0]);
   
   while ((c = getopt(argc,argv,options)) != -1) {
      if (c == '?') {
         c = optopt;
         printf("illegal option %c\n",c);
      } else if (c == ':') {
         c = optopt;
         printf("missing value for option %c\n",c);
      }
      else {
		  //toggle values based on arguments
         switch (c) {
            case 'n':
               num = atoi(optarg);
               break;
            case 'l':
			   lower = atoi(optarg);
               break;
            case 'u':
				upper = atoi(optarg) + 1;
               break;
            default:
               printf("Shouldn't happen\n");
         }
      }
   }
   
		//rand only does between 0 and max. ex 0 and 40, so...
		//if i want a num between 40 and 60, subtract the high from the low
		//and set that as the high to generate. Add the low to the generated num, 
		//and then you get a number between the lower and upper

		srand(time(NULL));
		for(int i = 0; i < num; i++){
			printf("%d\n", ((rand() % (upper - lower)) + lower));
			
		}
	//free memory
	free(prgn);
   exit(0);
}

