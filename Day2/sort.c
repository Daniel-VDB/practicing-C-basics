#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int *bubblesort(int *arr, int len);
int *selectionsort(int *arr, int len);
int *mergesort(int *arr, int len);
int *visual_mergesort(int *arr, int len);
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
    printf("Unsorted: ");
    print_arr(arr, length);
    visual_mergesort(arr, length);

    printf("Sorted: ");
    print_arr(arr, length);

    free(arr);
    return 0;
}


// Pointer based bubble sort
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

// Pointer based selection sort
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

int *mergesort(int *arr, int len){
    // Base cases
    if (len <= 1){
        return arr;
    }
    if (len == 2){
        if (arr[0] > arr[1]) {
            swap(&arr[0],&arr[1]);
        }
        return arr;
    }

    // Split array into left and right
    int left_len = len / 2; // Truncated (smaller)
    int right_len = len - left_len;

    int *left = malloc(sizeof(int) * left_len);
    if (left == NULL){
        printf("Failed memory allocation");
        return NULL;
    }
    int *right = malloc(sizeof(int) * right_len);
    if (right == NULL){
        free(left);
        printf("Failed memory allocation");
        return NULL;
    }

    for (int i = 0; i < left_len; i++){
        left[i] = arr[i];
    }
    for (int j = left_len; j < len; j++){
        right[j - left_len] = arr[j];
    }

    // Recursively sort the left and right side
    left = mergesort(left, left_len);
    right = mergesort(right, right_len);

    // In case of failed allocation of left and right in recursive calls
    if (left == NULL){
        if (right != NULL){free(right);}
        return NULL;
    }
    if (right == NULL){
        if (left != NULL){free(left);}
        return NULL;
    }

    // Merge left and right
    int l = 0; // Left cursor
    int r = 0; // Right cursor
    int m = 0; // Merged (arr) cursor

    while (l < left_len && r < right_len && m < len){
        if (left[l] > right[r]){
            arr[m] = right[r];
            r++;
        }
        else
        {
            arr[m] = left[l];
            l++;
        }
        m++;
    }
    while (l < left_len)
    {
        arr[m] = left[l];
        l++;
        m++;
    }
    while (r < right_len)
    {
        arr[m] = right[r];
        r++;
        m++;
    }

    // Free left and right branches, and return the merged array
    free(left);
    free(right);
    return arr;
}

int *visual_mergesort(int *arr, int len){
    // Base cases
    printf("Partition: ");
    print_arr(arr, len);

    if (len <= 1){
        return arr;
    }
    if (len == 2){
        if (arr[0] > arr[1]) {
            swap(&arr[0],&arr[1]);
        }
        return arr;
    }

    // Split array into left and right
    int left_len = len / 2; // Truncated (smaller)
    int right_len = len - left_len;

    int *left = malloc(sizeof(int) * left_len);
    if (left == NULL){
        printf("Failed memory allocation");
        return NULL;
    }
    int *right = malloc(sizeof(int) * right_len);
    if (right == NULL){
        free(left);
        printf("Failed memory allocation");
        return NULL;
    }

    for (int i = 0; i < left_len; i++){
        left[i] = arr[i];
    }
    for (int j = left_len; j < len; j++){
        right[j - left_len] = arr[j];
    }

    // Recursively sort the left and right side
    left = visual_mergesort(left, left_len);
    right = visual_mergesort(right, right_len);

    // In case of failed allocation of left and right in recursive calls
    if (left == NULL){
        if (right != NULL){free(right);}
        return NULL;
    }
    if (right == NULL){
        if (left != NULL){free(left);}
        return NULL;
    }

    // Merge left and right
    int l = 0; // Left cursor
    int r = 0; // Right cursor
    int m = 0; // Merged (arr) cursor

    while (l < left_len && r < right_len && m < len){
        if (left[l] > right[r]){
            arr[m] = right[r];
            r++;
        }
        else
        {
            arr[m] = left[l];
            l++;
        }
        m++;
    }
    while (l < left_len)
    {
        arr[m] = left[l];
        l++;
        m++;
    }
    while (r < right_len)
    {
        arr[m] = right[r];
        r++;
        m++;
    }

    // Free left and right branches, and return the merged array
    free(left);
    free(right);
    return arr;
}

// Print values of an array
void print_arr(int *arr, int len){
    if (len < 1){
        printf("[");
        return;
    }

    printf("[");
    for (int i = 0; i < len - 1; i++){
        printf("%i, ", arr[i]);
    }
    printf("%i]\n", arr[len - 1]);
    return;
}

// Swaps values with pointers
void swap(int *a, int *b){
    int tmp = *b;
    *b = *a;
    *a = tmp;
}