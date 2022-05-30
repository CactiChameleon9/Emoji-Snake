#include <stdio.h> //this is for printf (input output)

//similar to java syntax type name(parameters)
int main (int word_count, char **words) { //argc is number of inputs, argv is an array of inputs (**)

	printf("You typed in: \"");
	
	for (int i = 1; i < word_count; i += 1){

		if (i != word_count - 1){
			//printf takes a string (with subtitutions) followed by vairables to sub in
			printf("%s ", words[i]); 
		} else {
			printf("%s", words[i]);
		}
		
	}
	printf("\"\n");
	
	return 0;
}
