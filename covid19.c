#include "covid19.h"



int main(int argc, char *argv[]){
    
    inputStruct dadosInput;
    returnStruct dadosFicheiro;


    dadosInput=verificacaoInput(argc,argv);
    if(dadosInput.erro!=0){
        printf("%s\n",dadosInput.mensagemErro);
        return -1;
    }

    if (dadosInput.leituraDados==0)
    {
        dadosFicheiro = dadosAll(dadosInput.inputName);
    }else{
        
    }
}

