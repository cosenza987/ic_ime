#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    int al_code;
    long long int cpf;
    char al_nome[50];
    int num_dis;
    int* lista_dis_id;
} aluno;

typedef struct disciplina {
    int dis_id;
    char nome_dis[50];
    char nome_professor[50];
    int creditos;
} disciplina;

typedef struct periodo {
    int period_id;
    int num_al;
    int num_dis;
    aluno* lista_al_matriculados;
    disciplina* lista_dis_matriculadas;
} periodo;

//Criar minha lista,inicialmente vazia,de periodos:
periodo* lista_period = NULL;
int num_period = 0;

void salvar() {
    FILE *f;
    f = fopen("dados.txt", "w");
    fprintf(f, "%d\n", num_period);
    for(int i = 0; i < num_period; i++) {
        fprintf(f, "%d %d %d\n", lista_period[i].period_id, lista_period[i].num_al, lista_period[i].num_dis);
        for(int j = 0; j < lista_period[i].num_al; j++) {
            aluno cural = lista_period[i].lista_al_matriculados[j];
            fprintf(f, "%d %lld %d\n", cural.al_code, cural.cpf, cural.num_dis);
            fprintf(f, "%s\n", cural.al_nome);
            for(int k = 0; k < cural.num_dis; k++) {
                if(k == cural.num_dis - 1) {
                    fprintf(f, "%d\n", cural.lista_dis_id[k]);
                } else {
                    fprintf(f, "%d ", cural.lista_dis_id[k]);
                }
            }
        }
        for(int j = 0; j < lista_period[i].num_dis; j++) {
            disciplina curd = lista_period[i].lista_dis_matriculadas[j];
            fprintf(f, "%d %d\n", curd.dis_id, curd.creditos);
            fprintf(f, "%s\n", curd.nome_dis);
            fprintf(f, "%s\n", curd.nome_professor);
        }
    }
    fclose(f);
}

void recuperar() {
    FILE *f;
    f = fopen("dados.txt", "r");
    if(feof(f)) {
        return;
    }
    fscanf(f, "%d\n", &num_period);
    lista_period = malloc(num_period * sizeof(periodo));
    for(int i = 0; i < num_period; i++) {
        fscanf(f, "%d %d %d\n", &lista_period[i].period_id, &lista_period[i].num_al, &lista_period[i].num_dis);
        lista_period[i].lista_al_matriculados = malloc(lista_period[i].num_al * sizeof(aluno));
        lista_period[i].lista_dis_matriculadas = malloc(lista_period[i].num_dis * sizeof(disciplina));
        for(int j = 0; j < lista_period[i].num_al; j++) {
            aluno cural;
            fscanf(f, "%d %lld %d\n", &cural.al_code, &cural.cpf, &cural.num_dis);
            fscanf(f, " %[^\n]", cural.al_nome);
            cural.lista_dis_id = malloc(cural.num_dis * sizeof(int));
            for(int k = 0; k < cural.num_dis; k++) {
                fscanf(f, "%d", &cural.lista_dis_id[k]);
            }
            lista_period[i].lista_al_matriculados[j] = cural;
        }
        for(int j = 0; j < lista_period[i].num_dis; j++) {
            disciplina curd;
            fscanf(f, "%d %d\n", &curd.dis_id, &curd.creditos);
            fscanf(f, " %[^\n]", curd.nome_dis);
            fscanf(f, " %[^\n]", curd.nome_professor);
            lista_period[i].lista_dis_matriculadas[j] = curd;
        }
    }
    fclose(f);
}

void alunos_matriculados(int period_id) {
    //Period Index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    if (lista_period[period_index].num_al == 0) {
        printf("Nenhum aluno cadastrado no periodo...\n");
        return;
    }
    else {
        printf("Os alunos matriculados nesse periodo sao:\n");
        for (int i = 0;i < lista_period[period_index].num_al;i++) {
            printf("\n");
            printf("Nome Completo: %s\n", lista_period[period_index].lista_al_matriculados[i].al_nome);
            printf("CPF: %lld\n", lista_period[period_index].lista_al_matriculados[i].cpf);
            printf("Codigo de Matricula: %d\n", lista_period[period_index].lista_al_matriculados[i].al_code);
            printf("Cursando %d disciplinas\n", lista_period[period_index].lista_al_matriculados[i].num_dis);
            printf("Codigo das disciplinas cursadas: ");
            for (int j = 0;j < lista_period[period_index].lista_al_matriculados[i].num_dis;j++) {
                printf("%d ", lista_period[period_index].lista_al_matriculados[i].lista_dis_id[j]);
            }
            printf("\n");
        }
    }
}
void removerPeriod(int period_id) {
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    if (period_index == -1) {
        printf("Periodo nao cadastrado...\n");
        return;
    }
    //Caso o periodo seja o ultimo da lista:
    int last_index = num_period - 1;
    if (last_index == period_index) {
        num_period--;
        for (int i = 0;i < lista_period[period_index].num_al;i++) {
            free(lista_period[period_index].lista_al_matriculados[i].lista_dis_id);
        }
        free(lista_period[period_index].lista_al_matriculados);
        free(lista_period[period_index].lista_dis_matriculadas);
        printf("Periodo removido com sucesso.\n");
        return;
    }
    else {
        //Jogar o lista[last_index] pro lista[al_index]
        lista_period[period_index].period_id = lista_period[last_index].period_id;
        lista_period[period_index].num_al = lista_period[last_index].num_al;
        lista_period[period_index].num_dis = lista_period[last_index].num_dis;
        //Lista de Al matriculados:
        lista_period[period_index].lista_al_matriculados = (aluno*)realloc(lista_period[period_index].lista_al_matriculados, (lista_period[last_index].num_al) * sizeof(aluno));
        for (int i = 0;i < lista_period[last_index].num_al;i++) {
            lista_period[period_index].lista_al_matriculados[i].lista_dis_id = (int*)realloc(lista_period[period_index].lista_al_matriculados[i].lista_dis_id, (lista_period[last_index].lista_al_matriculados[i].num_dis) * sizeof(int));
            for (int j = 0;j < lista_period[last_index].lista_al_matriculados[i].num_dis;j++) {
                lista_period[period_index].lista_al_matriculados[i].lista_dis_id[j] = lista_period[last_index].lista_al_matriculados[i].lista_dis_id[j];
            }
            lista_period[period_index].lista_al_matriculados[i].al_code = lista_period[last_index].lista_al_matriculados[i].al_code;
            lista_period[period_index].lista_al_matriculados[i].cpf = lista_period[last_index].lista_al_matriculados[i].cpf;
            lista_period[period_index].lista_al_matriculados[i].num_dis = lista_period[last_index].lista_al_matriculados[i].num_dis;
            strcpy(lista_period[period_index].lista_al_matriculados[i].al_nome, lista_period[last_index].lista_al_matriculados[i].al_nome);
        }
        //Lista de Dis matriculadas:
        lista_period[period_index].lista_dis_matriculadas = (disciplina*)realloc(lista_period[period_index].lista_dis_matriculadas, (lista_period[last_index].num_dis) * sizeof(disciplina));
        for (int i = 0;i < lista_period[last_index].num_dis;i++) {
            lista_period[period_index].lista_dis_matriculadas[i].dis_id = lista_period[last_index].lista_dis_matriculadas[i].dis_id;
            lista_period[period_index].lista_dis_matriculadas[i].creditos = lista_period[period_index].lista_dis_matriculadas[i].creditos;
            strcpy(lista_period[period_index].lista_dis_matriculadas[i].nome_dis, lista_period[last_index].lista_dis_matriculadas[i].nome_dis);
            strcpy(lista_period[period_index].lista_dis_matriculadas[i].nome_professor, lista_period[last_index].lista_dis_matriculadas[i].nome_professor);
        }
        //Free no lista_period[last index]:
        num_period--;
        for (int i = 0;i < lista_period[last_index].num_al;i++) {
            free(lista_period[last_index].lista_al_matriculados[i].lista_dis_id);
        }
        free(lista_period[last_index].lista_al_matriculados);
        free(lista_period[last_index].lista_dis_matriculadas);
        printf("Periodo removido com sucesso.\n");
        return;
    }
    return;
}

void removerDisPeriod(int period_id, int dis_id) {
    //Procurar period index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Procurar disciplina no periodo index:
    int dis_index = -1;
    for (int i = 0;i < lista_period[period_index].num_dis;i++) {
        if (lista_period[period_index].lista_dis_matriculadas[i].dis_id == dis_id) {
            dis_index = i;
            break;
        }
    }
    //Caso nao ache:
    if (dis_index == -1) {
        printf("A disciplina nao esta matriculada no periodo...\n");
        return;
    }
    //Caso ache:
    //Caso esteja no final da lista:
    if (dis_index == (lista_period[period_index].num_dis) - 1) {
        lista_period[period_index].num_dis--;
        lista_period[period_index].lista_dis_matriculadas = (disciplina*)realloc(lista_period[period_index].lista_dis_matriculadas, (lista_period[period_index].num_dis) * sizeof(disciplina));
        printf("A disciplina foi removida do periodo com sucesso.\n");
        return;
    }
    //Caso nao esteja no final da lista:
    else {
        lista_period[period_index].num_dis--;
        int last_index = lista_period[period_index].num_dis;
        lista_period[period_index].lista_dis_matriculadas[dis_index].dis_id = lista_period[period_index].lista_dis_matriculadas[last_index].dis_id;
        lista_period[period_index].lista_dis_matriculadas[dis_index].creditos = lista_period[period_index].lista_dis_matriculadas[last_index].creditos;
        strcpy(lista_period[period_index].lista_dis_matriculadas[dis_index].nome_dis, lista_period[period_index].lista_dis_matriculadas[last_index].nome_dis);
        strcpy(lista_period[period_index].lista_dis_matriculadas[dis_index].nome_professor, lista_period[period_index].lista_dis_matriculadas[last_index].nome_professor);
        lista_period[period_index].lista_dis_matriculadas = (disciplina*)realloc(lista_period[period_index].lista_dis_matriculadas, (lista_period[period_index].num_dis) * sizeof(disciplina));
        printf("A disciplina foi removida do periodo com sucesso.\n");
        return;
    }
    return;
}
void cadastrarDisciplina(int period_id, int dis_id, char nome_dis[], char nome_professor[], int creditos) {
    //Period Index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Verificar se a disciplina ja esta cadastrada:
    for (int i = 0;i < lista_period[period_index].num_dis;i++) {
        if (lista_period[period_index].lista_dis_matriculadas[i].dis_id == dis_id) {
            printf("Disciplina ja cadastrada...\n");
            return;
        }
    }
    //Caso contrario, vamos cadastra-la:
    //Realocando espaco na memoria:
    int dis_index = lista_period[period_index].num_dis;
    lista_period[period_index].num_dis++;
    lista_period[period_index].lista_dis_matriculadas = (disciplina*)realloc(lista_period[period_index].lista_dis_matriculadas, (lista_period[period_index].num_dis) * sizeof(disciplina));
    //Salvando os dados da disciplina cadastrada:
    lista_period[period_index].lista_dis_matriculadas[dis_index].dis_id = dis_id;
    lista_period[period_index].lista_dis_matriculadas[dis_index].creditos = creditos;
    strcpy(lista_period[period_index].lista_dis_matriculadas[dis_index].nome_dis, nome_dis);
    strcpy(lista_period[period_index].lista_dis_matriculadas[dis_index].nome_professor, nome_professor);
    printf("Dados Cadastrados com sucesso\n");
    return;
}

void addDis(int period_id, int al_id, int dis_id) {
    //Periodo Index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Procurar Aluno Index:
    int al_index = -1;
    for (int i = 0;i < lista_period[period_index].num_al;i++) {
        if (lista_period[period_index].lista_al_matriculados[i].al_code == al_id) {
            al_index = i;
        }
    }
    //Caso nao encontre:
    if (al_index == -1) {
        printf("O aluno nao esta matriculado nesse periodo...\n");
        return;
    }
    //Vericiar se a disciplina esta cadastrada no periodo:
    int aux = -1;
    for (int i = 0;i < lista_period[period_index].num_dis;i++) {
        if (lista_period[period_index].lista_dis_matriculadas[i].dis_id == dis_id) {
            aux = i;
            break;
        }
    }
    //Caso nao esteja:
    if (aux == -1) {
        printf("A disciplina nao esta cadastrada no periodo...\n");
        return;
    }
    //Caso esteja:
    //Procurar Disciplina:
    int dis_index = -1;
    for (int i = 0;i < lista_period[period_index].lista_al_matriculados[al_index].num_dis;i++) {
        if (lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id[i] == dis_id) {
            dis_index = i;
            break;
        }
    }
    //Caso o aluno ja esteja matriculado nessa disciplina:
    if (dis_index != -1) {
        printf("O aluno ja esta matriculado nessa disciplina...\n");
        return;
    }
    //Caso nao esteja:
    dis_index = lista_period[period_index].lista_al_matriculados[al_index].num_dis;
    lista_period[period_index].lista_al_matriculados[al_index].num_dis++;
    lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id = (int*)realloc(lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id, (lista_period[period_index].lista_al_matriculados[al_index].num_dis) * sizeof(int));
    lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id[dis_index] = dis_id;
    printf("Disciplina adicionada com sucesso.\n");
    return;
}
void removerDis(int period_id, int al_id, int dis_id) {
    //Periodo Index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Procurar Aluno Index:
    int al_index = -1;
    for (int i = 0;i < lista_period[period_index].num_al;i++) {
        if (lista_period[period_index].lista_al_matriculados[i].al_code == al_id) {
            al_index = i;
        }
    }
    //Caso nao encontre:
    if (al_index == -1) {
        printf("O aluno nao esta matriculado nesse periodo...\n");
        return;
    }
    //Caso encontre:temos o al index
    //Procurar Disciplina:
    int dis_index = -1;
    for (int i = 0;i < lista_period[period_index].lista_al_matriculados[al_index].num_dis;i++) {
        if (lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id[i] == dis_id) {
            dis_index = i;
            break;
        }
    }
    //Caso o aluno nao esteja matriculado nessa disciplina:
    if (dis_index == -1) {
        printf("O aluno nao esta matriculado nessa disciplina...\n");
        return;
    }
    //Caso esteja:
    //Caso a disciplina seja a ultima da lista:
    if (dis_index == (lista_period[period_index].lista_al_matriculados[al_index].num_dis - 1)) {
        lista_period[period_index].lista_al_matriculados[al_index].num_dis--;
        lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id = (int*)realloc(lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id, lista_period[period_index].lista_al_matriculados[al_index].num_dis * sizeof(int));
        printf("A disciplina foi removida com sucesso.\n");
        return;
    }
    //Caso a disciplina nao seja a ultima da lista, troca ela de lugar com a ultima da lista e realoca a memoria:
    else {
        lista_period[period_index].lista_al_matriculados[al_index].num_dis--;
        int last_index = lista_period[period_index].lista_al_matriculados[al_index].num_dis;
        lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id[dis_index] = lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id[last_index];
        lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id = (int*)realloc(lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id, lista_period[period_index].lista_al_matriculados[al_index].num_dis * sizeof(int));
        printf("A disciplina foi removida com sucesso.\n");
        return;
    }
    return;
}
int verificar_registro(int period_id, int dis_id) {
    //Buscar pelo periodo index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Procurar a disciplina:
    int dis_index = -1;
    for (int i = 0;i < lista_period[period_index].num_dis;i++) {
        if (lista_period[period_index].lista_dis_matriculadas[i].dis_id == dis_id) {
            dis_index = i;
            break;
        }
    }
    if (dis_index == -1) {
        return 0;
    }
    return 1;
}

//Funcao de inserção de periodo:
int criarperiodo(int nome_periodo) {
    //Verificar se o periodo ja foi criado:
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == nome_periodo) {
            return 1;
        }
    }
    //Caso nao tenha sido criado,adicionar um tamanho a mais na lista:
    lista_period = (periodo*)realloc(lista_period, (num_period + 1) * sizeof(periodo));

    //Prencher o novo espaco da lista com as informacoes do periodo:
    lista_period[num_period].num_al = 0;
    lista_period[num_period].period_id = nome_periodo;
    lista_period[num_period].lista_al_matriculados = NULL;
    lista_period[num_period].num_dis = 0;
    lista_period[num_period].lista_dis_matriculadas = NULL;
    num_period++;

    return 0;
}

int checkcpf(long long cpf) {
    long long s = 0;
    while(cpf) {
        s += cpf % 10;
        cpf /= 10;
    }
    return (s % 10 == s / 10);
}

//Funcao de insercao de aluno(matricula):
int matricular(int period_id, int al_code, long long int cpf, char al_nome[], int* lista_dis_id, int num_dis) {
    //Primeiro, precisamos saber em que posicao do array esta o periodo em que vamos matricular:
    if(!checkcpf) {
        return -123;
    }
    int period_index = -1;
    int al_index;
    for (int i = 0; i < num_period; i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Verificar se o aluno ja esta matriculado:
    for (int i = 0; i < lista_period[period_index].num_al; i++) {
        if (lista_period[period_index].lista_al_matriculados[i].al_code == al_code) {
            return 1; // O aluno ja esta matriculado
        }
    }
    //Caso o aluno nao esteja matriculado, vamos criar um novo espaco na lista:
    lista_period[period_index].lista_al_matriculados = (aluno*)realloc(lista_period[period_index].lista_al_matriculados, (lista_period[period_index].num_al + 1) * sizeof(aluno));
    //Salvar os dados desse aluno:
    al_index = lista_period[period_index].num_al++;
    lista_period[period_index].lista_al_matriculados[al_index].al_code = al_code;
    lista_period[period_index].lista_al_matriculados[al_index].cpf = cpf;
    strcpy(lista_period[period_index].lista_al_matriculados[al_index].al_nome, al_nome);
    lista_period[period_index].lista_al_matriculados[al_index].num_dis = num_dis;

    lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id = (int*)malloc(num_dis * sizeof(int));

    for (int i = 0;i < num_dis;i++) {
        lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id[i] = lista_dis_id[i];

    }
    return 0;
}

void desmatricular_al(int period_id, int al_code) {
    //Buscar pelo periodo index:
    int period_index = -1;
    for (int i = 0; i < num_period; i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Buscar pelo index do aluno no periodo:
    int al_index = -1;
    for (int i = 0; i < lista_period[period_index].num_al; i++) {
        if (lista_period[period_index].lista_al_matriculados[i].al_code == al_code) {
            al_index = i;
            break;
        }
    }
    //Caso o aluno nao seja encontrado:
    if (al_index == -1) {
        printf("O aluno nao esta matriculado no periodo inserido...\n");
        return;
    }
    //Na funcao matricular, fizemos um malloc no lista_dis_id do aluno matriculado, portanto temos que liberar essa memoria alocada:
    free(lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id);
    //Precisamos diminuir o tamanho
    int new_index = (lista_period[period_index].num_al) - 1;
    //Dois casos:
    //So remove o ultimo aluno da lista e realoca a memoria
    if (new_index == al_index) {
        lista_period[period_index].num_al--;
        lista_period[period_index].lista_al_matriculados = (aluno*)realloc(lista_period[period_index].lista_al_matriculados, (lista_period[period_index].num_al * sizeof(aluno)));
        printf("Aluno desmatriculado com sucesso\n");
        return;
    }
    //Joga o ultimo aluno da lista para a posicao do aluno removido(al_index) para remover o ultimo e realocar a memoria
    else {
        //Passando os dados do ultimo aluno do array para a posicao do aluno que vai ser removido
        lista_period[period_index].lista_al_matriculados[al_index].al_code = lista_period[period_index].lista_al_matriculados[new_index].al_code;
        lista_period[period_index].lista_al_matriculados[al_index].cpf = lista_period[period_index].lista_al_matriculados[new_index].cpf;
        lista_period[period_index].lista_al_matriculados[al_index].num_dis = lista_period[period_index].lista_al_matriculados[new_index].num_dis;
        strcpy(lista_period[period_index].lista_al_matriculados[al_index].al_nome, lista_period[period_index].lista_al_matriculados[new_index].al_nome);
        lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id = lista_period[period_index].lista_al_matriculados[new_index].lista_dis_id;
        //Realocar a memoria:
        lista_period[period_index].num_al--;
        lista_period[period_index].lista_al_matriculados = (aluno*)realloc(lista_period[period_index].lista_al_matriculados, (lista_period[period_index].num_al * sizeof(aluno)));
        printf("Aluno desmatriculado com sucesso\n");
        return;
    }
}

void acessarDadosDis(int period_id, int dis_id) {
    //Period Index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Dis Index:
    int dis_index = -1;
    for (int i = 0;i < lista_period[period_index].num_dis;i++) {
        if (lista_period[period_index].lista_dis_matriculadas[i].dis_id == dis_id) {
            dis_index = i;
            break;
        }
    }
    //Disciplina nao cadastrada:
    if (dis_index == -1) {
        printf("Disciplina nao cadastrada no periodo...\n");
        return;
    }
    //Disciplina cadastrada:
    printf("Nome do Curso: %s\n", lista_period[period_index].lista_dis_matriculadas[dis_index].nome_dis);
    printf("Codigo da disciplina: %d\n", lista_period[period_index].lista_dis_matriculadas[dis_index].dis_id);
    printf("Nome do Professor que leciona: %s\n", lista_period[period_index].lista_dis_matriculadas[dis_index].nome_professor);
    printf("Quantidade de Creditos da disciplina: %d\n", lista_period[period_index].lista_dis_matriculadas[dis_index].creditos);
    return;
}

void acessarDadosAl(int al_code, int period_id) {
    //Precisamos do periodo index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Sabemos o periodo index e o codigo do aluno, portanto vamos achar seu index na lista de alunos matriculados no periodo:
    int al_index = -1;
    for (int i = 0;i < lista_period[period_index].num_al;i++) {
        if (lista_period[period_index].lista_al_matriculados[i].al_code == al_code) {
            al_index = i;
            break;
        }
    }
    //Caso nao encontre o aluno
    if (al_index == -1) {
        printf("O aluno nao esta matriculado neste periodo...\n");
        return;
    }
    //Caso tenha encontrado, sabemos seu index, vamos printar os dados dele na tela:
    else {
        printf("O aluno esta matriculado no periodo.\n\n");
        printf("Nome Completo: %s\n", lista_period[period_index].lista_al_matriculados[al_index].al_nome);
        printf("CPF: %lld\n", lista_period[period_index].lista_al_matriculados[al_index].cpf);
        printf("Codigo de Matricula: %d\n", lista_period[period_index].lista_al_matriculados[al_index].al_code);
        printf("Cursando %d disciplinas\n", lista_period[period_index].lista_al_matriculados[al_index].num_dis);
        printf("Codigo das disciplinas cursadas: ");
        for (int i = 0;i < lista_period[period_index].lista_al_matriculados[al_index].num_dis;i++) {
            printf("%d ", lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id[i]);
        }
        printf("\n");
        printf("Dados de cada disciplina:\n");
        for (int j = 0;j < lista_period[period_index].lista_al_matriculados[al_index].num_dis;j++) {
            printf("\n");
            acessarDadosDis(period_id, lista_period[period_index].lista_al_matriculados[al_index].lista_dis_id[j]);
        }
        printf("\n\n");
        return;
    }
}

void acessar_al_de_uma_disciplina(int period_id, int dis_id) {
    //Procurar o period_index:
    int period_index = -1;
    for (int i = 0;i < num_period;i++) {
        if (lista_period[i].period_id == period_id) {
            period_index = i;
            break;
        }
    }
    //Procurar a disciplina:
    int dis_index = -1;
    for (int i = 0;i < lista_period[period_index].num_dis;i++) {
        if (lista_period[period_index].lista_dis_matriculadas[i].dis_id == dis_id) {
            dis_index = i;
            break;
        }
    }
    //Disciplina nao matriculada:
    if (dis_index == -1) {
        printf("\n");
        printf("Disciplina nao cadastrada no periodo...\n");
        return;
    }
    //Disciplina encontrada:
    //Procurar os alunos que fazem essa disciplina O(n^2)
    printf("\n");
    printf("Os alunos matriculados em %s neste periodo sao:\n", lista_period[period_index].lista_dis_matriculadas[dis_index].nome_dis);
    for (int i = 0;i < lista_period[period_index].num_al;i++) {
        for (int j = 0;j < lista_period[period_index].lista_al_matriculados[i].num_dis;j++) {
            if (lista_period[period_index].lista_al_matriculados[i].lista_dis_id[j] == dis_id) {
                printf("%s\n", lista_period[period_index].lista_al_matriculados[i].al_nome);
                break;
            }
        }
    }
    return;
}

int main() {
    //Le o arquivo input.txt para resgatar os dados salvos anteriormente:
    recuperar();
    int exit = 0;
    int c;
    printf("Sistema de Matriculas:\n");
    //Menu para escolher o periodo:
//Primeiro while
    while (exit == 0 && c != 11) {
        int semestre;
        char letra;
        printf("\n");
        printf("Digite uma opcao:\n");
        printf("a-)Acessar/Adicionar periodo:\n");
        printf("b-)Remover periodo:\n");
        scanf(" %c", &letra);
        if (letra == 'a') {
            //Acesso/Criacao de periodo:
            printf("Digite o ID do Periodo que voce deseja consultar:\n");
            printf("Exemplo: Se deseja acessar as informacoes do periodo 2023.1,digite: 20231\n");
            scanf("%d", &semestre);
            int b = criarperiodo(semestre);
            if (b == 1) {
                printf("Periodo ja esta cadastrado\n");
            }
            else if (b == 0) {
                printf("Periodo nao cadastrado\n\n");
                printf("Criando dados do perido\n\n");
                printf("Periodo Cadastrado!\n");
            }
            //Segundo While, Menu para aluno e disciplina:
            while (exit == 0) {

                printf("\n");
                printf("Periodo %d:\n", semestre);
                printf("Escolha o que deseja realizar:\n");
                printf("1-)Matricular um aluno nesse periodo:\n");
                printf("2-)Remover matricula de um aluno desse periodo:\n");
                printf("3-)Cadastrar dados da disciplina no periodo:\n");
                printf("4-)Remover dados de uma disciplina no periodo:\n");
                printf("5-)Adicionar uma disciplina para um aluno nesse periodo:\n");
                printf("6-)Remover uma disciplina que um aluno esteja cursando nesse periodo:\n");
                printf("7-)Acessar as disciplinas que um aluno esta cursando nesse periodo:\n");
                printf("8-)Acessar os dados de uma disciplina deste periodo:\n");
                printf("9-)Acessar os alunos que estao cursando uma disciplina desse periodo:\n");
                printf("10-)Acessar alunos matriculados nesse periodo:\n");
                printf("11-)Trocar de Periodo:\n");
                printf("12-)Salvar Dados e Sair:\n");
                scanf("%d", &c);
                if (c == 1) {
                    char palavra[50];
                    long long int cpff;
                    int codigo;
                    int num;
                    int* vector; // lista de disciplinasID de um aluno
                    int z;
                    printf("Digite o nome completo do aluno:\n");
                    scanf(" %[^\n]", palavra);
                    printf("Digite o cpf do aluno:\n");
                    scanf("%lld", &cpff);
                    printf("Digite o codigo de matricula do aluno\n");
                    scanf("%d", &codigo);
                    printf("Digite o numero de disciplinas que o aluno vai cursar:\n");
                    scanf("%d", &num);
                    printf("Digite o codigo das disciplinas que ele vai cursar(Um por linha):\n");
                    vector = (int*)malloc(num * sizeof(int));
                    for (int i = 0; i < num; i++) {
                        printf("Codigo da disciplina %d:\n", i + 1);
                        scanf("%d", &vector[i]);
                        z = verificar_registro(semestre, vector[i]);
                        if (z == 0) {
                            printf("\n");
                            printf("Essa disciplina nao esta registrada neste periodo, iniciando registro:\n\n");
                            int cod_dis;
                            int cred;
                            char nome_prof[50];
                            char nome_mat[50];
                            printf("Forneca os dados da disciplina que voce deseja cadastrar:\n");
                            printf("Codigo da disciplina:\n");
                            scanf("%d", &cod_dis);
                            printf("Nome da disciplina:\n");
                            scanf(" %[^\n]", nome_mat);
                            printf("Nome do professor que leciona a disciplina:\n");
                            scanf(" %[^\n]", nome_prof);
                            printf("Quantidade de creditos da disciplina:\n");
                            scanf("%d", &cred);
                            cadastrarDisciplina(semestre, cod_dis, nome_mat, nome_prof, cred);
                        }

                    }
                    int aux = matricular(semestre, codigo, cpff, palavra, vector, num);
                    if (aux == 1) {
                        printf("O aluno ja esta matriculado.\n");
                    } else if (aux == 0) {
                        printf("O aluno foi matriculado com sucesso.\n\n");
                    } else if(aux == -123) {
                        printf("CPF invalido, retornando ao menu...\n\n");
                    } else {
                        printf("Erro, retornando ao menu...\n\n");
                    }
                }
                else if (c == 2) {
                    int codigo;
                    printf("Digite o Codigo do aluno que vai ser desmatriculado:\n");
                    scanf("%d", &codigo);
                    desmatricular_al(semestre, codigo);
                }
                else if (c == 3) {
                    int cod_dis;
                    int cred;
                    char nome_prof[50];
                    char nome_mat[50];
                    printf("Forneca os dados da disciplina que voce deseja cadastrar:\n");
                    printf("Codigo da disciplina:\n");
                    scanf("%d", &cod_dis);
                    printf("Nome da disciplina:\n");
                    scanf(" %[^\n]", nome_mat);
                    printf("Nome do professor que leciona a disciplina:\n");
                    scanf(" %[^\n]", nome_prof);
                    printf("Quantidade de creditos da disciplina:\n");
                    scanf("%d", &cred);
                    cadastrarDisciplina(semestre, cod_dis, nome_mat, nome_prof, cred);

                }
                else if (c == 4) {
                    int dis_id;
                    printf("Digite o codigo da disciplina que voce deseja remover do periodo:\n");
                    scanf("%d", &dis_id);
                    removerDisPeriod(semestre, dis_id);
                }
                else if (c == 5) {
                    int codigo_matricula;
                    int codigo_curso;
                    printf("Digite o codigo de matricula do aluno em questao:\n");
                    scanf("%d", &codigo_matricula);
                    printf("Os dados do aluno sao:\n");
                    acessarDadosAl(codigo_matricula, semestre);
                    printf("Digite o codigo da disciplina que voce deseja adicionar:\n");
                    scanf("%d", &codigo_curso);
                    addDis(semestre, codigo_matricula, codigo_curso);
                    acessarDadosAl(codigo_matricula, semestre);
                }
                else if (c == 6) {
                    int codigo_matricula;
                    int codigo_curso;
                    printf("Digite o codigo de matricula do aluno em questao:\n");
                    scanf("%d", &codigo_matricula);
                    printf("Os dados do aluno sao:\n");
                    acessarDadosAl(codigo_matricula, semestre);
                    printf("Digite o codigo da disciplina que voce deseja remover:\n");
                    scanf("%d", &codigo_curso);
                    removerDis(semestre, codigo_matricula, codigo_curso);
                    acessarDadosAl(codigo_matricula, semestre);
                }
                else if (c == 7) {
                    int password;
                    printf("Digite o codigo do aluno que voce deseja acessar os dados:\n");
                    scanf("%d", &password);
                    acessarDadosAl(password, semestre);
                }
                else if (c == 8) {
                    int number;
                    printf("Digite o codigo da disciplina que voce deseja acessar:\n");
                    scanf("%d", &number);
                    acessarDadosDis(semestre, number);
                }
                else if (c == 9) {
                    int codigo_dis;
                    printf("Digite o codigo da disciplina que voce deseja consultar:\n");
                    scanf("%d", &codigo_dis);
                    acessar_al_de_uma_disciplina(semestre, codigo_dis);
                }
                else if (c == 10) {
                    alunos_matriculados(semestre);
                }
                else if (c == 11) {
                    break;
                }
                else if (c == 12) {
                    salvar();
                    printf("Dados Salvos com sucesso\n");
                    exit = 1;
                }
                else {
                    printf("Opção Invalida\n\n");
                }
                // else
            } //segundo while

        } // if c==

        else if (letra == 'b') {
            if (num_period == 0) {
                printf("Nenhum periodo registrado...\n");
            }
            else {
                int id;
                printf("Os periodos registrados no sistema sao:\n");
                for (int i = 0;i < num_period;i++) {
                    printf("%d ", lista_period[i].period_id);
                }
                printf("\n");
                printf("Digite o ID do Periodo que deseja remover:\n");
                scanf("%d", &id);
                removerPeriod(id);
            }
        }
        else {
            printf("Opcao Invalida...\n");
        }
    } //primeiro while
}