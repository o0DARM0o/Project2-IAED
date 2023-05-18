#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cabecalho.h"


int main(){
    int c, run = 0;
    /*cria as listas do sistema*/
    linkedPrg *listPrg = NewLinkedListPrg();
    linkedCrr *listCrr = NewLinkedListCrr();
    linkedLig *listLig = newLinkedListLig();
    char buffer[MAX_BUFFER];

    while((c = getchar()) != EOF && run == 0){
        switch(c){
            case 'q' : run = 1;
                break;
            case 'c' : commandCarreira(listCrr, buffer);
                break;
            case 'p' : commandParagem(listPrg, buffer);
                break;
            case 'l' : commandLigacoes(listPrg, listCrr, listLig, buffer);
                break;
            case 'i' : commandInterseccoes(listPrg);
                break;
            case 'r' : commandRemCarreira(listCrr, buffer);
                break;
            case 'a' : commandLimpaSistema(listPrg, listCrr, listLig);
                break;
            case 'e' : commandRemParagem(listPrg, listCrr, listLig, buffer);
                break;
            default: printf("Invalid comand: %c\n", c);
        }
    }
    /* limpa o sistema*/
    deleteLinkedCarreiras(*listCrr);
    deleteLinkedLigacoes(*listLig);
    deleteLinkedParagens(*listPrg);
    free(listCrr);
    free(listLig);
    free(listPrg);
    return 0;
}

