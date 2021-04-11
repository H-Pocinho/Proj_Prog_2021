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

void limpaStdin(void){
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


int restricaoUm(int l, int c,char tabuleiro[15][24]){
    int i,j,m,n,ltemp,ctemp;
        for ( i = l; i < (l+3); i++)
        {
            for (j = c; j < (c+3); j++)
            {
                if (tabuleiro[i][j] != 45)
                {
                    for ( m = -1; m <=1; m++)
                    {
                        for ( n = -1; n <= 1; n++)
                        {
                            ltemp = m+i;
                            ctemp = n+j;

                           if ( (((ltemp < l) || (ltemp > (l+2))) || ((ctemp < c) || (ctemp > (c+2)))) && (((ltemp+m)<=15 && (ltemp+m)>=0) && ((ctemp+n)<=24 && (ctemp+n)>=0)))
                           {
                               if (tabuleiro[ltemp][ctemp] != 45 && tabuleiro[ltemp][ctemp] != 0)
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

void mostratabuleiro(int linhas, int colunas,char tabuleiro[15][24],int pecas[8]){
    int i, j,nmr;
    char letras [24] = {"ABCDEFGHIJKLMNOPQRSTUVWX"};
    for (i = 0; i<linhas; i++){
        for (j = 0; j<colunas; j++){
            if (j==0){
                nmr=linhas-i;
                if (nmr<10){
                    printf(" %d ",nmr);
                }
                else{
                    printf("%d ",nmr);
                }
            }
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("   ");
    for (i = 0; i < colunas; i++){
        printf("%c ",letras[i]);
    }
    printf("\n");
};

void modoPos1(int linhas,int colunas, char tabuleiro[][24],int pecas[], char biblio[43][3][3]){
    int i,j,m,n,tipoPeca,pecaRandom,try;
    for (i = 0; i < linhas; i=i+3){
        for ( j = 0; j < colunas; j=j+3){
            try=0;
            do{

                pecaRandom=((rand()%43));

                for ( m = 0; m < 3 ; m++){
                    for (n = 0; n < 3; n++){

                        tabuleiro[(m+i)][(n+j)]=biblio[0][m][n];
                    }
                }

                for ( m = 0; m < 3 ; m++){
                    for (n = 0; n < 3; n++){
                        tabuleiro[(m+i)][(n+j)]=biblio[pecaRandom][m][n];
                    }
                }


                if (try>=3){
                    for ( m = 0; m < 3 ; m++){
                        for (n = 0; n < 3; n++){
                            tabuleiro[(m+i)][(n+j)]=biblio[5][m][n];
                        }
                    }
                }
                try=try+1;
            } while (restricaoUm(i,j,tabuleiro) != 0);
        }
    }

    for ( i = 0; i < linhas; i=i+3){
        for ( j = 0; j < colunas; j=j+3){
            for ( m = 0; m < 3 ; m++){
                for (n = 0; n < 3; n++){
                    tipoPeca=(int)tabuleiro[(m+i)][(n+j)];
                    if (tipoPeca!=45){
                        pecas[tipoPeca - 49]=pecas[tipoPeca - 49]+1;
                    }
                }
            }
        }
    }

    for ( i = 0; i < 8; i++){
        pecas[i]=pecas[i]/(i+1);
    }

};

int modoPos2(int pecas[8], int linhas, int colunas, int nmrPecas, char tabuleiro[][24],char biblio[43][3][3],int inicioPecas[9]){
    int i,j,m,n,l;
    int tipoPeca,variantePeca,posicaoVariante,cnt8tentativas,flagPecaUsada,cnt1000=0;
    int pecasUsadas[8]={9,9,9,9,9,9,9,9};
    int nmrTotal= (linhas*colunas)/9;
    int nmrVazias = nmrTotal-nmrPecas;
    int quantidadePecas[9]={nmrVazias,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]};
    do{
        for (i = 0; i<linhas; i++){
            for (j = 0; j<colunas; j++){
                tabuleiro[i][j]=45;
            }
        }
        nmrTotal= (linhas*colunas)/9;
        for ( l = 0; l < 9; l++){
            if (l==0){
                quantidadePecas[l]=nmrVazias;
            }
            else{
                quantidadePecas[l]=pecas[l-1];
            }
        }

        for (i = 0; i < linhas; i=i+3){
            for ( j = 0; j < colunas; j=j+3){
                cnt8tentativas=0;
                do{
                    do{
                        flagPecaUsada=0;
                        tipoPeca=rand() % 9;
                        for (l = 0; l < 8; l++){
                            if (tipoPeca==pecasUsadas[l]){
                                flagPecaUsada=1;
                            }
                        }
                        if (flagPecaUsada==1){
                            continue;
                        }
                    } while (quantidadePecas[tipoPeca]<=0);


                    if (tipoPeca==8){
                        variantePeca=42;
                    }
                    else{
                        variantePeca = (rand() % (inicioPecas[tipoPeca+1] - inicioPecas[tipoPeca])) + inicioPecas[tipoPeca];
                    }

                    for ( m = 0; m < 3 ; m++){
                        for (n = 0; n < 3; n++){
                            tabuleiro[(m+i)][(n+j)]=biblio[variantePeca][m][n];
                        }
                    }

                    if (restricaoUm(i,j,tabuleiro) == 0){
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
                    cnt1000++;
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

void modoTiro1(int linhas, int colunas, char tabuleiro[15][24], char tabuleiroGUI[][24],int pecas[8]){
    int i,nmrpecas=0,tiroL,tiroC;
    char tiro=0;
    printf("%dx%d %d %d %d %d %d %d %d %d\n",colunas,linhas,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]);


    for ( i = 0; i < 8; i++)
    {
        nmrpecas=nmrpecas+pecas[i]*i;
    }

    do{
        do{
            do{
                tiroL=(rand() % linhas);
                tiroC=(rand() % colunas);
            }while(tabuleiroGUI[tiroL][tiroC]!=0);
            printf("%c%d",tiroL+65,tiroC+1);
            scanf("%c",&tiro);
            tabuleiroGUI[tiroL][tiroC]=tabuleiro[tiroL][tiroC];
                if (tabuleiro[tiroL][tiroC]!=45){
                    nmrpecas--;
                }
        } while (nmrpecas!=0);
    } while (nmrpecas>0);
    mostratabuleiro(linhas,colunas,tabuleiroGUI,pecas);
};

void modoTiro2(int linhas, int colunas, char tabuleiro[15][24], char tabuleiroGUI[][24],int pecas[8]){
   int i,j,tipoPeca=1,nmrDePeca=0,tiro;
   int ordemTiro[9][2]={{1,1},{0,1},{2,1},{1,0},{1,2},{0,0},{2,2},{0,2},{2,0}};     //ordem pela qual se dá os tiros, iamgina uma matriz de 3x3 em que o ponto 1,1 é o centro
    for ( i = 0; i < linhas; i=i+3)
    {
        for (j = 0; j < colunas; j=j+3)
        {                                               //estes 2 fors servem para rodar a quadricula em que estamos a alterar coisas
            nmrDePeca=0;                                //numero de partes de uma peça
            for ( tiro = 0; tiro < 9; tiro++)           //vai percorrer o padrão descrito em cima
            {
                tabuleiroGUI[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]]=tabuleiro[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]];     //tiro a ser dado aka passa a informação do tabuleiro invisel para o visivel(GUI)
                mostratabuleiro(linhas,colunas,tabuleiroGUI,pecas);                           //print do tabuleiro visivel
                if(tabuleiroGUI[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]] != 45)      //se for diferente de um traço. aka se for uma peça, regista-se o tipo de peça e aumenta-se a contagem do nmr de pedaços de peças, quando esses dois numeros forem iguais é pq o barco foi ao fundo aka se afundares 2 peças do barco tipo 2 então o barco afunda e este loop serve para fazer isso
                {
                    tipoPeca = tabuleiroGUI[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]] - 48;
                    nmrDePeca++;
                    if(nmrDePeca==tipoPeca){
                        break;
                    }
                }
            }
        }
    }
};

void modoTiro3(int linhas, int colunas, char tabuleiro[15][24], char tabuleiroGUI[][24],int pecas[8]){
   int m,n,ltemp,ctemp,i,j,tipoPeca=1,nmrDePeca=0,tiro;
   int ordemTiro[9][2]={{1,1},{0,1},{2,1},{1,0},{1,2},{0,0},{2,2},{0,2},{2,0}};
    for ( i = 0; i < linhas; i=i+3){
        for (j = 0; j < colunas; j=j+3){
            nmrDePeca=0;
            for ( tiro = 0; tiro < 9; tiro++){
                if (tabuleiroGUI[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]]==45){
                    continue;
                }

                tabuleiroGUI[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]]=tabuleiro[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]];
                mostratabuleiro(linhas,colunas,tabuleiroGUI,pecas);
                if(tabuleiroGUI[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]] != 45){
                    tipoPeca = tabuleiroGUI[i+ordemTiro[tiro][0]][j+ordemTiro[tiro][1]] - 48;
                    nmrDePeca++;
                    if(nmrDePeca==tipoPeca){
                        for ( ltemp = i; ltemp < (i+3); ltemp++){
                            for (ctemp = j; ctemp < (j+3); ctemp++){
                                if (tabuleiroGUI[ltemp][ctemp] != 45 && tabuleiroGUI[ltemp][ctemp] != 0){
                                    for ( m = -1; m <=1; m++){
                                        for ( n = -1; n <= 1; n++){
                                            if (tabuleiroGUI[ltemp+m][ctemp+n]==0 && (ltemp+m)<=15 && (ltemp+m)>=0 && (ctemp+n)<=24 && (ctemp+n)>=0){
                                                tabuleiroGUI[ltemp+m][ctemp+n]=45;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    mostratabuleiro(linhas,colunas,tabuleiroGUI,pecas);
                    break;
                    }
                }
            }
        }
    }
};

void modoJogo0(int modoPosicionamento, int pecas[], int linhas, int colunas, int nmrPecas, char tabuleiro[][24], char tabuleiroGUI[][24], char biblio[43][3][3],int inicioPecas[9]){

    switch (modoPosicionamento){

    case 2:

        if(modoPos2(pecas,linhas,colunas,nmrPecas,tabuleiro,biblio,inicioPecas)==-1){
            printf("Tabuleiro impossivel de ser gerado");
            exit(0);
        }
        break;

    default:
        modoPos1(linhas,colunas,tabuleiro,pecas,biblio);
        break;
    }
    mostratabuleiro(linhas,colunas,tabuleiro,pecas);
}





void modoJogo1(int modoPosicionamento, int pecas[], int linhas, int colunas, int nmrPecas, char tabuleiro[][24], char tabuleiroGUI[][24], char biblio[43][3][3],int inicioPecas[9]){
    int i,j,l,nmrJogadas=0,nmrCasasOcupadas=0;
    clock_t t;
    double tempo;
    char c;


    switch (modoPosicionamento)
    {
    case 1:
        modoPos1(linhas,colunas,tabuleiro,pecas,biblio);
        break;

    default:
        if(modoPos2(pecas,linhas,colunas,nmrPecas,tabuleiro,biblio,inicioPecas)==-1){
            printf("Tabuleiro impossivel de ser gerado");
            exit(0);
        }
        break;
    }
    printf("%dx%d %d %d %d %d %d %d %d %d\n",colunas,linhas,pecas[0],pecas[1],pecas[2],pecas[3],pecas[4],pecas[5],pecas[6],pecas[7]);

    for (i = 0; i<linhas; i++){
        for (j = 0; j<colunas; j++){
            if (tabuleiro[i][j] != 45)
            {
                nmrCasasOcupadas++;
            }

        }
    }
    t = clock();
    while (nmrCasasOcupadas>0){
        do{
            while (scanf("%c%d", &c,&l) != 2){
                printf("*Failled to read STDIN!\n");
                printf("*Introduza novamente");
                limpaStdin();
            }
            limpaStdin();
        } while (l>linhas||l<1||c<65||c>(colunas+64));
        nmrJogadas++;

        if (tabuleiroGUI[linhas-l-2][c-17]==0){
            tabuleiroGUI[linhas-l-2][c-17]=tabuleiro[linhas-l-2][c-17];
            if (tabuleiroGUI[linhas-l-2][c-17]!=45){
                nmrCasasOcupadas--;
            }
        }
        printf("%c\n",tabuleiroGUI[linhas-l-2][c-17]);
    }
    t = clock() - t;
    //tempo = ((double)t)/CLOCKS_PER_SEC;
    mostratabuleiro(linhas,colunas,tabuleiro,pecas);
    printf("Fim de jogo: %d jogadas em %lf segundos\n",nmrJogadas,(double)t);
}


void modoJogo2(int modoDisparo, int pecas[], int linhas, int colunas, int nmrPecas, char tabuleiro[][24], char tabuleiroGUI[][24], char biblio[43][3][3],int inicioPecas[9]){

switch (modoDisparo)
{
case 2:

    break;

case 3:
    /* code */
    break;


default:
    modoTiro1(linhas,colunas,tabuleiro,tabuleiroGUI,pecas);
    break;
}
}




int main(int argc, char *argv[]){

    srand(time(NULL));

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

    char tabuleiroGUI[15][24] = {
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
        flagMDAlterado=0,
        flagTAlterado=0;

    opterr = 0;
    while ((opt = getopt(argc, argv, "ht:j:p:d:1:2:3:4:5:6:7:8:")) != -1) {
            switch (opt)
            {
            case 't':
            flagTAlterado=1;
                if (sscanf(optarg, "%dx%d", &linhas, &colunas) != 2){
                    printf("Failled to read STDIN!\n");
                    exit(0);
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
                    printf("Failled to read STDIN!\n");
                    exit(0);
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
                    printf("Failled to read STDIN!\n");
                    exit(0);
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
                    printf("Failled to read STDIN!\n");
                    exit(0);
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
                    printf("Failled to read STDIN!\n");
                    exit(0);
                }
            break;

            case '2':
                if (sscanf(optarg, "%d", &pecas[1]) != 1){
                    printf("Failled to read STDIN!\n");
                    exit(0);
                }
            break;

            case '3':
                if (sscanf(optarg, "%d", &pecas[2]) != 1){
                    printf("Failled to read STDIN!\n");
                    exit(0);
                }
            break;

            case '4':
                if (sscanf(optarg, "%d", &pecas[3]) != 1){
                    printf("Failled to read STDIN!\n");
                    exit(0);
                }
            break;

            case '5':
                if (sscanf(optarg, "%d", &pecas[4]) != 1){
                    printf("Failled to read STDIN!\n");
                    exit(0);
                }
            break;

            case '6':
                if (sscanf(optarg, "%d", &pecas[5]) != 1){
                    printf("Failled to read STDIN!\n");
                    exit(0);
                }
            break;

            case '7':
                if (sscanf(optarg, "%d", &pecas[6]) != 1){
                    printf("Failled to read STDIN!\n");
                    exit(0);
                }
            break;

            case '8':
                if (sscanf(optarg, "%d", &pecas[7]) != 1){
                    printf("Failled to read STDIN!\n");
                    exit(0);
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


    if ((modoJogo != 2) && (flagMDAlterado !=0)){
        textoAjuda();
        printf("-1");
        return -1;
    }


    for (count = 0; count < 7; count++){                    //restição 3 e 4
        if (pecas[count]<pecas[count+1]){
            textoAjuda();
            printf("-1");
            return -1;
        }

        nmrPecas=nmrPecas+pecas[count];
        if (count==6){
            nmrPecas=nmrPecas+pecas[count+1];
        }

        if (nmrPecas>((linhas*colunas/9)/2)){
            textoAjuda();
            printf("-1");
            return -1;
        }
    }

    if (modoPosicionamento==1 && pecas[0]!=0)
    {
        textoAjuda();
        printf("-1");
        return -1;
    }

    switch (modoJogo)
    {
    case 0:
        if (flagTAlterado!=1){
            printf("Especifique o tamanho do tabuleiro");
            textoAjuda();
            printf("-1");
            return -1;
        }
        modoJogo0(modoPosicionamento,pecas,linhas,colunas,nmrPecas,tabuleiro,tabuleiroGUI,biblio,inicioPecas);
        exit(0);
    break;

    case 1:
        if (flagTAlterado!=1){
            printf("Especifique o tamanho do tabuleiro");
            textoAjuda();
            printf("-1");
            return -1;
        }
        modoJogo1(modoPosicionamento,pecas,linhas,colunas,nmrPecas,tabuleiro,tabuleiroGUI,biblio,inicioPecas);
        exit(0);
    break;

    case 2:
        modoJogo2(modoDisparo,pecas,linhas,colunas,nmrPecas,tabuleiro,tabuleiroGUI,biblio,inicioPecas);
        exit(0);
    break;
    }

    textoAjuda();
    printf("-1");
    return -1;
};