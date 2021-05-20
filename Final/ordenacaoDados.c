#include "covid19.h"

/*
*Nome da funcao: ordem_alfa
*
*Objetivo da funcao: Ordenar alfabeticamente a lista em memória com recurso a um BubbleSort
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser ordenada 
*
*Argumentos de saida: Um ponteiro *head para o inicio da lista já ordenada
*/

data *ordem_alfa(data *head)
{
    int nmrNodes = contagem(head);             //Com recurso a outra função conta o numero de nós da lista
    int i;

    for (i = 0; i < nmrNodes; i++) {
        data* atual = head;
        data* proximo = atual->next;
        data* anterior = NULL;

        while(proximo != NULL) {
            if (strcmp(atual->country, proximo->country) > 0)       //Aplica o Bubblesort
            {
                if (atual == head)
                {
                    head = proximo;
                } 
                else 
                {
                    anterior->next = proximo;
                }

                atual->next = proximo->next;
                proximo->next = atual; 
                anterior = proximo;
                proximo = atual->next;

            }
            else
            {
                anterior = atual;
                atual = atual->next;
                proximo = atual->next;
            }
        }
    }
    return head;
}

/*
*Nome da funcao: ordem_pop
*
*Objetivo da funcao: Ordenar por ordem decrescente de população a lista em memória com recurso a um BubbleSort
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser ordenada 
*
*Argumentos de saida: Um ponteiro *head para o inicio da lista já ordenada
*/

data *ordem_pop(data *head)
{
    int nmrNodes = contagem(head); //Com recurso a outra função conta o numero de nós da lista
    int i;

    for (i = 0; i < nmrNodes; i++) {
        
        data* atual = head;
        data* proximo = atual->next;
        data* anterior = NULL;

        while(proximo != NULL) {
            if (atual->population < proximo->population )
            { //Aplica o BubbleSorte para a população
                if (atual == head)
                {
                    head = proximo;
                } 
                else 
                {
                    anterior->next = proximo;
                }

                atual->next = proximo->next;
                proximo->next = atual; 
                anterior = proximo;
                proximo = atual->next;

            }
            else if (atual->population==proximo->population)
            {
                if (strcmp(atual->country, proximo->country) > 0)   //Em caso de empate ordena por ordem alfabetica
                {
                    if (atual == head)
                    {
                        head = proximo;
                    } 
                    else 
                    {
                        anterior->next = proximo;
                    }

                    atual->next = proximo->next;
                    proximo->next = atual; 
                    anterior = proximo;
                    proximo = atual->next;

                }
                else
                {
                    anterior = atual;
                    atual = atual->next;
                    proximo = atual->next;
                }
            }
            else
            {
                anterior = atual;
                atual = atual->next;
                proximo = atual->next;
            }
        }
    }
    return head;
}

/*
*Nome da funcao: ordem_inf_dea
*
*Objetivo da funcao: Ordenar por ordem decrescente de casos/mortes numa dada data
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser ordenada 
*           dadosInput -> struct com toda a informação do input pela linha de comandos
*           tipo -> "cases" caso queiramos ordernar com base nos casos | "deaths" caso queiramos ordernar com base nas mortes
*
*Argumentos de saida: Um ponteiro *head para o inicio da lista já ordenada
*/

data *ordem_inf_dea(data *head,inputStruct dadosInput, char tipo[])
{
    int nmrNodes = contagem(head);  //Com recurso a outra função conta o numero de nós da lista
    int i,o=0;                      //variaveis auxiliares
    int flagDataExistente=0;        // 0 se o pais atual não tiver dados relativos á data | 1 se o pais a seguir não tiver dados relativos a uma data | 2 se ambos os paises tiverem informação relativa á data
    data* aux3 = head;
    variableData* aux = NULL;
    
    

    for (i = 0; i < nmrNodes; i++) {
        data* atual = head;
        data* proximo = atual->next;
        data* anterior = NULL;
        
        aux = NULL;
        variableData* aux2 = NULL;


        while(proximo != NULL) {                    
            flagDataExistente=0;
            for (aux=atual->dadosSemanais;aux!=NULL;aux=aux->next)
            {
                if(strcmp(aux->year_week,dadosInput.dataOrdenacao)==0 && strcmp(aux->indicator,tipo)==0){

                    flagDataExistente=1; 

                    for (aux2=proximo->dadosSemanais;aux2!=NULL;aux2=aux2->next)
                    {

                        if (strcmp(aux2->year_week,dadosInput.dataOrdenacao)==0 && strcmp(aux2->indicator,tipo)==0)     //ordena com base no numero de casos/mortes
                        {
                            flagDataExistente=2;

                            if (aux->weekly_count < aux2->weekly_count )
                            {
                                if (atual == head)
                                {
                                    head = proximo;
                                }
                                else 
                                {
                                    anterior->next = proximo;
                                }

                                atual->next = proximo->next;
                                proximo->next = atual; 
                                anterior = proximo;
                                proximo = atual->next;

                            }
                            else if (aux->weekly_count == aux2->weekly_count)
                            {
                                if (strcmp(atual->country, proximo->country) > 0)
                                {              //em caso de empate ordena alfabeticamente
                                    if (atual == head)
                                    {
                                        head = proximo;
                                    } 
                                    else
                                    {
                                        anterior->next = proximo;
                                    }

                                    atual->next = proximo->next;
                                    proximo->next = atual; 
                                    anterior = proximo;
                                    proximo = atual->next;

                                }
                                else
                                {
                                    anterior = atual;
                                    atual = atual->next;
                                    proximo = atual->next;
                                }
                            }
                            else
                            {
                                anterior = atual;
                                atual = atual->next;
                                proximo = atual->next;
                            } 
                        }
                        
                    }
                }
            }
            if (flagDataExistente==0)               
            {       
                head=coloca_cauda(head,atual);      //Caso não haja informação relativa a essa data manda o nó para o fim da lista
                break;

            }
            else if(flagDataExistente==1)
            {         //Caso não haja informação relativa a essa data manda o nó para o fim da lista
                head=coloca_cauda(head,proximo);
                break;
            }
        }
    }

    
    
    for (aux3=head;aux3!=NULL;aux3=aux3->next)
    {
        for (aux=aux3->dadosSemanais;aux!=NULL;aux=aux->next)
        {
            if ((strcmp(aux->year_week,dadosInput.dataOrdenacao)==0) && (strcmp(aux->indicator,tipo)==0) && (aux->weekly_count!=0))
            {
                o=o+1;          //Conta o numero de nós válido 
            }
               
        }
    }
    
    aux3=head;
    if (o==0)
    {
        head=ordem_alfa(head);
    }
    else
    {
        for ( i = 1; i < o; i++)
        {
            aux3=aux3->next;
        }   
        aux3->next=ordem_alfa(aux3->next);      //ordena por ordem alfabetica o que está no fim da lista 
    }
    

    return head;
}

/*
*Nome da funcao: ordem_variable_data
*
*Objetivo da funcao: Ordenar a lista colocando os casos primeiros e depois as mortes por mordem crescente de datas
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser ordenada 
*
*Argumentos de saida: Um ponteiro *head para o inicio da lista já ordenada
*/

data *ordem_variable_data(data *head){
    int nmrNodes=0;           
    int i;
    data *node = head;
    variableData *aux;
    variableData* atual;
    variableData* proximo;
    variableData* anterior;


    while (node != NULL)            //Vai passar por todos os nós da lista principal
    {
        nmrNodes=0;
        aux = node->dadosSemanais;
        while (aux!=NULL)
        {
            nmrNodes++;
            aux = aux->next;
        }

        for (i = 0; i < nmrNodes; i++) {
            atual = node->dadosSemanais;
            proximo = node->dadosSemanais->next;
            anterior = NULL;

            while(proximo != NULL) {
                if (strcmp(atual->indicator, proximo->indicator) > 0)       //Aplica o Bubblesort para colocar cases primeiro
                {
                    if (atual == node->dadosSemanais)
                    {
                        node->dadosSemanais = proximo;
                    } 
                    else 
                    {
                        anterior->next = proximo;
                    }

                    atual->next = proximo->next;
                    proximo->next = atual; 
                    anterior = proximo;
                    proximo = atual->next;

                }
                else if(strcmp(atual->indicator, proximo->indicator) == 0){
                    if (strcmp(atual->year_week, proximo->year_week) > 0)       //Aplica o Bubblesort para colocar por ordem crescente de datas
                    {
                        if (atual == node->dadosSemanais)
                        {
                            node->dadosSemanais = proximo;
                        } 
                        else 
                        {
                            anterior->next = proximo;
                        }

                        atual->next = proximo->next;
                        proximo->next = atual; 
                        anterior = proximo;
                        proximo = atual->next;
                    }
                    else
                    {
                        anterior = atual;
                        atual = atual->next;
                        proximo = atual->next;
                    }
                }
                else
                {
                    anterior = atual;
                    atual = atual->next;
                    proximo = atual->next;
                }
            }
        }
        node = node->next;
    }
    return head;
}

/*
*Nome da funcao: contagem
*
*Objetivo da funcao: conta o numero de nós de uma lista
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser contada
*
*Argumentos de saida: um int com o numero de nós
*/

int contagem(data* head)
{
    int nmr = 0;  
    struct data* node = head;
    while (node != NULL)
    {
        nmr++;
        node = node->next;
    }
    return nmr;
}