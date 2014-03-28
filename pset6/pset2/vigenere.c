#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

//Function changes char based on key
char changeChar(char input, int key){
  char newChar = '0';
  int temp = 0;
  
  if(key > 90){
    key -= 97;
  } else if(key >= 65){
    key -= 65;
  }
  
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

int main(int argc, char* argv[]){
  string keyword;

  if (argc == 2) {
    keyword = argv[1];
    //Check keyword for non-alphabetic characters
    for(int i = 0; i < strlen(keyword); i++){
      if(!(isalpha(keyword[i]))){
        printf("A non-alphabetic character was encountered.\n");
        return 1;
      }
    }
      
    char newChar;
    string input;
    int keywordIndex = 0, temp; 
    
    input = GetString();
    
    //Change character based on keyword
    for(int i = 0; i < strlen(input); i++){
      if(isalpha(input[i])){
        temp = keyword[keywordIndex];
        newChar = changeChar(input[i],temp);
        ++keywordIndex;
      }else{
        newChar = input[i];
      }
      
      if(keywordIndex >= strlen(keyword)){
        keywordIndex = 0;
      } 
      printf("%c",newChar);
    }
    printf("\n");
  } else {
    printf("No keyword was given.\n");
    return 1; 
  }
  
  return 0;
}
