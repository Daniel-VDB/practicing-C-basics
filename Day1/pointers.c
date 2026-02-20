#include <stdio.h>
#include <stdlib.h>

int slen(char *string);
char *sreverse(char *string);
char* scpy(char *dst, char *src);
int strcomp(char *a, char*b);
int swap(int *a, int *b);
int find_largest(int *arr, int length);

int main(void){
    int a = 1;
    int b = 2;

    int *ptr1 = &a;
    int *ptr2 = &b;

    swap(ptr1,ptr2);
    printf("a: %i\nb: %i\n", a, b);
}

int slen(char *string){
    int i = 0;
    while (string[i] != '\0'){
        i++;
    }
    return i;
}

char *sreverse(char *string){
    int l = slen(string);
    char *reversed = malloc(sizeof(char) * (l + 1));
    reversed[l] = '\0';
    for (int i = 0; i < l; i++){
        reversed[i] = string[l-i-1];
    }
    return reversed;
}

char *scpy(char *dst, char *src){
    char *start = dst;
    while((*dst++ = *src++) != '\0');
    return start;
}

int strcomp(char *a, char*b){
    do {
        if(*a != *b){
            return (*a - *b);
        }
        a++;
        b++;
    } while (*a != '\0' && *b != '\0');
    if (*a != '\0') return 1;
    if (*b != '\0') return -1;
    return 0;
}

int swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int find_largest(int *arr, int length){
    int max = *arr++;
    for (int i = 1; i < length; i++){
        if(*arr > max) max = *arr;
        arr++;
    }
    return max;
}

int find_largest_no_ptr(int *arr, int length){
    int max = *arr;
    for (int i = 1; i < length; i++){
        if(arr[i] > max) max = arr[i];
    }
    return max;
}