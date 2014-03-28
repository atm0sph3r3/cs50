#include <stdio.h>
#include <cs50.h>

int main(void){
  
  int input;
  
  //Get user input
  do{
    printf("Height: ");
    input = GetInt();
  } while(input < 0 || input > 23);
  
  //Print out pyramid 
  for(int i = 0; i < input; i++){
    //Print spaces
    for(int m = input - 1; m > i; m--){
      printf("%c",' ');
    }
    
    //Print #
    for(int j = 0; j < i + 2; j++){
      printf("%c",'#');
    }
    //New line after spaces and # have been printed
    printf("\n");
  } 
  return 0;
}
