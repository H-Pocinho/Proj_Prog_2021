/*
Projecto feito por:
Henrique Alves Pocinho Nº99952
Rodrigo Pereira Nº100080

Wargame
*/
//esqueleto da função de input feito

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>



char biblio[43][9] = {
    {45,45,45,45,45,45,45,45,45},

    {49,45,45,45,45,45,45,45,45},
    {45,49,45,45,45,45,45,45,45},
    {45,45,49,45,45,45,45,45,45},
    {45,45,45,49,45,45,45,45,45},
    {45,45,45,45,49,45,45,45,45},
    {45,45,45,45,45,49,45,45,45},
    {45,45,45,45,45,45,49,45,45},
    {45,45,45,45,45,45,45,49,45},
    {45,45,45,45,45,45,45,45,49},

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
    {45,45,45,45,45,50,45,45,50},

    {51,51,51,45,45,45,45,45,45},
    {45,45,45,51,51,51,45,45,45},
    {45,45,45,45,45,45,51,51,51},
    {51,45,45,51,45,45,51,45,45},
    {45,51,45,45,51,45,45,51,45},
    {45,45,51,45,45,51,45,45,51},

    {52,52,45,52,52,45,45,45,45},
    {45,52,52,45,52,52,45,45,45},
    {45,45,45,52,52,45,52,52,45},
    {45,45,45,45,52,52,45,52,52},

    {53,53,53,45,53,45,45,53,45},
    {53,45,45,53,53,53,53,45,45},
    {45,53,45,45,53,45,53,53,53},
    {45,45,53,53,53,53,45,45,53},

    {45,54,45,54,45,54,54,54,54},
    {45,54,54,54,45,54,45,54,54},
    {54,54,54,54,45,54,45,54,45},
    {54,54,45,54,45,54,54,54,45},

    {55,45,55,55,55,55,55,45,55},
    {55,55,55,45,55,45,55,55,55},

    {56,56,56,56,45,56,56,56,56}
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

int main(int argc, char *argv[]){

int opt = 0;
char *t[20];
while ((opt = getopt(argc, argv, "ht:j:p:d:1:2:3:4:5:6:7:8:")) != -1) {
        switch (opt)
        {
        case 'h':
            printf("\nBem-vindo ao WarGames\n");
            printf("Projecto de Prog feito por:\n");
            printf("\tHenrique Alves Pocinho Nº99952\n");
            printf("\tRodrigo Pereira Nº100080\n\n");
            printf("Comandos:\n");
            printf("-t AxB : Serve para introduzir as dimensoes do tabuleiro onde A e o numero de linhas e B e o numero de colunas.\n");
            printf("-j x : modo de jogo entre 0 e 2.\n");
            printf("-p x : modo de posicionamento das pecas pelo computador, entre 1 e 2.\n");
            printf("-d x : modo de disparo do computador, entre 1 e 3.\n");
            printf("-Y X : y e um numero entre 1 e 8 que representa uma das pecas, e X e o numero dessas peças que existem.\n");
        break;
        
        case 't':
            t[0]=optarg;
        break;

        case 'j':

        break;

        case 'p':

        break;

        case 'd':

        break;
        
        case '1':

        break;

        case '2':

        break;

        case '3':

        break;

        case '4':

        break;

        case '5':

        break;

        case '6':

        break;

        case '7':

        break;

        case '8':

        break;

        default:
            printf("Erro de introducao\n");
            exit(0);
        break;
        }
    }   

    printf("%s",*t);
}




/*
void fun1(){
    char tab1[3][3] = {"---","---","---"};
    int g, h, i, j;
    printf("Escolha a linha:");
    if (scanf("%d", &g) != 1){
        printf("Failled to read STDIN!\n");
        exit(0);
    }
    g = g-1;
    printf("\nEscolha a coluna:");
    if (scanf("%d", &h) != 1){
        printf("Failled to read STDIN!\n");
        exit(0);
    }
    h = h - 1;
    tab1[g][h] = '1';
    printf("%s",tab1);
}

void fun2(){
    char tab2[3][3] = {"---","---","---"};
}

void fun6(){
    //Falta implentar um LOOP para quando o num !=1ou2ou3ou4
    char tab6 [3][3] = {"---","---","---"};
    int orient, conf=0, loop;
    loop = 0;
    printf("A ponta do barco para cima = 1\n");
    printf("A ponta do barco para baixo = 2\n");
    printf("A ponta do barco para esquerda = 3\n");
    printf("A ponta do barco para direita = 4\n");
    do
    {
        if (scanf("%d", &conf != 1)){
            printf("Failled to read STDIN!\n");
            exit(0);
    }
    } while (((conf =! 1) || (conf =! 2)) || ((conf =! 3) || (conf =! 4)));
    

    
    switch(conf){
    case 1:
        strcpy(tab6[0],"-6-");
        strcpy(tab6[1],"6-6");
        strcpy(tab6[2],"666");
        loop = 1;
        printf("a");
        break;

    case 2:
        strcpy(tab6[0],"666");
        strcpy(tab6[1],"6-6");
        strcpy(tab6[2],"-6-");
        loop = 1;
        break;
        
    case 3:
        strcpy(tab6[0],"-66");
        strcpy(tab6[1],"6-6");
        strcpy(tab6[2],"-66");
        loop = 1;
        break;

    case 4:
        strcpy(tab6[0],"66-");
        strcpy(tab6[1],"6-6"),
        strcpy(tab6[2],"66-");
        loop = 1;
        break;

    default:
    printf("Erro");
    break;
    }
}

void fun7(){
    char tab7[3][3] = {"---","---","---"};
    int orient, conf, loop;
    loop = 0;
    conf = 0;
    printf("Horizontal = 1\n");
    printf("Vertical = 2\n");
    while (conf != 1)
    {
        printf("Posicão:");
        if (scanf("%d", &orient) != 1){
            printf("Failled to read STDIN!\n");
            exit(0);
        }
        printf("Tem a certeza?\t Sim = 1    Não = 0\n");
    
        if (scanf("%d", &conf) != 1){
            printf("Failled to read STDIN!\n");
            exit(0);
        }
        while (loop = 0)
        {

        switch (orient)
            {
            case 1:
            tab7[0][0] = '7';
            tab7[0][1] = '7';
            tab7[0][2] = '7';
            tab7[1][0] = '-';
            tab7[1][1] = '7';
            tab7[1][2] = '-';
            tab7[2][0] = '7';
            tab7[2][1] = '7';
            tab7[2][2] = '7';
            loop = 1;
            break;

            case 2:
            tab7[0][0] = '7';
            tab7[0][1] = '-';
            tab7[0][2] = '7';
            tab7[1][0] = '7';
            tab7[1][1] = '7';
            tab7[1][2] = '7';
            tab7[2][0] = '7';
            tab7[2][1] = '-';
            tab7[2][2] = '7';
            loop = 1;
            break;

            default:
            printf("Erro");
            break;
            }
        
        }
    }
}

void fun8(){
    char tab8[3][3] = {"888","8-8","888"};
}


void colocaPeça(){

}*/