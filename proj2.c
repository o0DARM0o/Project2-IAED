/* iaed-23 - ist1102760 - projeto2 */
/* 
 * autor: Diogo Marques 102760
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cabecalho.h"


linkedPrg *NewLinkedListPrg(){
    linkedPrg *list = (linkedPrg*)malloc(sizeof(struct linkedPrg ));

    list[0] = NULL; /*Cabeca da lista é iniciada a NULL*/

    return list; /*Retorna ponteiro para o primeiro no da lista*/
}

linkedCrr *NewLinkedListCrr(){
    linkedCrr *list = (linkedCrr*)malloc(sizeof(struct  nodeCrr));

    list[0] = NULL; /*Cabeca da lista é iniciada a NULL*/

    return list; /*Retorna ponteiro para o primeiro no da lista*/
}

linkedLig *newLinkedListLig(){
    linkedLig *list = (linkedLig*)malloc(sizeof(struct linkedLig));

    list[0] = NULL; /*Cabeca da lista é iniciada a NULL*/

    return list; /*Retorna ponteiro para o primeiro no da lista*/
}


/* SEGUNDO PROJETO*/


/* funcao conta quantas carreiras passam numa determinada paragem*/
int contaNumCrr(linkedCrr head){
    int cnt = 0;
    linkedCrr aux = head;
    while(aux){
        cnt++;
        aux =aux->next;
    }
    return cnt;
}

/* funcao remove a carreira de todas as paragens e atualiza o numero de carreiras da paragem*/
linkedPrg libertaCarreira(Carreira *crr){
    linkedPrg aux = crr->paragens, y;
    linkedCrr x;
    while(aux){ 
        x = aux->prg->carreiras;
        for(x = aux->prg->carreiras; x != NULL; x = x->next){
            if(strcmp(x->crr->nome, crr->nome) == 0){
               aux->prg->carreiras = removeCarreira(aux->prg->carreiras, 
                x->crr, 1); /*por cada paragem pertencente à carreira elimina-se a 
                carreira da linked list de carreiras pertencentes à paragem*/
               break;
            }
        }
        x = aux->prg->carreiras;
        aux->prg->nCarreiras = contaNumCrr(x); /* atualiza o numero de carreiras da paragem*/
        y = aux;
        aux = aux->next;
        free(y); /* free do node alocado para paragem na carrereira*/
    }
    free(crr->nome);
    /*if(crr->numParagens >= 2){
        free(crr->origem);
        free(crr->destino);
    }*/
    free(crr);
    return NULL;
}
 
/*funçao com principal objetivo eliminar uma carreira de uma linkedlist
funciona em dois modos, se modo = 1 entao o objetivo é eliminar uma carreira
apenas de uma linked list se o modo for igual a 0, a funcao elimina a carreira
do sistema e limpa a carreira de todas a paragens a que pertencia*/
linkedCrr removeCarreira(linkedCrr head, Carreira *crr, int modo){
    linkedCrr anterior = NULL, aux = head;
    while(aux != NULL){
        if(strcmp(aux->crr->nome, crr->nome) != 0){
            anterior = aux;
            aux = aux->next;
        }else{
            if(anterior == NULL){ /* caso se verique entao eliminamos o primeiro elemento da lista*/
                head = aux->next;
            }else{
                anterior->next = aux->next; /*remove elemento*/
            }
                if(modo != 1){ /* caso modo = 1 entao libertamos a carreria de todas as paragens associadas*/
                    if(aux->crr->numParagens >= 2){
                        free(aux->crr->origem);
                        free(aux->crr->destino);
                    }
                    libertaCarreira(aux->crr);
                }
                free(aux); /* free do node da carreira*/
                return head;
        }
    }
    return head;
}

/* funcao principal do comando 'r', em que remove a carreira do sistema
e perccorre todas as paragnes do sistema eliminando a carreira de uma paragem
caso a mesma tivesse no seu percurso a paragem*/
void commandRemCarreira(linkedCrr* head, char buffer[]){
    Carreira *crr;
    lePalavra(buffer);
    crr = procuraCarreira(buffer, head);
    if(crr == NULL){
        printf("%s: no such line.\n", buffer);
    }else{
        *head = removeCarreira(*head, crr, 0); /* remove carreira do sistema*/
    }
    memset(buffer, 0, strlen(buffer)+1);

}

/* funcao apaga a linked list de todas as paragens do sistema*/
linkedPrg deleteLinkedParagens(linkedPrg head){
    linkedPrg curr = head, temp;
    while(curr){ /* percorre a linked list de paragens e liberta o espaço*/
        temp = curr;
        if(temp->prg->nCarreiras != 0 ){
            free(temp->prg->carreiras);
        }
        free(temp->prg->nome);
        curr = curr->next;
        free(temp->prg);
        free(temp);
    }
    return NULL; /* cabeça da lista passa a null*/
}

/*funcao apaga a linked list de todas as carreiras do sistema*/
linkedCrr deleteLinkedCarreiras(linkedCrr head){
    linkedCrr curr = head, temp;
    while(curr){ /* percorre a linked list de carreiras e liberta o espaço*/
        temp = curr;
        if(temp->crr->numLigacoes != 0){
            free(temp->crr->origem);
            free(temp->crr->destino);
            free(temp->crr->paragens);
        }
        free(temp->crr->nome);
        curr = curr->next;
        free(temp->crr);
        free(temp);
    }
    return NULL; /* cabeça da lista passa a null*/
}

/* funcao apaga a linked list de todas as ligacoes do sistema*/
linkedLig deleteLinkedLigacoes(linkedLig head){
    linkedLig curr = head, temp;
    while(curr){ /* percorre a linked list de ligacoes e liberta o espaço*/
        temp = curr;
        free(temp->lig->carreira);
        free(temp->lig->destino);
        free(temp->lig->origem);
        curr = curr->next;
        free(temp->lig);
        free(temp);
    }
    return NULL; /* cabeça da lista passa a null*/
}

/* funcao principal do comando 'a' com obejtivo de limpar o sistema, eliminado
todos os dados*/
void commandLimpaSistema(linkedPrg *head, linkedCrr *headCrr, 
linkedLig *headLig){
    leAteAoFim();
    if(head != NULL && headCrr != NULL && headLig != NULL){ /* limpa o sistema*/
        *head = deleteLinkedParagens(*head);
        *headCrr = deleteLinkedCarreiras(*headCrr);
        *headLig = deleteLinkedLigacoes(*headLig);
    }
}

/* funcao reseta carreira caso sobre somente uma paragem na carreira
depois de eliminada paragem dada no stdin, caso modo = 1 removemos o destino
caso igual a 0 removemos a origem*/
void resetCarreira(Carreira *crr, int modo, linkedPrg *linked){
    Paragem *prgAux;
    crr->numParagens = 0;
    crr->custo = 0;
    crr->duracao = 0;
    crr->numLigacoes = 0;
    free(crr->paragens); /* cabela da lista fica a null*/
    crr->paragens = NULL;
    if(modo == 0){
        prgAux = procuraParagem(crr->origem, linked);
        free(crr->origem);
    }else{
        prgAux = procuraParagem(crr->destino, linked);
        free(crr->destino);
    }
    if(prgAux != NULL){
        prgAux->nCarreiras--; /* atualiza o numero de carreiras da paragem*/
    }
}

/* funcao atualiza a paragem de destino da carreira caso a paragem em questao
a ser eliminada corresponda à paragem de destino da carreira*/
linkedPrg atualizaDestino(linkedPrg head, Carreira *crr, Paragem *prg,
 linkedPrg *linked){
    linkedPrg aux;
    crr->numParagens--; /* atualiza numero de paragens da carreira*/
    if(crr->numParagens == 1){ /* se sobrar somente uma paragem a carreira fica sem paragens*/
        resetCarreira(crr, 0, linked);
        free(crr->destino);
        return head; /* cabeça da lista fica a null*/
    }
    aux = head;
    eliminaParagem(head, prg, NULL, 1); /* remove paragem*/
    while(aux->next != NULL){ /* procuro o ultimo elemento*/
        aux = aux->next;
    }
    free(crr->destino);
    crr->destino = (char*)malloc(sizeof(char)*(strlen(aux->prg->nome)+1));
    if(!crr->destino){
        printf("No memory.\n");
        exit(0);
    }
    strcpy(crr->destino, aux->prg->nome); /*atauliza o nome da paragem de destino da carrera*/
    return head;
}

/* funcao atualiza a paragem de origem da carreira caso a paragem em questao
a ser eliminada corresponda à paragem de origem da carreira*/
linkedPrg atualizaOrigem(linkedPrg head, Carreira *crr, Paragem *prg
, linkedPrg *linked){
    crr->numParagens--; /* atualiza numero de paragens da carreira*/
    if(crr->numParagens == 1){ /* se sobrar somente uma paragem a carreira fica sem paragens*/
        resetCarreira(crr, 1, linked);
        free(crr->origem);
        return NULL; /* cabeça da lista fica a null*/
    }
    head = eliminaParagem(head, prg, NULL, 1);
    free(crr->origem);
    crr->origem = (char*)malloc(sizeof(char)*(strlen(head->prg->nome)+1));
    if(!crr->origem){
        printf("No memory.\n");
        exit(0);
    }
    strcpy(crr->origem, head->prg->nome); /* atualiza a nova origem da carreira*/
    return head;
}

/* funcao atualiza a linked list de paragens da carreira depois de ser eliminada
uma ou mais paragens da mesma*/
linkedPrg atualizaPrgCarreira(Carreira *crr, Paragem *prg, linkedPrg *headPrg){
    linkedPrg  aux;
    if(strcmp(prg->nome, crr->origem) == 0 && 
        strcmp(prg->nome, crr->destino) == 0){ /* caso a paragem a eliminar seja tanto origem como destino
        atualizamos a origem e destino da carreira*/
        crr->paragens = atualizaOrigem(crr->paragens, crr, prg, headPrg);
        atualizaDestino(crr->paragens, crr, prg, headPrg);
    }else if(strcmp(prg->nome, crr->destino) == 0){ /*elimina a ultima paragem da carreira e atualiza o destino*/
         atualizaDestino(crr->paragens, crr, prg, headPrg);
    }else if(strcmp(prg->nome, crr->origem) == 0){ /* elimina a origam da carreira e atualiza a mesma*/
        crr->paragens = atualizaOrigem(crr->paragens, crr, prg, headPrg);
    }else{ /* caso nao seja nem origem nem destino elimina no meio da lista*/
         eliminaParagem(crr->paragens, prg, NULL, 1);
        crr->numParagens--;
    }
    if(crr->numParagens > 0){ /* elimina paragem dentro da lista caso seja encontrado mais paragens iguais*/
        aux = crr->paragens;
        while(aux->next){
            if(strcmp(prg->nome, aux->prg->nome) == 0){
                crr->numParagens--;
                aux = aux->next;
                eliminaParagem(crr->paragens, prg, NULL, 1);
            }else{
                aux = aux->next;
            }
        }
    }
    if(strcmp(crr->destino, prg->nome) == 0){ /* se depois de atualizarmos as 
    paragens o destino é igual à paragem a eliminar, eliminamos a mesma*/
        atualizaDestino(crr->paragens, crr, prg, headPrg);
    }
    if(crr->numParagens == 1){
        crr->numParagens = 0;
    }
    return crr->paragens;
}

/* funcao apaga o espaço reservardo na linked lista de carreiras de uma
paragem e atualiza a linked list de paragens da carreira ao eliminar paragens*/
linkedCrr popCarreira(linkedCrr head, linkedCrr *headCrr, Paragem *prg, linkedPrg *headPrg){
    linkedCrr aux = head->next;
    Carreira *crr;
    if(head != NULL){
        crr = procuraCarreira(head->crr->nome, headCrr);
        crr->paragens = atualizaPrgCarreira(crr, prg, headPrg); /*atauliza paragens da carreira*/
        free(head);
        
    }
    return aux;
}

/* funçao limpa todas as carreiras da linked list das carreiras
com percurso naquela paragem, que vai ser eliminada*/
void libertaParagem(Paragem *prg, linkedCrr *headCrr, linkedPrg *headPrg){
    linkedCrr head = prg->carreiras;
    while(head){
        head = popCarreira(head, headCrr, prg, headPrg); /* remove carreria da lista de carreiras da paragem*/
    }
}

/*funçao com principal objetivo eliminar uma paragem de uma linkedlist
funciona em dois modos, se modo = 1 entao o objetivo é eliminar a paragem
apenas de uma linked list se o modo for igual a 0, a funcao elimina a poaragem
do sistema e limpa a paragem de todas as carreiras a que pertencia*/
linkedPrg eliminaParagem(linkedPrg head, Paragem *prg, linkedCrr *headCrr, int modo){
    linkedPrg anterior = NULL, aux = head;
    while(aux != NULL){
        if(strcmp(aux->prg->nome, prg->nome) != 0){
            anterior = aux;
            aux = aux->next;
        }else{
            if(anterior == NULL){ /*caso seja para eliminar a cabeça de lista*/
                head = aux->next;
            }else{
                anterior->next = aux->next;
            }
            if(modo != 1){  /* caso modo = 1 entao libertamos a paragem de todas as carreiras associadas*/
                libertaParagem(aux->prg, headCrr , &head);
            }
            free(aux); /* liberta node da paragem*/
            return head;
        }
    }
    return head;
}

/*  funcao verifica se a prg dada como argumento é uma paragem de destino
ou origem*/
int verificaExtremo(linkedPrg *heagPrg, Paragem *prg){
    linkedPrg aux = *heagPrg, ant = NULL;
    if(strcmp(aux->prg->nome, prg->nome) == 0){
        return 0; /*origem da carreira*/
    }
    while(aux){
        ant = aux;
        aux = aux->next;
    }
    if(strcmp(ant->prg->nome , prg->nome) == 0){
        return 1; /*destino da carreira*/
    }
    return -1;
}

/* funcao procura uma determinada ligacao no linked list e devolve a ligacao caso
exista*/
Ligacao *procuraLigacao(linkedLig *headLig, int posicao, Carreira *crr, Paragem *prg){
    linkedLig aux;
    for(aux = *headLig; aux != NULL; aux = aux->next){
        if(strcmp(aux->lig->carreira, crr->nome) == 0 &&
        strcmp(aux->lig->origem, prg->nome) == 0){
            if(posicao == 0){ /* devolve a primeira ligaçao onde se encontra como origem a paragem dada*/
                return aux->lig;
            }
        }
        if(strcmp(aux->lig->carreira, crr->nome) == 0 &&
        strcmp(aux->lig->destino, prg->nome) == 0){
            if(posicao == 1){ /* devolve a primeira ligaçao onde se encontra como destino a paragem dada*/
                return aux->lig;
            }
        }
    }
    return NULL; /* caso não seja encontrada nenhuma ligaçao*/
}

/* funcao atualiza o custo e duracao da carreira*/
void atualizaCustos(Carreira *crr, Ligacao *lig){
    crr->custo -= lig->custo;
    crr->duracao -= lig->duracao;
    crr->numLigacoes--;
}

/* funcao verifica se os custos da carreira teem de ser alterados, em caso positivo altera*/
void verificaCustos(linkedLig *headLig, Paragem *prg){
    linkedCrr headCrr;
    linkedLig aux = *headLig;
    Ligacao *lig;
    int extremo;
    for(headCrr = prg->carreiras; headCrr != NULL; headCrr = headCrr->next){ /* percorre as carreiras das paragens*/
        if(procuraParagem(prg->nome, &headCrr->crr->paragens) != NULL){
            aux = *headLig;
            while(aux){ /* percorre a lista de ligacoes do sistema*/
                if(strcmp(aux->lig->carreira, headCrr->crr->nome)== 0 
                && (strcmp(prg->nome, aux->lig->destino) == 0 || strcmp(prg->nome, aux->lig->origem) == 0) ){ /* verifica se a ligacao corresponde à carreira e à paragem*/
                    if(strcmp(headCrr->crr->destino, headCrr->crr->origem) == 0){ /*caso a origem e destino sejam iguais entao retiramos o custo das duas ligacoes*/
                        lig = procuraLigacao(headLig, 0, headCrr->crr, prg);
                        atualizaCustos(headCrr->crr, lig);
                        lig = procuraLigacao(headLig, 1, headCrr->crr, prg);
                        atualizaCustos(headCrr->crr, lig);
                        break;
                    }
                    if((extremo = verificaExtremo(&headCrr->crr->paragens, prg)) >= 0 ){ /* caso seja maior que 0  retiramos o custo e a duraçao da ligacao
                    associada à paragem extremista da carreira*/
                        lig = procuraLigacao(headLig, extremo, headCrr->crr, prg);
                        atualizaCustos(headCrr->crr, lig);
                        break;
                    }
                }
                aux = aux->next;
            }
        }
    }
}

/* funcao principal do comando 'e' em que elimina uma paragem do sistema*/
void commandRemParagem(linkedPrg *headPrg, linkedCrr *headCrr, linkedLig *headLig, char buffer[]){
    Paragem *prg;
    if(headPrg != NULL){
        lePalavra(buffer);
        prg = procuraParagem(buffer, headPrg);
        if(prg == NULL){
            printf("%s: no such stop.\n", buffer);
            return;
        }
        verificaCustos(headLig, prg); /* verifica se os custos da carreira sao alterados*/
        *headPrg = eliminaParagem(*headPrg, prg, headCrr, 0); /*elimina paragem do sistema*/
        memset(buffer, 0, strlen(buffer)+1);
    }
    
}
