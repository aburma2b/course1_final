/******************************************************************************
 * Copyright (C) 2018 by Ankush Burman
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file main.c
 * @brief Main entry point to the final assignment of Course 1
 *
 * This file contains the main code for the final assignment for Course 1.
 * The main function calls one function depending on the compile time switch.
 *
 * @author Ankush Burman
 * @date Nov 25, 2018
 *
 */

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "platform.h"
#include "memory.h"
#include "course1.h"
#include "data.h"
#include "stats.h"



int main(void)
{
   #ifdef COURSE1
    course1();
   #endif

   return 0;
}
