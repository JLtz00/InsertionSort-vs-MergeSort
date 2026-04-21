#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STEP 100
#define MAX_SIZE 10000
#define MIN_SIZE 0
#define REPEAT 10

static void insertionSort(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = key;
  }
}

static void merge(int arr[], int temp[], int left, int mid, int right) {
  int i = left;
  int j = mid + 1;
  int k = left;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }

  while (i <= mid)
    temp[k++] = arr[i++];

  while (j <= right)
    temp[k++] = arr[j++];

  memcpy(arr + left, temp + left, (right - left + 1) * sizeof(int));
}

static void mergeSortRecursive(int arr[], int temp[], int left, int right) {
  if (left >= right)
    return;

  int mid = left + (right - left) / 2;

  mergeSortRecursive(arr, temp, left, mid);
  mergeSortRecursive(arr, temp, mid + 1, right);
  merge(arr, temp, left, mid, right);
}

static void mergeSort(int arr[], int temp[], int n) {
  if (n <= 1)
    return;

  mergeSortRecursive(arr, temp, 0, n - 1);
}

static void generateRandomArray(int arr[], int n, int maxValue) {
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % maxValue;
  }
}

static long long elapsedNanoseconds(struct timespec start, struct timespec end) {
  long long seconds = (long long)(end.tv_sec - start.tv_sec);
  long long nanoseconds = (long long)(end.tv_nsec - start.tv_nsec);
  return seconds * 1000000000LL + nanoseconds;
}

static double measureInsertionSort(int baseArr[], int n) {
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  insertionSort(baseArr, n);
  clock_gettime(CLOCK_MONOTONIC, &end);

  return (double)elapsedNanoseconds(start, end) / 1000.0;
}

static double measureMergeSort(int baseArr[], int temp[], int n) {
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  mergeSort(baseArr, temp, n);
  clock_gettime(CLOCK_MONOTONIC, &end);

  return (double)elapsedNanoseconds(start, end) / 1000.0;
}

int main(void) {
  srand((unsigned int)time(NULL));

  printf("# n insertion_us merge_us\n");

  for (int n = MIN_SIZE; n <= MAX_SIZE; n += STEP) {
    size_t sizeArr = n * sizeof(int);
    int *baseArr = malloc(sizeArr);
    int *Arr1 = malloc(sizeArr);
    int *Arr2 = malloc(sizeArr);
    int *temp = malloc(sizeArr);

    double iSortTime = 0;
    double mSortTime = 0;

    if (baseArr == NULL || Arr1 == NULL || Arr2 == NULL || temp == NULL) {
      fprintf(stderr, "Error: no se pudo reservar memoria para n=%d\n", n);
      return EXIT_FAILURE;
    }

    generateRandomArray(baseArr, n, 100000);

    for (int i = 0; i < REPEAT; i++) {
      memcpy(Arr1, baseArr, sizeArr);
      memcpy(Arr2, baseArr, sizeArr);

      iSortTime += measureInsertionSort(Arr1, n);
      mSortTime += measureMergeSort(Arr2, temp, n);
    }

    iSortTime /= REPEAT;
    mSortTime /= REPEAT;

    printf("%d %.6f %.6f\n", n, iSortTime, mSortTime);
    free(baseArr);
    free(Arr1);
    free(Arr2);
    free(temp);
  }

  return EXIT_SUCCESS;
}
