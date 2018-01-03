/* File: mergesort.h
 * Author: Dan McFalls (dmcfalls@stanford.edu)
 *
 * Single-threaded and multithreaded implementations of MergeSort.
 */

/* 
 * Represents an index in an array.
 */
typedef unsigned int index_t;

/*
 * Single-threaded version of the MergeSort algorithm.
 */
void mergesortST(float arr[], index_t left, index_t right);

/*
 * Multithreaded version of the MergeSort algorithm.
 */
void mergesortMT(float arr[], index_t left, index_t right);
