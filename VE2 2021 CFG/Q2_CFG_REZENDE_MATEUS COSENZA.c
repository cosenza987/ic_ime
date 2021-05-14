//sistema operacional: windows 10
#include <stdio.h>
#include <string.h>

double calculoRecursivo(int pop, int n);
double calculoIterativo(int pop, int n);
double abss(double k, double j);
void calculoEstabilidade();
int ii;

int main() {
    int opcao = -1, n, pop;
    printf("Insira o valor inicial da populacao: ");
    scanf("%d", &pop);
    while(opcao != 1 && opcao != 2) {
        printf("Escolha uma opcao:\n");
        printf("1-Calcular o tamanho da populacao apos n geracoes.\n");
        printf("2-Calcular o tamanho final da populacao e o total de geracoes necessario.\n");
        scanf("%d", &opcao);
        int op2;
        switch(opcao) {
            case 1:
                printf("Digite o numero de geracoes: ");
                scanf("%d", &n);
                printf("O calculo deve ser feito: \n");
                while(op2 != 1 && op2 != 2) {
                    printf("1-Recursivamente.\n");
                    printf("2-Iterativamente.\n");
                    scanf("%d", &op2);
                    if(op2 == 1) {
                        printf("Populacao final de %d individuos.", (int)calculoRecursivo(pop, n));
                    }
                    if(op2 == 2) {
                        printf("Populacao final de %d individuos.", (int)calculoIterativo(pop, n));
                    }
                }
                break;
            case 2:
                ii = pop;
                calculoEstabilidade();
                break;
            default:
                continue;
        }
    }
    return 0;
}

double calculoRecursivo(int pop, int n) {
    if(n == 0) {
        return pop;
    } else {
        return (0.8 * calculoRecursivo(pop, n - 1) + 30.0);
    }
}

double calculoIterativo(int pop, int n) {
    double i, j, k;
    if(n == 0) {
        return pop;
    } else {
        while(n--) {
            j = (0.8 * pop) + 30.0;
            pop = j;
        }
        return pop;
    }
}

//modulo da diferenca entre dois valores
double abss(double k, double j) {
    if(k > j) {
        return k - j;
    } else {
        return j - k;
    }
}

void calculoEstabilidade() {
    int geracoes = -1;
    double o = 1, p = 2;
    while(1) {
        geracoes++;
        o = calculoRecursivo(ii, geracoes);
        p = calculoRecursivo(ii, geracoes + 1);
        double k = abss(o, p);
        if(k < 0.1) {
            break;
        }
    }
    o = calculoRecursivo(ii, geracoes);
    int asdas = o;
    printf("Populacao se estabiliza com %d individuos apos %d geracoes", asdas, geracoes);
}