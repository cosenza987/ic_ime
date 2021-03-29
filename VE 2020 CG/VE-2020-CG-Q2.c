//comensal bora 25, pau no cu dos urso
#include <stdio.h>

int main() {
    char alf[30], k;
    int i = 0;
    for(i = 0; i < 26; i++) {
        alf[i] = 'A'  + i;
    }
    printf("Digite uma letra maiuscula: ");
    scanf("%c", &k);
    printf("\n");
    int lim = k - 'A';
    for(i = 0; i <= lim; i++) {
        for(int j = 0; j <= i; j++) {
            printf("%c", alf[j]);
        }
        if(i != 0) {
            for(int j = i - 1; j >= 0; j--) {
                printf("%c", alf[j]);
            }
        }
        printf("\n");
    }
    for(i = lim - 1; i >= 0; i--) {
        for(int j = 0; j <= i; j++) {
            printf("%c", alf[j]);
        }
        if(i != 0) {
            for(int j = i - 1; j >= 0; j--) {
                printf("%c", alf[j]);
            }
        }
        printf("\n");
    }
    return 0;
}
