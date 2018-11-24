/*
 * del.cpp
 *
 *  Created on: Nov 24, 2018
 *      Author: jernicozz
 */
#include<stdio.h>
#include<cmath>
#include<stdlib.h>

int find_fact(int*factors, int pointer, int number){
	int f=2;
	int first = 0;
	while(f<=sqrt(number)){
		if(number%f==0)
		{
			if (first==0){
				factors[0] = f;
				first++;
			}
			if(factors[pointer]!=f){
				pointer +=2;
				factors[pointer] = f;
				factors[pointer+1] = 0;
			}
			factors[pointer+1]++;
			number /= f;

			f = 1;
		}
		f++;
	}
	if(number != 1){
		if(factors[pointer]!=number){
			pointer +=2;
			factors[pointer] = number;
			factors[pointer+1] = 0;
		}
		factors[pointer+1]++;
	}
	return pointer;

}

int main(){
	int n;
	int fact_n;
	int*factors;
	//int*allfact; он будет дольше ходить по решету
	scanf("%d",&n);
	if (n<2){
		printf("There are no prime factors");
		return -1;
	}
	fact_n = log(n)+1;
	factors = (int*)malloc(2*fact_n*sizeof(int));
	factors[0] = 0;
	factors[1] = 0;
	fact_n = find_fact(factors,0,n);
	for(int i = 0; i<=fact_n;i+=2)
		printf(" %d in power %d ,",factors[i], factors[i+1]);
	free(factors);
	return 0;
}



