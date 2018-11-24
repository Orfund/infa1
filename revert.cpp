/*
 * revert.cpp
 *
 *  Created on: Nov 24, 2018
 *      Author: jernicozz
 */

#include <stdio.h>
int main() {
int n, k=0, i = 0, lo;
scanf("%d", &n);
for(;1<<i<=n;i++)
lo = i;
for(i=0;i<=lo;i++){
k+=(1<<(lo-i))*(n>>i&1);
}
printf("%d", k);
return k;
}


