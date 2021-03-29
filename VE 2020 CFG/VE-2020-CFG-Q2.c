// womdowsVERSAUM DES
#include <stdio.h>

int main() {
    int alt, tri, base, base1, base2, entra, row;
    printf("Digite a altura do triforce: ");
    scanf(" %d", &alt);
    if(alt%2 != 0 || alt < 4) {
        printf("ALTURA INVALIDA\n");
    } else {
        row = 0;
        tri = (alt / 2); //pegando a altura de cada triangulo
        base = (2*tri) - 1;
        base1 = base; // base do triangulo de cima
        base2 = base; //base do triangulo invisivel de baixo
        entra = tri - 1; //a quantidade de espacos antes do primeiro triangulo da parte de baixo
        //imprimindo o triangulo de cima
        for(row = 0; row < tri; row++) {
            for(int i = 0; i < base1; i++) {
            printf(" ");
            }
            base1--;
            for(int k = 0; k < (2*row) + 1; k++) {
                printf("*");
            }
            printf("\n");
        }
        //imprimindo os dois de baixo agora
        for(row = 0; row < tri; row++) {
            for(int i = 0; i < entra; i++) {
                printf(" ");
            }
            for(int i = 0; i < (2*row) + 1; i++) {
                printf("*");
            }
            for(int i = 0; i < base2; i++) {
                printf(" ");
            }
            for(int i = 0; i < (2*row) + 1; i++) {
                printf("*");
            }
            entra--;
            base2 = base2 - 2;
            printf("\n");
        }
    }
    return 0;
}
