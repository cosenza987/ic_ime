//sistema operacional: windows 10
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char a[20][30], f[20][30], p[20][30];

void strlower(char str[]);
void insert();
void printar();
void finda();
void findp();

int main() {
    insert();
    int opcao = -1;
    printf("Banco de Dados do Cinefilo!\n");
    while(opcao != 3) {
        printf("\nEscolha uma opcao.\n");
        printf("\t\t0 - Listar toda a base de dados.\n");
        printf("\t\t1 - Buscar ator.\n");
        printf("\t\t2 - Buscar personagem.\n");
        printf("\t\t3 - Sair.\n");
        scanf("%d", &opcao);
        switch(opcao) {
            case 0:
                printar();
                break;
            case 1:
                finda();
                break;
            case 2:
                findp();
                break;
            case 3:
                printf("Terminado. Volte sempre!\n");
                continue;
            default:
                printf("Opcao invalida!\n");
        }
    }
    return 0;
}

//para facilitar a busca
void strlower(char str[]) {
    for(int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}

//insercao da base de dados
void insert() {
    strcpy(a[1], "Harrison Ford");
    strcpy(f[1], "Star Wars");
    strcpy(p[1], "Hans Solo");
    strcpy(a[2], "Julia Roberts");
    strcpy(f[2], "Uma Linda Mulher");
    strcpy(p[2], "Vivian Ward");
    strcpy(a[3], "Anthony Hopkins");
    strcpy(f[3], "O Silencio dos Inocentes");
    strcpy(p[3], "Hannibal Lecter");
    strcpy(a[4], "Jim Carrey");
    strcpy(f[4], "O Maskara");
    strcpy(p[4], "Stanley Ipkiss");
    strcpy(a[5], "Jim Carrey");
    strcpy(f[5], "O Maskara");
    strcpy(p[5], "Maskara");
    strcpy(a[6], "Julia Roberts");
    strcpy(f[6], "O Sorriso de Mona Lisa");
    strcpy(p[6], "Katherine Watson");
    strcpy(a[7], "Sean Connery");
    strcpy(f[7], "007 Contra Goldfinger");
    strcpy(p[7], "James Bond");
    strcpy(a[8], "Harrison Ford");
    strcpy(f[8], "Templo da Perdicao");
    strcpy(p[8], "Indiana Jones");
    strcpy(a[9], "Anthony Hopkins");
    strcpy(f[9], "Dragao Vermelho");
    strcpy(p[9], "Hannibal Lecter");
    strcpy(a[10], "Harrison Ford");
    strcpy(f[10], "Ultima Cruzada");
    strcpy(p[10], "Indiana Jones");
    strcpy(a[11], "Jim Carrey");
    strcpy(f[11], "O Show de Truman");
    strcpy(p[11], "Truman Brubank");
    strcpy(a[12], "Anthoney Hopkins");
    strcpy(f[12], "Dois Papas");
    strcpy(p[12], "Papa Bento XVI");
    strcpy(a[13], "Julia Roberts");
    strcpy(f[13], "Comer, Rezar e Amar");
    strcpy(p[13], "Elizabeth Gilbert");
    strcpy(a[14], "Daniel Craig");
    strcpy(f[14], "007 - Cassino Royale");
    strcpy(p[14], "James Bond");
}

//impressa do banco de dados
void printar() {
    //linha 1
    for(int i = 0; i < 28; i++) {
        printf(" ");
    }
    printf("Ator/Atriz");
    for(int i = 0; i < 30; i++) {
        printf(" ");
    }
    printf("Filme");
    for(int i = 0; i < 25; i++) {
        printf(" ");
    }
    printf("Personagem\n");
    //resto das linhas da pra loopar
    for(int k = 1; k <= 14; k++) {
        if(k < 10) {
            printf(" %d-", k);
        } else {
            printf("%d-", k);
        }
        for(int i = 0; i < 35 - strlen(a[k]); i++) {
            printf(" ");
        }
        printf("%s", a[k]);
        for(int i = 0; i < 35 - strlen(f[k]); i++) {
            printf(" ");
        }
        printf("%s", f[k]);
        for(int i = 0; i < 35 - strlen(p[k]); i++) {
            printf(" ");
        }
        printf("%s\n", p[k]);
    }
}

//busca de ator
void finda() {
    char entrada[30], temp[30], bb;
    int ind = 0, poss[15];
    printf("Digite o nome do ator/atriz: ");
    scanf("%c", &bb);
    scanf("%[^\n]", entrada);
    strlower(entrada);
    for(int i = 1; i <= 14; i++) {
        strcpy(temp, a[i]);
        strlower(temp);
        if(strcmp(temp, entrada) == 0) {
            if(ind == 0) {
                for(int k = 0; k < 30; k++) {
                    printf(" ");
                }
                printf("Filme");
                for(int k = 0; k < 25; k++) {
                    printf(" ");
                }
                printf("Personagem\n");
            }
            for(int k = 0; k < 35 - strlen(f[i]); k++) {
                printf(" ");
            }
            printf("%s", f[i]);
            for(int k = 0; k < 35 - strlen(p[i]); k++) {
                printf(" ");
            }
            printf("%s\n", p[i]);
            ind++;
        }
    }
    if(ind == 0) {
        printf("Nao encontrado!\n");
    }
}

//busca de personagem
void findp() {
    char entrada[30], temp[30], bb;
    int ind = 0, poss[15];
    printf("Digite o nome do personagem: ");
    scanf("%c", &bb);
    scanf("%[^\n]", entrada);
    strlower(entrada);
    for(int i = 1; i <= 14; i++) {
        strcpy(temp, p[i]);
        strlower(temp);
        if(strcmp(temp, entrada) == 0) {
            if(ind == 0) {
                for(int k = 0; k < 30; k++) {
                    printf(" ");
                }
                printf("Filme");
                for(int k = 0; k < 31; k++) {
                    printf(" ");
                }
                printf("Ator\n");
            }
            for(int k = 0; k < 35 - strlen(f[i]); k++) {
                printf(" ");
            }
            printf("%s", f[i]);
            for(int k = 0; k < 35 - strlen(a[i]); k++) {
                printf(" ");
            }
            printf("%s\n", a[i]);
            ind++;
        }
    }
    if(ind == 0) {
        printf("Nao encontrado!\n");
    }
}