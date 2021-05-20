#include "covid19.h"

/*
*Nome da funcao: restricao_min
*
*Objetivo da funcao: Restringir os dados a serem analisados a paises com mais de n mil habitantes
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser restringida
*           min -> numero minimo de habitantes em milhares
*
*Argumentos de saida: Um ponteiro *head para o inicio da lista já restringida
*/

data* restricao_min(data* head,long int min){
    
    data* atual = head;
    data* anterior = NULL;
    data* remover = NULL;
    variableData* aux=NULL;
    variableData* remover2=NULL;

    min=min*1000;

    while (atual != NULL) {

        if (atual->population > min) {      //Se o pais estiver dentro da restrição passa para o próximo
            anterior = atual;
            atual = atual->next;
            continue;
        }

        remover=atual;                      //Se não estiver dentro da restrição vai preparar para remover 

        if (anterior) {
            anterior->next = remover->next;
        } else {
            head = remover->next;
        }

        aux=remover->dadosSemanais;

        while(aux!=NULL)                    //Remove a lista dos dados variaveis
        {
            remover2=aux;
            aux=aux->next;
            free(remover2);
        }

        atual = atual->next;
        free(remover);                      //Remove o nó que não está dentro da restrição
    }

    return head;
}

/*
*Nome da funcao: restricao_max
*
*Objetivo da funcao: Restringir os dados a serem analisados a paises com menos de n mil habitantes
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser restringida
*           max -> numero máximo de habitantes em milhares
*
*Argumentos de saida: Um ponteiro *head para o inicio da lista já restringida
*/

data* restricao_max(data* head,long int max){
    
    data* atual = head;
    data* anterior = NULL;
    data* remover = NULL;
    variableData* aux=NULL;
    variableData* remover2=NULL;

    max=max*1000;

    while (atual != NULL) {

        if (atual->population < max) {      //Se o pais estiver dentro da restrição passa para o próximo
            anterior = atual;
            atual = atual->next;
            continue;
        }

        remover=atual;                      //Se não estiver dentro da restrição vai preparar para remover 

        if (anterior) {
            anterior->next = remover->next;
        } else {
            head = remover->next;
        }

        aux=remover->dadosSemanais;

        while(aux!=NULL)                    //Remove a lista dos dados variaveis
        {
            remover2=aux;
            aux=aux->next;
            free(remover2);
        }

        atual = atual->next;
        free(remover);                      //Remove o nó que não está dentro da restrição
    }

    return head;
}

/*
*Nome da funcao: restricao_data
*
*Objetivo da funcao: Restringir os dados a serem analisados a uma data
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser restringida
*           date -> data em questão
*
*Argumentos de saida: Um ponteiro *head para o inicio da lista já restringida
*/

data* restricao_data(data* head,char date[10]){

    variableData* atual = NULL;
    variableData* anterior = NULL;
    variableData* remover = NULL;
    data* aux = head;


    for (aux=head;aux!=NULL;aux=aux->next)              //Vai percorrer toda a lista 
    {
        atual=aux->dadosSemanais;
        anterior=NULL;
        remover=NULL;

        while (atual != NULL) {
            if (strcmp(atual->year_week,date)==0) {    //Vai percorrer a lista de dados variaveis e libertar tudo o que não tiver a data escolhida 
                anterior = atual;
                atual = atual->next;
                continue;
            }

            remover=atual;

            if (anterior)
            {
                anterior->next = remover->next;
            } else {
                aux->dadosSemanais = remover->next;
            }
            
            atual = atual->next;
            free(remover);  
        }
    }

    return head;
}

/*
*Nome da funcao: restricao_datas
*
*Objetivo da funcao: Restringir os dados a serem analisados a um intervalo de datas
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser restringida
*           date1 -> primeira data inserida
*           date2 -> segunda data inserida
*
*Argumentos de saida: Um ponteiro *head para o inicio da lista já restringida
*/

data* restricao_datas(data* head,char date1[10],char date2[10]){

    variableData* atual = NULL;
    variableData* anterior = NULL;
    variableData* remover = NULL;
    data* aux = head;

    char data[3][10];    // [0] ano  menor | [1] ano maior | [2] ano data em questão
    
    if (strcmp(date1,date2)<0)      // mete em [0] o ano menor e em [1] o maior
    {
        strcpy(data[0],date1);
        strcpy(data[1],date2);
    }
    else{
        strcpy(data[1],date1);
        strcpy(data[0],date2); 
    }

    for (aux=head;aux!=NULL;aux=aux->next)              //Vai percorrer a lista
    {
        atual=aux->dadosSemanais;
        anterior=NULL;
        remover=NULL;
        while (atual != NULL) {                        //Vai percorrer a sublista

            strcpy(data[2],atual->year_week);

            if (strcmp(data[2],data[0])>=0 && strcmp(data[2],data[1])<=0){      //Vê se está dentro do intervalo     
                    anterior = atual;
                    atual = atual->next;
                    continue;                                                   //Se estiver dentro do intervalo salta para proxima linha
            }

            remover=atual;      //Se não estiver, vai saltar para a próxima linha a linha atual é removida

            if (anterior) {
                anterior->next = remover->next;
            } else {
                aux->dadosSemanais = remover->next;
            }
            
            atual = atual->next;
            free(remover);
            
        }
    }

    return head;
}