// feito no windows 10
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    printf("Digite a altura da letra C a ser impressa: ");
    scanf("%d", &n);
    if(n % 6 != 0 || n < 1) {
        printf("Altura invalida!\n");
    } else {
        int h = n / 3;
        int espaco = h - 1;
        // parte de cima do C
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < espaco; j++) {
                printf(" ");
            }
            for(int j = 0; j < n - espaco; j++) {
                printf("*");
            }
            espaco--;
            printf("\n");
        }
        // parte do meio do C
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < n / 2; j++) {
                printf("*");
            }
            printf("\n");
        }
        espaco = 0;
        //parte de baixo do C
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < espaco; j++) {
                printf(" ");
            }
            for(int j = 0; j < n - espaco; j++) {
                printf("*");
            }
            espaco++;
            printf("\n");
        }
    }
    return 0;
}