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

char tabuleiro[15][24] ={
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

char tabuleiroGUI[15][24] ={
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

char biblioZero[1][9] = {
    {45,45,45,45,45,45,45,45,45}
};

char biblioUm[9][9] = {
    {49,45,45,45,45,45,45,45,45},
    {45,49,45,45,45,45,45,45,45},
    {45,45,49,45,45,45,45,45,45},
    {45,45,45,49,45,45,45,45,45},
    {45,45,45,45,49,45,45,45,45},
    {45,45,45,45,45,49,45,45,45},
    {45,45,45,45,45,45,49,45,45},
    {45,45,45,45,45,45,45,49,45},
    {45,45,45,45,45,45,45,45,49}
};

char biblioDois[12][9] = {
    {50,50,45,45,45,45,45,45,45},
    {45,50,50,45,45,45,45,45,45},
    {45,45,45,50,50,45,45,45,45},
    {45,45,45,45,50,50,45,45,45},
    {45,45,45,45,45,45,50,50,45},
    {45,45,45,45,45,45,45,50,50},
    {50,45,45,50,45,45,45,45,45},
    {45,45,45,50,45,45,50,45,45},
    {45,50,45,45,50,45,45,45,45},
    {45,45,45,45,50,45,45,50,45},
    {45,45,50,45,45,50,45,45,45},
    {45,45,45,45,45,50,45,45,50}
};

char biblioTres[6][9] = {
    {51,51,51,45,45,45,45,45,45},
    {45,45,45,51,51,51,45,45,45},
    {45,45,45,45,45,45,51,51,51},
    {51,45,45,51,45,45,51,45,45},
    {45,51,45,45,51,45,45,51,45},
    {45,45,51,45,45,51,45,45,51}
};

char biblioQuatro[4][9] = {
    {52,52,45,52,52,45,45,45,45},
    {45,52,52,45,52,52,45,45,45},
    {45,45,45,52,52,45,52,52,45},
    {45,45,45,45,52,52,45,52,52}
};

char biblioCinco[4][9] = {
    {53,53,53,45,53,45,45,53,45},
    {53,45,45,53,53,53,53,45,45},
    {45,53,45,45,53,45,53,53,53},
    {45,45,53,53,53,53,45,45,53}
};

char biblioSeis[4][9] = {
    {45,54,45,54,45,54,54,54,54},
    {45,54,54,54,45,54,45,54,54},
    {54,54,54,54,45,54,45,54,45},
    {54,54,45,54,45,54,54,54,45}
};

char biblioSete[2][9] = {
    {55,45,55,55,55,55,55,45,55},
    {55,55,55,45,55,45,55,55,55}
};

char biblioOito[1][9] = {
    {56,56,56,56,45,56,56,56,56}
};







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
}

int restricaoDois(int l, int c,char tabuleiro[15][24]){
    int i,j,m,n,ltemp,ctemp;
        for ( i = l; i < (l+3); i++)
        {
            for (j = c; j < (c+3); j++)
            {
                if (tabuleiro[i][j] != 45){
                    for ( m = -1; m <=1; m++)
                    {
                        for ( n = -1; n <= 1; n++)
                        {
                            ltemp = m+i;
                            ctemp = n+j;

                           if ( ((ltemp < l) || (ltemp > (l+2))) || ((ctemp < c) || (ctemp > (c+2)))){
                               if (tabuleiro[ltemp][ctemp] != 45 && tabuleiro[ltemp][ctemp] != 0){
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

void mostratabuleiro(int linhas, int colunas,char tabuleiro[15][24]){
    int i, j,nmr;
    char letras [24] = {"ABCDEFGHIJKLMNOPQRSTUVWX"};
        for (i = 0; i<linhas; i++){
            for (j = 0; j<colunas; j++){
                if (j==0)
                {
                    nmr=linhas-i;
                    printf("%d ",nmr);
                }
                printf("%c ", tabuleiro[i][j]);
            }
            printf("\n");
        }
        printf("  ");
        for (i = 0; i < colunas; i++)
        {
            printf("%c ",letras[i]);
        }
        printf("\n"); 
}

void modoPos1(int linhas,int colunas, char tabuleiro[][24],char biblio[43][3][3]){
    int i,j,m,n,pecaRandom,try;
    for (i = 0; i < linhas; i=i+3){
        for ( j = 0; j < colunas; j=j+3){
            try=0;
            do{

                pecaRandom=((rand()%42)+1);

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
                
                try=try+1;
                if (try>=3){
                    for ( m = 0; m < 3 ; m++){
                        for (n = 0; n < 3; n++){   
                            tabuleiro[(m+i)][(n+j)]=biblio[5][m][n];
                        }
                    }
                }

            } while (restricaoDois(i,j,tabuleiro) != 0);
        }
    }
};

void modoPos2(int pecas[8], int linhas, int colunas){
    int matrixsO;
    int nPecas;
    matrixsO = ((linhas*colunas)/9)/2;
    nPecas=pecas[0]+pecas[1]+pecas[2]+pecas[3]+pecas[4]+pecas[5]+pecas[6]+pecas[7];
    if (nPecas > matrixsO){
        printf("As peças não cabem no tabuleiro");
        exit(0);
    }
}


void modoTiro1(int linhas, int colunas, char tabuleiro[15][24], char tabuleiroGUI[][24]){
    int i,j,nmrpecas=0,tiroL,tiroC,key;
    for (i = 0; i<linhas; i++){
        for (j = 0; j<colunas; j++){
            if(tabuleiro[i][j] != 45){
                nmrpecas++;
            }
        }
    }
    do{
        key=0;
        do{
            tiroL=(rand() % linhas);
            tiroC=(rand() % colunas);
            if (tabuleiroGUI[tiroL][tiroC]==0){
                tabuleiroGUI[tiroL][tiroC]=tabuleiro[tiroL][tiroC];
                if (tabuleiro[tiroL][tiroC]!=45)
                {
                    nmrpecas--;
                }
                
                key=1;
            }    
        } while (key == 0);
        mostratabuleiro(linhas,colunas,tabuleiroGUI);
    } while (nmrpecas>0);
};

int main(int argc, char *argv[]){

    srand(time(NULL));
    int opt = 0,
        linhas=9,
        colunas=9,
        modoJogo=0,
        modoPosicionamento=1,
        modoDisparo=1,
        pecas[8]={0};

    opterr = 0;
    while ((opt = getopt(argc, argv, "ht:j:p:d:1:2:3:4:5:6:7:8:")) != -1) {
            switch (opt)
            {
            case 't':
                sscanf(optarg, "%dx%d", &linhas, &colunas);
                if (((linhas < 9) || (linhas>15)) || ((colunas < 9) || (colunas>24)) || ((colunas%3 != 0) || (linhas%3 != 0))){
                    printf("Valores inválidos para o tamanho, por favor tente de novo\n");
                    printf("Utilize um numero entre 9 e 15 para linhas e entre 9 e 24 para colunas e s0 utilize multiplos de 3\n");
                    exit(0);
                }    
            break;

            case 'j':
                sscanf(optarg, "%d", &modoJogo);
                if (modoJogo<0 || modoJogo>2){
                    printf("Valores inválidos para o modo de jogo, por favor tente de novo\n");
                    printf("Utilize um numero entre 0 e 2\n");
                    exit(0);
                }
            break;

            case 'p':
                sscanf(optarg, "%d", &modoPosicionamento);
                if (modoPosicionamento<1 || modoPosicionamento>2){
                    printf("Valores inválidos para o modo de posicionamento, por favor tente de novo\n");
                    printf("Utilize um numero entre 1 e 2\n");
                    exit(0);
                }
            break;

            case 'd':
                sscanf(optarg, "%d", &modoDisparo);
                if (modoDisparo<1 || modoDisparo>3){
                    printf("Valores inválidos para o modo de disparo, por favor tente de novo\n");
                    printf("Utilize um numero entre 1 e 3\n");
                    exit(0);
                }
            break;
            
            case '1':
                sscanf(optarg, "%d", &pecas[0]);
            break;

            case '2':
                sscanf(optarg, "%d", &pecas[1]);
            break;

            case '3':
                sscanf(optarg, "%d", &pecas[2]);
            break;

            case '4':
                sscanf(optarg, "%d", &pecas[3]);
            break;

            case '5':
                sscanf(optarg, "%d", &pecas[4]);
            break;

            case '6':
                sscanf(optarg, "%d", &pecas[5]);
            break;

            case '7':
                sscanf(optarg, "%d", &pecas[6]);
            break;

            case '8':
                sscanf(optarg, "%d", &pecas[7]);
            break;

            default:
                printf("Erro de introducao, opcao desconhecida\n\n");
            case 'h':
                textoAjuda();
            break;
            }
        } 

    printf("%d %d %d %d %d \n",linhas,colunas,modoJogo,modoPosicionamento,modoDisparo);

    if ((modoJogo != 2) && (modoDisparo !=1))
        {
            textoAjuda();
            exit(0);
        }


    mostratabuleiro(linhas,colunas,tabuleiro);
    modoPos1(linhas,colunas,tabuleiro,biblio);
    mostratabuleiro(linhas,colunas,tabuleiro);
    mostratabuleiro(linhas,colunas,tabuleiroGUI);
    modoTiro1(linhas,colunas,tabuleiro,tabuleiroGUI);
    return 0;
}
