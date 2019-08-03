/******************************************************************************
 * Copyright (C) 2019 Ankush Burman
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Ankush Burman are not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file memory.c
 * @brief Abstraction of memory read and write operations
 *
 * This implementation file provides an abstraction of reading and
 * writing to memory via function calls. There is also a globally
 * allocated buffer array used for manipulation.
 *
 * @author Alex Fosdick
 * @date April 1 2017
 *
 */
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "memory.h"
#include "platform.h"

  const int32_t arr_len = 16;

  //Hardcoded array with ascii values
  const uint8_t ascii_arr[arr_len] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,\
                                 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44,\
                                 0x45, 0x46};

/***********************************************************
 Function Definitions
***********************************************************/

int32_t my_findnum(uint8_t *ptr)
{
  
  int32_t i;
  for(i = 0; i < arr_len; i++){
    if(ascii_arr[i] == *ptr){
     return i;
    }
  }

  return 0;
  
}

uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base)
{

  uint8_t *ptr_start = ptr;
  int length = 0; 
  int q = data;
 
  //Checking if ptr passes to function is valid or not
  if(ptr == NULL){
    PRINTF("Null pointer passed as parameter. Exiting ITOA function");
    return 1;
  }

  //Adding null character to string
  *ptr = 0x00;
  ptr++;

  //Algorithm for converting any number to a number of given base
  do{
    *ptr = ascii_arr[q%base];
    ptr++;
    q /= base;
    length++;
  }while( q > 0);

  //Adds a negatvie sign if passed number is negative
  if(data < 0){
    *ptr = 0x2D;
  }

  //Reverses the string because the algorithm
  //calculates least significant digit to 
  //most significant. 
  my_reverse(ptr_start, ((size_t)length) );

  return length;

}


int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base)
{

  int i, if_signed;
  size_t length = (size_t) digits;
  uint8_t *ptr_start = ptr;
  int32_t data = 0;

  //Checks if Null ptr is being passed to function.
  if(ptr == NULL){
    PRINTF("Null pointer passed to ATOI function. Exiting.");
    return 1;
  }

  //Checks if ASCII number is negative.
  //Adds one to the length to account for the negative sign
  //in the string
  if(*ptr == 0x2D){
    if_signed = -1;
    length += 1;
    ptr++;
  }

  //Reverses the order of the digits
  //Plus one is added to length to account for NULL character
  my_reverse(ptr_start, length+1);
  
  for(i = 0; i < digits; i++){
    data += (my_findnum(*ptr))*(base^i);
  }

  //If ASCII number was negative, mulitplies int number by
  // -1 to get a negative number.
  if(if_signed < 0){
    data *= -1;
  }

  return data;

}
  
