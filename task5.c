
#include "task1.h"
#include <math.h>
int isPrime(int n){
    for(int i = 0; i < sqrt(n) + 1; ++i){
        if( n % i == 0 )
            return 0;
    }
    return 1;
}

int countOnes(int n){
    int res = 0;
    for(int i = 0; i < sizeof(int)*8; ++i){
        res += (n >> i) & 1;
    }
    return res;
}

int task5Wrapper(void){
    FILE * f = fopen("in5.txt", "w");
    int l, r;
    fscanf(f, "%d%d", &l, &r);
    int count = 0;
    for(int i = l; i <= r; ++i){
        count += isPrime(countOnes(i));
    }
    printf("%d\n", count);
    fclose(f);
    return 0;
}

