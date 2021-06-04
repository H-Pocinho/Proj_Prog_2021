#include "covid19.h"

/*
*Nome da funcao: dados_all
*
*Objetivo da funcao: Lê a totalidade do ficheiro e coloca em memória
*
*Argumentos de entrada: 
*           str -> nome do ficheiro
*
*Argumentos de saida: Uma struct chamada dados que contem **ficheiro, ou seja o ponteiro para o ficheiro em memória e nLinhas que é o numero de linhas do ficheiro
*/

returnStruct dados_all(char str[]){
    returnStruct dados;
    FILE *fpIN;

    char  linha[300]={'\0'};
    char *token; 
    const char separador[2] = ",";
    char **ficheiro = NULL;
    int nLinhas=0;

    if ((fpIN= fopen(str, "r"))==NULL){                                     //abre o ficheiro
        printf("Não foi possivel abrir o ficheiro. Programa terminado\n");
        liberta_mem_ficheiros(ficheiro,nLinhas);
        exit(EXIT_FAILURE);
    } 

    fgets(linha,300,fpIN);                                                  //vai ver se a primeira linha é cabeçalho
    token = strtok(linha,separador);
    token = strtok(NULL, separador);
      

    if (strcmp(token,"country_code")!=0){                                    //Se a primeira linha não for um cabeçalho dá erro
        printf("-1 Erro de Leitura\n");
        printf("Cabeçalho mal formatado\n");
        liberta_mem_ficheiros(ficheiro,nLinhas);
        fclose(fpIN); 
        exit(EXIT_FAILURE);
    }      
                                                                
    while (fgets(linha,300,fpIN)!=NULL)                                     //percorre o  programa e guarda-o em memória
    {
        if(verifica_linha(linha,nLinhas+2)){                                //verifica se a linha é válida
            liberta_mem_ficheiros(ficheiro,nLinhas);
            fclose(fpIN); 
            exit(EXIT_FAILURE);
        }                              

        if (ficheiro==NULL || (nLinhas%1)==0)  
        {
            ficheiro = (char**)realloc(ficheiro, (nLinhas+1)*sizeof(char*));
            if (ficheiro==NULL){
                printf("realloc falhou. ficheiro demasiado grande. programa terminado.\n");
                liberta_mem_ficheiros(ficheiro,nLinhas);
                fclose(fpIN); 
                exit(EXIT_FAILURE);
            }
        }

            if ((ficheiro[nLinhas]= (char*)malloc(strlen(linha)+2))==NULL){
                printf("malloc falhou. ficheiro demasiado grande. programa terminado.\n");
                liberta_mem_ficheiros(ficheiro,nLinhas);
                fclose(fpIN); 
                exit(EXIT_FAILURE);
            }

        strcpy(ficheiro[nLinhas++],linha);
    }
    fclose(fpIN);                                       //fecha o ficheiro
                                                        // guarda informação relevante numa struct, nomeadamente
    dados.ponteiroFicheiro=ficheiro;                    // O ponteiro para o inicio do ficheiro em memória
    dados.nLinhas=nLinhas;                              // O numero de linhas do ficheiro em memória
    return dados;
}

/*
*Nome da funcao: dados_cont
*
*Objetivo da funcao: Lê apenas as linhas do ficheiro relativas a um continente e coloca em memória
*
*Argumentos de entrada: 
*           str -> nome do ficheiro
*           continente -> nome do continente que é desejado
*
*Argumentos de saida: Uma struct chamada dados que contem **ficheiro, ou seja o ponteiro para o ficheiro em memória e nLinhas que é o numero de linhas do ficheiro
*/

returnStruct dados_cont(char str[],char continente[]){
    returnStruct dados;
    FILE *fpIN;

    char  linha[300]={'\0'};
    char linhaTEMP[300];
    char **ficheiro = NULL;
    int nLinhas=0;        //Numero de linhas com continentes válidos
    int ctgLinhas=0;      //Contagem de totalidade de linhas
    char *token; 
    const char separador[2] = ",";
    int o;               
    int flagContinente=0;//Indica se o pais pertence ao continente correcto

    if ((fpIN= fopen(str, "r"))==NULL){                               //abre o ficheiro
        printf("Não consegui abrir o ficheiro. Programa terminado\n");
        liberta_mem_ficheiros(ficheiro,nLinhas);
        exit(EXIT_FAILURE);
    } 

    fgets(linha,300,fpIN);                                              //vai ver se a primeira linha é cabeçalho
    token = strtok(linha,separador);
    token = strtok(NULL, separador);
      

    if (strcmp(token,"country_code")!=0){                              //Se a primeira linha não for um cabeçalho dá erro
        printf("-1 Erro de Leitura\n");
        printf("Cabeçalho mal formatado\n");
        liberta_mem_ficheiros(ficheiro,nLinhas);
        fclose(fpIN); 
        exit(EXIT_FAILURE);
    }                                                                   
    
    while (fgets(linha,300,fpIN)!=NULL)
    {   
        if(verifica_linha(linha,ctgLinhas+2)){                          //Verifica se a linha é válida
            liberta_mem_ficheiros(ficheiro,nLinhas);
            fclose(fpIN); 
            exit(EXIT_FAILURE);
        }

        ctgLinhas++;
        flagContinente=0;
        strcpy(linhaTEMP,linha);
        token = strtok(linhaTEMP, separador);

        for(o = 0; o < 3;o++ )
        {
            token = strtok(NULL, separador);
            if (strcmp(token,continente)==0){                           //vê-se a linha é relativa ao continente pedido
                flagContinente=1;
                break;
            }
        }

        if (flagContinente==1)                                         //coloca as linhas pedidas em memória
        {
            if ((ficheiro==NULL|| (nLinhas%1)==0))  
            {
                ficheiro= (char**)realloc(ficheiro, (nLinhas+1)*sizeof(char*));
                if (ficheiro==NULL){
                    printf("realloc falhou. ficheiro demasiado grande. programa terminado.\n");
                    liberta_mem_ficheiros(ficheiro,nLinhas);
                    fclose(fpIN); 
                    exit(EXIT_FAILURE);
                }
            }

            if ((ficheiro[nLinhas]= (char*)malloc(strlen(linha)+2))==NULL){
                printf("malloc falhou. ficheiro demasiado grande. programa terminado.\n");
                liberta_mem_ficheiros(ficheiro,nLinhas);
                fclose(fpIN); 
                exit(EXIT_FAILURE);
            }
            strcpy(ficheiro[nLinhas++], linha); 
        }
        

    }
    fclose(fpIN);                                       // fecha o ficheiro
                                                        // guarda informação relevante numa struct, nomeadamente
    dados.ponteiroFicheiro=ficheiro;                    // O ponteiro para o inicio do ficheiro em memória
    dados.nLinhas=nLinhas;                              // O numero de linhas do ficheiro em memória
    return dados;
}

/*
*Nome da funcao: read_DAT
*
*Objetivo da funcao: Cria o ficheiro DAT de saida do programa
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser colocada no ficheiro
*           nome -> nome do ficheiro a ser criado

*Argumentos de saida: Um ponteiro para a cabeça da lista criada com os dados lido do ficheiro
*/

data* read_DAT(data *head,char nome[]){
    char finalizador='0';
    char fimFicheiro='0';
    FILE *fptr;
    data *noData;
    variableData *noVariableData;
    
    if ((fptr = fopen(nome,"rb"))==NULL){                                                           //Abre o ficheiro
        printf("Não foi possivel abrir o ficheiro. Programa terminado\n");
        exit(EXIT_FAILURE);
    } 
    
    while(fimFicheiro!='&'){                                                                        //Vai percorrer o ficheiro até encontrar o caracter de fim de ficheiro
        finalizador='0';

        if((noData = (data*) calloc(1,sizeof(data)))==NULL){                                        //Aloca espaço para o nó
            printf("Calloc falhou\n");
            exit(EXIT_FAILURE);
        }

        fread(noData,sizeof(data),1,fptr);                                                          //Preenche o espaço alocado com a informação dos ficheiro
        noData->next=NULL;
        noData->dadosSemanais=NULL;
        head=insere_cauda_data(head,noData);                                                       //Coloca o nó na lista

        while (finalizador!='#')                                                                    //Percorre o ficheiro até encontrar o caracter de fim de nó
        {
            if((noVariableData = (variableData*) calloc(1,sizeof(variableData)))==NULL){            //Aloca espaço para o nó
                printf("Calloc falhou\n");
                exit(EXIT_FAILURE);
            }
            
            fread(noVariableData,sizeof(variableData),1,fptr);                                      //Preenche o espaço alocado com a informação dos ficheiro
            noVariableData->next=NULL;
            noData->dadosSemanais=insere_cauda_variable_data(noData->dadosSemanais,noVariableData);//Coloca o nó na lista

            fread(&finalizador,sizeof(char),1,fptr);                                                //Procura o caracter finalizador
            if (finalizador!='#')
            {
                fseek(fptr,-sizeof(char),SEEK_CUR);                                                 //Se não for puxa o ponteiro para onde estava antes de tentar ler o caracter finalizador
            }
        }

        fread(&fimFicheiro,sizeof(char),1,fptr);                                                    //Procura o caracter de fim de ficheiro
        if (fimFicheiro!='&')
        {
            fseek(fptr,-sizeof(char),SEEK_CUR);                                                     //Se não for puxa o ponteiro para onde estava antes de tentar ler o caracter de fim de ficheiro
        }
    }


    fclose(fptr);                                                                                   //Fecha o ficheiro
    return head;
}

/*
*Nome da funcao: file_output_CSV
*
*Objetivo da funcao: Cria o ficheiro CSV de saida do programa
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser colocada no ficheiro
*           nome -> nome do ficheiro a ser criado
*/

void file_output_CSV(data *head,char nome[]){
    FILE *fptr;
    data *aux;
    variableData *aux2;
    
    if ((fptr = fopen(nome,"w"))==NULL){                                     //abre o ficheiro
        printf("Não foi possivel abrir o ficheiro. Programa terminado\n");
        exit(EXIT_FAILURE);
    } 

    fprintf(fptr,"country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");      //cria a linha de cabeçalho
    for (aux=head;aux!=NULL;aux=aux->next)
    {   
        for (aux2=aux->dadosSemanais;aux2!=NULL;aux2=aux2->next)
        {
            fprintf(fptr,"%s,%s,%s,%ld,%s,%d,%s,%s,%ld\n",aux->country,aux->country_code,aux->continent,aux->population,aux2->indicator,aux2->weekly_count,aux2->year_week,aux2->rate_14_day,aux2->cumulative_count); //cria uma linha com base no que está em memória
        }
    }
    fclose(fptr);              
    liberta_lista(head);    //liberta a lista
}

/*
*Nome da funcao: file_output_DAT
*
*Objetivo da funcao: Cria o ficheiro DAT de saida do programa
*
*Argumentos de entrada: 
*           *head -> ponteiro para o inicio da lista que vai ser colocada no ficheiro
*           nome -> nome do ficheiro a ser criado
*/

void file_output_DAT(data *head,char nome[]){
    FILE *fptr;
    data *aux;
    variableData *aux2;
    
    if ((fptr = fopen(nome,"wb"))==NULL){                                           //abre o ficheiro
        printf("Não foi possivel abrir o ficheiro. Programa terminado\n");
        exit(EXIT_FAILURE);
    } 

    
    for (aux=head;aux!=NULL;aux=aux->next)
    {   
        if (aux->dadosSemanais!=NULL)
        {
            fwrite(aux,sizeof(data),1,fptr);                                        //cria uma linha com base no que está em memória da lista principal
        }
        
        for (aux2=aux->dadosSemanais;aux2!=NULL;aux2=aux2->next)
        {
            fwrite(aux2,sizeof(variableData),1,fptr);                               //cria uma linha com base no que está em memória da lista de dados variaveis
        }

        if (aux->dadosSemanais!=NULL)
        {
            fwrite("#",sizeof(char),1,fptr);                                            //Insere um caracter de fim de nó
        }
        
        
    }
    fwrite("&",sizeof(char),1,fptr);                                                //Insere um caracter de  fim de ficheiro
    fclose(fptr);              
    liberta_lista(head);                                                            //liberta a lista
}

/*
*Nome da funcao: liberta_mem_ficheiro
*
*Objetivo da funcao: Permite apagar o ficheiro da memória com base nos parametros da struct criada pelas funções de leitura
*
*Argumentos de entrada: 
*           *ficheiro -> ponteiro para o inicio do ficheiro
*           nlinhas -> numero de linhas do ficheiro em memória
*/

void liberta_mem_ficheiros(char *ficheiro[], int nLinhas){
    int i;

    if (ficheiro!=NULL) {                   //percorre a memória e vai limpando o ficheiro linha a linha
        for (i=0 ; i < nLinhas ; i++)
            if (ficheiro[i]!=NULL)
                free(ficheiro[i]);
        free(ficheiro);
    }
}

/*
*Nome da funcao: verifica_linha
*
*Objetivo da funcao: Verifica se uma linha é válida
*
*Argumentos de entrada: 
*           linha -> linha que vai ser analisada
*           nmrLinha -> numero da linha do ficheiro que vai ser analisada
*
*Argumentos de saida: 1 caso a linha seja inválida | 0 caso a linha seja inválida
*/

int verifica_linha(char linha[500],int nmrLinha){
    int i=0,o=0,coluna=1;
    char keywordsValidas[7][10]={"Europe","Asia","Africa","Oceania","America","cases","deaths"};
    char guardaColuna[10]={'\0'};                                                       //Vai guarda uma word caso seja relevante
    int flagAnalisado=1;

    while (i<strlen(linha))                                                             //Vai percorrer a linha caracter a caracter e vai analisar a linha com base nas divisões de coluna
    {
        if(coluna==1){
            if(isalpha(linha[i])==0 && linha[i]!=' ' && linha[i]!='-'){                 //Analise da coluna 1 (paises)
                fprintf(stderr,"-1 Erro de Leitura\n");
                fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                return 1;
            }
        }

        if(coluna==2){                                                                  //Analise da coluna 2 (codigo dos paises)
            o++;
            if(linha[i]<65 || linha[i]>90 || (linha[i+1]==',' && o<3) || o>3){
                fprintf(stderr,"-1 Erro de Leitura\n");
                fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                return 1;
            }
        }

        if(coluna==3 || coluna==5){                                                     //Analise das colunas 3 e 5 (continente e indicador)
            guardaColuna[o]=linha[i];
            o++;
            if(isalpha(linha[i])==0){
                fprintf(stderr,"-1 Erro de Leitura\n");
                fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                return 1;
            }
        }

        if(coluna==4||coluna==6||coluna==9){                                            //Analise das colunas 4,6,9 (população, contagem semanal e contagem acumulada)
            if(isdigit(linha[i])==0){
                fprintf(stderr,"-1 Erro de Leitura\n");
                fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                return 1;
            }
        }

        if (coluna==7){                                                                 //Analise da coluna 7 (datas)
            for ( o = i; o < i+4; o++)
            {
                if(isdigit(linha[o])==0){
                    fprintf(stderr,"-1 Erro de Leitura\n");
                    fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                    return 1;
                }
            }
            
            if(linha[o++]!='-'){
                    fprintf(stderr,"-1 Erro de Leitura\n");
                    fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                    return 1;
            }
            
            for ( o = i+5; o < i+7; o++)
            {
                if(isdigit(linha[o])==0){
                    fprintf(stderr,"-1 Erro de Leitura\n");
                    fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                    return 1;
                }
            }
            i=o-1;
        }
        
        if (coluna==8)                                                                  //Analise da coluna 8 (rácio)
        {
            if(isdigit(linha[i])==0 && linha[i]!='.'){
                fprintf(stderr, "-1 Erro de Leitura\n");
                fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                return 1;
            }
        }

        i++;

        if (linha[i]==',')                                                              //Vê se faltam colunas e confirma os valores da coluna 3 e 5
        {
            if (coluna==5 || coluna==3)
            {
                for ( o = 0; o < 7; o++)
                {
                    if(strcmp(guardaColuna,keywordsValidas[o])==0){
                        if (!((o==5 || o==6) && coluna==5) && !((o!=5 && o!=6) && coluna==3))
                        {
                            fprintf(stderr,"-1 Erro de Leitura\n");
                            fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                            return 1;
                        }
                        flagAnalisado=1;
                    }
                }

                if(flagAnalisado==0){
                    fprintf(stderr,"-1 Erro de Leitura\n");
                    fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
                    return 1;
                }
                  
            }
            
            flagAnalisado=0;            //permite limpar e preparar as variaveis auxiliares para a proxima iteração do ciclo
            for ( o = 0; o < 10; o++)
            {
                guardaColuna[o]=0;
            }
            coluna++;
            i++;
            o=0;                        

            if (linha[i]==',' && coluna !=8 ){
                fprintf(stderr,"-1 Erro de Leitura\n");
                fprintf(stderr,"Falta um parametro na linha %d coluna %d\n",nmrLinha,coluna);
                return 1;
            }
            if (linha[i]==',' && coluna==8 ){
                coluna++;
                i++;
            }
        }

        if ((linha[i]==13 || linha[i]=='\n')  && coluna==9 && linha[i-1]!=','){
                return 0;
        }else if((linha[i]==13 || linha[i]=='\n')  && coluna==9 && linha[i-1]==','){        //Ultimas verificações da coluna 9
            fprintf(stderr,"-1 Erro de Leitura\n");
            fprintf(stderr,"Na linha %d coluna %d\n",nmrLinha,coluna);
            return 1;
        }
    }
    return 0;
}