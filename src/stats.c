/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file stats.c 
 * @brief Implements the functions defined in stats.h. 
 *
 * This file implements the functions defined 
 * in stats.h. This file also executes the implemented
 * functions via the main function in this file.
 *
 * @author Ankush Burman
 * @date Oct 10, 2018
 *
 */



#include <stdio.h>
#include "stats.h"

/* Size of the Data Set */
#define SIZE (40)
/*
int main(void) 
{

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

  int len = SIZE-1;
  print_statistics(test, len);
  print_array(test, len);
  // Other Variable Declarations Go Here 
  // Statistics and Printing Functions Go Here 
 
 return 0;

}*/


void sort_array(unsigned char *array, int low, int high)
{
 //quicksort algorithm
 int p;  /* index of partition */

 if((high-low) > 0) {
  p = quicksort_partition(array, low, high);
  sort_array(array, low, p-1);
  sort_array(array, p+1, high);
 }
}


int quicksort_partition(unsigned char *array, int low, int high)
{
  int i;  /* counter */
  int p;  /* pivot element index */
  int firstlow;  /*divider position of pivot element */

  p = high;
  firstlow = low;

  for (i = low; i < high; i++) { 
   if(array[i] > array[p]) {
    swap(&array[i], &array[firstlow]);
    firstlow++;
   }
  }

 swap(&array[p], &array[firstlow]);

 return(firstlow);
}


void swap(unsigned char *a, unsigned char *b)
{
 unsigned char swap = *a;
 *a = *b;
 *b = swap;
}


void print_array(unsigned char *array, int len)
{
 
 #ifdef VERBOSE
 int i, j = 0;

 for (i = 0; i <= len; i++) {
  printf("%d ", array[i]);
  j++;

  if(j >= 8) {
  printf("\n");
  j = 0;
  }
 }
 printf("\n");
 #endif 

}


int find_minimum(unsigned char *array, int len)
{
 
 sort_array(array, 0, len);
 return(array[len]);

}


int find_maximum(unsigned char *array, int len)
{
 sort_array(array, 0, len);
 return(array[0]);
}


float find_mean(unsigned char *array, int len)
{
 int i;
 int temp = 0;

 for(i = 0; i <= len; i++) {
  temp = array[i]+temp;
 }

 return(temp/(len+1));
}


float find_median(unsigned char *array, int len)
{ 
 
 int half = len/2;

 if(!(len%2)) {
  return(array[half]);
 } else {
   return((array[half]+array[half+1])/2); 
 }
}
 
 
void print_statistics(unsigned char *array, int len)
{
 printf("Minimum = %d \n", find_minimum(array, len));
 printf("Maximum = %d \n", find_maximum(array, len));
 printf("Mean = %5.1f \n", find_mean(array, len));
 printf("Median = %5.1f \n", find_median(array, len));
 printf("\n");
}

