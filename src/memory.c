/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 * modified and completed by Ankush Burman 2019
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
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

/***********************************************************
 Function Definitions
***********************************************************/
void set_value(char * ptr, unsigned int index, char value)
{
  ptr[index] = value;
}


void clear_value(char * ptr, unsigned int index)
{
  set_value(ptr, index, 0);
}


char get_value(char * ptr, unsigned int index)
{
  return ptr[index];
}


void set_all(char * ptr, char value, unsigned int size)
{
  unsigned int i;
  for(i = 0; i < size; i++) {
    set_value(ptr, i, value);
  }
}


void clear_all(char * ptr, unsigned int size)
{
  set_all(ptr, 0, size);
}


uint8_t *my_memmove(uint8_t *src, uint8_t *dst, size_t length)
{
 
  if(src == NULL || dst == NULL){
    PRINTF("Null pointers passed to function.");
    return NULL;
  }

  int i;
  //Because 0th position is always included.
  int overlap_len = length-1;

  if((dst <= src && dst+overlap_len >= src+overlap_len) ||\
  (dst >= src && dst <= src+overlap_len) ||\
  (dst+overlap_len >= src && dst+overlap_len <= src+overlap_len)) {
    
    uint8_t *temp = (uint8_t*)  calloc(length, sizeof(uint8_t));
    if(temp == NULL){
     PRINTF("Error allocating memory.");
     return NULL;
    }

    for(i = 0; i < length; i++){
      *(temp+i) = *(src+i);
    }

    for(i = 0; i < length; i++){
      *(dst+i) = *(temp+i);
    }

    free(temp);
  }

  else {
    for(i = 0; i < length; i++){
    *(dst+i) = *(src+i);
   }

  }

  return dst;

}


uint8_t *my_memcopy(uint8_t *src, uint8_t *dst, size_t length)
{  
  int i;

  if(src == NULL || dst == NULL){
    PRINTF("Null pointers passed to function. Exiting.");
    return NULL;
  }

  for(i = 0; i < length; i++){
    *(dst+i) = *(src+i);
  }

  return dst;
}


uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value)
{
  int i;

  if(src == NULL){
    PRINTF("Null pointer or length zero passed to function.\
    Exiting.");
    return src;
  }

  for(i = 0; i < length; i++){
    *(src+i) = value;
  }

  return src;
}


uint8_t *my_memzero(uint8_t *src, size_t length)
{  
  int i;

  if(src == NULL){
    PRINTF("Null pointer passed to function. Exiting.");
    return src;
  }

  for(i = 0; i < length; i++){
    *(src+i) = 0;
  }

  return src;
}


uint8_t *my_reverse(uint8_t *src, size_t length)
{
  if(src == NULL){
    PRINTF("Null pointer passed to free_words. Exiting.");
    return src;
  }
  
  uint8_t *src_begin = src;
  uint8_t *end = src+(length-1);
  uint8_t temp;
  
  while(src < end){
    temp = *src;
    *src = *end;
    *end = temp;
    src++;
    end--;
  }
 
  return src_begin;
}


int32_t *reserve_words(size_t length)
{
  int32_t *reserve = (int32_t*)  malloc(length*sizeof(int32_t));
  if(reserve == NULL){
    PRINTF("Memory allocation failed.");
    return NULL;
  }

  return reserve;
}


void free_words(uint32_t *src)
{
  if(src == NULL){
    PRINTF("Null pointer passed to free_words. Exiting.");
    return;
  }

  free(src);
  return;
}
