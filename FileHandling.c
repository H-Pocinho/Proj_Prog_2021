
#include "covid19.h"

returnStruct dadosAll(char str[]){
    returnStruct dados;
    FILE *fpIN;

    char  linha[300];
    char **ficheiro = NULL;
    int nLinhas=0;

    if ((fpIN= fopen(str, "r"))==NULL)  {
        printf("Não consegui abrir o ficheiro. Programa terminado\n");
        exit(EXIT_FAILURE);
    } 

    fgets(linha,300,fpIN);
    while (fgets(linha,300,fpIN)!=NULL)
    {
        if (ficheiro==NULL|| (nLinhas%1)==0)  
        {
    
            ficheiro= (char**)realloc(ficheiro, (nLinhas+1)*sizeof(char*));
            if (ficheiro==NULL)
            {
                printf("realloc falhou. ficheiro demasiado grande. programa terminado.\n");
                exit(EXIT_FAILURE);
            }
        }

            if ((ficheiro[nLinhas]= (char*)malloc(strlen(linha)+2))==NULL)  {
                printf("malloc falhou. ficheiro demasiado grande. programa terminado.\n");
                exit(EXIT_FAILURE);
            }

        strcpy(ficheiro[nLinhas++], linha);
    }
    fclose(fpIN);

    dados.ponteiroFicheiro=ficheiro;
    dados.nLinhas=nLinhas;
    return dados;
}