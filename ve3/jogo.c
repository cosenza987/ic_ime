/*
TRABALHO RPG (VE 3)
Grupo: Ten De Togni, Ten Wade, Mateus Cosenza, Isaac Uchoa
Sistema operacional: Windows 10
*/

//libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//ctes
#define NOME_ARQUIVO_ENTRADA "entrada.txt"
#define NOME_ARQUIVO_SAIDA "saida.txt"

//enum
typedef enum _tipo_node {
    raiz, nao_terminal, terminal, tesouro_terminal, dead_end
} tipo_node;

//structs

typedef struct _node {
    int indice;
    char texto[1000];
    tipo_node tipo;
    char texto1[1000];
    char texto2[1000];
    char texto3[1000];
    int key, treasure;
    struct _node *ant;
    struct _node *prox2;
    struct _node *prox;
} node;

typedef struct _enemy {
    char nome[50];
    int level, hp, attack, defense, id, hp_max;
} enemy;

typedef struct _userr {
    char nome[50];
    int level, hp, attack, defense, race, hp_max;
    int haskey;
} userr;

node *ptr_inicio, *ptr_atual, *ptr_rand;
FILE *arquivo_saida;
enemy mariposa, rato, barata, macaco, cupim;
userr usuario;
int key, treasure, level = 0, morreu = 0, racee;
int mapa[23] = {0};

//prototipos
char *ler_nome(char *nome_arquivo);
node *buscar_node(int indice);
void insertar(int indice, char *texto, char *texto1, char *texto2, char *texto3, tipo_node tipo, node *antt);
void apagar();
void key_treasure();
void create_user(char naame[50]);
void update_user(int nivel, int race);
void create();
void inserir_mariposa();
void inserir_barata();
void inserir_cupim();
void inserir_macaco();
void inserir_rato();
void key_treasure();
void batalha(userr a1, enemy b2);
int max(int a, int b);
void printmap();
void limpar();
void printending();
void newending();
void bufferzar();

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, " "); //it aint working my dudes, no diacritics this time around
    key_treasure();
    insertar(0, "Saguao do Castelo", "A sua direita e a sua esquerda, de maneira simetrica, estao dois grandes corredores, ao lado dos quais estao duas escadas. Os corredores, entretanto, estao obstruidos por escombros, somente as escadas sao, com alguma dificuldade, transitaveis. ", "", "De volta nesse saguao... A saida nao eh mais uma possibilidade.", raiz, NULL);
    create();
    if(!(arquivo_saida = fopen(NOME_ARQUIVO_SAIDA, "w"))) {
        printf("ERRO AO ABRIR O ARQUIVO DE SAIDA!\n");
        return 1;
    }
    arquivo_saida = fopen(NOME_ARQUIVO_SAIDA, "w");
    char name[50];
    int opcao;
    ptr_atual = buscar_node(0);
    strcpy(name, ler_nome(NOME_ARQUIVO_ENTRADA));
    create_user(name);
    printf("Para uma melhor experiencia, recomenda-se deixar o terminal em tela cheia.\n");
    fprintf(arquivo_saida, "Para uma melhor experiencia, recomenda-se deixar o terminal em tela cheia.\n");
    printf("Pressione a tecla 'enter' para continuar\n");
    fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
    bufferzar();
    getchar();
    printf("Boa noite, %s. Voce esta desacordado e sente que varios 1's e 0's sao, por assim dizer, a materia-prima nao so do seu corpo, mas de toda a realidade\n", name);
    fprintf(arquivo_saida, "Boa noite, %s. Voce esta desacordado e sente que varios 1's e 0's sao, por assim dizer, a materia-prima nao so do seu corpo, mas de toda a realidade\n", name);
    printf("Mas nao ha tempo para devaneios tolos! Voce se ve diante de um castelo de aspecto imponente e sinistro, como resquicios do que um dia foi o centro de um grande imperio.\n");
    fprintf(arquivo_saida, "Mas nao ha tempo para devaneios tolos! Voce se ve diante de um castelo de aspecto imponente e sinistro, como resquicios do que um dia foi o centro de um grande imperio.\n");
    printf("Olhando ao redor, no entanto, voce so encontra ruinas. Voce decide se aproximar mais do castelo e, ao ver um grande portao entreaberto, entra por ele.\n");
    fprintf(arquivo_saida, "Olhando ao redor, no entanto, voce so encontra ruinas. Voce decide se aproximar mais do castelo e, ao ver um grande portao entreaberto, entra por ele.\n");
    printf("Ao passar pelo portao, voce se encontra em um salao amplo que um dia foi luxuoso, as paredes de marmore que um dia representaram forca e poder, agora estao cobertas com poeira. E mariposas! Mariposas por toda parte!\n");
    printf("Voce ve uma estatua destruida a sua frente e, mais a frente da estatua, a entrada de um corredor obstruido por escombros, com estruturas parecidas com torres que, depois de uma rapida observacao, voce constata estarem vazias, semelhantes a fossos. Assim, voce se lembra de uma antiga lenda, de que ha um tesouro magico escondido nesse castelo que ninguem nunca achou. Sera necessario algo para abri-lo?\n");
    printf("A sua frente, entretanto, voce ve, formando um semicirculo, 5 itens peculiares: um Walkie Talkie, uma Chave Inglesa, uma Bussola, um Tijolo e um Circuito Avulso. Fora isso, em um canto, voce tambem ve um pedaco de papel e carvao, sera que pode ser usado para voce nao se perder aqui?\n");
    printf("No meio do semicirculo ha uma inscricao: 'Escolha sabiamente o seu item, pois ele modificara a sua jornada.'\nEscolha um item:\n");
    printf("1 - Walkie Talkie (Garante um pouco mais de HP e uma maior probabilidade de fugir de batalhas)\n");
    printf("2 - Chave Inglesa (Garante um ataque bem mais elevado, porem com o custo de uma defesa pouco menor)\n");
    printf("3 - Bussola (Garante um pouco mais de defesa e uma maior probabilidade de fugir de batalhas)\n");
    printf("4 - Tijolo (Garante um pouco mais de ataque)\n");
    printf("5 - Circuito Avulso (Garante um HP bem mais elevado, porem com o custo de uma defesa pouco menor)\n");
    fprintf(arquivo_saida, "Ao passar pelo portao, voce se encontra em um salao amplo que um dia foi luxuoso, as paredes de marmore que um dia representaram forca e poder, agora estao cobertas com poeira. E mariposas! Mariposas por toda parte!\nVoce ve uma estatua destruida a sua frente e, mais a frente da estatua, a entrada de um corredor obstruido por escombros, com estruturas parecidas com torres que, depois de uma rapida observacao, voce constata estarem vazias, semelhantes a fossos. Assim, voce se lembra de uma antiga lenda, de que ha um tesouro magico escondido nesse castelo que ninguem nunca achou. Sera necessario algo para abri-lo?\n");
    fprintf(arquivo_saida, "A sua frente, entretanto, voce ve, formando um semicirculo, 5 itens peculiares: um Walkie Talkie, uma Chave Inglesa, uma Bussola, um Tijolo e um Circuito Avulso. Fora isso, em um canto, voce tambem ve um pedaco de papel e carvao, sera que pode ser usado para voce nao se perder aqui?\nNo meio do semicirculo ha uma inscricao: 'Escolha sabiamente o seu item, pois ele modificara a sua jornada.'\nEscolha um item:\n");
    fprintf(arquivo_saida, "1 - Walkie Talkie (Garante um pouco mais de HP e uma maior probabilidade de fugir de batalhas)\n2 - Chave Inglesa (Garante um ataque bem mais elevado, porem com o custo de uma defesa pouco menor)\n3 - Bussola (Garante um pouco mais de defesa e uma maior probabilidade de fugir de batalhas)\n4 - Tijolo (Garante um pouco mais de ataque)\n5 - Circuito Avulso (Garante um HP bem mais elevado, porem com o custo de uma defesa pouco menor)\n");
    while(1) {
        scanf("%d", &opcao);
        if(opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5) {
            break;
        } else {
            printf("Opcao invalida!\n");
            fprintf(arquivo_saida, "Opcao invalida!\n");
        }
    }
    racee = opcao;
    update_user(level, opcao);
    fprintf(arquivo_saida, "%d\n", opcao);
    while(1) {
        limpar();
        if(ptr_atual->tipo == tesouro_terminal) {
            int random = rand() % 100;
            if(random < 10) {
                switch(random) {
                    case 0:
                    case 1:
                        inserir_mariposa();
                        batalha(usuario, mariposa);
                        break;
                    case 2:
                    case 3:
                        inserir_rato();
                        batalha(usuario, rato);
                        break;
                    case 4:
                    case 5:
                        inserir_barata();
                        batalha(usuario, barata);
                        break;
                    case 6:
                    case 7:
                        inserir_cupim();
                        batalha(usuario, cupim);
                        break;
                    case 8:
                    case 9:
                        inserir_macaco();
                        batalha(usuario, macaco);
                        break;
                    default:
                        continue;
                }
            }
            if(mapa[ptr_atual->indice] == 0) {
                printf("Ao entrar no local pela primeira vez, voce o marca no seu mapa com o numero %d.\n", ptr_atual->indice);
                fprintf(arquivo_saida, "Ao entrar no local pela primeira vez, voce o marca no seu mapa com o numero %d.\n", ptr_atual->indice);
                printf("%s\n", ptr_atual->texto);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto);
            } else {
                printf("%s (Local de numero %d)\n", ptr_atual->texto, ptr_atual->indice);
                fprintf(arquivo_saida, "%s (Local de numero %d)\n", ptr_atual->texto, ptr_atual->indice);
            }
            if(mapa[ptr_atual->indice] == 0) {
                printf("%s\n", ptr_atual->texto1);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto1);
            } else {
                printf("%s\n", ptr_atual->texto3);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto3);
            }
            mapa[ptr_atual->indice] = 1;            
            printf("Parabens, voce conseguiu encontrar o tesouro!\n");
            fprintf(arquivo_saida, "Parabens, voce conseguiu encontrar o tesouro!\n");
            if(usuario.haskey == 0) {
                printf("Infelizmente, o tesouro esta trancando e voce nao possui a chave secreta para poder abrir.\n");
                printf("Voltando para o local anterior...\n");
                fprintf(arquivo_saida, "Infelizmente, o tesouro esta trancando e voce nao possui a chave secreta para poder abrir.\nVoltando para o local anterior...\n");
                ptr_atual = ptr_atual->ant;
                printf("Pressione a tecla 'enter' para continuar\n");
                fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
                bufferzar();
                getchar();
                continue;
            } else {
                printf("Voce possui a chave secreta para abrir o tesouro!\n");
                fprintf(arquivo_saida, "Voce possui a chave secreta para abrir o tesouro!\n");
                bufferzar();
                getchar();
                //printending();
                newending();
                printf("Obrigado por jogar.\n");
                fprintf(arquivo_saida, "Obrigado por jogar.\n");
                printf("Pressione a tecla 'enter' para fechar o jogo\n");
                fprintf(arquivo_saida, "Pressione a tecla 'enter' para fechar o jogo\n");
                getchar();
                fclose(arquivo_saida);
                return 0;
            }
        }
        limpar();
        if(ptr_atual->tipo == terminal || ptr_atual->tipo == dead_end) {
            int random = rand() % 100;
            if(random < 10) {
                switch(random) {
                    case 0:
                    case 1:
                        inserir_mariposa();
                        batalha(usuario, mariposa);
                        break;
                    case 2:
                    case 3:
                        inserir_rato();
                        batalha(usuario, rato);
                        break;
                    case 4:
                    case 5:
                        inserir_barata();
                        batalha(usuario, barata);
                        break;
                    case 6:
                    case 7:
                        inserir_cupim();
                        batalha(usuario, cupim);
                        break;
                    case 8:
                    case 9:
                        inserir_macaco();
                        batalha(usuario, macaco);
                        break;
                    default:
                        continue;
                }
            }
            if(mapa[ptr_atual->indice] == 0) {
                printf("Ao entrar no local pela primeira vez, voce o marca no seu mapa com o numero %d.\n", ptr_atual->indice);
                fprintf(arquivo_saida, "Ao entrar no local pela primeira vez, voce o marca no seu mapa com o numero %d.\n", ptr_atual->indice);
            }
            if(ptr_atual->key == 1 && usuario.haskey == 0) {
                printf("Parabens, voce conseguiu achar a chave secreta, agora consegue abrir o tesouro que esta perdido em algum canto desse castelo.\n");
                fprintf(arquivo_saida, "Parabens, voce conseguiu achar a chave secreta, agora consegue abrir o tesouro que esta perdido em algum canto desse castelo.\n");
                usuario.haskey = 1;
            }
            if(mapa[ptr_atual->indice] == 0) {
                printf("%s\n", ptr_atual->texto);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto);
                printf("%s\n", ptr_atual->texto1);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto1);
            } else {
                printf("%s (Local de numero %d)\n", ptr_atual->texto, ptr_atual->indice);
                fprintf(arquivo_saida, "%s (Local de numero %d)\n", ptr_atual->texto, ptr_atual->indice);
                printf("%s\n", ptr_atual->texto3);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto3);
            }
            mapa[ptr_atual->indice] = 1;
            printf("Apos uma melhor inspecao, ve-se que nao ha outra saida aqui sem ser por onde voce entrou.\n");
            printf("Voltando...\n");
            fprintf(arquivo_saida, "Apos uma melhor inspecao, ve-se que nao ha outra saida aqui sem ser por onde voce entrou.\nVoltando...\n");
            ptr_atual = ptr_atual->ant;
            printf("Pressione a tecla 'enter' para continuar\n");
            fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
            bufferzar();
            getchar();
        }
        limpar();
        if(ptr_atual->tipo == nao_terminal) {
            int random = rand() % 100, opcaoo;
            if(random < 10) {
                switch(random) {
                    case 0:
                    case 1:
                        inserir_mariposa();
                        batalha(usuario, mariposa);
                        break;
                    case 2:
                    case 3:
                        inserir_rato();
                        batalha(usuario, rato);
                        break;
                    case 4:
                    case 5:
                        inserir_barata();
                        batalha(usuario, barata);
                        break;
                    case 6:
                    case 7:
                        inserir_cupim();
                        batalha(usuario, cupim);
                        break;
                    case 8:
                    case 9:
                        inserir_macaco();
                        batalha(usuario, macaco);
                        break;
                    default:
                        continue;
                }
            }
            if(mapa[ptr_atual->indice] == 0) {
                printf("Ao entrar no local pela primeira vez, voce o marca no seu mapa com o numero %d.\n", ptr_atual->indice);
                fprintf(arquivo_saida, "Ao entrar no local pela primeira vez, voce o marca no seu mapa com o numero %d.\n", ptr_atual->indice);
            }
            if(ptr_atual->key == 1 && usuario.haskey == 0) {
                printf("Parabens, voce conseguiu achar a chave secreta, agora consegue abrir o tesouro que esta perdido em algum canto desse castelo.\n");
                fprintf(arquivo_saida, "Parabens, voce conseguiu achar a chave secreta, agora consegue abrir o tesouro que esta perdido em algum canto desse castelo.\n");
                usuario.haskey = 1;
            }
            if(mapa[ptr_atual->indice] == 0) {
                printf("%s\n", ptr_atual->texto);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto);
            } else {
                printf("%s (Local de numero %d)\n", ptr_atual->texto, ptr_atual->indice);
                fprintf(arquivo_saida, "%s (Local de numero %d)\n", ptr_atual->texto, ptr_atual->indice);
            }
            if(mapa[ptr_atual->indice] == 0 || (mapa[ptr_atual->prox->indice] == 0 && mapa[ptr_atual->prox2->indice] == 0)) {
                printf("%s\n", ptr_atual->texto1);
                printf("%s\n", ptr_atual->texto2);
                fprintf(arquivo_saida, "%s\n%s\n", ptr_atual->texto1, ptr_atual->texto2);
            } else {
                printf("%s\n", ptr_atual->texto3);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto3);
            }
            printf("O que deseja fazer?\n1 - Voltar para %s. (Marcado no mapa com numero %d)\n", ptr_atual->ant->texto, ptr_atual->ant->indice);
            fprintf(arquivo_saida, "O que deseja fazer?\n1 - Voltar para %s. (Marcado no mapa com numero %d)\n", ptr_atual->ant->texto, ptr_atual->ant->indice);
            if(mapa[ptr_atual->indice] == 0 || (mapa[ptr_atual->prox->indice] == 0 && mapa[ptr_atual->prox2->indice] == 0)) {
                printf("2 - Seguir para a primeira descricao.\n");
                fprintf(arquivo_saida, "2 - Seguir para a primeira descricao.\n");
                printf("3 - Seguir para a outra descricao.\n");
                fprintf(arquivo_saida, "3 - Seguir para a outra descricao.\n");
            } else {
                if(mapa[ptr_atual->prox->indice] == 0) {
                    printf("2 - Seguir para o outro local, desconhecido.\n");
                    fprintf(arquivo_saida, "2 - Seguir para o outro local, desconhecido.\n");
                } else {
                    printf("2 - Seguir para %s. (Marcado no mapa com numero %d)\n", ptr_atual->prox->texto, ptr_atual->prox->indice);
                    fprintf(arquivo_saida, "2 - Seguir para %s. (Marcado no mapa com numero %d)\n", ptr_atual->prox->texto, ptr_atual->prox->indice);
                }
                if(mapa[ptr_atual->prox2->indice] == 0) {
                    printf("3 - Seguir para o outro local, desconhecido.\n");
                    fprintf(arquivo_saida, "3 - Seguir para o outro local, desconhecido.\n");
                } else {
                    printf("3 - Seguir para %s. (Marcado no mapa com numero %d)\n", ptr_atual->prox2->texto, ptr_atual->prox2->indice);
                    fprintf(arquivo_saida, "3 - Seguir para %s. (Marcado no mapa com numero %d)\n", ptr_atual->prox2->texto, ptr_atual->prox2->indice);
                }
            }
            printf("4 - Olhar o mapa.\n");
            fprintf(arquivo_saida, "4 - Olhar o mapa.\n");
            mapa[ptr_atual->indice] = 1;
            scanf("%d", &opcaoo);
            switch(opcaoo) {
                case 1:
                    if(ptr_atual->ant == NULL) {
                        printf("A porta de entrada trancou, voce nao pode fugir do castelo\n");
                        fprintf(arquivo_saida, "A porta de entrada trancou, voce nao pode fugir do castelo\n");
                        printf("Pressione a tecla 'enter' para continuar\n");
                        fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
                        bufferzar();
                        getchar();
                        break;
                    }
                    ptr_atual = ptr_atual->ant;
                    break;
                case 2:
                    ptr_atual = ptr_atual->prox;
                    break;
                case 3:
                    ptr_atual = ptr_atual->prox2;
                    break;
                case 4:
                    printmap();
                    printf("Pressione a tecla 'enter' para continuar\n");
                    fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
                    bufferzar();
                    getchar();
                    break;
                default:
                    printf("opcao invalida\n");
                    fprintf(arquivo_saida, "opcao invalida!\n");
                    continue;
            }
            if(opcaoo == 1) {
                continue;
            }
        }
        if(ptr_atual->tipo == raiz) {
            if(mapa[ptr_atual->indice] == 0) {
                printf("Ao entrar no Saguao pela primeira vez, voce marca como a localizacao %d, bem no centro do papel.\n", ptr_atual->indice);
                fprintf(arquivo_saida, "Ao entrar no Saguao pela primeira vez, voce marca como a localizacao %d, bem no centro do papel.\n", ptr_atual->indice);
            }
            printf("%s\n", ptr_atual->texto);
            fprintf(arquivo_saida, "%s\n", ptr_atual->texto);
            if(mapa[ptr_atual->indice] == 0) {
                printf("%s\n", ptr_atual->texto1);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto1);
            } else {
                printf("%s\n", ptr_atual->texto3);
                fprintf(arquivo_saida, "%s\n", ptr_atual->texto3);
            }
            mapa[ptr_atual->indice] = 1;
            int opcaoo;
            printf("O que deseja fazer?\n1 - Subir a escada da esquerda.\n2 - Subir a escada da direita.\n3 - Olhar o mapa.\n");
            scanf("%d", &opcaoo);
            fprintf(arquivo_saida, "O que deseja fazer?\n1 - Subir a escada da esquerda.\n2 - Subir a escada da direita.\n3 - Olhar o mapa.\nO usuario escolheu a opcao: %d\n", opcaoo);
            switch(opcaoo) {
                case 1:
                    ptr_atual = ptr_atual->prox;
                    break;
                case 2:
                    ptr_atual = ptr_atual->prox2;
                    break;
                case 3:
                    printmap();
                    printf("Pressione a tecla 'enter' para continuar\n");
                    fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
                    bufferzar();
                    getchar();
                    break;
                default:
                    printf("Opcao invalida!\n");
                    fprintf(arquivo_saida, "Opcao invalida!\n");
                    continue;
            }
        }
        limpar();
    }
    fclose(arquivo_saida);
    return 0;
}

char *ler_nome(char *nome_arquivo) {
    FILE *arquivo_entrada;
    char *nome = NULL, buffer[100];
    arquivo_entrada = fopen(nome_arquivo, "r");
    if(arquivo_entrada == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DE ENTRADA!\n");
        fprintf(arquivo_saida, "ERRO AO ABRIR O ARQUIVO DE ENTRADA!\n");
        exit(1);        
    }
    if(!feof(arquivo_entrada)) {
        nome = fgets(buffer, 100, arquivo_entrada);
    }  
    fclose(arquivo_entrada);
    return nome;
}

node *buscar_node(int indice) {
    node *ptr_aux = ptr_inicio;
    if(ptr_aux == NULL) {
        return NULL;
    } else {
        while(ptr_aux != NULL) {
            if(ptr_aux->indice == indice) {
                return ptr_aux;
            }
            ptr_aux = ptr_aux->prox;
        }
    }
    return NULL;
}

void insertar(int indice, char *texto, char *texto1, char *texto2, char *texto3, tipo_node tipo, node *antt) {
    node *ptr = (node *) malloc(sizeof(node));
    if(ptr == NULL) {
        printf("ERRO NA ALOCACAO DE MEMORIA!\n");
        fprintf(arquivo_saida, "ERRO NA ALOCACAO DE MEMORIA!\n");
        fclose(arquivo_saida);
        exit(1);
    }
    ptr->indice = indice;
    strcpy(ptr->texto, texto);
    strcpy(ptr->texto1, texto1);
    strcpy(ptr->texto2, texto2);
    strcpy(ptr->texto3, texto3);
    ptr->tipo = tipo;
    ptr->ant = antt;
    ptr->prox = NULL;
    ptr->prox2 = NULL;
    node *ptr_aux = ptr_inicio;
    if(ptr_aux == NULL) {
        ptr_inicio = ptr;
    } else {
        ptr_rand = ptr;
    }
    if(key == indice) {
        ptr->key = 1;
    }
    if(treasure == indice) {
        ptr->treasure = 1;
        ptr->tipo = tesouro_terminal;
    }
    if(indice == 0) {
        ptr->tipo = raiz;
    }
}

void apagar() {
    node *ptr_aux = ptr_inicio;
    if(ptr_aux != NULL) {
        while(ptr_aux->prox != NULL) {
            if(ptr_aux->ant != NULL) {
                free(ptr_aux->ant);
            }
            ptr_aux = ptr_aux->prox;
        }
        if(ptr_aux->ant != NULL) {
            free(ptr_aux->ant);
        }
        free(ptr_aux);
    }
    ptr_inicio = NULL;
}

void create_user(char naame[50]) {
    strcpy(usuario.nome, naame);
    //usuario.level = 0;
    usuario.haskey = 0;
    return;
}

void update_user(int nivel, int race) {
    usuario.race = race;
    if(usuario.race == 1) { //this is the base level stuff to use as a reference for later races
        usuario.hp = (22 + (usuario.level * 4));
        usuario.attack = (2 + (usuario.level * 3));
        usuario.defense = (2 + (usuario.level * 3));
    } else if(usuario.race == 2) {
        usuario.hp = (20 + (usuario.level * 3));
        usuario.attack = (4 + (usuario.level * 5));
        usuario.defense = (2 + (usuario.level * 2));
    } else if(usuario.race == 3) {
        usuario.hp = (20 + (usuario.level * 3));
        usuario.attack = (2 + (usuario.level * 3));
        usuario.defense = (3 + (usuario.level * 4));
    } else if(usuario.race == 4) {
        usuario.hp = (22 + (usuario.level * 4));
        usuario.attack = (2 + (usuario.level * 3));
        usuario.defense = (2 + (usuario.level * 3));
    } else if(usuario.race == 5) {
        usuario.hp = (24 + (usuario.level * 5));
        usuario.attack = (2 + (usuario.level * 3));
        usuario.defense = (2 + (usuario.level * 2));
    }
    usuario.hp_max = usuario.hp;
    return;
}

void create() {
    node *ptr = (node *) malloc(sizeof(node));
    node *ptr2 = (node *) malloc(sizeof(node));
    node *ptr3 = (node *) malloc(sizeof(node));
    node *ptr4 = (node *) malloc(sizeof(node));
    node *ptr5 = (node *) malloc(sizeof(node));
    ptr = ptr_inicio;
    insertar(1, "Sala do Trono", "Voce sobe a escada desviando de alguns escombros e chega a uma sala grande, ao entrar nela, se depara com algumas subsalas, dentre as quais esta uma grande cadeira, quem sabe um trono. Voce vasculha a sala inteira e encontra apenas uma plaqueta suja com tres letras: G, E, N. Talvez esse seja o local onde o Rei do castelo ficava durante suas horas de trabalho.", "Voltando ao inicio da sala, voce ve dois caminhos: Pela direita, um corredor que leva a uma sala com uma inscricao indistinguivel de longe. Pela esquerda, um outro corredor leva voce a uma outra sala ampla.", "Ruinas de uma aparente 'Sala de Comando'", nao_terminal, ptr_inicio);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(2, "Grande Refeitorio", "Depois de andar pelos corredores, voce encontra uma entrada para um salao e entra por ela. O que voce encontra eh um salao grande, com mesas empoeiradas, estando algumas delas quebradas. Aparentemente, o salao era frequentado por muitas pessoas para as refeicoes.", "Ao lado da sala principal, voce ve uma sala anexa, semelhante a primeira, porem mais conservada. Voce pode subir para a sala anexa ou deixar o salao e subir uma longa escadaria.", "Ruinas de um antigo refeitorio (aparentemente para pessoas nao importantes)", nao_terminal, ptr_inicio);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr4 = ptr3;
    ptr = ptr2;
    insertar(3, "Sala do Conselheiro", "Voce decidiu ir na direcao da inscricao indistinguivel. Aos poucos, a inscricao vai tornando-se dinstiguivel e voce consegue ler 'ADMINISTRACAO'. Mas que fato curioso, veja voce, um castelo teria uma sala de admnistracao? Bem, pensar durante a exploracao de um castelo em ruinas nao parece ser uma atitude sensata, e melhor continuar explorando...", "Voce olha para a direita e ve um laboratorio escuro, olhando para a frente, voce ve uma sala com uma mesa e alguns acessorios sobre ela.", "Restos de uma sala, ve-se escrito 'ADMINISTRACAO'", nao_terminal, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(4, "Sala de Aprendizagem", "Tendo voce decidido a seguir o caminho da sala ampla, voce entra, luzes acendem automaticamente (seria isso um feitico?). Ao observar o cenario, voce percebe que as mesas, as cadeiras e um grande retangulo verde-escuro ao fim da sala lembram salas de aula de escolas... Espera, na epoca dos castelos ja existiam escolas? Algo de errado nao esta certo...", "Mais Longe, voce ve uma escada e uma salinha com uma inscricao indistiguivel de longe.", "Uma sala destruida, essas cadeiras fazem parecer de uma sala de aula...", nao_terminal, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr5 = ptr3;
    ptr = ptr2;
    insertar(7, "Sala dos Mestres", "Ao entrar no laboratorio escuro, suas pupilas se ajustam e voce consegue, as poucos, distinguir os moveis do laboratorio. Pilhas e mais pilhas de papel por todos os lados. Em um ponto iluminado sobre uma das mesas, voce consegue enxergar a palavra 'Mestrado'. Seria esse o local onde os mestres da corte passavam seus dias estudando?", "Olhando com atencao, voce ve uma porta que parece adentrar para um laboratorio ainda mais profundo, onde homens ainda mais sabios se recolhiam para estudar... Olhando de relance para o outro lado, voce ve uma porta com uma iluminacao leve, um mal cheiro forte e um fio de agua correndo pela porta.", "Um antigo laboratorio, aparentemente usado por alunos de mestrado", nao_terminal, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(8, "Sala Recreativa", "Ao entrar na sala da mesa, voce se depara com uma garrafinha de cafe e biscoitinhos. Mas que local familiar... sera aqui onde se reuniam os sabios do castelo? Sera que ainda ha algo para olhar aqui? O que?! Nao me diga que voce esta pensando em comer os biscoitinhos e tomar aquele cafe!!", "", "Ruinas de uma sala, parece um lugar onde algumas pessoas iam para descansar", dead_end, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr = ptr2;
    insertar(15, "Sala do Mestre dos Mestres", "Chegamos num lugar onde sao encontradas diversas maquinas e restos de computador. Pela complexidade dos equipamentos, somente pessoas com um grau alto de sabedoria poderia usa-los, devem ser pessoas que almejam um alto titulo academico. Apesar das estruturas impactantes, nao tem para onde ir.", "", "Um laboratorio destruido, esses restos aqui parecem de alguem cursando um doutorado...", terminal, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(16, "Banheiro Reservado", "Comodo apertado, porem, com diversas estruturas para realizar as necessidades. Como o ambiente eh pequeno e foram encontradas trancas nas portas, eh notorio que so um certo grupo de pessoas usavam as estruturas desse lugar, provavelmente, as pessoas com um grau de intelecto maior que as demais. O ambiente eh tao pequeno que nao existe nem porta.", "", "Restos de um banheiro... Ainda fede muito", terminal, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr = ptr5;
    insertar(9, "Escadas", "Longas escadarias em formato de caracol, degraus em marmore e corrimaos em ferro, hoje ja desgastados pela oxidacao.", "Ao subir, pela esquerda encontramos um lugar grande com varios destrocos em vidro, ja, pela direita, o que parece que sao ruinas em madeira.", "Um conjunto de escadas, sera que levam para outro pavimento?", nao_terminal, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(10, "Sala de Controle", "Lugar bem pequeno com pequenas mesas e cadeiras, poucas pessoas deviam utilizar o que esse comodo tinha a oferecer, porem pelos quadros e anotacoes encontrados, devia ser um setor voltado a administracao. Como aparenta ser um ambiente reservado, nao existe caminhos alem daqui.", "", "Ruinas de uma sala... Esses montes de telefones lembram uma secretaria", dead_end, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr = ptr2;
    insertar(17, "Sala do Alquimista", "Lugar muito amplo, com diversos balcoes. Ao observar melhor, sao encontrados diversos tipos de vidracarias e residuos de diversas misturas. Tudo indica que experimentos quimicos eram realizados nesse ambiente. Mas para que esses experimentos serviam? Essa duvida vai perdurar, assim como a resposta da grande pergunta 'para onde nos vamos?', nao existe nenhuma porta, entao temos que voltar.  ", "", "Restos de um laboratorio, varias garrafas espalhadas com simbolos quimicos", terminal, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(18, "Dormitorio Pequeno", "Nada aqui eh interessante, temos diversos armarios vazios e camas; uma sobre as outras. Porem eh encontrado certas placas degradadas com o tempo e eh possivel ler em uma delas que aqui so eram permitidas mulheres. Entao, eh de supor, que seria um ambiente para acolher diversas meninas dessa era.", "", "Um alojamento destruido, porem meio pequeno, poucas pessoas viviam aqui", terminal, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr = ptr4;
    insertar(5, "Pequeno Refeitorio", "Ao entrar na sala mais conservada, voce nota que ha uma sutil diferenca entre as duas salas, a primeira sala era a sala em que os lacaios do rei comiam, enquanto na outra, a mais conservada, os mais nobres subordinados da coroa comiam.", "Alem disso, voce olha para a direita e ve uma porta entreaberta de onde vem uma luz fraca. Olhando pela janela, voce ve uma longa escadaria.", "Restos de um refeitorio, mas esse parece ser mais elaborado", nao_terminal, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(6, "Ferreiro", "Ao entrar pelo laboratorio escuro, voce consegue acender uma tocha. Ao examinar com atencao, voce distingue estruturas grandes e complexas de metal. Seriam elas armamentos? Hummm, mas que estranho, esse castelo era um polo de avanco tecnologico. Seria mesmo este castelo um castelo medieval? Talvez voce esteja apenas delirando pelo tempo que passou no meio das ruinas... Ou sera que... Bem, nao ha tempo!!", "Na sua esquerda ha uma sala cheia de roupas na porta, na direita, um fosso com uma cabine dentro, seria um elevador?", "Um laboratorio, mas tambem cheio de pecas de armas?", nao_terminal, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr5 = ptr3;
    ptr = ptr2;
    insertar(11, "Cozinha", "Ambiente com muitos equipamentos em aco e bacias enormes, tambem em aco. Creio que essas bacias eram aquecidas nesses equipamentos para o preparo de diversos cardapios. A comida devia ser maravilhosa! ", "", "Isso daqui era certamente uma cozinha", dead_end, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(12, "Corredor", "Longo corredor em ruinas e teias de aranha, sem muito o que oferecer.", "Porem levam a dois caminhos distintos, a esquerda leva para um comodo relativamente grande com estruturas de madeira, e a direita para um grande salao com pinturas na parede.", "Um corredor aos pedacos, sera que leva para outro pavimento?", nao_terminal, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr = ptr3;
    insertar(19, "Dormitorio Grande", "Ambiente com estruturas que mais se parecem com camas, o diferente eh que eh uma em cima da outra! Tal ideia deve ter sido desenvolvida para otimizar o pequeno espaco, entao, provavelmente, estamos num lugar que um dia servia como um tipo de dormitorio. ", "", "Ruinas de um alojamento, mas esse daqui eh bem grande", terminal, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(20, "Sala das Personalidades", "Ao que parece, esta eh uma sala bem grande com grandes degraus. Bem provavel que esses degraus abrigavam certas cadeiras para aulas serem ministradas. Adicionalmente, duas figuras de personalidades estao em destaque nas largas paredes, talvez sejam cientistas de uma era longinqua. ", "", "Um anfiteatro bem grande, por que ha duas figuras vesgas no fundo?", terminal, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr = ptr5;
    insertar(13, "Sala de Banhos", "Pequeno ambiente com armarios e bancos. Alguns armarios, estao com pecas de roupas antigas e num ambiente anexado, varios canos saindo das paredes sao vistos, devem ser algum mecanismo para que saia agua, bem provavel que essa agua era utilizada para banhos devido a altura dos canos.", "", "Um vestiario arruinado, ha roupas por todo lado e canos despedacados.", dead_end, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(14, "Vao Vertical", "Entramos num pequeno cubiculo, porem com uma altura enorme. Ao olhar para cima, uma porta no andar superior esta entreaberta, acredito, que, em epocas passadas, pessoas eram transportadas para cima e para baixo nesse longo vao vertical por algum mecanismo.", "Depois de escalar e entrar nessa porta, observamos que a esquerda existem um enorme salao e a direita, uma sala menor com grandes prateleiras.", "Um simples elevador, sera que ainda funciona?", nao_terminal, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
    ptr = ptr3;
    insertar(21, "Sala de Reunioes", "Chegamos num ambiente enorme, com o que parece, um palco imponente e com centenas de assentos, onde um dia, abrigava multidoes de pessoas para algum tipo de conferencia ou palestra. Nota-se tambem, uma diversidade de estandartes em suas paredes que provavelmente significava algo sobre a soberania de algum territorio.", "", "Um salao gigante, parece um auditorio, com um mapa gigante de um antigo pais na parte de tras.", terminal, ptr);
    ptr2 = ptr_rand;
    ptr->prox = ptr2;
    insertar(22, "Sala dos Livros", "Ao adentrar no recinto, observa-se grandes prateleiras empoeiradas como uma vastidao de livros de diversos assuntos que vao desde matematica antiga ate relatos de historias militares.", "", "Somente ha livros rasgados e jogados no chao, certamente era uma biblioteca", terminal, ptr);
    ptr3 = ptr_rand;
    ptr->prox2 = ptr3;
}

void inserir_mariposa() {
    strcpy(mariposa.nome, "Mariposa 'GatGat'");
    mariposa.level = (rand() % (usuario.level + 2 + max(usuario.level - 2, 0) + 1));
    mariposa.hp = (rand() % (mariposa.level * 2 + 3)) + 11;
    mariposa.attack = (rand() % (mariposa.level * 3 + 1)) + 3;
    mariposa.defense = (rand() % (mariposa.level * 3 + 1)) + 2;
    mariposa.id = 0;
    mariposa.hp_max = mariposa.hp;
}

void inserir_rato() {
    strcpy(rato.nome, "Rato 'Chillis'");
    rato.level = (rand() % (usuario.level + 2 + max(usuario.level - 2, 0) + 1));
    rato.hp = (rand() % (rato.level * 3 + 5)) + 12;
    rato.attack = (rand() % (rato.level * 2 + 1)) + 2;
    rato.defense = (rand() % (rato.level * 3 + 1)) + 3;
    rato.id = 2;
    rato.hp_max = rato.hp;
}

void inserir_barata() {
    strcpy(barata.nome, "Barata 'Roach'");
    barata.level = (rand() % (usuario.level + 2 + max(usuario.level - 2, 0) + 1));
    barata.hp = (rand() % (barata.level * 3 + 5)) + 12;
    barata.attack = (rand() % (barata.level * 3 + 1)) + 2;
    barata.defense = (rand() % (barata.level * 5 + 1)) + 4;
    barata.id = 3;
    barata.hp_max = barata.hp;
}

void inserir_macaco() {
    strcpy(macaco.nome, "Macaco 'Martel'");
    macaco.level = (rand() % (usuario.level + 2 + max(usuario.level - 2, 0) + 1));
    macaco.hp = (rand() % (macaco.level * 4 + 5)) + 13;
    macaco.attack = (rand() % (macaco.level * 3 + 1)) + 3;
    macaco.defense = (rand() % (macaco.level * 3 + 1)) + 3;
    macaco.id = 4;
    macaco.hp_max = macaco.hp;
}

void inserir_cupim() {
    strcpy(cupim.nome, "Cupim Gigante 'TPA'");
    cupim.level = (rand() % (usuario.level + 2 + max(usuario.level - 2, 0) + 1));
    cupim.hp = (rand() % (cupim.level * 3 + 5)) + 12;
    cupim.attack = (rand() % (cupim.level * 3 + 1)) + 3;
    cupim.defense = (rand() % (cupim.level * 4 + 1)) + 4;
    cupim.id = 5;
    cupim.hp_max = cupim.hp;
}

void key_treasure() { //we could make the treasure only appear in the last slots?? to make the diagram better
    key = rand() % (12) + 3;
    treasure = rand() % (8) + 15;
    return;
}

void batalha(userr a1, enemy b2) {
    int rodada = 0;
    int hpuser = a1.hp;
    int hpenemy = b2.hp;
    printf("Voce acaba de entrar em uma batalha contra o %s!\n", b2.nome);
    fprintf(arquivo_saida, "Voce acaba de entrar em uma batalha o %s!\n", b2.nome);
    printf("O inimigo %s possui nivel %d, com HP %d, ataque %d e defesa %d.\n", b2.nome, b2.level, b2.hp_max, b2.attack, b2.defense);
    fprintf(arquivo_saida, "O inimigo %s possui nivel %d, com HP %d, ataque %d e defesa %d.\n", b2.nome, b2.level, b2.hp_max, b2.attack, b2.defense);
    while(hpuser > 0 && hpenemy > 0) {
        int option;
        printf("Pressione a tecla 'enter' para continuar\n");
        fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
        bufferzar();
        getchar();
        if(rodada != 0) {
            limpar();
        }
        printf("%s: HP = %d, Ataque = %d, Defesa = %d, Nivel = %d\n", a1.nome, hpuser, a1.attack, a1.defense, a1.level);
        fprintf(arquivo_saida, "HP = %d, Ataque = %d, Defesa = %d, nivel = %d\n", hpuser, a1.attack, a1.defense, a1.level);
        printf("%s: HP = %d, Ataque = %d, Defesa = %d, Nivel = %d\n", b2.nome, hpenemy, b2.attack, b2.defense, b2.level);
        fprintf(arquivo_saida, "%s: HP = %d, Ataque = %d, Defesa = %d, Nivel = %d\n", b2.nome, hpenemy, b2.attack, b2.defense, b2.level);
        printf("Voce esta na rodada %d\nO que deseja fazer?\n1 - Atacar\n2 - Tentar fugir\n", rodada);
        scanf("%d", &option);
        fprintf(arquivo_saida, "Voce esta na rodada %d\nO que deseja fazer?\n1 - Atacar\n2 - Tentar fugir\nO usuario escolheu a opcao: %d\n", rodada, option);
        if(option == 1) {
            int crit = (rand() % 100), critt = 0;
            printf("Atacando!\n");
            fprintf(arquivo_saida, "Atacando\n");
            if(crit < 30) {
                printf("Ataque critico!\n");
                fprintf(arquivo_saida, "Ataque critico!\n");
                critt = 1;
            }
            if(critt == 1) {
                printf("Voce deu %d de dano enquanto o inimigo %s deu %d de dano\n", (max(a1.attack - b2.defense, 2)) * 2, b2.nome, (max(b2.attack - a1.defense, 1)));
                fprintf(arquivo_saida, "Voce deu %d de dano enquanto o inimigo %s deu %d de dano\n", (max(a1.attack - b2.defense, 1)) * 2, b2.nome, (max(b2.attack - a1.defense, 1)));
                hpenemy = hpenemy - ((max(a1.attack - b2.defense, 2)) * 2);
                hpuser = hpuser - (max(b2.attack - a1.defense, 1));
            } else {
                printf("Voce deu %d de dano enquanto o inimigo %s deu %d de dano\n", (max(a1.attack - b2.defense, 2)), b2.nome, (max(b2.attack - a1.defense, 1)));
                fprintf(arquivo_saida, "Voce deu %d de dano enquanto o inimigo %s deu %d de dano\n", (max(a1.attack - b2.defense, 2)), b2.nome, (max(b2.attack - a1.defense, 1)));
                hpenemy = hpenemy - ((max(a1.attack - b2.defense, 2)));
                hpuser = hpuser - (max(b2.attack - a1.defense, 1));
            }
            printf("O seu HP ao final da rodada eh: %d de %d\nHP do inimigo ao final da rodada eh: %d de %d\n", max(hpuser, 0), a1.hp_max, max(hpenemy, 0), b2.hp_max);
            fprintf(arquivo_saida, "O seu HP ao final da rodada eh: %d de %d\nHP do inimigo ao final da rodada eh: %d de %d\n", max(hpuser, 0), a1.hp_max, max(hpenemy, 0), b2.hp_max);
            rodada++;
            //printf("Pressione a tecla 'enter' para continuar\n");
            //fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
            getchar();
            continue;
        } else if(option == 2) {
            int fugir = (rand() % 100);
            if(a1.race == 3 || a1.race == 1) {
                if(fugir < 70) {
                    printf("Voce conseguiu fugir com sucesso!\n");
                    fprintf(arquivo_saida, "Voce conseguiu fugir com sucesso!\n");
                    printf("Voce agora descansa para poder recuperar o seu HP.\n");
                    fprintf(arquivo_saida, "Voce agora descansa para poder recuperar o seu HP.\n");
                    printf("Pressione a tecla 'enter' para continuar\n");
                    fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
                    bufferzar();
                    getchar();
                    limpar();
                    return;
                } else {
                    printf("Nao conseguiu fugir!\n");
                    fprintf(arquivo_saida, "Nao conseguiu fugir!\n");
                    printf("O inimigo %s consegue te atacar! Ele te da %d de dano.\n", b2.nome, (max(b2.attack - a1.defense, 2)));
                    fprintf(arquivo_saida, "O inimigo %s consegue te atacar! Ele te da %d de dano.\n", b2.nome, (max(b2.attack - a1.defense, 2)));
                    hpuser = hpuser - (max(b2.attack - a1.defense, 2));
                    printf("Seu HP final: %d de %d\n", max(hpuser, 0), a1.hp_max);
                    fprintf(arquivo_saida, "Seu HP final: %d de %d\n", max(hpuser, 0), a1.hp_max);
                    rodada++;
                }
            } else {
                if(fugir < 50) {
                    printf("Voce conseguiu fugir com sucesso!\n");
                    fprintf(arquivo_saida, "Voce conseguiu fugir com sucesso!\n");
                    printf("Pressione a tecla 'enter' para continuar\n");
                    fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
                    bufferzar();
                    getchar();
                    limpar();
                    return;
                } else {
                    printf("Nao conseguiu fugir!\n");
                    fprintf(arquivo_saida, "Nao conseguiu fugir!\n");
                    printf("O inimigo %s consegue te atacar! Ele te da %d de dano.\n", b2.nome, (max(b2.attack - a1.defense, 2)));
                    fprintf(arquivo_saida, "O inimigo %s consegue te atacar! Ele te da %d de dano.\n", b2.nome, (max(b2.attack - a1.defense, 2)));
                    hpuser = hpuser - (max(b2.attack - a1.defense, 2));
                    printf("Seu HP final: %d de %d\n", max(hpuser, 0), a1.hp_max);
                    fprintf(arquivo_saida, "Seu HP final: %d de %d\n", max(hpuser, 0), a1.hp_max);
                    rodada++;
                }
            }
        } else {
            printf("Opcao errada!\n");
            fprintf(arquivo_saida, "Opcao errada!\n");
        }
    }
    if(hpuser <= 0) {
        if(hpenemy <= 0) {
            printf("Por pouco voce escapou dessa! Tera que descansar por um bom tempo para se recuperar.\n");
            fprintf(arquivo_saida, "Por pouco voce escapou dessa! Tera que descansar por um bom tempo para se recuperar.\n");
            bufferzar();
            getchar();
            return;
        }
        printf("Voce morreu! Infelizmente o jogo acaba por aqui.\n");
        printf("Obrigado por jogar!\n");
        fprintf(arquivo_saida, "Voce morreu! Infelizmente o jogo acaba por aqui.\nObrigado por jogar!\n");
        fclose(arquivo_saida);
        exit(2);
    }
    usuario.level++;
    printf("Parabens, voce subiu de nivel, agora eh nivel %d\n", usuario.level);
    fprintf(arquivo_saida, "Parabens, voce subiu de nivel, agora eh nivel %d\n", usuario.level);
    update_user(usuario.level, racee);
    printf("Apos essa ardua batalha, voce descansa para recuperar completamente o seu HP.\n");\
    fprintf(arquivo_saida, "Apos essa ardua batalha, voce descansa para recuperar completamente o seu HP.\n");
    printf("Pressione a tecla 'enter' para continuar\n");
    fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
    bufferzar();
    getchar();
    limpar();
    return;
}

int max(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

void printmap() {
    //first line
    if(mapa[18] == 1) {
        printf("______ ______ ______ ______ ______ ______");
        fprintf(arquivo_saida, "______ ______ ______ ______ ______ ______");
    } else {
        printf("______ ______ ______ ______ ______ ______");
        fprintf(arquivo_saida, "______ ______ ______ ______ ______ ______");
    }
    if(mapa[19] == 1) {
        printf(" ______\n");
        fprintf(arquivo_saida, " ______\n");
    } else {
        printf(" ______\n");
        fprintf(arquivo_saida, " ______\n");
    }
    //second line
    if(mapa[18] == 1) {
        printf("|    | |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
        fprintf(arquivo_saida, "|    | |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
    } else {
        printf("|XXXX| |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
    }
    if(mapa[19] == 1) {
        printf(" |    |\n");
        fprintf(arquivo_saida, " |    |\n");
    } else {
        printf(" |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX|\n");
    }
    //third line
    if(mapa[18] == 1) {
        printf("| 18 | |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
        fprintf(arquivo_saida, "| 18 | |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
    } else {
        printf("|XXXX| |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
    }
    if(mapa[19] == 1) {
        printf(" | 19 |\n");
        fprintf(arquivo_saida, " | 19 |\n");
    } else {
        printf(" |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX|\n");
    }
    //fourth line
    if(mapa[18] == 1) {
        printf("|_  _| |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
        fprintf(arquivo_saida, "|_  _| |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
    } else {
        printf("|XXXX| |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX| |XXXX| |XXXX| |XXXX|");
    }
    if(mapa[19] == 1) {
        printf(" |_  _|\n");
        fprintf(arquivo_saida, " |_  _|\n");
    } else {
        printf(" |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX|\n");
    }
    //fifth line
    if(mapa[18] == 1) {
        printf("__||__ ______ ______ ______ ______ ______");
        fprintf(arquivo_saida, "__||__ ______ ______ ______ ______ ______");
    } else {
        printf("______ ______ ______ ______ ______ ______");
        fprintf(arquivo_saida, "______ ______ ______ ______ ______ ______");
    }
    if(mapa[19] == 1) {
        printf(" __||__\n");
        fprintf(arquivo_saida, " __||__\n");
    } else {
        printf(" ______\n");
        fprintf(arquivo_saida, " ______\n");
    }
    //sixth line
    if(mapa[9] == 1) {
        printf("|    |");
        fprintf(arquivo_saida, "|    |");
    } else {
        printf("|XXXX|");
        fprintf(arquivo_saida, "|XXXX|");
    }
    if(mapa[4] == 1) {
        printf(" |    |");
        fprintf(arquivo_saida, " |    |");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[10] == 1) {
        printf(" |    | |XXXX|");
        fprintf(arquivo_saida, " |    | |XXXX|");
    } else {
        printf(" |XXXX| |XXXX|");
        fprintf(arquivo_saida, " |XXXX| |XXXX|");
    }
    if(mapa[11] == 1) {
        printf(" |    |");
        fprintf(arquivo_saida, " |    |");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[5] == 1) {
        printf(" |    |");
        fprintf(arquivo_saida, " |    |");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[12] == 1) {
        printf(" |    |\n");
        fprintf(arquivo_saida, " |    |\n");
    } else {
        printf(" |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX|\n");
    }
    //seventh line
    if(mapa[9] == 1) {
        printf("| 09 ===");
        fprintf(arquivo_saida, "| 09 ===");
    } else {
        printf("|XXXX| |");
        fprintf(arquivo_saida, "|XXXX| |");
    }
    if(mapa[4] == 1) {
        printf(" 04 ");
        fprintf(arquivo_saida, " 04 ");
    } else {
        printf("XXXX");
        fprintf(arquivo_saida, "XXXX");
    }
    if(mapa[10] == 1) {
        printf("=== 10 | |XXXX|");
        fprintf(arquivo_saida, "=== 10 | |XXXX|");
    } else {
        printf("| |XXXX| |XXXX|");
        fprintf(arquivo_saida, "| |XXXX| |XXXX|");
    }
    if(mapa[11] == 1) {
        printf(" | 11 ===");
        fprintf(arquivo_saida, " | 11 ===");
    } else {
        printf(" |XXXX| |");
        fprintf(arquivo_saida, " |XXXX| |");
    }
    if(mapa[5] == 1) {
        printf(" 05 ");
        fprintf(arquivo_saida, " 05 ");
    } else {
        printf("XXXX");
        fprintf(arquivo_saida, "XXXX");
    }
    if(mapa[12] == 1) {
        printf("=== 12 |\n");
        fprintf(arquivo_saida, "=== 12 |\n");
    } else {
        printf("| |XXXX|\n");
        fprintf(arquivo_saida, "| |XXXX|\n");
    }
    //eighth line
    if(mapa[9] == 1) {
        if(mapa[17] == 1) {
            printf("|_  _|");
            fprintf(arquivo_saida, "|_  _|");
        } else {
            printf("|____|");
            fprintf(arquivo_saida, "|____|");
        }
    } else {
        printf("|XXXX|");
        fprintf(arquivo_saida, "|XXXX|");
    }
    if(mapa[4] == 1) {
        printf(" |_  _|");
        fprintf(arquivo_saida, " |_  _|");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[10] == 1) {
        printf(" |____| |XXXX|");
        fprintf(arquivo_saida, " |____| |XXXX|");
    } else {
        printf(" |XXXX| |XXXX|");
        fprintf(arquivo_saida, " |XXXX| |XXXX|");
    }
    if(mapa[11] == 1) {
        printf(" |____|");
        fprintf(arquivo_saida, " |____|");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[5] == 1) {
        printf(" |_  _|");
        fprintf(arquivo_saida, " |_  _|");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[12] == 1) {
        if(mapa[20] == 1) {
            printf(" |_  _|\n");
            fprintf(arquivo_saida, " |_  _|\n");
        } else {
            printf(" |____|\n");
            fprintf(arquivo_saida, " |____|\n");
        }
    } else {
        printf(" |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX|\n");
    }
    //ninth line
    if(mapa[17] == 1) {
        printf("__||__ ");
        fprintf(arquivo_saida, "__||__ ");
    } else {
        printf("______ ");
        fprintf(arquivo_saida, "______ ");
    }
    if(mapa[4] == 1) {
        printf("__||__ ______ ______ ______");
        fprintf(arquivo_saida, "__||__ ______ ______ ______");
    } else {
        printf("______ ______ ______ ______");
        fprintf(arquivo_saida, "______ ______ ______ ______");
    }
    if(mapa[5] == 1) {
        printf(" __||__");
        fprintf(arquivo_saida, " __||__");
    } else {
        printf(" ______");
        fprintf(arquivo_saida, " ______");
    }
    if(mapa[20] == 1) {
        printf(" __||__\n");
        fprintf(arquivo_saida, " __||__\n");
    } else {
        printf(" ______\n");
        fprintf(arquivo_saida, " ______\n");
    }
    //tenth line
    if(mapa[17] == 1) {
        printf("|    |");
        fprintf(arquivo_saida, "|    |");
    } else {
        printf("|XXXX|");
        fprintf(arquivo_saida, "|XXXX|");
    }
    if(mapa[1] == 1) {
        printf(" |    |");
        fprintf(arquivo_saida, " |    |");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    printf(" |    | |    | |    |");
    fprintf(arquivo_saida, " |    | |    | |    |");
    if(mapa[2] == 1) {
        printf(" |    |");
        fprintf(arquivo_saida, " |    |");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[20] == 1 ) {
        printf(" |    |\n");
        fprintf(arquivo_saida, " |    |\n");
    } else {
        printf(" |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX|\n");
    }
    //eleventh line
    if(mapa[17] == 1) {
        printf("| 17 |");
        fprintf(arquivo_saida, "| 17 |");
    } else {
        printf("|XXXX|");
        fprintf(arquivo_saida, "|XXXX|");
    }
    if(mapa[1] == 1) {
        printf(" | 01 =");
        fprintf(arquivo_saida, " | 01 =");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    printf("========= 00 ========");
    fprintf(arquivo_saida, "========= 00 ========");
    if(mapa[2] == 1) {
        printf("== 02 |");
        fprintf(arquivo_saida, "== 02 |");
    } else {
        printf("=|XXXX|");
        fprintf(arquivo_saida, "=|XXXX|");
    }
    if(mapa[20] == 1) {
        printf(" | 20 |\n");
        fprintf(arquivo_saida, " | 20 |\n");
    } else {
        printf(" |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX|\n");
    }
    //twelfth line
    if(mapa[17] == 1) {
        printf("|____|");
        fprintf(arquivo_saida, "|____|");
    } else {
        printf("|XXXX|");
        fprintf(arquivo_saida, "|XXXX|");
    }
    if(mapa[1] == 1) {
        if(mapa[3] == 1) {
            printf(" |_  _|");
            fprintf(arquivo_saida, " |_  _|");
        } else {
            printf(" |____|");
            fprintf(arquivo_saida, " |____|");
        }
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    printf(" |____| |____| |____|");
    fprintf(arquivo_saida, " |____| |____| |____|");
    if(mapa[2] == 1) {
        if(mapa[6] == 1) {
            printf(" |_  _|");
            fprintf(arquivo_saida, " |_  _|");
        } else {
            printf(" |____|");
            fprintf(arquivo_saida, " |____|");
        }
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[20] == 1) {
        printf(" |____|\n");
        fprintf(arquivo_saida, " |____|\n");
    } else {
        printf(" |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX|\n");
    }
    //thirteenth line
    if(mapa[3] == 1) {
        printf("______ __||__ ______ ______ ______ ");
        fprintf(arquivo_saida, "______ __||__ ______ ______ ______ ");
    } else {
        printf("______ ______ ______ ______ ______ ");
        fprintf(arquivo_saida, "______ ______ ______ ______ ______ ");
    }
    if(mapa[6] == 1) {
        printf("__||__ ______\n");
        fprintf(arquivo_saida, "__||__ ______\n");
    } else {
        printf("______ ______\n");
        fprintf(arquivo_saida, "______ ______\n");
    }
    //fourteenth line
    if(mapa[3] == 1) {
        printf("|XXXX| | || | ");
        fprintf(arquivo_saida, "|XXXX| | || | ");
    } else {
        printf("|XXXX| |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| ");
    }
    if(mapa[15] == 1) {
        printf("|    | |XXXX|");
        fprintf(arquivo_saida, "|    | |XXXX|");
    } else {
        printf("|XXXX| |XXXX|");
        fprintf(arquivo_saida, "|XXXX| |XXXX|");
    }
    if(mapa[22] == 1) {
        printf(" |    |");
        fprintf(arquivo_saida, " |    |");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[6] == 1) {
        printf(" | || | |XXXX|\n");
        fprintf(arquivo_saida, " | || | |XXXX|\n");
    } else {
        printf(" |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX| |XXXX|\n");
    }
    //fifteenth line
    if(mapa[3] == 1) {
        printf("|XXXX| | || | ");
        fprintf(arquivo_saida, "|XXXX| | || | ");
    } else {
        printf("|XXXX| |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| ");
    }
    if(mapa[15] == 1) {
        printf("| 15 | |XXXX|");
        fprintf(arquivo_saida, "| 15 | |XXXX|");
    } else {
        printf("|XXXX| |XXXX|");
        fprintf(arquivo_saida, "|XXXX| |XXXX|");
    }
    if(mapa[22] == 1) {
        printf(" | 22 |");
        fprintf(arquivo_saida, " | 22 |");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[6] == 1) {
        printf(" | || | |XXXX|\n");
        fprintf(arquivo_saida, " | || | |XXXX|\n");
    } else {
        printf(" |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX| |XXXX|\n");
    }
    //sixteenth line
    if(mapa[3] == 1) {
        printf("|XXXX| |_||_| ");
        fprintf(arquivo_saida, "|XXXX| |_||_| ");
    } else {
        printf("|XXXX| |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| ");
    }
    if(mapa[15] == 1) {
        printf("|_  _| |XXXX|");
        fprintf(arquivo_saida, "|_  _| |XXXX|");
    } else {
        printf("|XXXX| |XXXX|");
        fprintf(arquivo_saida, "|XXXX| |XXXX|");
    }
    if(mapa[22] == 1) {
        printf(" |____|");
        fprintf(arquivo_saida, " |____|");
    } else {
        printf(" |XXXX|");
        fprintf(arquivo_saida, " |XXXX|");
    }
    if(mapa[6] == 1) {
        printf(" |_||_| |XXXX|\n");
        fprintf(arquivo_saida, " |_||_| |XXXX|\n");
    } else {
        printf(" |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, " |XXXX| |XXXX|\n");
    }
    //seventeenth line
    printf("______ ");
    fprintf(arquivo_saida, "______ ");
    if(mapa[3] == 1) {
        printf("__||__ ");
        fprintf(arquivo_saida, "__||__ ");
    } else {
        printf("______ ");
        fprintf(arquivo_saida, "______ ");
    }
    if(mapa[15] == 1) {
        printf("__||__ ");
        fprintf(arquivo_saida, "__||__ ");
    } else {
        printf("______ ");
        fprintf(arquivo_saida, "______ ");
    }
    printf("______ ");
    fprintf(arquivo_saida, "______ ");
    if(mapa[22] == 1 ) {
        printf("__||__ ");
        fprintf(arquivo_saida, "__||__ ");
    } else {
        printf("______ ");
        fprintf(arquivo_saida, "______ ");
    }
    if(mapa[6] == 1) {
        printf("__||__ ");
        fprintf(arquivo_saida, "__||__ ");
    } else {
        printf("______ ");
        fprintf(arquivo_saida, "______ ");
    }
    printf("______\n");
    fprintf(arquivo_saida, "______\n");
    //eighteenth line
    if(mapa[8] == 1) {
        printf("|    | ");
        fprintf(arquivo_saida, "|    | ");
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    if(mapa[3] == 1) {
        printf("|    | ");
        fprintf(arquivo_saida, "|    | ");
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    if(mapa[7] == 1) {
        printf("|    | |XXXX| ");
        fprintf(arquivo_saida, "|    | |XXXX| ");
    } else {
        printf("|XXXX| |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| ");
    }
    if(mapa[14] == 1) {
        printf("|    | ");
        fprintf(arquivo_saida, "|    | ");
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    if(mapa[6] == 1) {
        printf("|    | ");
        fprintf(arquivo_saida, "|    | ");
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    if(mapa[13] == 1) {
        printf("|    |\n");
        fprintf(arquivo_saida, "|    |\n");
    } else {
        printf("|XXXX|\n");
        fprintf(arquivo_saida, "|XXXX|\n");
    }
    //nineteenth line
    if(mapa[8] == 1) {
        printf("| 08 ===");
        fprintf(arquivo_saida, "| 08 ===");
    } else {
        printf("|XXXX| |");
        fprintf(arquivo_saida, "|XXXX| |");
    }
    if(mapa[3] == 1) {
        printf(" 03 ");
        fprintf(arquivo_saida, " 03 ");
    } else {
        printf("XXXX");
        fprintf(arquivo_saida, "XXXX");
    }
    if(mapa[7] == 1) {
        printf("=== 07 | |XXXX| ");
        fprintf(arquivo_saida, "=== 07 | |XXXX| ");
    } else {
        printf("| |XXXX| |XXXX| ");
        fprintf(arquivo_saida, "| |XXXX| |XXXX| ");
    }
    if(mapa[14] == 1) {
        printf("| 14 ===");
        fprintf(arquivo_saida, "| 14 ===");
    } else {
        printf("|XXXX| |");
        fprintf(arquivo_saida, "|XXXX| |");
    }
    if(mapa[6] == 1) {
        printf(" 06 ");
        fprintf(arquivo_saida, " 06 ");
    } else {
        printf("XXXX");
        fprintf(arquivo_saida, "XXXX");
    }
    if(mapa[13] == 1) {
        printf("=== 13 |\n");
        fprintf(arquivo_saida, "=== 13 |\n");
    } else {
        printf("| |XXXX|\n");
        fprintf(arquivo_saida, "| |XXXX|\n");
    }
    //twentieth line
    if(mapa[8] == 1) {
        printf("|____| ");
        fprintf(arquivo_saida, "|____| ");
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    if(mapa[3] == 1) {
        printf("|____| ");
        fprintf(arquivo_saida, "|____| ");
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    if(mapa[7] == 1) {
        if(mapa[16] == 1) {
            printf("|_  _| ");
            fprintf(arquivo_saida, "|_  _| ");
        } else {
            printf("|____| ");
            fprintf(arquivo_saida, "|____| ");
        }
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    printf("|XXXX| ");
    fprintf(arquivo_saida, "|XXXX| ");
    if(mapa[14] == 1) {
        if(mapa[21] == 1) {
            printf("|_  _| ");
            fprintf(arquivo_saida, "|_  _| ");
        } else {
            printf("|____| ");
            fprintf(arquivo_saida, "|____| ");
        }
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    if(mapa[6] == 1) {
        printf("|____| ");
        fprintf(arquivo_saida, "|____| ");
    } else {
        printf("|XXXX| ");
        fprintf(arquivo_saida, "|XXXX| ");
    }
    if(mapa[13] == 1) {
        printf("|____|\n");
        fprintf(arquivo_saida, "|____|\n");
    } else {
        printf("|XXXX|\n");
        fprintf(arquivo_saida, "|XXXX|\n");
    }
    //twenty first line
    if(mapa[16] == 1) {
        printf("______ ______ __||__ ______ ");
        fprintf(arquivo_saida, "______ ______ __||__ ______ ");
    } else {
        printf("______ ______ ______ ______ ");
        fprintf(arquivo_saida, "______ ______ ______ ______ ");
    }
    if(mapa[21] == 1) {
        printf("__||__ ______ ______\n");
        fprintf(arquivo_saida, "__||__ ______ ______\n");
    } else {
        printf("______ ______ ______\n");
        fprintf(arquivo_saida, "______ ______ ______\n");
    }
    //twenty second line
    if(mapa[16] == 1) {
        printf("|XXXX| |XXXX| |    | |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |    | |XXXX| ");
    } else {
        printf("|XXXX| |XXXX| |XXXX| |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX| |XXXX| ");
    }
    if(mapa[21] == 1) {
        printf("|    | |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, "|    | |XXXX| |XXXX|\n");
    } else {
        printf("|XXXX| |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX|\n");
    }
    //twenty third line
    if(mapa[16] == 1) {
        printf("|XXXX| |XXXX| | 16 | |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| | 16 | |XXXX| ");
    } else {
        printf("|XXXX| |XXXX| |XXXX| |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX| |XXXX| ");
    }
    if(mapa[21] == 1) {
        printf("| 21 | |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, "| 21 | |XXXX| |XXXX|\n");
    } else {
        printf("|XXXX| |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX|\n");
    }
    //twenty fourth line
    if(mapa[16] == 1) {
        printf("|XXXX| |XXXX| |    | |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |    | |XXXX| ");
    } else {
        printf("|XXXX| |XXXX| |XXXX| |XXXX| ");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX| |XXXX| ");
    }
    if(mapa[21] == 1) {
        printf("|    | |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, "|    | |XXXX| |XXXX|\n");
    } else {
        printf("|XXXX| |XXXX| |XXXX|\n");
        fprintf(arquivo_saida, "|XXXX| |XXXX| |XXXX|\n");
    }
    getchar();
    return;
}

void limpar() {
    #ifdef __linux__
    system("clear");
    #elif defined WIN32
    system("cls");
    #else
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    #endif
}

void printending() {
    printf("Ao abrir, muitos itens sao encontrados como moedas de ouro com formatos de engrenagens e um castelo cunhado em seu centro, documentos e diversos papeis. Porem, um desses papeis lhe chama sua atencao. Nele esta escrito 'Maior Escola de Engenharia do Brasil' acima de uma foto aerea de um grande castelo que se assemelha ao que estamos!\n");
    fprintf(arquivo_saida, "Ao abrir, muitos itens sao encontrados como moedas de ouro com formatos de engrenagens e um castelo cunhado em seu centro, documentos e diversos papeis. Porem, um desses papeis lhe chama sua atencao. Nele esta escrito 'Maior Escola de Engenharia do Brasil' acima de uma foto aerea de um grande castelo que se assemelha ao que estamos!\n");
    printf("Pressione a tecla 'enter' para continuar\n");
    fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
    bufferzar();
    getchar();
    printf("Revirando mais os documentos, descobrimos que estamos no Instituto Militar de Engenharia e as salas que encontramos eram bem especificas. Assim, pode-se associar cada local em que passamos com outro demarcado aqui. Fazendo a conexao do que foi visto ao longo da jornada, pode-se fazer a seguinte lista:\n");
    fprintf(arquivo_saida, "Revirando mais os documentos, descobrimos que estamos no Instituto Militar de Engenharia e as salas que encontramos eram bem especificas. Assim, pode-se associar cada local em que passamos com outro demarcado aqui. Fazendo a conexao do que foi visto ao longo da jornada, pode-se fazer a seguinte lista:\n");
    printf("Pressione a tecla 'enter' para continuar\n");
    fprintf(arquivo_saida, "Pressione a tecla 'enter' para continuar\n");
    printf("Salao do IME - Saguao do Castelo\n");
    fprintf(arquivo_saida, "Salao do IME - Saguao do Castelo\n");
    if(mapa[1] == 1) {
        printf("Sala de Comando - Sala do Trono\n");
        fprintf(arquivo_saida, "Sala de Comando - Sala do Trono\n");
    }
    if(mapa[2] == 1) {
        printf("Rancho dos Alunos - Grande Refeitorio\n");
        fprintf(arquivo_saida, "Rancho dos Alunos - Grande Refeitorio\n");
    }
    if(mapa[3] == 1) {
        printf("Administracao - Sala do Conselheiro\n");
        fprintf(arquivo_saida, "Administracao - Sala do Conselheiro\n");
    }
    if(mapa[4] == 1) {
        printf("Salas de Aula - Salas de Aprendizagem\n");
        fprintf(arquivo_saida, "Salas de Aula - Salas de Aprendizagem\n");
    }
    if(mapa[5] == 1) {
        printf("Rancho dos Oficiais - Pequeno Refeitorio\n");
        fprintf(arquivo_saida, "Rancho dos Oficiais - Pequeno Refeitorio\n");
    }
    if(mapa[6] == 1) {
        printf("Laboratorio de Armamento - Ferreiro\n");
        fprintf(arquivo_saida, "Laboratorio de Armamento - Ferreiro\n");
    }
    if(mapa[7] == 1) {
        printf("Laboratorio do Mestrado - Sala dos Mestres\n");
        fprintf(arquivo_saida, "Laboratorio do Mestrado - Sala dos Mestres\n");
    }
    if(mapa[8] == 1) {
        printf("Sala dos Professores - Sala Recreativa\n");
        fprintf(arquivo_saida, "Sala dos Professores - Sala Recreativa\n");
    }
    if(mapa[9] == 1) {
        printf("Escadas - Escadas\n");
        fprintf(arquivo_saida, "Escadas - Escadas\n");
    }
    if(mapa[10] == 1) {
        printf("Secretaria - Sala de Controle\n");
        fprintf(arquivo_saida, "Secretaria - Sala de Controle\n");
    }
    if(mapa[11] == 1) {
        printf("Cozinha - Cozinha\n");
        fprintf(arquivo_saida, "Cozinha - Cozinha\n");
    }
    if(mapa[12] == 1) {
        printf("Corredor da Ala - Corredor\n");
        fprintf(arquivo_saida, "Corredor da Ala - Corredor\n");
    }
    if(mapa[13] == 1) {
        printf("Vestiario - Sala de Banhos\n");
        fprintf(arquivo_saida, "Vestiario - Sala de Banhos\n");
    }
    if(mapa[14] == 1) {
        printf("Elevador - Vao Vertical\n");
        fprintf(arquivo_saida, "Elevador - Vao Vertical\n");
    }
    if(mapa[15] == 1) {
        printf("Laboratorio do Doutorado - Sala do Mestre dos Mestres\n");
        fprintf(arquivo_saida, "Laboratorio do Doutorado - Sala do Mestre dos Mestres\n");
    }
    if(mapa[16] == 1) {
        printf("Banheiro dos Professores - Banheiro Reservado\n");
        fprintf(arquivo_saida, "Banheiro dos Professores - Banheiro Reservado\n");
    }
    if(mapa[17] == 1) {
        printf("Laboratorio de Quimica - Sala do Alquimista\n");
        fprintf(arquivo_saida, "Laboratorio de Quimica - Sala do Alquimista\n");
    }
    if(mapa[18] == 1) {
        printf("Alojamento Feminino - Dormitorio Pequeno\n");
        fprintf(arquivo_saida, "Alojamento Feminino - Dormitorio Pequeno\n");
    }
    if(mapa[19] == 1) {
        printf("Alojamento Masculino - Dormitorio Grande\n");
        fprintf(arquivo_saida, "Alojamento Masculino - Dormitorio Grande\n");
    }
    if(mapa[20] == 1) {
        printf("Anfiteatro - Sala das Personalidades\n");
        fprintf(arquivo_saida, "Anfiteatro - Sala das Personalidades\n");
    }
    if(mapa[21] == 1) {
        printf("Auditorio - Sala de Reunioes\n");
        fprintf(arquivo_saida, "Auditorio - Sala de Reunioes\n");
    }
    if(mapa[22] == 1) {
        printf("Biblioteca - Sala dos Livros\n");
        fprintf(arquivo_saida, "Biblioteca - Sala dos Livros\n");
    }
    return;
}

void newending() {
    printf("Ao abrir a caixa do tesouro, a caixa voa das suas maos por ocasiao de uma explosao verde-oliva. Depois de se recuperar e recobrar os sentidos, voce ve o espectro de um militar barbudo. Voce esta prestes a chamar o militar de varado e acochambrao, ate que, por intervencao divina, voce percebe que e o espectro de Ricardo Franco, o Patrono dos engenheiros militares. O espectro se aproxima de voce e comeca a falar\n");
    fprintf(arquivo_saida, "Ao abrir a caixa do tesouro, a caixa voa das suas maos por ocasiao de uma explosao verde-oliva. Depois de se recuperar e recobrar os sentidos, voce ve o espectro de um militar barbudo. Voce esta prestes a chamar o militar de varado e acochambrao, ate que, por intervencao divina, voce percebe que e o espectro de Ricardo Franco, o Patrono dos engenheiros militares. O espectro se aproxima de voce e comeca a falar\n");
    bufferzar();
    getchar();
    printf("Espectro de Ricardo Franco:\n");
    fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
    bufferzar();
    getchar();
    printf("Ora Ora, quem diria, um paisano me libertou de minha prisao. Nao sei ao certo o que houve com esta honrosa casa, mas desde que alguns militares da aeronautica vieram fazer uma visita suspeita eu perdi a consciencia. Venha ca, o que voce tem ai na mao?\n");
    fprintf(arquivo_saida, "Ora Ora, quem diria, um paisano me libertou de minha prisao. Nao sei ao certo o que houve com esta honrosa casa, mas desde que alguns militares da aeronautica vieram fazer uma visita suspeita eu perdi a consciencia. Venha ca, o que voce tem ai na mao?\n");
    bufferzar();
    getchar();
    if(usuario.race == 4) { //tijolo
        printf("(Ricardo Franco examina sua mao e pega o tijolo)\n");
        fprintf(arquivo_saida, "(Ricardo Franco examina sua mao e pega o tijolo)\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Humm, um tijolo, venha aqui, venha aqui.\n");
        fprintf(arquivo_saida, "Humm, um tijolo, venha aqui, venha aqui.\n");
        bufferzar();
        getchar();
        printf("Ricardo Franco se aproxima de uma parede com um buraco no formato do seu tijolo e encaixa o tijolo. De repente, uma onda de luz irradia o ambiente restaurando todas as ruinas. O 'Castelo' retoma sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        fprintf(arquivo_saida, "Ricardo Franco se aproxima de uma parede com um buraco no formato do seu tijolo e encaixa o tijolo. De repente, uma onda de luz irradia o ambiente restaurando todas as ruinas. O 'Castelo' retoma sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram lancar o feitico em minha honrosa casa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido o tijolo, voce vai ter o privilegio de fazer o curso de fortificacao e construcao! Ate mais, paisano!\n");
        fprintf(arquivo_saida, "Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram lancar o feitico em minha honrosa casa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido o tijolo, voce vai ter o privilegio de fazer o curso de fortificacao e construcao! Ate mais, paisano!\n");
    } else if(usuario.race == 1) { //walkie tlakie
        printf("(Ricardo Franco examina sua mao e pega o walkie talkie)\n");
        fprintf(arquivo_saida, "(Ricardo Franco examina sua mao e pega o walkie talkie)\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Humm, um radinho, venha aqui, venha aqui.\n");
        fprintf(arquivo_saida, "Humm, um radinho, venha aqui, venha aqui.\n");
        bufferzar();
        getchar();
        printf("Ricardo Franco aperta o botao vermelho e aciona os lancadores de misseis controlados pelo sistema ASTROS II. De repente, uma parede de misseis teleguiados vem em direcao ao IME e destroi um campo de forca. O 'Castelo' retoma sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        fprintf(arquivo_saida, "Ricardo Franco aperta o botao vermelho e aciona os lancadores de misseis controlados pelo sistema ASTROS II. De repente, uma parede de misseis teleguiados vem em direcao ao IME e destroi um campo de forca. O 'Castelo' retoma sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram colocar um campo de forca que deixava em ruinas a minha honrosa casa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido o walkie talkie, voce vai ter o privilegio de fazer o curso de telecomunicacoes! Ate mais, paisano!\n");
        fprintf(arquivo_saida, "Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram colocar um campo de forca que deixava em ruinas a minha honrosa casa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido o walkie talkie, voce vai ter o privilegio de fazer o curso de telecomunicacoes! Ate mais, paisano!\n");
    } else if(usuario.race == 3) { //bussola
        printf("(Ricardo Franco examina sua mao e pega a bussola)\n");
        fprintf(arquivo_saida, "(Ricardo Franco examina sua mao e pega a bussola)\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Humm, uma bussola, venha aqui, venha aqui.\n");
        fprintf(arquivo_saida, "Humm, uma bussola, venha aqui, venha aqui.\n");
        bufferzar();
        getchar();
        printf("Ricardo Franco pega a bussola e brada 'DIRECAO AO INFINITO, OOORDINARIO!! MAARCHE!'. Depois de marchar por 1792km sob a orientacao da bussola, voce e o espetro chegam na praia vermelha e encontram o IME em sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        fprintf(arquivo_saida, "Ricardo Franco pega a bussola e brada 'DIRECAO AO INFINITO, OOORDINARIO!! MAARCHE!'. Depois de marchar por 1792km sob a orientacao da bussola, voce e o espetro chegam na praia vermelha e encontram o IME em sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram me aprisionar em uma replica de minha honrosa casa em ruinas. Logo que despertei, pensei ser aquela a minha casa e estava com a moral muito baixa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido a bussola, voce vai ter o privilegio de fazer curso de Engenharia cartografica! Ate mais, paisano!\n");
        fprintf(arquivo_saida, "Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram me aprisionar em uma replica de minha honrosa casa em ruinas. Logo que despertei, pensei ser aquela a minha casa e estava com a moral muito baixa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido a bussola, voce vai ter o privilegio de fazer curso de Engenharia cartografica! Ate mais, paisano!\n");
    } else if(usuario.race == 2) { //chave inglesa
        printf("(Ricardo Franco examina sua mao e pega a chave inglesa)\n");
        fprintf(arquivo_saida, "(Ricardo Franco examina sua mao e pega a chave inglesa)\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Humm, uma chave inglesa, venha aqui, venha aqui.\n");
        fprintf(arquivo_saida, "Humm, uma chave inglesa, venha aqui, venha aqui.\n");
        bufferzar();
        getchar();
        printf("Ricardo Franco pega a chave inglesa, desce ate o terreo e comeca a consertar um blindado, trata-se do Guarani, o blindado projetado por engenheiros do IME.O espectro leva voce, dentro do blindado, ate Sao Jose dos Campos e vai tirar satisfacoes com alguns alunos de la. Depois de algumas mijadas, os alunos do outro instituto admitem seu erro e voltam com o espectro para o IME. O espectro manda os alunos limparem toda a bagunca enquanto sentam e levantam ao silvo de apito. O 'Castelo' retoma sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        fprintf(arquivo_saida, "Ricardo Franco pega a chave inglesa, desce ate o terreo e comeca a consertar um blindado, trata-se do Guarani, o blindado projetado por engenheiros do IME.O espectro leva voce, dentro do blindado, ate Sao Jose dos Campos e vai tirar satisfacoes com alguns alunos de la. Depois de algumas mijadas, os alunos do outro instituto admitem seu erro e voltam com o espectro para o IME. O espectro manda os alunos limparem toda a bagunca enquanto sentam e levantam ao silvo de apito. O 'Castelo' retoma sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram vandalizar a minha honrosa casa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido a chave inglesa, voce vai ter o privilegio de fazer curso de Engenharia Mecanica! Ate mais, paisano!\n");
        fprintf(arquivo_saida, "Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram vandalizar a minha honrosa casa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido a chave inglesa, voce vai ter o privilegio de fazer curso de Engenharia Mecanica! Ate mais, paisano!\n");
    } else if(usuario.race == 5) { //circuito avulso
        printf("(Ricardo Franco examina sua mao e pega a circuito avulso)\n");
        fprintf(arquivo_saida, "(Ricardo Franco examina sua mao e pega a circuito avulso)\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Humm, um circuito avulso, venha aqui, venha aqui.\n");
        fprintf(arquivo_saida, "Humm, um circuito avulso, venha aqui, venha aqui.\n");
        bufferzar();
        getchar();
        printf("Ricardo Franco acopla o circuito avulso a uma estrutura maior e uma luz e irradiada e uma voz robotica fala, em bom tom: 'Sistema Iteano de arruinamento desabilitado. O 'Castelo' retoma sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        fprintf(arquivo_saida, "Ricardo Franco acopla o circuito avulso a uma estrutura maior e uma luz e irradiada e uma voz robotica fala, em bom tom: 'Sistema Iteano de arruinamento desabilitado. O 'Castelo' retoma sua forma plena e Ricardo Franco brada 'VIBRA ALUNO!!!'\n");
        bufferzar();
        getchar();
        printf("Espectro de Ricardo Franco:\n");
        fprintf(arquivo_saida, "Espectro de Ricardo Franco:\n");
        bufferzar();
        getchar();
        printf("Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram montar um sistema eletronico a fim de deixar em ruinas a minha honrosa casa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido o circuito avulso, voce vai ter o privilegio de fazer qualquer curso da SE/3! Ate mais, paisano!\n");
        fprintf(arquivo_saida, "Ora Ora, agora tudo ficou claro, lembro-me bem do que aconteceu. Depois do IME conseguir passar 25 anos consecutivos sendo a melhor faculdade de engenharia do Brasil, alguns alunos de um instituto de outra forca decidiram montar um sistema eletronico a fim de deixar em ruinas a minha honrosa casa. Gracas a voce, querido paisano, o Instituto Militar de Engenharia, Real academia de Artilharia, Fortificacao e Desenho, 1792, vai poder voltar a assumir sua posicao na realidade academica nacional. Por ter escolhido o circuito avulso, voce vai ter o privilegio de fazer qualquer curso da SE/3! Ate mais, paisano!\n");
    }
}

void bufferzar() {
    #ifdef __linux__
    //__fpurge(stdin);
    /*while((c = getchar()) != '\n' && c != EOF)
	//	 discard  ; */
    #elif defined WIN32
    fflush(stdin);
    #else
    char c;
    while((c = getchar()) != '\n' && c != EOF) {
        /* discard */ ;
    }
    #endif
}

