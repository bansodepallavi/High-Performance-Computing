#include <omp.h>
#include <bits/stdc++.h>
using namespace std;

int main() {
		
	vector<int>a(1000),b(1000),c(1000,0);
	int count = 0;
	double time = omp_get_wtime();
	
	#pragma omp parallel 
	{
		#pragma omp for nowait
		for(int i=0;i<1000;i++)
			a[i] = i;
		
		#pragma omp for nowait
		for(int i=0;i<1000;i++)
			b[i] = 1000 - i;
	}
	
	#pragma omp parallel for reduction(+: count) schedule(dynamic,400)
	for(int i=0;i<1000;i++) {
		c[i] = a[i] + b[i];
		count++;
	}
	

	for(int i=0;i<1000;i++)
		printf("%d ",c[i]);
		
	printf("\n \n %d No of times loop executed",count);
	printf("\n Using %d no of threads and %f execution time",omp_get_max_threads(),omp_get_wtime() - time);
	
}
