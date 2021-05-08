#include <stdio.h>

int recursivo(int n) {
    if(n == 1 || n == 2 || n == 3) {
        return 1;
    } else {
        int resposta = (1*recursivo(n - 1)) + (2 * recursivo(n - 2)) + (3 * recursivo(n - 3));
        return resposta;
    }
}

int iterativo(int n) {
    int arr[n + 1], i;
    for(i = 1; i <= 3; i++) {
        arr[i] = 1;
    }
    for(i = 4; i <= n; i++) {
        arr[i] = (1 * arr[i - 1]) + (2 * arr[i - 2]) + (3 * arr[i - 3]);
    }
    return arr[n];
}

int main() {
    int n;
    printf("Insira um numero natural: ");
    scanf("%d", &n);
    printf("\nT(%d) = %d (RECURSIVO)", n, recursivo(n));
    printf("\nT(%d) = %d (ITERATIVO)", n, iterativo(n));
    return 0;
}
