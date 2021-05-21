#include "covid19.h"

/*
*Nome da funcao: cria_pais
*
*Objetivo da funcao: criar um nó da lista de paises
*
*Argumentos de entrada:
*   -nome: nome do pais
*   -codigo: codigo do pais
*   -continente: continente do pais
*   -pop: população do pais
*
*Argumentos de saida:
*   -novoPais: nó já feito e não ligado
*/

data *cria_pais(char nome[100], char codigo[5], char continente[10], long int pop){
    data *novoPais;
    
    if((novoPais = (data*) calloc(1,sizeof(data)))==NULL){          //Aloca espaço para o nó
        printf("Calloc falhou\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novoPais->country,nome);                                 //prenche o nó
    strcpy(novoPais->country_code,codigo);
    strcpy(novoPais->continent,continente);
    novoPais->population=pop;
    novoPais->dadosSemanais=NULL;
    novoPais->next=NULL;

    return novoPais;
}

/*
*Nome da funcao: cria_variable_data
*
*Objetivo da funcao: criar um nó da lista de dados variaveis
*
*Argumentos de entrada:
*   -indicador: indicador da linha
*   -contagemSemanal: contagem semanal da linha
*   -semanaAno: semana e ano da linha
*   -ratio14Dias: rácio dos ultimos 14 dias da linha
*   -contagemComulativa: soma das contagens semanais da linha
*
*Argumentos de saida:
*   -novaData: nó já feito e não ligado
*/

variableData *cria_variable_data(char indicador[10], int contagemSemanal, char semanaAno[10], char ratio14Dias[25], long int contagemComulativa)
{
    variableData *novaData;
    if((novaData = (variableData*) calloc(1,sizeof(variableData)))==NULL){          //Aloca espaço para o nó
        printf("Calloc falhou\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novaData->indicator,indicador);                                          //Prenche o nó
    novaData->weekly_count=contagemSemanal;
    strcpy(novaData->year_week,semanaAno);
    strcpy(novaData->rate_14_day,ratio14Dias);
    novaData->cumulative_count=contagemComulativa;
    novaData->next=NULL;

    return novaData;
}

/*
*Nome da funcao: insere_cabeca_data
*
*Objetivo da funcao: insere um nó na cabeça da lista
*
*Argumentos de entrada:
*   -*head: ponteiro para a cabeça da lista
*   -*nodulo: ponteiro para o nó que se quer inserir
*
*Argumentos de saida:
*   -head: ponteiro para cabeça da lista com o nó já inserido
*/

data *insere_cabeca_data(data *head,data *nodulo){

    if (head==NULL)
    {
        head = nodulo;
    }else{
        nodulo->next=head;
        head=nodulo;
    }
    return head;
}

/*
*Nome da funcao: insere_cauda_data
*
*Objetivo da funcao: insere um nó na cauda da lista
*
*Argumentos de entrada:
*   -*head: ponteiro para a cabeça da lista
*   -*nodulo: ponteiro para o nó que se quer inserir
*
*Argumentos de saida:
*   -head: ponteiro para cabeça da lista com o nó já inserido
*/

data *insere_cauda_data(data *head,data *nodulo){
    data *aux;
    if (head==NULL)
    {
        head = nodulo;
    }else{
        aux=head;
        while (aux->next!=NULL)
        {
            aux=aux->next;
        }
        aux->next=nodulo;
    }
    return head;
}


/*
*Nome da funcao: insere_cabeca_variable_data
*
*Objetivo da funcao: insere um nó na cabeça da lista de dados variaveis
*
*Argumentos de entrada:
*   -*head: ponteiro para a cabeça da lista de dados variaveis
*   -*nodulo: ponteiro para o nó que se quer inserir
*
*Argumentos de saida:
*   -head: ponteiro para cabeça da lista de dados variaveis com o nó já inserido
*/

variableData *insere_cabeca_variable_data(variableData *head,variableData *nodulo){
    if (head==NULL)
    {
        head = nodulo;
    }else{
        nodulo->next=head;
        head=nodulo;
    }
    return head;
}

/*
*Nome da funcao: insere_cauda_variable_data
*
*Objetivo da funcao: insere um nó na cauda da lista de dados variaveis
*
*Argumentos de entrada:
*   -*head: ponteiro para a cabeça da lista de dados variaveis
*   -*nodulo: ponteiro para o nó que se quer inserir
*
*Argumentos de saida:
*   -head: ponteiro para cabeça da lista de dados variaveis com o nó já inserido
*/

variableData *insere_cauda_variable_data(variableData *head,variableData *nodulo){
    variableData *aux;
    if (head==NULL)
    {
        head = nodulo;
    }else{
        aux=head;
        while (aux->next!=NULL)
        {
            aux=aux->next;
        }
        aux->next=nodulo;
    }
    return head;
}

/*
*Nome da funcao: cria_lista_paises
*
*Objetivo da funcao: cria a lista dos paises com base no dados do ficheiro em memória
*
*Argumentos de entrada:
*   -*head: ponteiro para a cabeça da lista
*   -dadosFicheiros: struct com o ponteiro para o ficheiro em memória e com o numero de linhas
*
*Argumentos de saida:
*   -head: ponteiro para cabeça da lista com tudo lá dentro
*/

data *cria_lista_paises(data *head, returnStruct dadosFicheiro){
    char linhaTEMP[500];            //Linha temporária que tem uma linha do ficheiro retirada da memória
    int i,o;                        //variaveis auxiliares para loops
    char *token; 
    char separador[2] = ",";  
    char input[4][100];             //variavel que vai ter os parametros para a função cria_pais
    int flagPais;                   //Indica se o pais já existe ou não
    data *novoPais;
    data *aux;

    for ( i = 0; i < dadosFicheiro.nLinhas; i++)                                //vai percorrer o ficheiro todo
    {
        strcpy(linhaTEMP,*(dadosFicheiro.ponteiroFicheiro+i));                  //Copia uma linha para ser trabalhada
        token = strtok(linhaTEMP, separador);                                   
        strcpy(input[0],token);

        for(o = 1; o < 4;o++ )
        {
            token = strtok(NULL, separador);                                    //A linha é separada e colocada num array
            strcpy(input[o],token);
        }

        flagPais = 0;

        for (aux=head;aux!=NULL;aux=aux->next)
        {
            if(strcmp(aux->country_code,input[1])==0){                          //Verifica se o pais já existe
                flagPais=1;
                break;
            }
        }

        if (flagPais==0)
        {
            novoPais=cria_pais(input[0],input[1],input[2], atoi(input[3]));     //Cria pais se ele não existir
            head=insere_cabeca_data(head,novoPais);
        }
    }

    adiciona_variable_data(head,dadosFicheiro);                                 //Vai se colocar os dados variaveis
    
    liberta_mem_ficheiros(dadosFicheiro.ponteiroFicheiro,dadosFicheiro.nLinhas);//liberta-se o ficheiro que está em memória

    return head;
}

/*
*Nome da funcao: adiciona_variable_data
*
*Objetivo da funcao: adiciona á lista já existente os dados variaveis com base no ficheiro em memória
*
*Argumentos de entrada:
*   -*head: ponteiro para a cabeça da lista
*   -dadosFicheiros: struct com o ponteiro para o ficheiro em memória e com o numero de linhas
*
*Argumentos de saida:
*   -head: ponteiro para cabeça da lista com tudo lá dentro
*/

void adiciona_variable_data(data *head, returnStruct dadosFicheiro){
    int i;
    char linhaTEMP[500];
    char *token; 
    const char separador[2] = ",";
    char input[6][100];
    int o;
    data *aux;
    variableData *aux2;

    for ( i = 0; i < dadosFicheiro.nLinhas; i++)                    //Percorre o ficheiro em memória
    {
        strcpy(linhaTEMP,*(dadosFicheiro.ponteiroFicheiro+i));      
        token = strtok(linhaTEMP, separador);
        token = strtok(NULL, separador);
        strcpy(input[0],token);                                     //Guarda o pais no input[0]
        token = strtok(NULL, separador);
        token = strtok(NULL, separador);
        for (o = 1; o < 6; o++)                                     //lê o resto da linha e guarda as informações
        {
            if((token = strtok(NULL, separador))==NULL){
                strcpy(input[5],input[4]);
                strcpy(input[4],"");
                break;
            }
            strcpy(input[o],token);
        }
  
       for (aux=head;aux!=NULL;aux=aux->next)                       //Coloca a informação lista e coloca a informação na lista
        {
            if (strcmp(aux->country_code,input[0])==0)
            {
                aux2=cria_variable_data(input[1],atoi(input[2]), input[3], input[4], strtol(input[5],NULL,10));
                aux->dadosSemanais=insere_cabeca_variable_data(aux->dadosSemanais,aux2);
            }
        }
    }
}

/*
*Nome da funcao: coloca_cauda
*
*Objetivo da funcao: coloca na cauda da lista o nó que lhe for passado
*
*Argumentos de entrada:
*   -*list: ponteiro para a cabeça da lista
*   -*node: ponteiro para o node que se quer colocar na cauda 
*
*Argumentos de saida:
*   -head: ponteiro para cabeça da lista rearranjada
*/

data *coloca_cauda(data *list, data *node){
    data *head = list;
    data *anterior = NULL, *atual = head;

    if(list == NULL || list->next == NULL)      //Se a lista for nula 
        return head;

    while(atual){                               //se não percorre a lista
        if(atual == node){                      //reteria o nó que se quer colovar no fim
            if(atual == head){
                head = atual->next;
            } else {
                anterior ->next = atual->next;
            }
            atual = atual->next;
        } else {
            anterior = atual;
            atual = atual->next;
        }
    }

    anterior->next = node;                  //coloca-se o nó no fim
    node->next = NULL;
    return head;
}

/*
*Nome da funcao: liberta_lista
*
*Objetivo da funcao: tira a lista de memória
*
*Argumentos de entrada:
*   -*head: ponteiro para a cabeça da lista
*
*Argumentos de saida:
* 
*/

void liberta_lista(data *head){

    data* aux;
    variableData *aux2, *aux3;
    
    while (head != NULL)                //percorre a lista
    {
        aux2=head->dadosSemanais;
        while (aux2 != NULL){
            aux3=aux2;
            aux2=aux2->next;
            free(aux3);                 //dá free aos dados auxiliares
        }
        aux = head;
        head = head->next;
        free(aux);                      //dá free ao nó da lista principal
    }
}