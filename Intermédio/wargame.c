/*
Projecto feito por:
Henrique Alves Pocinho Nº99952
Rodrigo Pereira Nº100080

Wargame
*/


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <time.h>


/*
*Nome da funcao: textoAjuda
*
*Objetivo da funcao: Imprime o texto de ajuda em caso de erro
*/

void textoAjuda(){
    printf("\nBem-vindo ao WarGames\n");
    printf("Projecto de Prog feito por:\n");
    printf("\tHenrique Alves Pocinho Nº99952\n");
    printf("\tRodrigo Pereira Nº100080\n\n");
    printf("Comandos:\n");
    printf("-t AxB : Serve para introduzir as dimensoes do tabuleiro onde A e o numero de linhas e B e o numero de colunas. (default 9x9)\n");
    printf("-j x : modo de jogo entre 0 e 2. (default 0)\n");
    printf("-p x : modo de posicionamento das pecas pelo computador, entre 1 e 2. (default 1)\n");
    printf("-d x : modo de disparo do computador, entre 1 e 3.(default 1)\n");
    printf("-Y X : y e um numero entre 1 e 8 que representa uma das pecas, e X e o numero dessas pecas que existem.\n");
};



/*
*Nome da funcao: limpaStdin
*
*Objetivo da funcao: Limpa o standard input para não haver erros ou problemas durante a introdução de coordenadas
*/

void limpaStdin(){
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}



/*
*Nome da funcao: restricaoUm
*
*Objetivo da funcao: Aplica a restrição 1
*
*Argumentos de entrada: l e c (linha e coluna ou seja a posição inicial da quadrivcula em que se vai verificar a restrição) e o tabuleiro
*
*Argumentos de saida: 1 caso a restrição não se verifique e 0 caso se verifique
*/

int restricaoUm(int l, int c,char tabuleiro[15][24]){
    int i,j,m,n,ltemp,ctemp;
        for ( i = l; i < (l+3); i++) //Seleciona a peça na horizontal
        {
            for (j = c; j < (c+3); j++) //seleciona a peça na vertical
            {
                if (tabuleiro[i][j] != 45) //Vê se a peça não é um "-"
                {
                    for ( m = -1; m <=1; m++) //Vai estudar a quadricula cirncundante peça a peça(horizontal)
                    {
                        for ( n = -1; n <= 1; n++) //Vai estudar a quadricula cirncundante (vertical)
                        {
                            ltemp = m+i;
                            ctemp = n+j;

                           if ( (((ltemp < l) || (ltemp > (l+3))) || ((ctemp < c) || (ctemp > (c+3)))) && (((ltemp)<15 && (ltemp)>=0) && ((ctemp)<24 && (ctemp)>=0))) //Verifica se a posição a ver avaliada está dentro do tabuleiro e se está fora da quadricula em que a peça se encontra
                           {
                               if (tabuleiro[ltemp][ctemp] != 45 ) //O que faz a verificação
                               {
                                   return 1;
                               }
                           }
                        }
                    }
                }
            }
        }
    return 0;
};



/*
*Nome da funcao: mostraTabuleiro
*
*Objetivo da funcao: Imprime o tabuleiro
*
*Argumentos de entrada: linhas e colunas (numero de linhas e de colunas) e tabuleiro para ser impresso
*/

void mostraTabuleiro(int linhas, int colunas,char tabuleiro[15][24]){
    int i, j,nmr;
    char letras [24] = {"ABCDEFGHIJKLMNOPQRSTUVWX"};
    for (i = 0; i<linhas; i++){ //Altera a linha
        for (j = 0; j<colunas; j++){ //Altera a coluna
            if (j==0){
                nmr=linhas-i;
                if (nmr<10){
                    printf(" %d ",nmr);
                }
                else{
                    printf("%d ",nmr);
                }
            }
            printf("%c ", tabuleiro[i][j]); //Print do valor da coordenada selecionada
        }
        printf("\n");
    }
    printf("   ");
    for (i = 0; i < colunas; i++){
        printf("%c ",letras[i]);
    }
    printf("\n");
};



/*
*Nome da funcao: modoPos1
*
*Objetivo da funcao: Aplica o modo de posicionamento 1
*
*Argumentos de entrada: linhas e colunas (numero de linhas e de colunas) e tabuleiro em que se quer colocar as peças, o array peças como referencia para o programa poder anotar o nmr de peças que usou e bilbio para as peças poderem ser chamadas
*/

void modoPos1(int linhas,int colunas, char tabuleiro[][24],int pecas[], char biblio[43][3][3]){
    int i,j,m,n,tipoPeca,pecaRandom,try;
    for (i = 0; i < linhas; i=i+3){  //altera a quadricula na horizontal
        for ( j = 0; j < colunas; j=j+3){ //altera a quadricula na vertical
            try=0;
            do{

                pecaRandom=((rand()%43)); //seleciona uma peça da biblioteca de peças aleatoriamente

                for ( m = 0; m < 3 ; m++){ //altera a coluna
                    for (n = 0; n < 3; n++){ //altera a linha

                        tabuleiro[(m+i)][(n+j)]=biblio[0][m][n]; //garantir que o local de posicionamento está limpo
                    }
                }

                for ( m = 0; m < 3 ; m++){
                    for (n = 0; n < 3; n++){
                        tabuleiro[(m+i)][(n+j)]=biblio[pecaRandom][m][n]; //coloca as coordenada da peça com o valor da coordenada da peça selecionada
                    }
                }


                if (try>=3){
                    for ( m = 0; m < 3 ; m++){
                        for (n = 0; n < 3; n++){
                            tabuleiro[(m+i)][(n+j)]=biblio[5][m][n];
                        }
                    }
                }//Se a peça não for colocada nas 3 tentativas, selecionar a peça No 5 da biblioteca
                try=try+1;
            } while (restricaoUm(i,j,tabuleiro) != 0); //Restrição 1
        }
    }

    for ( i = 0; i < linhas; i=i+3){
        for ( j = 0; j < colunas; j=j+3){
            for ( m = 0; m < 3 ; m++){
                for (n = 0; n < 3; n++){
                    tipoPeca=(int)tabuleiro[(m+i)][(n+j)];
                    if (tipoPeca!=45){
                        pecas[tipoPeca - 49]=pecas[tipoPeca - 49]+1;
                    } //Obter a quantidade de cada peça utilizada
                }
            }
        }
    }

    for ( i = 0; i < 8; i++){
        pecas[i]=pecas[i]/(i+1);
    }  //Guardar a quantidade de cada peça utilizada

};



/*
*Nome da funcao: modoPos2
*
*Objetivo da funcao: Aplica o modo de posicionamento 2
*
*Argumentos de entrada: linhas e colunas (numero de linhas e de colunas) o array pecas que contem a quantidade de peças a serem colocadas, nmrpeças, tabuleiro em que se deseja colocar as peças, biblio de peaçs e o array auxiliar inicioPecas
*
*Argumentos de saida: -1 caso o tabuleiro não consiga ser gerado 1 caso seja gerado com sucesso
*/

int modoPos2(int pecas[8], int linhas, int colunas, int nmrPecas, char tabuleiro[][24],char biblio[43][3][3],int inicioPecas[9]){
    int i,j,m,n,l;
    int tipoPeca,variantePeca,posicaoVariante,cnt8tentativas=0,flagPecaUsada,cnt1000=0;
    int pecasUsadas[8]={9,9,9,9,9,9,9,9};
    int nmrTotal= (linhas*colunas)/9; 
    int nmrVazias = nmrTotal-nmrPecas;
    int quantidadePecas[9]={nmrVazias,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]};
    do{
        for (i = 0; i<linhas; i++){
            for (j = 0; j<colunas; j++){
                tabuleiro[i][j]=45;
            }
        } //garantir que o tabuleiro está a zeros
        nmrTotal = (linhas*colunas)/9;
        for ( l = 0; l < 9; l++){
            if (l==0){
                quantidadePecas[l]=nmrVazias; //Quantidade de peças vazias
            }
            else{
                quantidadePecas[l]=pecas[l-1]; //Quantidade de peças com valor
            }
        }

        for (i = 0; i < linhas; i=i+3){ 
            for ( j = 0; j < colunas; j=j+3){ //seleciona uma peça 3x3
                cnt8tentativas=0;
                do{
                    do{
                        flagPecaUsada=0;
                        tipoPeca=rand() % 9; //Seleciona uma dos 9 tipos de peças disponiveis (A peça vazia está incluida)
                        for (l = 0; l < 8; l++){
                            if (tipoPeca==pecasUsadas[l]){
                                flagPecaUsada=1;
                            }
                        }
                        if (flagPecaUsada==1){
                            continue;
                        } //verificar se a peça já foi usada
                    } while (quantidadePecas[tipoPeca]<=0);


                    if (tipoPeca==8){
                        variantePeca=42;
                    }
                    else{
                        variantePeca = (rand() % (inicioPecas[tipoPeca+1] - inicioPecas[tipoPeca])) + inicioPecas[tipoPeca];
                    }

                    for ( m = 0; m < 3 ; m++){
                        for (n = 0; n < 3; n++){
                            tabuleiro[(m+i)][(n+j)]=biblio[variantePeca][m][n]; //Substitui a coordenada pelo valor da peça escolhida
                        }
                    }

                    if (restricaoUm(i,j,tabuleiro) == 0){ //Caso cumpra a restrição 1
                        quantidadePecas[tipoPeca]--;
                        nmrTotal--;
                        break;
                    }

                    if (tipoPeca==8){
                        pecasUsadas[cnt8tentativas]=tipoPeca;
                        cnt8tentativas++;
                    }
                    else{
                        posicaoVariante=0;
                        do{
                            variantePeca = inicioPecas[tipoPeca]+posicaoVariante;
                            for ( m = 0; m < 3 ; m++){
                                for (n = 0; n < 3; n++){
                                    tabuleiro[(m+i)][(n+j)]=biblio[variantePeca][m][n];
                                }
                            }
                            if (restricaoUm(i,j,tabuleiro) == 0){
                                break;
                            }
                            posicaoVariante++;
                        } while (variantePeca < inicioPecas[tipoPeca+1]);
                        if (variantePeca >= inicioPecas[tipoPeca+1]){
                            pecasUsadas[cnt8tentativas]=tipoPeca;
                            cnt8tentativas++;
                        }
                        if (restricaoUm(i,j,tabuleiro) == 0){
                            quantidadePecas[tipoPeca]--;
                            nmrTotal--;
                            break;
                        }
                    }
                } while (cnt8tentativas<8);
                if (nmrTotal<=0){
                    return 1;
                }
                if (cnt8tentativas==8){
                    cnt1000++; //Adiciona ao counter e quando chegar ao 1000, dá return -1
                    break;
                }
            }
            if (cnt8tentativas==8){
                break;
            }
        }
    } while (cnt1000<1000);
    return -1;
};



/*
*Nome da funcao: modoTiro1
*
*Objetivo da funcao: Aplica o modo de tiro 1
*
*Argumentos de entrada: linhas e colunas (numero de linhas e de colunas) o array pecas que contem o numero de barcos de cada tipo, tabuleiro em que se vão dar os tiros
*/

void modoTiro1(int linhas, int colunas, char tabuleiro[15][24],int pecas[8]){
    int i,j,nmrpecas=0,tiroL,tiroC,nmrjogadas=0;
    char tiro=0;
    time_t t;
    for ( i = 0; i < 8; i++)
    {
        nmrpecas=nmrpecas+(i+1)*pecas[i]; 
    }
    
    printf("%dx%d %d %d %d %d %d %d %d %d\n",linhas,colunas,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]);

    t = time(NULL);
    do{
       do{
            tiroL=(rand() % linhas); //Seleciona uma linha aleatoria
            tiroC=(rand() % colunas); //seleciona uma coluna aleatoria
        }while( tabuleiro[linhas-1-tiroL][tiroC] != 45);
        nmrjogadas=nmrjogadas+1;
        printf("%c%d\n",tiroC+65,tiroL+1);
        do{
            scanf("%c",&tiro);
            limpaStdin();
        } while (tiro != '-' && tiro != '1' && tiro != '2' && tiro != '2' && tiro != '3' && tiro != '4' && tiro != '5' && tiro != '6' && tiro != '7' && tiro != '8');
        if (tiro!='-') //se o alvo for diferente de '-'
        {
            tabuleiro[linhas-1-tiroL][tiroC]=tiro;
            nmrpecas--; //Retirar 1 ao numero de peças
        }else{
            tabuleiro[linhas-1-tiroL][tiroC] = 'x'; 
        }
    } while (nmrpecas>0); 
    t = time(NULL) - t;
    for ( i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas ; j++)
        { 
            if (tabuleiro[i][j] == 'x')
            {
                tabuleiro[i][j] = '-';
            }
        }
    }
    
    
    printf("Fim de jogo: %d jogadas em %d segundos\n",nmrjogadas,(int)t);
    mostraTabuleiro(linhas,colunas,tabuleiro);
};



/*
*Nome da funcao: modoTiro2
*
*Objetivo da funcao: Aplica o modo de tiro 2
*
*Argumentos de entrada: linhas e colunas (numero de linhas e de colunas) o array pecas que contem o numero de barcos de cada tipo, nmrPecas existentes, tabuleiro em que se vão dar os tiros
*/

void modoTiro2(int linhas, int colunas,int nmrPecas, char tabuleiro[15][24],int pecas[8]){
   int i,j,tipoPeca=1,nmrDePeca=0,posicaoTiro,nmrjogadas=0;
   char tiro;
   int ordemTiro[9][2]={{1,1},{0,1},{2,1},{1,0},{1,2},{0,0},{2,2},{0,2},{2,0}};     //ordem pela qual se dá os tiros, imagina uma matriz de 3x3 em que o ponto 1,1 é o centro
   time_t t;
   printf("%dx%d %d %d %d %d %d %d %d %d\n",linhas,colunas,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]);
   t = time(NULL);
    for ( i = 0; i < linhas; i=i+3)
    {
        for (j = 0; j < colunas ; j=j+3)
        {                                               //estes 2 fors servem para rodar a quadricula em que estamos a alterar coisas
            nmrDePeca=0;                                //numero de partes de uma peça
            for ( posicaoTiro = 0; posicaoTiro < 9; posicaoTiro++)           //vai percorrer o padrão descrito em cima
            {
                printf("%c%d\n",j+ordemTiro[posicaoTiro][1]+65,linhas-ordemTiro[posicaoTiro][0]-i);
                do{
                    scanf("%c",&tiro);
                    limpaStdin();
                } while (tiro != '-' && tiro != '1' && tiro != '2' && tiro != '2' && tiro != '3' && tiro != '4' && tiro != '5' && tiro != '6' && tiro != '7' && tiro != '8');
                nmrjogadas++;
                tabuleiro[i+ordemTiro[posicaoTiro][0]][j+ordemTiro[posicaoTiro][1]]=tiro;    
                if(tiro != 45)      //se for diferente de um traço. aka se for uma peça, regista-se o tipo de peça e aumenta-se a contagem do nmr de pedaços de peças, quando esses dois numeros forem iguais é pq o barco foi ao fundo aka se afundares 2 peças do barco tipo 2 então o barco afunda e este loop serve para fazer isso
                {
                    tipoPeca = (int)tiro - 48;
                    nmrDePeca++;
                    if(nmrDePeca==tipoPeca){
                        nmrPecas--;
                        if (nmrPecas==0){
                            break;
                        }
                        break;
                    }
                }
            }
            if (nmrPecas==0){
                break;
            }
        }
        if (nmrPecas==0){
            break;
        }
    }
    t = time(NULL) - t;
    printf("Fim de jogo: %d jogadas em %d segundos\n",nmrjogadas,(int)t);
    mostraTabuleiro(linhas,colunas,tabuleiro);
};



/*
*Nome da funcao: modoTiro3
*
*Objetivo da funcao: Aplica o modo de tiro 3
*
*Argumentos de entrada: linhas e colunas (numero de linhas e de colunas) o array pecas que contem o numero de barcos de cada tipo, nmrPecas existentes, tabuleiro em que se vão dar os tiros
*/

void modoTiro3(int linhas, int colunas,int nmrPecas, char tabuleiro[15][24],int pecas[8]){
   int m,n,ltemp,ctemp,i,j,k,tipoPeca=1,nmrDePeca=0,posicaoTiro,nmrjogadas=0,tiroValido=0;
   char tiro;
   time_t t;
   int ordemTiro[9][2]={{1,1},{0,1},{2,1},{1,0},{1,2},{0,0},{2,2},{0,2},{2,0}};
   printf("%dx%d %d %d %d %d %d %d %d %d\n",linhas,colunas,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]);
   t = time(NULL);
    for ( i = 0; i < linhas; i=i+3){
        for (j = 0; j < colunas; j=j+3){
            nmrDePeca=0;
            for ( posicaoTiro = 0; posicaoTiro < 9; posicaoTiro++){
                if (tabuleiro[i+ordemTiro[posicaoTiro][0]][j+ordemTiro[posicaoTiro][1]]=='x'){
                    continue;
                }
                printf("%c%d\n",j+ordemTiro[posicaoTiro][1]+65,linhas-ordemTiro[posicaoTiro][0]-i);
                do{
                    scanf("%c",&tiro);
                    limpaStdin();
                } while (tiro != '-' && tiro != '1' && tiro != '2' && tiro != '2' && tiro != '3' && tiro != '4' && tiro != '5' && tiro != '6' && tiro != '7' && tiro != '8');
                nmrjogadas++;
                tabuleiro[i+ordemTiro[posicaoTiro][0]][j+ordemTiro[posicaoTiro][1]]=tiro; 
                if(tiro != 45){
                    tipoPeca = tiro - 48;
                    nmrDePeca++;
                    if(nmrDePeca==tipoPeca){
                        for ( ltemp = i; ltemp < (i+3); ltemp++){
                            for (ctemp = j; ctemp < (j+3); ctemp++){
                                if (tabuleiro[ltemp][ctemp] != 'x' && tabuleiro[ltemp][ctemp] != '-' ){
                                    for ( m = -1; m <=1; m++){
                                        for ( n = -1; n <= 1; n++){
                                            if (tabuleiro[ltemp+m][ctemp+n]==45 && (ltemp+m)<15 && (ltemp+m)>=0 && (ctemp+n)<24 && (ctemp+n)>=0){
                                                tabuleiro[ltemp+m][ctemp+n]='x';
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        nmrPecas--;
                        if (nmrPecas==0){
                            break;
                        }
                    }
                }else{
                tabuleiro[i+ordemTiro[posicaoTiro][0]][j+ordemTiro[posicaoTiro][1]]='x'; //Em tudo semelhante ao modo de tiro 2 MAS este x existe para a area á volta da peça que ja foi afundada
                }
            }
            if (nmrPecas==0){
                break;
            }
        }
        if (nmrPecas==0){
            break;
        }
    }
    t = time(NULL)-t;
    for ( i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas ; j++)
        { 
            if (tabuleiro[i][j] == 'x')
            {
                tabuleiro[i][j] = '-';
            }
        }
    }
    printf("Fim de jogo: %d jogadas em %d segundos\n",nmrjogadas,(int)t);
    mostraTabuleiro(linhas,colunas,tabuleiro);
};



/*
*Nome da funcao: modoJogo0
*
*Objetivo da funcao: Aplica o modo de jogo 0 (gera um tabuleiro)
*
*Argumentos de entrada: modoPosicionamento define o modo de posicionamento que vai ser aplicado, o array pecas como referencia vai guardar as peças a serem usadas, linhas e colunas definem o nmr de linhas e colunas , nmrPecas indica o numero total de barcos , tabuleiro em que se vai aplicar o modo de jogo e os array que tem as codificações de peças
*/

void modoJogo0(int modoPosicionamento, int pecas[], int linhas, int colunas, int nmrPecas, char tabuleiro[][24], char biblio[43][3][3],int inicioPecas[9]){

    switch (modoPosicionamento){ //Selecionar o modo de posicionamento
    
    case 2:

        if(modoPos2(pecas,linhas,colunas,nmrPecas,tabuleiro,biblio,inicioPecas)==-1){ //Impossivel gerar o tabuleiro devido ao numero de resets
            printf("Tabuleiro impossivel de ser gerado");
            exit(0);
        }
        break;

    default:
        modoPos1(linhas,colunas,tabuleiro,pecas,biblio); //modo de posicionamento 1
        break;
    }
    printf("%dx%d %d %d %d %d %d %d %d %d\n",linhas,colunas,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]);
    mostraTabuleiro(linhas,colunas,tabuleiro); //Função que dá print ao tabuleiro
}



/*
*Nome da funcao: modoJogo1
*
*Objetivo da funcao: Aplica o modo de jogo 1 (gera um tabuleiro e aceita input para tiros)
*
*Argumentos de entrada: modoPosicionamento define o modo de posicionamento que vai ser aplicado, o array pecas como referencia vai guardar as peças a serem usadas, linhas e colunas definem o nmr de linhas e colunas , nmrPecas indica o numero total de barcos , tabuleiro em que se vai aplicar o modo de jogo e os array que tem as codificações de peças
*/

void modoJogo1(int modoPosicionamento, int pecas[], int linhas, int colunas, int nmrPecas, char tabuleiro[][24], char biblio[43][3][3],int inicioPecas[9]){
    int i,j,l,nmrJogadas=0,nmrCasasOcupadas=0;
    char posicoes[15][24]={
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    time_t t; //Inicia o timer
    char c;
 
    switch (modoPosicionamento){ //Selecionar o modo de posicionamento
    case 2:

        if(modoPos2(pecas,linhas,colunas,nmrPecas,tabuleiro,biblio,inicioPecas)==-1){ //Impossivel gerar o tabuleiro devido ao numero de resets
            printf("Tabuleiro impossivel de ser gerado");
            exit(0);
        }
        break;

    default:
        modoPos1(linhas,colunas,tabuleiro,pecas,biblio); //modo de posicionamento 1
        break;
    }


    printf("%dx%d %d %d %d %d %d %d %d %d\n",linhas,colunas,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]); //Print ao numero de peças de cada tipo

    for (i = 0; i<linhas; i++){
        for (j = 0; j<colunas; j++){
            if (tabuleiro[i][j] != 45)
            {
                nmrCasasOcupadas++;
            }

        }
    } //conta o numero de casas ocupadas
    t = time(NULL);
    while (nmrCasasOcupadas>0){ //Disparar numa peça
        do{
            while (scanf("%c%d", &c,&l) != 2){
                printf("*Erro ao ler o input!\n");
                printf("*Introduza novamente\n");
                limpaStdin();
            }
            limpaStdin();
        } while (l>linhas||l<1||c<65||c>(colunas+64));
        nmrJogadas++;

        if (posicoes[linhas-l][c-65]==0){
            posicoes[linhas-l][c-65]=1; //Mudar o valor da peça selecionada
            if (tabuleiro[linhas-l][c-65]!=45){
               nmrCasasOcupadas--; //Caso acerte uma peça, retirar um da quantidade contada
            }
        }
        printf("%c\n",tabuleiro[linhas-l][c-65]);  
    }
    t = time(NULL) - t; //termina a contagem do programa
    printf("Fim de jogo: %d jogadas em %d segundos\n",nmrJogadas,(int)t);
}



/*
*Nome da funcao: modoJogo2
*
*Objetivo da funcao: Aplica o modo de jogo 2 (escolhe um modo de tiro)
*
*Argumentos de entrada: modoDisparo define o modo de disparo que vai ser aplicado, o array pecas como referencia vai guardar as peças a serem usadas, linhas e colunas definem o nmr de linhas e colunas , nmrPecas indica o numero total de barcos , tabuleiro em que se vai aplicar o modo de jogo
*/

void modoJogo2(int modoDisparo, int pecas[], int linhas, int colunas, int nmrPecas, char tabuleiro[15][24]){

switch (modoDisparo)
{
case 2:
    modoTiro2(linhas,colunas,nmrPecas,tabuleiro,pecas);
    break;

case 3:
    modoTiro3(linhas,colunas,nmrPecas,tabuleiro,pecas);
    break;


default:
    modoTiro1(linhas,colunas,tabuleiro,pecas);
    break;
}
}



/*
*Nome da funcao: main
*
*Objetivo da funcao: Estrutura central do programa
*
*Argumentos de entrada: argc e *argv para o funcionamento do getopt
*
*Argumentos de saida: -1 caso haja erros | 1 caso o jogo corra sem erros | 0 caso o jogador peça ajuda
*/

int main(int argc, char *argv[]){

    srand(time(NULL));
    //Valores do Tabuleiro
    char tabuleiro[15][24] = {
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
        {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45}
    };

    //biblioteca das peças
    char biblio[43][3][3] = {
        {{45,45,45},{45,45,45},{45,45,45}},

        {{49,45,45},{45,45,45},{45,45,45}},
        {{45,49,45},{45,45,45},{45,45,45}},
        {{45,45,49},{45,45,45},{45,45,45}},
        {{45,45,45},{49,45,45},{45,45,45}},
        {{45,45,45},{45,49,45},{45,45,45}},
        {{45,45,45},{45,45,49},{45,45,45}},
        {{45,45,45},{45,45,45},{49,45,45}},
        {{45,45,45},{45,45,45},{45,49,45}},
        {{45,45,45},{45,45,45},{45,45,49}},

        {{50,50,45},{45,45,45},{45,45,45}},
        {{45,50,50},{45,45,45},{45,45,45}},
        {{45,45,45},{50,50,45},{45,45,45}},
        {{45,45,45},{45,50,50},{45,45,45}},
        {{45,45,45},{45,45,45},{50,50,45}},
        {{45,45,45},{45,45,45},{45,50,50}},
        {{50,45,45},{50,45,45},{45,45,45}},
        {{45,45,45},{50,45,45},{50,45,45}},
        {{45,50,45},{45,50,45},{45,45,45}},
        {{45,45,45},{45,50,45},{45,50,45}},
        {{45,45,50},{45,45,50},{45,45,45}},
        {{45,45,45},{45,45,50},{45,45,50}},

        {{51,51,51},{45,45,45},{45,45,45}},
        {{45,45,45},{51,51,51},{45,45,45}},
        {{45,45,45},{45,45,45},{51,51,51}},
        {{51,45,45},{51,45,45},{51,45,45}},
        {{45,51,45},{45,51,45},{45,51,45}},
        {{45,45,51},{45,45,51},{45,45,51}},

        {{52,52,45},{52,52,45},{45,45,45}},
        {{45,52,52},{45,52,52},{45,45,45}},
        {{45,45,45},{52,52,45},{52,52,45}},
        {{45,45,45},{45,52,52},{45,52,52}},

        {{53,53,53},{45,53,45},{45,53,45}},
        {{53,45,45},{53,53,53},{53,45,45}},
        {{45,53,45},{45,53,45},{53,53,53}},
        {{45,45,53},{53,53,53},{45,45,53}},

        {{45,54,45},{54,45,54},{54,54,54}},
        {{45,54,54},{54,45,54},{45,54,54}},
        {{54,54,54},{54,45,54},{45,54,45}},
        {{54,54,45},{54,45,54},{54,54,45}},

        {{55,45,55},{55,55,55},{55,45,55}},
        {{55,55,55},{45,55,45},{55,55,55}},

        {{56,56,56},{56,45,56},{56,56,56}}
    };

    int inicioPecas[9]={0,1,10,22,28,32,36,40,42};

    int opt = 0,
        linhas=9,
        colunas=9,
        modoJogo=0,
        modoPosicionamento=1,
        modoDisparo=1,
        pecas[8]={0,0,0,0,0,0,0,0},
        count=0,
        nmrPecas=0,
        flagMDAlterado=0;
    while ((opt = getopt(argc, argv, "ht:j:p:d:1:2:3:4:5:6:7:8:")) != -1) {
            switch (opt)
            {
            case 't':
                if (sscanf(optarg, "%dx%d", &linhas, &colunas) != 2){
                    printf("Erro ao ler o input de -t !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
                if (((linhas < 9) || (linhas>15)) || ((colunas < 9) || (colunas>24)) || ((colunas%3 != 0) || (linhas%3 != 0))){
                    printf("Valores inválidos para o tamanho, por favor tente de novo\n");
                    printf("Utilize 9, 12 ou 15 para linhas e 9, 12, 15, 18, 21 ou 24 para colunas\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case 'j':
                if (sscanf(optarg, "%d", &modoJogo) != 1){
                    printf("Erro ao ler o input de -j !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
                if (modoJogo<0 || modoJogo>2){
                    printf("Valores inválidos para o modo de jogo, por favor tente de novo\n");
                    printf("Utilize um numero entre 0 e 2\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case 'p':
                if (sscanf(optarg, "%d", &modoPosicionamento) != 1){
                    printf("Erro ao ler o input de -p !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
                if (modoPosicionamento<1 || modoPosicionamento>2){
                    printf("Valores inválidos para o modo de posicionamento, por favor tente de novo\n");
                    printf("Utilize um numero entre 1 e 2\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case 'd':
                if (sscanf(optarg, "%d", &modoDisparo) != 1){
                    printf("Erro ao ler o input de -d !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
                flagMDAlterado=1;
                if (modoDisparo<1 || modoDisparo>3){
                    printf("Valores inválidos para o modo de disparo, por favor tente de novo\n");
                    printf("Utilize um numero entre 1 e 3\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case '1':
                if (sscanf(optarg, "%d", &pecas[0]) != 1){
                    printf("Erro ao ler o input de -1 !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case '2':
                if (sscanf(optarg, "%d", &pecas[1]) != 1){
                    printf("Erro ao ler o input de -2 !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case '3':
                if (sscanf(optarg, "%d", &pecas[2]) != 1){
                    printf("Erro ao ler o input de -3 !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case '4':
                if (sscanf(optarg, "%d", &pecas[3]) != 1){
                    printf("Erro ao ler o input de -4 !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case '5':
                if (sscanf(optarg, "%d", &pecas[4]) != 1){
                    printf("Erro ao ler o input de -5 !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case '6':
                if (sscanf(optarg, "%d", &pecas[5]) != 1){
                    printf("Erro ao ler o input de -6 !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case '7':
                if (sscanf(optarg, "%d", &pecas[6]) != 1){
                    printf("Erro ao ler o input de -7 !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case '8':
                if (sscanf(optarg, "%d", &pecas[7]) != 1){
                    printf("Erro ao ler o input de -8 !\n");
                    textoAjuda();
                    printf("-1");
                    return -1;
                }
            break;

            case 'h':
                textoAjuda();
                return 0;
            break;

            default:
                printf("Erro de introducao, opcao desconhecida\n\n");
                textoAjuda();
                printf("-1");
                return -1;
            break;
            }
        }
    
    for (count = 0; count < 7; count++){//restição 3 e 4
        if (pecas[count]<pecas[count+1]){
            printf("Falhou restricao 3\n");
            textoAjuda();
            printf("-1");
            return -1;
        }

        nmrPecas=nmrPecas+pecas[count];
        if (count==6){
            nmrPecas=nmrPecas+pecas[count+1];
        }

        if (nmrPecas>((linhas*colunas/9)/2)){
            printf("Falhou restricao 4\n");
            textoAjuda();
            printf("-1");
            return -1;
        }
    }



    if ((modoJogo != 2) && (flagMDAlterado !=0)){
        printf("Modo de jogo incompativel com o modo de tiro escolhido\n");
        textoAjuda();
        printf("-1");
        return -1;
    }

    
    if (modoPosicionamento == 2 && pecas[0] == 0){
        printf("Para este modo de posicionamento funcionar escolha o nmr de pecas\n");
        textoAjuda();
        printf("-1");
        return -1;
    }

    if (modoJogo != 2 && modoPosicionamento==1 && pecas[0] != 0 ){
        printf("Para este modo de posicionamente funcionar nao escolha o nmr de pecas\n");
        textoAjuda();
        printf("-1");
        return -1;
    }

    if (modoJogo == 2 && pecas[0] == 0){
        printf("Para este modo de jogo funcionar indique o numero de pecas\n");
        textoAjuda();
        printf("-1");
        return -1;
    }


    //selecionar o modo de jogo
    switch (modoJogo)
    {
    case 0:
        modoJogo0(modoPosicionamento,pecas,linhas,colunas,nmrPecas,tabuleiro,biblio,inicioPecas);
        return 1;
    break;

    case 1:
        modoJogo1(modoPosicionamento,pecas,linhas,colunas,nmrPecas,tabuleiro,biblio,inicioPecas);
        mostraTabuleiro(linhas,colunas,tabuleiro);
        return 1;
    break;

    case 2:
        modoJogo2(modoDisparo,pecas,linhas,colunas,nmrPecas,tabuleiro);
        return 1;
    break;
    }
    printf("Algo correu mal, por favor tente de novo\n");
    textoAjuda();
    printf("-1");
    return -1;
};