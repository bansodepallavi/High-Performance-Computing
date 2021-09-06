#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
 
#define N 50             /* number of rows in matrix A */ 
#define P 50                /* number of columns in matrix A */ 
#define M 50                 /* number of columns in matrix B */ 
 
int main (int argc, char *argv[]) 
{ 
int  tid, nthreads, i, j, k; 
double a[N][P], b[P][M], c[N][M]; 
omp_set_num_threads(4);
 double time = omp_get_wtime();
/*** Create a parallel region explicitly scoping all variables ***/ 
#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k) 
  { 

  tid = omp_get_thread_num(); 
  if (tid == 0) 
    { 
    nthreads = omp_get_num_threads(); 
    printf("Starting matrix multiple example with %d threads\n",nthreads); 
    printf("Initializing matrices...\n"); 
    } 
  /*** Initialize matrices ***/ 
  #pragma omp for 
  for (i=0; i<N; i++) 
    for (j=0; j<P; j++) 
      a[i][j]= i+j; 
      
  #pragma omp for 
  for (i=0; i<P; i++) 
    for (j=0; j<M; j++) 
      b[i][j]= i*j; 
      
  #pragma omp for 
  for (i=0; i<N; i++) 
    for (j=0; j<M; j++) 
      c[i][j]= 0; 
 
  /*** Do matrix multiply sharing iterations on outer loop ***/ 
  /*** Display who does which iterations for demonstration purposes ***/ 
  printf("Thread %d starting matrix multiply...\n",tid); 

  #pragma omp for 
  for (i=0; i<N; i++) 
    { 
    printf("Thread=%d did row=%d\n",tid,i); 
    for(j=0; j<M; j++) 
      for (k=0; k<P; k++) 
        c[i][j] += a[i][k] * b[k][j]; 
    } 
  }   /*** End of parallel region ***/ 
 
/*** Print results ***/ 
printf("******************************************************\n"); 
printf("Result Matrix:\n"); 
for (i=0; i<N; i++) 
  { 
  for (j=0; j<M; j++) 
    printf("%6.2f   ", c[i][j]); 
  printf("\n"); 
  } 
printf("******************************************************\n"); 
printf ("Done In %f Seconds",omp_get_wtime() - time); 
printf("\n Using %d Threads",omp_get_max_threads());

return(0); 
}
