#include <stdio.h>
#include <string.h>

char msg_original[501], msg_codificada[1001], msg_decodificada[501];

void codifica(char msg_original[501], char msg_codificada[1001]) {
    int i = 0, j = 0;
    for(i = 0; i < strlen(msg_original); i++) {
        if(msg_original[i] != ' ' && ((msg_original[i] >= 'A' && msg_original[i] <= 'Z') || (msg_original[i] >= 'a' && msg_original[i] <= 'z'))) {
            msg_codificada[j] = 'p';
            msg_codificada[j + 1] = msg_original[i];
            j = j + 2;
        } else if(msg_original[i] == ' ') {
            msg_codificada[j] = ' ';
            j++;
        } else {
            msg_codificada[j] = msg_original[i];
            j++;
        }
    }
    return;
}

void decodifica(char msg_codificada[1001], char msg_decodificada[501]) {
    int i = 0, j = 0;
    while(i < strlen(msg_codificada)) {
        if(msg_codificada[i] == 'p') {
            msg_decodificada[j] = msg_codificada[i + 1];
            j++;
            i = i + 2;
        } else {
            msg_decodificada[j] = msg_codificada[i];
            j++;
            i++;
        }
    }
    return;
}

int main() {
    printf("Digite uma mensagem de ate 500 caracteres:\n");
    gets(msg_original);
    codifica(msg_original, msg_codificada);
    printf("\nMENSAGEM CODIFICADA:\n");
    puts(msg_codificada);
    decodifica(msg_codificada, msg_decodificada);
    printf("\nMENSAGEM DECODIFICADA:\n");
    puts(msg_decodificada);
    return 0;
}