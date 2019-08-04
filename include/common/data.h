/******************************************************************************
 * Copyright (C) 2019 by Ankush Burman
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Ankush Burman are not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file data.h
 * @brief Abstraction of data manipulation operations
 *
 * This header file provides an abstraction of Integer to ASCII
 * and ASCII to Integer via function calls.  
 *
 * @author Ankush Burman
 * @date July 31 2019
 *
 */

#ifndef __DATA_H__
#define __DATA_H__

#define arr_len (16)

int32_t my_findnum(uint8_t *ptr);
/**
 * @brief Takes a pointer to ascii value and converts it to int 
 *
 * Given a a pointer to a char which holds an ascii value. Converts
 * said ascii value to the corresponding number and returns it as
 * an integer.
 *
 * @param ptr Address of char with ascii value
 *
 * @return Integer which corresponds to ascii value.
 */

int32_t my_exponent(int32_t base, int32_t power);
/**
 * @brief Returns bases to the power of power 
 *
 * This function is for calculating powers and exponents.
 * Without using the math.h library.
 *
 * @param base the base number
 * @param power The power the base needs to be raised to
 *
 * @return Integer value of the resulting power calculation.
 */

uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);
/**
 * @brief Takes integer converts into ASCII string 
 *
 * Given a 32 bit integers converts it to an ASCII string
 * composed a char pointer array. Returns the address of 
 * the start of the char pointer array.
 *
 * @param data Integer to convert
 * @param ptr Start address of char pointer array
 * @param base The base the integer needs to be converted to
 *
 * @return Start address of char pointer array.
 */

int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);
/**
 * @brief Takes ASCII string and converts into an integer 
 *
 * Given a pointer to a char data set in ASCII format, this
 * function converts it to a 32 bit integer. Integer can 
 * be signed or unsigned.
 *
 * @param ptr Pointer to data array
 * @param digits Number of digits in char array
 * @param base The base ASCII number is in
 *
 * @return 32 bit integer.
 */

#endif /* __DATA_H__ */



