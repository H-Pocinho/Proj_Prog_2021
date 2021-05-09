#include "covid19.h"



inputStruct verificacaoInput(int counter, char *input[]){
    char inputsPossiveis[7][3]={"-L","-S","-D","-P","-i","-o","-h"};
    char continentesPossiveis[5][10]={"Europe","Asia","Africa","Oceania","America"};
    char string[250];
    int i,j,o;
    int flagIO=0;
    char *token; 
    const char separador[2] = ".";
    inputStruct parametros;
    parametros.leituraDados=0;
    parametros.ordenecaoDados=0;
    parametros.selecaoDados=0;
    parametros.restricaoDados=0;
    parametros.erro=1;
    strcpy(parametros.mensagemErro, "Introduza -i e -o");


    for ( i = 0; i < counter; i++)
    {
        for ( j = 0; j < 7; j++)
        {
            if (strcmp(input[i],inputsPossiveis[j])==0)
            {
                switch (j)
                {

                case 0:
                    if(strcmp(input[i+1],"all")!=0){
                        parametros.leituraDados=1;
                        for ( o = 0; o < 5; o++){
                            if (strcmp(input[i+1], continentesPossiveis[o])==0){
                                strcpy(parametros.continente,input[i+1]);
                                break;
                            }
                        }

                        if (o == 5){
                            parametros.erro=1;
                            strcpy(parametros.mensagemErro, "Erro na leitura do input continente");  
                            return parametros;
                        }
                    }
                break;
                
                case 1:
                    if (strcmp(input[i+1],"alfa")==0){
                        parametros.ordenecaoDados=0;
                    }else if(strcmp(input[i+1],"pop")==0){
                        parametros.ordenecaoDados=1;
                    }else if(strcmp(input[i+1],"inf")==0){
                        parametros.ordenecaoDados=2;
                        strcpy(parametros.dataOrdenacao,input[i+2]);
                    }else if(strcmp(input[i+1],"dea")==0){
                        parametros.selecaoDados=3;
                        strcpy(parametros.dataOrdenacao,input[i+2]);
                    }else{
                        parametros.erro=1;
                        strcpy(parametros.mensagemErro, "Erro na leitura do input -S");  
                        return parametros;
                    }
                break;


                case 2:
                    if (strcmp(input[i+1],"inf")==0){
                        parametros.selecaoDados=1;
                    }else if(strcmp(input[i+1],"dea")==0){
                        parametros.selecaoDados=2;
                    }else if(strcmp(input[i+1],"racioinf")==0){
                        parametros.selecaoDados=3;
                    }else if(strcmp(input[i+1],"raciodea")==0){
                        parametros.selecaoDados=4;
                    }else{
                        parametros.erro=1;
                            strcpy(parametros.mensagemErro, "Erro na leitura do input -D");  
                        return parametros;
                    }
                break;

                case 3:
                    if (strcmp(input[i+1],"min")==0){
                        parametros.restricaoDados=1;
                        parametros.popRestricao=atoi(input[i+2]);
                    }else if(strcmp(input[i+1],"max")==0){
                        parametros.restricaoDados=2;
                        parametros.popRestricao=atoi(input[i+2]);
                    }else if(strcmp(input[i+1],"date")==0){
                        parametros.restricaoDados=3;
                        strcpy(parametros.dataRestricao[0],input[i+2]);
                    }else if(strcmp(input[i+1],"dates")==0){
                        parametros.restricaoDados=4;
                        strcpy(parametros.dataRestricao[0],input[i+2]);
                        strcpy(parametros.dataRestricao[1],input[i+3]);
                    }else{
                        parametros.erro=1;
                        strcpy(parametros.mensagemErro, "Erro na leitura do input -P");  
                        return parametros;
                    }
                break;

                case 4:
                    strcpy(parametros.inputName,input[i+1]);
                    strcpy(string,parametros.inputName);
                    token = strtok(string, separador);
                    token = strtok(NULL, separador);
                    if (strcmp(token,"csv")==0)
                    {
                        flagIO++;
                    }else if(strcmp(token,"dat")==0){
                        flagIO++;
                    }else{
                        parametros.erro=1;
                        strcpy(parametros.mensagemErro, "Tipo de ficheiro de input inválido");
                        return parametros;
                    }
                break;

                case 5:
                    strcpy(parametros.outputName,input[i+1]);
                    strcpy(string,parametros.outputName);
                    token = strtok(string, separador);
                    token = strtok(NULL, separador);
                    if (strcmp(token,"csv")==0)
                    {
                        flagIO++;
                    }else if(strcmp(token,"dat")==0){
                        flagIO++;
                    }else{
                        parametros.erro=1;
                        strcpy(parametros.mensagemErro, "Tipo de ficheiro de output inválido");
                        return parametros;
                    }
                break;

                case 6:
                        strcpy(parametros.mensagemErro, "\0");
                    return parametros;
                break;

                default:
                break;
                }
            } 
        }
    }
    if (flagIO==2)
    {
        parametros.erro=0;
        strcpy(parametros.mensagemErro, "\0");
    }
    return parametros;
}