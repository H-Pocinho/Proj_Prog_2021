#ifndef COVID19_H_INCLUDED
#define COVID19_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/*meter aqui funções*/
// Pode ser util usar STRTOK e STRSTR


typedef struct inputStruct {
    int leituraDados;       //0 = all | 1 = continentes
    char continente[10];    //nome do continente
    int ordenecaoDados;     // 0 = alfa | 1 = pop | 2 = inf | 3 = dea
    char dataOrdenacao[10]; // data para ordenacaoDados
    int selecaoDados;       // 0 = NA | 1 = inf | 2 = dea | 3 = racioinf | 4 = raciodea
    int restricaoDados;     // 0 = NA | 1 = min | 2 = max | 3 = date | 4 = dates
    long int popRestricao;
    char dataRestricao[2][10];
    char inputName[250];
    char outputName[250];
    int erro;               // 0 = NA | 1 = erro
    char mensagemErro[250];
} inputStruct;

typedef struct returnStruct {
    char** ponteiroFicheiro;
    int nLinhas;
} returnStruct;


inputStruct verificacaoInput(int counter, char *input[]);
returnStruct dadosAll(char str[]);


#endif