#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

void bubbleSort(double* arr, int n);
void swap(double *arr1el, double *arr2el);
void printArray(double* arr, int size);
double* getRandomValues(int n);

int main() 
{ 
    int n = 1000;
    double *arr = getRandomValues(n);
    bubbleSort(arr, n); 
    //printArray(arr, n); 
    //free(arr);
    return 0; 
} 

double* getRandomValues(int n)
{
  srand(time(0));
  double* arr = (double*) calloc(n, sizeof(double));
  if(arr == NULL)                     
    {
        printf("memory not allocated");
        exit(0);
    }
  for(int i = 0; i < n ; i++)
      *(arr + i) = rand() + 1;
  return arr;
}

void bubbleSort(double* arr, int n) 
{ 
   int i, j; 
   bool swapped;
   int change = 0;
   int compare = 0; 

   for (i = 0; i < n - 1; i++) 
   { 
     swapped = false; 
     for (j = 0; j < n - i - 1; j++) 
     { 
        compare += 1; 
        if (*(arr + j) > *(arr + j + 1)) 
        { 
           swap((arr + j), (arr + j + 1)); 
           change += 1;
           swapped = true; 
        } 
     } 
  
     if (swapped == false) 
     {
        //printf(" %d %d", change, compare);
        break; 
     }
   } 
   printf(" %d %d", change, compare);
} 

void swap(double *arr1el, double *arr2el) 
{ 
    double temp = *arr1el; 
    *arr1el = *arr2el; 
    *arr2el = temp; 
} 

void printArray(double* arr, int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        printf(" %0.0lf", *(arr + i)); 
} 
  