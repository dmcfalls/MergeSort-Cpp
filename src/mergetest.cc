#include "mergesort.h"

#include <stdio.h>
#include <assert.h>
#include <string>
#include <time.h>

#define RANDOM_SEED 42
#define LARGE_ARRAY_SHIFT 20
#define NUM_REPS 10

using namespace std;

int floatCmp(const void *f1, const void *f2) {
	float result = *(float *)f1 - *(float *)f2;
	if (result > 0) return 1;
	else if (result < 0) return -1;
	return 0;
}

int arrCmp(float arr1[], float arr2[]) {
	index_t len1 = sizeof(arr1) / sizeof(float);
	index_t len2 = sizeof(arr2) / sizeof(float);
	if (len1 != len2) return 0;
	for (index_t i = 0; i < len1; i++) {
		if (arr1[i] != arr2[i]) return 0;
	}
	return 1;
}

void printArray(float arr[], index_t length) {
	printf("{");
	for (index_t i = 0; i < length - 1; i++) {
		printf("%.2f ", arr[i]);
	}
	printf("%.2f", arr[length - 1]);
	printf("}\n");
}

void testCorrectness(string type) {
	float arr1[] = { 4, 1, 2, 5, 3 };
  float arr2[] = { 9, 4, 5, 2, 8, 1, 7, 6, 3 };

  float sorted1[] = { 1, 2, 3, 4, 5 };
  float sorted2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  if (type == "Singlethreaded") {
    printf("  Single-threaded version:\n");
  	mergesortST(arr1, 0, 5);
  	mergesortST(arr2, 0, 9);
  } else if (type == "Multithreaded") {
    printf("  Multithreaded version:\n");
  	mergesortMT(arr1, 0, 5);
  	mergesortMT(arr2, 0, 9);
  } else {
  	printf("  Incorrect Argument!\n");
  	return;
  }

  printf("  arr1: "); printArray(arr1, 5);
  assert(arrCmp(arr1, sorted1));

  printf("  arr2: "); printArray(arr2, 9);
  assert(arrCmp(arr2, sorted2));
}

double stressTest(string type, size_t shift) {
	size_t array_size = 1 << (LARGE_ARRAY_SHIFT + shift);
	float *arr = new float[array_size];
	time_t t = time(NULL);
	for(size_t i = 0; i < NUM_REPS; i++) {
		for (index_t i = 0; i < array_size; i++) {
			arr[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
		if (type == "Singlethreaded") {
		  mergesortST(arr, 0, array_size);
		} else if (type == "Multithreaded") {
		  mergesortMT(arr, 0, array_size);
		} else if (type == "Builtin") {
			qsort(arr, sizeof(arr) / sizeof(float), sizeof(float), floatCmp);
		} else {
			printf("  Incorrect Argument!\n");
      delete[] arr;
			return difftime(time(NULL), t);
		}
	}
  delete[] arr;
	return difftime(time(NULL), t);
}

int main () {
	srand(RANDOM_SEED);
	printf("MergeSort Tests: \n");

  printf("Single-threaded MergeSort: \n");

  printf("Correctness Tests: \n");
  //testCorrectness("Singlethreaded");
  testCorrectness("Multithreaded");

  printf("Performance Tests:\n");
  for (size_t i = 0; i < 10; i++) {
  	printf("  Round %d:\n", (int)i);
	  printf("   Single-threaded version:\n");
	  double t1 = stressTest("Singlethreaded", i);
	  printf("    Time: %.f seconds\n", t1);
	  printf("   Multithreaded version:\n");
	  double t2 = stressTest("Multithreaded", i);
	  printf("    Time: %.f seconds\n", t2);
	  printf("   C Quicksort Builtin:\n");
	  double t0 = stressTest("Builtin", i);
	  printf("    Time: %.f seconds\n", t0);
	}

  printf("All done! \n");
  return 0;
}
