#include <stdio.h>

int facto(int n);
int recur_facto(int n);
int power(int n, int p);
int pow_recur(int n, int p);

int main(void){
    int n;
    printf("Number: ");
    scanf("%d", &n); 
    int fac = facto(n);
    int pow = pow_recur(n, 5);
    printf("%i factorial is: %i\n", n, fac);
    printf("%i to the power of 5 is: %i\n", n, pow);
}

int facto(int n){
    int a = 1;
    for (int i = 1; i < n+1; i++){
        a *= i;
    }
    return a;
}

int recur_facto(int n){
    if (n <= 1)
    {
        return 1;
    }
    return n * recur_facto(n-1);
}

int power(int n, int p){
    int result = 1;
    for (int i = 0; i < p; i++){
        result *= n;
    }
    return result;
}

int pow_recur(int n, int p){
    if (p == 0){
        return 1;
    }
    if (p == 1){
        return n;
    }
    return n * pow_recur(n, p - 1);
}
