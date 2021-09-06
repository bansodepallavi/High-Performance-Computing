#include <stdlib.h>   //malloc and free
#include <stdio.h>    //printf
#include <omp.h>      //OpenMP

// Very small values for this simple illustrative example
#define ARRAY_SIZE 6     //Size of arrays whose elements will be added together.
#define NUM_THREADS 3    //Number of threads to use for vector addition.

int main (int argc, char *argv[]) 
{
	// elements of arrays a and b will be added
	// and placed in array c
	int * a;
	int * b; 
	int * c;
        
    int n = ARRAY_SIZE;                 // number of array elements
	int n_per_thread;                   // elements per thread
	int total_threads = NUM_THREADS;    // number of threads to use  
	int i;       // loop index
        
        a = (int *) malloc(sizeof(int)*n);
	b = (int *) malloc(sizeof(int)*n);
	c = (int *) malloc(sizeof(int)*n);

        // initialize arrays a and b with consecutive integer values
	// as a simple example
        for(i=0; i<n; i++) {
            a[i] = i;
        }
        for(i=0; i<n; i++) {
            b[i] = i;
        }   
        
	// Additional work to set the number of threads.
	// We hard-code to 4 for illustration purposes only.
	omp_set_num_threads(total_threads);
	
	n_per_thread = n/total_threads;
	#pragma omp parallel for default(shared) schedule(static, n_per_thread)
        for(i=0; i<n; i++) {
		c[i] = a[i]+b[i];
		// Which thread am I? Show who works on what for this samll example
		printf("Thread %d works on element%d\n", omp_get_thread_num(), i);
        }
	
	printf("\n array 1 a[i]   - ");
        for(i=0; i<n; i++) {
		printf("%d ",a[i]);
        }
	printf("\n array 2 b[i]   - ");
        for(i=0; i<n; i++) {
		printf("%d ",b[i]);
        }
	printf("\n res array c[i] - ");
        for(i=0; i<n; i++) {
		printf("%d ",c[i]);
        }
        free(a);  free(b); free(c);
	
	return 0;
}
