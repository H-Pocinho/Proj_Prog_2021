/*
Projecto feito por:
Henrique Alves Pocinho Nº99952
Rodrigo Pereira Nº100080

Wargame
*/
//o 1,6,7,8 está feito. Amanhã devo acabar o resto && tudo foi testado no code blocks com 0 erros

int main(){


    return 0;
}

void fun1(){
    char tab1[3][3] = {"---","---","---"};
    int g, h, i, j;
    printf("Escolha a linha:");
    scanf("%d", &g);
    g = g-1;
    printf("\nEscolha a coluna:");
    scanf("%d", &h);
    h = h - 1;
    tab1[g][h] = '1';

}

void fun8(){
char tab8[3][3] = {"888","8-8","888"};

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
        scanf("%d", &orient);
        printf("Tem a certeza?\t Sim = 1    Não = 0\n");
        scanf("%d", &conf);
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
    default:
    printf("Erro");
        break;
    }
    
 }


}
void fun6(){
    //Falta implentar um LOOP para quando o num !=1ou2ou3ou4
    char tab6 [3][3] = {"---","---","---"};
    int orient, conf, loop;
    loop = 0;
    printf("A ponta do barco para cima = 1\n");
    printf("A ponta do barco para baixo = 2\n");
    printf("A ponta do barco para esquerda = 3\n");
    printf("A ponta do barco para direita = 4\n");
    scanf("%d", &conf);
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