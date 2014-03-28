#include <stdio.h>
#include <cs50.h>
#include <math.h>

int calcChange(float input){
  int sum, intInput, remainder;
  
  input *= 100;
  intInput = round(input);

  //Number of quarters
  sum = intInput / 25;
  remainder = intInput % 25;
  
  //Number of dimes
  sum += remainder / 10;
  remainder %= 10;
  
  //Number of nickels
  sum += remainder / 5;
  remainder %= 5;
  
  //Number of pennies
  sum += remainder;
  
  return sum;
}

int main(void){
  
  float input;
  
  //Get user input
  do{
    printf("Input the change.\n");
    input = GetFloat();
  } while (input < 0);
  
  //Calculate change
  printf("%d\n",calcChange(input));
 
  return 0;
}
