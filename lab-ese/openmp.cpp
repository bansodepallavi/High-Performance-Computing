#include<omp.h>
#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main()
{
	string n;
	cout<<"enter number\n";
	cin>>n;
	
	int k=n.length();
	
	omp_set_num_threads(3);
	int i=4,flg=0;
	#pragma omp parallel for shared(i)
	for(i=0;i<k;i++)
	{
		if(n[i]==n[k-1-i])
		printf("Thread %d working on section %d\n", omp_get_thread_num(), i);
		else
		flg=1;
	}
	if(flg==0)
	printf("palindrome");
    else
    printf("not palindrome");
	return 0;
}
