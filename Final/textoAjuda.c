#include "covid19.h"

/*
*Nome da funcao: textoAjuda
*
*Objetivo da funcao: Imprime o texto de ajuda em caso de erro
*/

void texto_ajuda()
{
    printf("\nBem-vindo ao programa de analise de dados relativos ao covid19\n");
    printf("Projecto de Prog feito por:\n");
    printf("\tHenrique Alves Pocinho Nº99952\n");
    printf("\tRodrigo Pereira Nº100080\n\n");

    printf("Comandos:\n\n");

    printf("»   -L x : Permite ao utilizador escolher o tipo de dados a ler:\n");
    printf("        > all: lê todos os dados disponiveis\n");
    printf("        > continente: lê todos os dados disponiveis relativos ao continente escolhido\n\n");

    printf("»   -S x : Permite escolher o método de ordenação de dados\n");
    printf("        > alfa: ordem alfabética\n");
    printf("        > pop: ordem descrescente de população de países\n");
    printf("        > inf yyyy-ww: ordem decrescente do número total de infectados por países num data yyyy-ww\n");
    printf("        > dea yyyy-ww: ordem decrescente do número total de mortes por países num data yyyy-ww\n\n");

    printf("»   -D x : Permite escolher o método de selecção de dados\n");
    printf("        > inf: seleciona para cada pais a semana com mais infectados\n");
    printf("        > dea: seleciona para cada pais a semana com mais mortes\n");
    printf("        > racioinf: seleciona para cada pais a semana com o maior rácio de infectados\n");
    printf("        > raciodea: seleciona para cada pais a semana com o maior rácio de mortes\n\n");

    printf("»   -P x : Permite escolher o método de restrição de dados\n");
    printf("        > min n: restringe os dados a paises com mais de n mil habitantes\n");
    printf("        > max n: restringe os dados a paises com menos de n mil habitantes\n");
    printf("        > date yyyy-ww: restringe os dados à semana indicada\n");
    printf("        > dates yyyy-ww yyyy-www: restringe os dados ao intervalo indicado\n\n");

    printf("»   -i x : Permite introduzir o nome do ficheiro de entrada de dados (de cariz obrigatório para o funcionamento do programa)\n\n");
    
    printf("»   -o x : Permite introduzir o nome do ficheiro de saida de dados (de cariz obrigatório para o funcionamento do programa)\n\n");

    printf("»   -h x : Mostra este texto\n\n");

}