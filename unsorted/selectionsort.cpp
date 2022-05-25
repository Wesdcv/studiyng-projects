#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

void selectionSort(double* arr, int n);
void swap(double *arr1el, double *arr2el);
void printArray(double* arr, int size);
double* getRandomValues(int n);

int main() 
{ 
    int n = 1000;
    double *arr = getRandomValues(n);
    selectionSort(arr, n); 
    //printArray(arr, n); 
    free(arr);
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

void selectionSort(double* arr, int n) 
{ 
	int i, j; 
	int change = 0;
	int compare = 0; 

	for (int i = 0, j = n - 1; i < j; i++, j--) 
	{ 
        double minel = *(arr + i);
		double maxel = *(arr + i); 
        int minN = i;
		int maxN = i; 
        for (int k = i; k <= j; k++)  
		{ 
			compare += 1;
            if (*(arr + k) > maxel) 
			{ 
                maxel = *(arr + k); 
                maxN = k; 
            } 
			
			else if (*(arr + k) < minel) 
			{ 
				compare += 1;
                minel = *(arr + k); 
                minN = k; 
            } 

			else
			{
				compare += 1;
			}
        } 
	
        swap((arr + i), (arr + minN)); 
		change += 1;

		compare += 1;
        if (*(arr + minN) == maxel)  
		{
            swap((arr + j), (arr + minN)); 
			change += 1;
		}
        else
		{
            swap((arr + j), (arr + maxN));
			change += 1; 
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
  