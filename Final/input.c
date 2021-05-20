#include "covid19.h"

/*
*Nome da funcao: verificacao_input
*
*Objetivo da funcao: verifica o input introduzido na linha de comandos
*
*Argumentos de entrada: 
*           counter -> numero de inputs
*           *input -> ponteiro para os inpus
*
*Argumentos de saida: Uma struct chamada parametros que contem toda a informação relevante aos inputs (a estrutura está descrita no header)
* 
*Nota: De forma a garantir a robustez do programa esta função infelizmente ficou bastante grande.
*/

inputStruct verificacao_input(int counter, char *input[]){
    char inputsPossiveis[7][3]={"-L","-S","-D","-P","-i","-o","-h"};                    //Lista de inputs válidos
    char continentesPossiveis[5][10]={"Europe","Asia","Africa","Oceania","America"};    //lista de continentes válidos
    char string[250];                                                                   //String auxiliar que vai conter os nomes dos ficheiros
    int i,j,o;                                                                          //Variaveis auxiliares para loops
    int flagValido=0;                                                                   //Indica se o input é valido
    int flagIO=0;                                                                       //Indica se existe os parametros -i e -o foram passados
    char *token;                                                                        //Token para strtok
    const char separador[2] = ".";                                                      //Separador para strtok
    inputStruct parametros;                                                             //Struct de saida de dados
    parametros.leituraDados=0;                                                          //Inicialização dos campos da struct de saida de dados        
    parametros.ordenecaoDados=0;
    parametros.selecaoDados=0;
    parametros.restricaoDados=0;
    parametros.erro=1;
    strcpy(parametros.mensagemErro, "Introduza -i e -o");


    for ( i = 0; i < counter; i++)                                              //Vai percorrer todos os inputs
    {
        flagValido=0;
        for ( j = 0; j < 7; j++)                                                //Vai percorrer a lista de input válidos
        {
            if (strcmp(input[i],inputsPossiveis[j])==0){                        //Vai comparar o input e lista de inputs válidos
                flagValido=1;
                switch (j)
                {

                case 0:                                                                             //vai analisar o input -L
                    if (i+1>=counter){
                        strcpy(parametros.mensagemErro, "Faltam parametros na opção -L");
                        return parametros;
                    }
                    
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
                            strcpy(parametros.mensagemErro, "Erro na leitura na opção -L");
                            return parametros;
                        }
                    }
                break;
                
                case 1:                                                                             //vai analisar o input -S
                    if (i+1>=counter){
                        strcpy(parametros.mensagemErro, "Faltam parametros na opção -S");
                        return parametros;
                    }
                    if (strcmp(input[i+1],"alfa")==0){
                        parametros.ordenecaoDados=0;
                    }else if(strcmp(input[i+1],"pop")==0){
                        parametros.ordenecaoDados=1;
                    }else if(strcmp(input[i+1],"inf")==0){
                        if (i+2>=counter){
                            strcpy(parametros.mensagemErro, "Faltam parametros na opção -S");
                            return parametros;
                        }
                        if(is_date(input[i+2])==0){
                            strcpy(parametros.mensagemErro, "Data inválida na opção -S");
                            return parametros;
                        }

                        parametros.ordenecaoDados=2;
                        strcpy(parametros.dataOrdenacao,input[i+2]);

                    }else if(strcmp(input[i+1],"dea")==0){
                        if (i+2>=counter){
                            strcpy(parametros.mensagemErro, "Faltam parametros na opção -S");
                            return parametros;
                        }
                        if(is_date(input[i+2])==0){
                            strcpy(parametros.mensagemErro, "Data inválida na opção -S");
                            return parametros;
                        }

                        parametros.ordenecaoDados=3;
                        strcpy(parametros.dataOrdenacao,input[i+2]);

                    }else{
                        parametros.erro=1;
                        strcpy(parametros.mensagemErro, "Erro na leitura do input -S");  
                        return parametros;
                    }
                break;


                case 2:                                                                         //Vai analisar o input -D
                    if (i+1>=counter){
                        strcpy(parametros.mensagemErro, "Faltam parametros na opção -D");
                        return parametros;
                    }
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

                case 3:                                                                         //Vai analisar o input -P
                    if (i+2>=counter){
                        strcpy(parametros.mensagemErro, "Faltam parametros na opção -P");
                        return parametros;
                    }
                    if (strcmp(input[i+1],"min")==0){
                        if (atoi(input[i+2])==0 && strcmp(input[i+2],"0")!=0){
                            strcpy(parametros.mensagemErro, "Numero inválido na opção -P");
                            return parametros;
                        }

                        parametros.restricaoDados=1;
                        parametros.popRestricao=atoi(input[i+2]);

                    }else if(strcmp(input[i+1],"max")==0){
                        if (atoi(input[i+2])==0 && strcmp(input[i+2],"0")!=0){
                            strcpy(parametros.mensagemErro, "Numero inválido na opção -P");
                            return parametros;
                        }

                        parametros.restricaoDados=2;
                        parametros.popRestricao=atoi(input[i+2]);

                    }else if(strcmp(input[i+1],"date")==0){

                        parametros.restricaoDados=3;

                        if( is_date(input[i+2])==0 ){
                            strcpy(parametros.mensagemErro, "Data inválida na opção -P");
                            return parametros;
                        }

                        strcpy(parametros.dataRestricao[0],input[i+2]);

                    }else if(strcmp(input[i+1],"dates")==0){
                        if (i+3>=counter){
                            strcpy(parametros.mensagemErro, "Faltam parametros na opção -P");
                            return parametros;
                        }
                        if( is_date(input[i+2])==0 || is_date(input[i+3])==0 ){
                            strcpy(parametros.mensagemErro, "Data inválida na opção -P");
                            return parametros;
                        }

                        parametros.restricaoDados=4;
                        strcpy(parametros.dataRestricao[0],input[i+2]);
                        strcpy(parametros.dataRestricao[1],input[i+3]);

                    }else{
                        parametros.erro=1;
                        strcpy(parametros.mensagemErro, "Erro na leitura do input -P");  
                        return parametros;
                    }
                break;

                case 4:                                                                 //Vai analisar o input -i
                    if (i+1>=counter){
                        strcpy(parametros.mensagemErro, "Faltam parametros na opção -i");
                        return parametros;
                    }
                    strcpy(parametros.inputName,input[i+1]);
                    strcpy(string,parametros.inputName);
                    token = strtok(string, separador);
                    if((token = strtok(NULL, separador))==NULL){
                        strcpy(parametros.mensagemErro, "Tipo de ficheiro de input inválido");
                        return parametros;
                    }
                    if (strcmp(token,"csv")==0){
                        parametros.inputType=0;
                        flagIO++;
                    }else if(strcmp(token,"dat")==0){
                        parametros.inputType=1;
                        flagIO++;
                    }else{
                        parametros.erro=1;
                        strcpy(parametros.mensagemErro, "Tipo de ficheiro de input inválido");
                        return parametros;
                    }
                break;

                case 5:                                                                             //vai analisar o input -o
                    if (i+1>=counter){
                        strcpy(parametros.mensagemErro, "Faltam parametros na opção -o");
                        return parametros;
                    }
                    strcpy(parametros.outputName,input[i+1]);
                    strcpy(string,parametros.outputName);
                    token = strtok(string, separador);
                    if((token = strtok(NULL, separador))==NULL){
                        strcpy(parametros.mensagemErro, "Tipo de ficheiro de output inválido");
                        return parametros;
                    }
                    if (strcmp(token,"csv")==0){
                        parametros.outputType=0;
                        flagIO++;
                    }else if(strcmp(token,"dat")==0){
                        parametros.outputType=1;
                        flagIO++;
                    }else{
                        parametros.erro=1;
                        strcpy(parametros.mensagemErro, "Tipo de ficheiro de output inválido");
                        return parametros;
                    }
                break;

                case 6:                                             //Analise do input -h
                    strcpy(parametros.mensagemErro, "\0");
                    return parametros;
                break;

                default:
                break;
                }
            }
        }

        if (input[i][0]=='-' && flagValido!=1){             //Indica se a opção é valida ou não
            strcpy(string,"Opção ");
            strcat(string,input[i]);
            strcat(string," inválida");
            strcpy(parametros.mensagemErro,string);
            return parametros;
        }
            
    }
    if (flagIO==2){                                        //Verifica se foi introduzido -i e -o
        parametros.erro=0;
        strcpy(parametros.mensagemErro, "\0");
    }
    return parametros;
}

/*
*Nome da funcao: is_date
*
*Objetivo da funcao: verifica se a string que lhe é passada é uma data no formato yyyy-ww
*
*Argumentos de entrada: 
*           string -> string que quer ser analisada
*
*Argumentos de saida: 0 data inválida | 1 data válida
*/

int is_date(char string[10]){
    char separador[2] = "-";
    char *token;
    char TEMP[10];
    strcpy(TEMP,string);
    int j=0;

    if((token = strtok(TEMP,separador))==NULL){
        return 0;
    }

    while(j<strlen(token)){
        if (isdigit(token[j])==0)
        {
            return 0;
        }
        j++;
    }

    if((token = strtok(NULL,separador))==NULL){
        return 0;
    }
    j=0;
    while(j<strlen(token)){
        if (isdigit(token[j])==0)
        {
            return 0;
        }
        j++;
    }

    if (atoi(token)>53 || atoi(token)<0)
    {
        return 0;
    }

    return 1;
}