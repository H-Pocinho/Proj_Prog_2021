#ifndef COVID19_H_INCLUDED
#define COVID19_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h> 


typedef struct variableData {  //Struct que define um nó da lista de dados variaveis
    char indicator[10];
    int weekly_count;
    char year_week[10];
    char rate_14_day[25];
    long int cumulative_count;

    struct variableData* next; 
} variableData;

typedef struct data {      //Struct que define um nó da lista de dados principais
    char country[100];
    char country_code[5];
    char continent[10];
    long int population;
    variableData *dadosSemanais;

    struct data* next; 
} data;


typedef struct returnStruct {   //Struct que contem os dados de saida das funções de leitura de dados
    char** ponteiroFicheiro;    // ponteiro para o inicio do ficheiro
    int nLinhas;                // numero de linhas do ficheiro
} returnStruct;

typedef struct inputStruct {    //Struct que contem os dados de saida das funções de input de dados pela linha de comandos
    int leituraDados;           // 0 = all | 1 = continentes
    char continente[10];        // nome do continente
    int ordenecaoDados;         // 0 = alfa | 1 = pop | 2 = inf | 3 = dea
    char dataOrdenacao[10];     // data para ordenacaoDados
    int selecaoDados;           // 0 = NA | 1 = inf | 2 = dea | 3 = racioinf | 4 = raciodea
    int restricaoDados;         // 0 = NA | 1 = min | 2 = max | 3 = date | 4 = dates
    long int popRestricao;      // nmr de pessoas
    char dataRestricao[2][10];  // datas que serão usadas nas restrições
    char inputName[250];        // nome do ficheiro de input
    int inputType;              // 0 = CSV | 1 = DAT
    char outputName[250];       // nome do ficheiro de output
    int outputType;             // 0 = CSV | 1 = DAT
    int erro;                   // 0 = NA | 1 = erro
    char mensagemErro[250];     // mensagem de erro
} inputStruct;

//Função de ajuda (Ficheiro textoAjuda.c)

void texto_ajuda();


//Funções de manipulação de ficheiros (Ficheiro manipulacaoFicheiros.c)

returnStruct dados_all(char str[]);
returnStruct dados_cont(char str[],char continente[]);
data* read_DAT(data *head,char nome[]);
void file_output_CSV(data *head,char nome[]);
void file_output_DAT(data *head,char nome[]);
void liberta_mem_ficheiros(char *ficheiro[], int nLinhas);
int verifica_linha(char linha[500],int nmrLinha);


//função de seleção de dados (Ficheiro selecaoDados.c)

data* selecao_inf_dea_ratio(data* head, char tipo[],int flagRatio);


//Funções de restrição de dados (Ficheiro restricaoDados.c)

data* restricao_min(data* head,long int min);
data* restricao_max(data* head,long int max);
data* restricao_data(data* head,char date[10]);
data* restricao_datas(data* head,char date1[10],char date2[10]);


//Funções de ordenação de dados (Ficheiro ordenacaoDados.c)

data* ordem_alfa (data *head);
data* ordem_pop(data *head);
data* ordem_inf_dea(data *head,inputStruct dadosInput, char tipo[]);
data *ordem_variable_data(data *head);
int contagem(data* head);


//Manipulação do input da linha de comandos

int is_date(char string[]);
inputStruct verificacao_input(int counter, char *input[]);


//Funções de tratamento e manipulação de listas

data *cria_pais(char nome[], char codigo[], char continente[10], long int pop);
data *insere_cabeca_data(data *head,data *nodulo);
variableData *cria_variable_data(char indicador[10], int contagemSemanal, char semanaAno[10], char ratio14Dias[25], long int contagemComulativa);
variableData *insere_cabeca_variable_data(variableData *head,variableData *nodulo);
data *cria_lista_paises(data *head, returnStruct dadosFicheiro);
void adiciona_variable_data(data *head, returnStruct dadosFicheiro);
data *coloca_cauda(data *list, data *element);
void liberta_lista(data *head);

#endif