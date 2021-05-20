#include "covid19.h"

/*
*Nome da funcao: selecao_inf_dea_ratio
*
*Objetivo da funcao: selecionar o tipo de dados que vai passar para a proxima fase de analise
*
*Argumentos de entrada:
*   -head: cabeça da lista a que se aplicar esta selecão
*   -tipo: word que vai ter "cases" ou "deaths" dependendo do que se desejar
*   -flagRatio: 0 caso estejamos a trabalhar com numeros ou 1 caso estejamos a trabalhar com ratios
*
*Argumentos de saida:
*   -head: cabeça da lista a que foi aplicada esta seleção
*/


data* selecao_inf_dea_ratio(data* head,char tipo[],int flagRatio){
    data* aux;
    variableData* aux2;
    variableData* temp=NULL;
    variableData* remover=NULL;
    variableData* anterior=NULL;

    for (aux=head;aux!=NULL;aux=aux->next)                          //este ciclo vai permitir percorrer a lista dos paises
    {
        temp=NULL;
        for (aux2=aux->dadosSemanais;aux2!=NULL;aux2=aux2->next)    //este ciclo vai percorrer a lista de variable data de cada pais
        {
            if(temp==NULL && strcmp(aux2->indicator,tipo)==0)       // se temp for NULL atribuimos o primeiro valor que seja analisado para o indicador em questão 
            {
                temp=aux2;
                //O strtod converte a string para um double logo pode-se perder informação para rácios que são muito mas mesmo muito semelhantes
            }else if (temp!=NULL && ((temp->weekly_count<=aux2->weekly_count && flagRatio==0) || (strtod(temp->rate_14_day,NULL)<=strtod(aux2->rate_14_day,NULL) && flagRatio==1)) && strcmp(aux2->indicator,tipo)==0)  //vai decidir se o valor que está em temp é ou não atualizado com base nos parametros de entrada
            {
                if ((temp->weekly_count==aux2->weekly_count && flagRatio==0) || (strtod(temp->rate_14_day,NULL)==strtod(aux2->rate_14_day,NULL) && flagRatio==1)) 
                {
                    if (strcmp(temp->year_week,aux2->year_week)<0) //caso os valores sejam iguais, é desenpatado ficando data mais recente
                    {
                        temp=aux2;
                    }
                }else{
                    temp=aux2;
                }
            }
        }

        /*após este pedaço de codigo a variavel temp tem o endereço do nó da lista selecionado*/

        aux2=aux->dadosSemanais;
        remover=NULL;
        anterior=NULL;
        
        while (aux2!=NULL)  //este while serve para percorrer a lista da variable data e dar free a todos os nós que não foram selecionados
        {
            if (aux2==temp){
                    anterior = aux2;
                    aux2 = aux2->next;
                    continue;
            }

            remover=aux2;

            if (anterior) {
                anterior->next = remover->next;
            } else {
                aux->dadosSemanais = remover->next;
            }
            
            aux2 = aux2->next;
            free(remover);
            
        }
    }
    return head;
}   
