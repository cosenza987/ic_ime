// feito no windows 10
#include <stdio.h>
#include <math.h>

double max(double a, double b) {
    if(a > b){
        return a;
    } else {
        return b;
    }
}

int main() {
    double rz1, iz1, rz2, iz2;
    int opcao = -1;
    printf("------- CALCULADORA DE NUMEROS COMPLEXOS -------\n\n");
    printf("Digite a parte real de Z1: ");
    scanf("%lf", &rz1);
    printf("Digite a parte imaginaria de Z1: ");
    scanf("%lf", &iz1);
    printf("Digite a parte real de Z2: ");
    scanf("%lf", &rz2);
    printf("Digite a parte imaginaria de Z1: ");
    scanf("%lf", &iz2);
    printf("\n\n");
    while (opcao != 9) {
        printf("Qual operacao deseja realizar com Z1 e Z2?\n");
        printf("- Digite 1 para imprimi-los na tela\n");
        printf("- Digite 2 para calcular Z1 + Z2\n");
        printf("- Digite 3 para calcular Z1 - Z2\n");
        printf("- Digite 4 para calcular Z1 * Z2\n");
        printf("- Digite 5 para imprimir os conjugados de Z1 e Z2\n");
        printf("- Digite 6 para imprimir Z1 / Z2\n");
        printf("- Digite 7 para calcular os modulos de Z1 e Z2\n");
        printf("- Digite 8 para calcular os argumentos de Z1 e Z2 em radianos\n");
        printf("- Digite 9 para sair do programa\n");
        printf("Opcao desejada: ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                printf("Z1 = %.3lf + %.3lfi e Z1 = %.3lf + %.3lfi\n\n", rz1, iz1, rz2, iz2);
                break;
            case 2:
                printf("Z1 + Z2 = %.3lf + %.3lfi\n\n", rz1 + rz2, iz1 + iz2);
                break;
            case 3:
                printf("Z1 - Z2 = %.3lf + %.3lfi\n\n", rz1 - rz2, iz1 - iz2);
                break;
            case 4:
                printf("Z1 * Z2 = %.3lf + %.3lfi\n\n", (rz1*rz2 - iz1*iz2), (rz1*iz2 + rz2*iz1));
                break;
            case 5:
                printf("conjugado de Z1 = %.3lf + %.3lfi e conjugado de Z2 = %.3lf + %.3lfi\n\n", rz1, (-1*iz1), rz2, (-1*iz2));
                break;
            case 6:
                printf("Z1 / Z2 = %.3lf + %.3lfi\n\n", (rz1*rz2 + iz1*iz2)/(rz2*rz2 + iz2*iz2), (iz1*rz2 - rz1*iz2)/(rz2*rz2 + iz2*iz2));
                break;
            case 7:
                printf("modulo de Z1 = %.3lf e modulo de Z2 = %.3lf\n\n", sqrt(rz1*rz1 + iz1*iz1), sqrt(rz2*rz2 + iz2*iz2));
                break;
            case 8:
                printf("argumento de Z1 = %.3lf e argumento de Z2 = %.3lf\n\n", max(asin(iz1/(sqrt(rz1*rz1 + iz1*iz1))), acos(rz1/(sqrt(rz1*rz1 + iz1*iz1)))), max(acos(rz2/(sqrt(rz2*rz2 + iz2*iz2))), asin(iz2/(sqrt(rz2*rz2 + iz2*iz2)))));
                break;
            case 9:
                printf("Saindo da calculadora...\n\n");
                break;
            default:
                printf("Opcao invalida!\n\n");
        }
    }
    return 0;
}