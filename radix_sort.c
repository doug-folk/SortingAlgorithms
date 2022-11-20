#include <stdlib.h> //para malloc, calloc, free
#include <string.h> //para memcpy, memset,

void counting_sort(int *v, int n, int div, int base, int *temp){
    int i, t, c[base], acum = 0;
    memset(c, 0, base * sizeof(int));

    #define DIGIT(x) (x / div) % base

    for(i = 0; i < n; i++){
        c[DIGIT(v[i])]++;
    }

    for(i = 0; i < base; i++){
        t = c[i];
        c[i] = acum;
        acum += t;
    }

    for (i = 0; i < n; i++){
        temp[c[DIGIT(v[i])]] = v[i];
        c[DIGIT(v[i])]++;
    }

    memcpy(v, temp, sizeof(int) * n);
    
}

void radix_sort(int *v, int n){
    int k, div = 1;
    k = max(v, n);
    int *temp = malloc(sizeof(int) * n);

    while (k > 0){
        counting_sort(v, n, div, 10, temp);
        div *= 10;
        k /= 10;
    }
    free(temp);
}