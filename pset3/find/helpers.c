/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

//Prototype for recursive function for binary search
bool searchBinary(int values[], int lower, int upper, int value);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    return searchBinary(values, 0, (n - 1), value);
}

bool searchBinary(int values[], int lower, int upper, int value){
  int half = (upper + lower) / 2;
  
  if(upper < lower){
    return false;
  }
 
  if(values[half] == value){
    return true;
  } else if (values[half] < value) {
    return searchBinary(values, half + 1, upper, value);
  } else if (values[half] > value) {
    return searchBinary(values, lower, half - 1, value);
  }
  
  return false;
}

void swap(int values[], int iIndex, int jIndex){
  int oldValue = values[iIndex];
  int newValue = values[jIndex];
  
  values[iIndex] = newValue;
  values[jIndex] = oldValue;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
  int min, minIndex, j;

    //selection sort
    for(int i = 0; i < (n - 1); i++){
      min = values[i];
      minIndex = i;
      for(j = i + 1; j < n; j++){
        if(values[j] < min){
          minIndex = j;
          min = values[j];
        }
      }
      swap(values, i, minIndex);
    }
    return;
}
