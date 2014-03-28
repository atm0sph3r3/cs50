/*
Application to create Caesar-cyphered text
*/
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Function changes char based on key
char changeChar(char input, int key){
  char newChar = '0';
  int temp = 0;
  
  if(isalpha(input)){
    temp = input;
    //Handles lowercase letters
    if(temp >= 97) {
      temp += (key % 26);
      if(temp > 122) {
        temp -= 26;
      }
    //Handles uppercase letters
    } else {
      temp += (key % 26);
      if(temp > 90){
        temp -= 26;
      }
    }
    
    newChar = temp;
  } else {
    newChar = input;
  }
  
  return newChar;
}

int main (int argc, char* argv[]){
	
	int key;
	string input;
	
	if(argc == 2){
		key = atoi(argv[1]);
		input = GetString();
		for(int i = 0; i < strlen(input); i++){
		  printf("%c",changeChar(input[i],key));
		}
		printf("\n");
	} else {
	  printf("A key was not specified.");
		return 1;
	}
	
	return 0;
}
