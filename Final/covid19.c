#include "covid19.h"

/*
*Nome da funcao: main
*
*Objetivo da funcao: Executar o programa
*
*Argumentos de entrada: 
*           argc -> numero de inputs
*           *argv -> ponteiro para os inpus
*
*Argumentos de saida: -1 caso haja um erro | 0 caso o programa seja executado com sucesso
*/

int main(int argc, char *argv[]){
    
    data *headPais=NULL;
    inputStruct dadosInput;
    returnStruct dadosFicheiro;

    dadosInput=verificacao_input(argc,argv);                                            //leitura de inputs da linha de comandos

    if(dadosInput.erro!=0){                                                             //Se houver um erro no inputa da linha de comandos
        printf("%s\n",dadosInput.mensagemErro);                                         //Mostra mensagem relativa a esse erro
        texto_ajuda();                                                                  //Mostra a mensagem de ajuda
        return -1;                                                                      //Dá return a -1
    }

    switch (dadosInput.inputType)                                                       //Dependendo do tipo de ficheiro de input
    {
    case 0:                                                                             //Se for CSV
        if (dadosInput.leituraDados==0)
        {
            dadosFicheiro = dados_all(dadosInput.inputName);                            //Pode ler a totalidade do ficheiro
        }else{
            dadosFicheiro = dados_cont(dadosInput.inputName,dadosInput.continente);     //Ou ler apenas um continente especifico
        }
    break;

    case 1:                                                                             //Se for DAT
            headPais=read_DAT(headPais,dadosInput.inputName);                           //Vai ser lido
                switch (dadosInput.outputType)
                    {
                    case 0:
                        file_output_CSV(headPais,dadosInput.outputName);                //E pode ser impresso como CSV
                    break;
                    
                    case 1:
                        file_output_DAT(headPais,dadosInput.outputName);                //Ou como DAT dependendo do input dado
                    break;
                    }
            return 0;                                                                   //Se o ficheiro de input tiver sido do tipo DAT o programa acaba apos a escrita do ficheiro
    break;
    }



    headPais =  cria_lista_paises(headPais,dadosFicheiro);                              //Após a leitura vai ser criada uma lista com a informação que está em memória                   

    switch (dadosInput.selecaoDados)                                                    //Vai selecionar dados
    {
    case 1:
        headPais=selecao_inf_dea_ratio(headPais,"cases",0);                             //Semana com mais casos
    break;

    case 2:
        headPais=selecao_inf_dea_ratio(headPais,"deaths",0);                            //Semana com mais mortos
    break;

    case 3:
        headPais=selecao_inf_dea_ratio(headPais,"cases",1);                             //Semana com maior rácio de infectados
    break;

    case 4:
        headPais=selecao_inf_dea_ratio(headPais,"deaths",1);                            //Semana com maior rácio de mortes
    break;

    default:
    break;
    }

    switch (dadosInput.restricaoDados)                                                  //Vai ser aplicada restrição de dados
    {
    case 1:
        headPais=restricao_min(headPais,dadosInput.popRestricao);                       //Paises com mais população do que o limite
    break;

    case 2:
        headPais=restricao_max(headPais,dadosInput.popRestricao);                       //Paises com menos população do que o limite
    break;

    case 3:
        headPais=restricao_data(headPais,dadosInput.dataRestricao[0]);                  //Dados relativos apenas a uma semana
    break;

    case 4:
        headPais=restricao_datas(headPais,dadosInput.dataRestricao[0],dadosInput.dataRestricao[1]);       //Dados relativos a um intervalo de datas  
    break;
    
    default:
    break;
    }


    switch (dadosInput.ordenecaoDados)                                                  //Vai ser aplicada uma ordenação de dados
    {
    case 1:
        headPais=ordem_pop(headPais);                                                   //Ordem decrescente de população
    break;

    case 2:
        headPais=ordem_inf_dea(headPais,dadosInput,"cases");                            //Ordem decrescente do numero total de infectados numa dada semana
    break;

    case 3:
        headPais=ordem_inf_dea(headPais,dadosInput,"deaths");                           //Ordem decrescente do numero total de mortes numa dada semana
    break;
    
    default:
        headPais=ordem_alfa(headPais);
    break;
    }

    headPais=ordem_variable_data(headPais);                                             //Coloca os dados variaveis por ordem decrescente de datas e primeiro as linhas referentes a casos e depois a mortes

    switch (dadosInput.outputType)                                                      //Depois disto tudo vai ser criado um ficheiro com a informação relevante
    {
    case 0:
        file_output_CSV(headPais,dadosInput.outputName);                                //Cria um CSV 
    break;
    
    case 1:
        file_output_DAT(headPais,dadosInput.outputName);                                //Cria um DAT
    break;
    }

    return 0;                                                                           //Programa acaba
}