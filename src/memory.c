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
 uint8_t *dst_beginning = dst;
 uint8_t *temp_begin;

 if((dst <= src && dst+length >= src) ||\
 (dst >= src && dst <= src+length) ||\
 (dst+length >- src && dst+length <= src+length)) {

   uint8_t *temp = malloc(sizeof(uint8_t)*length);
   if(temp == NULL){
    PRINTF("Error allocating memory.");
    return NULL;
   }
   else temp_begin = temp;

   for(i = 0; i < length; i++){
     *temp = *src;
     free(src);
     temp++;
     src++;
   }

   for(i = 0; i < length; i++){
     *temp_begin = *dst;
     free(temp_begin);
     temp_begin++;
     dst++;
   }

 }

 else {
   
   for(i = 0; i < length; i++){
     *dst = *src;
     free(src);
     src++;
     dst++;
   }

 }

 return dst_beginning;

}
