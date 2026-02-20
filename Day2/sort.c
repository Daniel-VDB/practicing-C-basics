#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int *bubblesort(int *arr, int len);
int *selectionsort(int *arr, int len);
void print_arr(int *arr, int len);
void swap(int *a, int *b);

int main(void){
    srand(time(NULL));

    int length;
    printf("Please enter array length: ");
    scanf("%d", &length);

    int *arr = malloc(sizeof(int) * length);
    if (arr == NULL){printf("Allocation error"); return 1;}

    for (int i = 0; i < length; i++){
            arr[i] = rand();
    }
    print_arr(arr, length);
    selectionsort(arr, length);
    print_arr(arr, length);

    free(arr);
    return 0;
}

int *bubblesort(int *arr, int len){
    for (int i = 0; i < len; i++){
        bool sorted = true;
        for (int j = 0; j < len - 1 - i; j++){
            if (arr[j] > arr[j+1]){
                sorted = false;
                swap(&arr[j], &arr[j+1]); // Swap values at pointers of arr[j] & arr[j+1]
            }
        }
        if (sorted) return arr; // If no swaps have been made in this pass, the function is sorted
    }
    return arr;
}

int *selectionsort(int *arr, int len){
    for (int i = 0; i < len; i++){
        int min = i;
        for (int j = i + 1; j < len; j++){
            if (arr[j] < arr[min]){
                min = j; // New minimum found on right of sorted elements
            }
        }
        if (min != i){
            swap(&arr[min], &arr[i]); // Swap values at pointers of arr[min] & arr[i] if they are different
        }
    }
    return arr;
}

void print_arr(int *arr, int len){
    printf("Array = [");
    for (int i = 0; i < len; i++){
        printf("%i, ", arr[i]);
    }
    printf("]\n");
    return;
}

void swap(int *a, int *b){ // Swaps values with pointers
    int tmp = *b;
    *b = *a;
    *a = tmp;
}