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
 * @file stats.h 
 * @brief Holds function definitions
 *
 * This file holds the function definitions
 * which calculate statistics of values held in an array.
 * This file was written as part of assignment 1 for a
 * coursera course.
 *
 * @author Ankush Burman
 * @date Oct 10, 2018
 *
 */
#ifndef __STATS_H__
#define __STATS_H__

/* Add Your Declarations and Function Comments here */ 

/**
 * @brief <Add Brief Description of Function Here>
 *
 * <Add Extended Description Here>
 *
 * @param <Add InputName> <add description here>
 * @param <Add InputName> <add description here>
 * @param <Add InputName> <add description here>
 * @param <Add InputName> <add description here>
 *
 * @return <Add Return Informaiton here>
 */

/**
 * @brief Function prints statistics of array
 *
 * Function iterates over array and prints out statistics such as
 * minimum, maximum, mean, and median.
 *
 * @param array passing array to be computed on by reference
 * @param len the length of array
 *
 * @return returns 0
 */
 void print_statistics(unsigned char *array, int len);

/**
 * @brief Function prints contents of array
 *
 * Function iterates over array and prints out all its contents
 * Each line is coded to fit 8 elements while printing for readibility
 *
 * @parm array passing array by reference
 * @parm len passing the length of the array as an int
 *
 * @return returns 0
 */
 void print_array(unsigned char *array, int len);

/**
 * @brief Function finds the median
 *
 * Function finds median of all the values held in the array.
 * Function is coded to deal with arrays which have odd and even
 * number of values. If array has odd number of values then the exact
 * middle is the median. If array has even number of values then the
 * median has to be calculated by using the two middle values
 * (This can yield floats).
 * 
 * @parm array passing array by reference
 * @parm len passing the length of the array as an int
 *
 * @return returns median as a floating point
 */
 float find_median(unsigned char *array, int len);

/**
 * @brief Function finds the mean
 *
 * Function finds mean of all the values held in the array
 * 
 * @parm array passing array by reference
 * @parm len passing the length of the array as an int
 *
 * @return returns mean
 */
 float find_mean(unsigned char *array, int len);

/**
 * @brief Function finds the maximum
 *
 * Function finds maximum our of all the values held in the array
 * 
 * @parm array passing array by reference
 * @parm len passing the length of the array as an int
 *
 * @return returns maximum
 */
 int find_maximum(unsigned char *array, int len);

 /**
 * @brief Function finds the minimum
 *
 * Function finds minimum out of all the values held in the array
 * 
 * @parm array passing array by reference
 * @parm len passing the length of the array as an int
 *
 * @return returns minimum
 */
 int find_minimum(unsigned char *array, int len);

/**
 * @brief Function utilizes quick sort algorithm to sort array 
 *
 * Function sorts the array from largest to smallest by
 * utilizing a recursive quicksort algorithm.
 * 
 * @parm array passing array by reference
 * @parm low passing the lowest index of array
 * @parm high passing the highest index of array
 *
 * @return void
 */
 void sort_array(unsigned char *array, int low, int high);

/**
 * @brief Function partitions array for quicksort
 *
 * Function partitions the array based on a pivot point which is
 * last  element of array. 
 * 
 * @parm array passing array by reference
 * @parm low passing the lowest index of array
 * @parm high passing the highest index of array
 *
 * @return new pivot point
 */
 int quicksort_partition(unsigned char *array, int low, int high);

 /**
 * @brief Function swaps values of variables
 *
 * Function swaps values of two unsigned char
 * variables which are  passed by reference
 * 
 * @parm a passing first variable by reference
 * @parm b passing secont variable by reference
 *
 * @return void
 */
 void swap(unsigned char *a, unsigned char *b);


#endif /* __STATS_H__ */
