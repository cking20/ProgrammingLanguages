char **permutate(int n, char *theString){
	/*
	This function recursively displays all permutations of 
		a string (theString) with specified lenght (n).
	Heaps algorithm is utilized to provide an efficient solution. 
	*/
	char **stringArray[]
	
	//using Heaps Algorithm
	if(n == 1){
		//print the final permutation
		//string copy this to the 2D array
		//printf("%s\n", theString);
	} else {
		for(int i = 0; i < n - 1; i++){
			//print the next permutation
			permutate(n -1, theString);
			//perform a swap of the chars in the string
			if(n%2 == 0){
				swap(theString+i, theString + (n-1));
			} else{
				swap(theString, theString + (n-1));
			}
		}
		permutate(n-1, theString);
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