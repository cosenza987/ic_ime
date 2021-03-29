// comensal viva 25, nao importa como voce faca, sempre ha como errar
#include <stdio.h>

int res[10]; // uma maneira de separar cada resultado, com 0 indicando insuficiente, 1 indicando regular e etc.

int main() {
    int idade, dist, flex, abd, barra, ind = 0; // indicador para a suficiencia
    printf("***Bem-vindo a calculadora do TAF***\n\n");
    printf("Idade do militar: ");
    scanf("%d", &idade);
    if(idade != 18 && idade != 19) {
        printf("\nIDADE INVALIDA!\n");
        return 0;
    }
    printf("Distancia em m percorrida em 12 min: ");
    scanf("%d", &dist);
    printf("Nr de flexoes de braco: ");
    scanf("%d", &flex);
    printf("Nr de abdominais: ");
    scanf("%d", &abd);
    printf("Nr de flexoes na barra: ");
    scanf("%d", &barra);
    printf("\nRESULTADOS:\n");
    printf("\nCorrida: ");
    if(dist < 2700) {
        printf("I\n");
        res[0]++;
    } else if(dist >= 2700 && dist < 2800) {
        printf("R\n");
        res[1]++;
    } else if(dist >= 2800 && dist < 3100) {
        printf("B\n");
        res[2]++;
    } else if(dist >= 3100 && dist < 3200) {
        printf("MB\n");
        res[3]++;
    } else {
        printf("E\n");
        res[4]++;
    }
    if(dist < 2950) {
        ind++;
    }
    printf("Flexao de Braco: ");
    if(flex <= 20) {
        printf("I\n");
        res[0]++;
    } else if(flex > 20 && flex <= 25) {
        printf("R\n");
        res[1]++;
    } else if(flex > 25 && flex <= 34) {
        printf("B\n");
        res[2]++;
    } else if(flex > 34 && flex <= 38) {
        printf("MB\n");
        res[3]++;
    } else {
        printf("E\n");
        res[4]++;
    }
    if(flex < 30) {
        ind++;
    }
    printf("Abdomnial: ");
    if(abd <= 34) {
        printf("I\n");
        res[0]++;
    } else if(abd > 34 && abd <= 44) {
        printf("R\n");
        res[1]++;
    } else if(abd > 44 && abd <= 63) {
        printf("B\n");
        res[2]++;
    } else if(abd > 63 && abd <= 73) {
        printf("MB\n");
        res[3]++;
    } else {
        printf("E\n");
        res[4]++;
    }
    if(abd < 54) {
        ind++;
    }
    printf("Flexao na Barra: ");
    if(barra <= 4) {
        printf("I\n");
        res[0]++;
    } else if(barra > 4 && barra <= 6) {
        printf("R\n");
        res[1]++;
    } else if(barra > 6 && barra <= 9) {
        printf("B\n");
        res[2]++;
    } else if(barra > 9 && barra <= 11) {
        printf("MB\n");
        res[3]++;
    } else {
        printf("E\n");
        res[4]++;
    }
    if(barra < 8) {
        ind++;
    }
    printf("\nSuficiencia: ");
    if(ind == 0) {
        printf("S");
    } else {
        printf("NS");
    }
    printf(" / Mencao: ");
    if(res[0] > 0) {
        printf("I");
    } else if(res[1] > 0) {
        printf("R");
    } else if(res[2] > 0) {
        printf("B");
    } else if(res[3] > 0) {
        printf("MB");
    } else {
        printf("E");
    }
    return 0;
}
