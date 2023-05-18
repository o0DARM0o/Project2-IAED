/* iaed-23 - ist1102760 - projeto2 */
/* 
 * autor: Diogo Marques 102760
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cabecalho.h"

/* FUNÇÕES DE LEITURA*/

/* funçao que lê o nome da paregem entre aspas, retorna 0 em
caso de uma leitura bem sucedida e -1 se o nome passar dos limites*/
int leNomeParagem(char str[]){
    int estado = 1, i = 0;
    char c = getchar();

    while(estado == 1){ /* enquanto estiver entre as aspas guarda o nome no vetor */
        str[i++] = c;
        c = getchar();
        if(c == '"'){
            str[i] = '\0';
            estado = 0;
        }
    }
    return 0;
}

/* função que lê a proxima palavra dada no input até encontrar um espaço 
ou até encontrar aspas retorna true em caso de ter chegado ao fim da linha*/
int lePalavra(char str[]){
    char c = getchar();
    int i = 0;
    while(c == ' ' || c == '\t'){
        c = getchar();
    }
    while(c != ' ' && c != '\n'){ /* lê palavra até encontrar espaço branco ou fim de linha*/
            str[i] = c;
        if(c == '"'){ /* se encontrar aspas significa que temos um nome de paragem com espaços brancos*/
            leNomeParagem(str);
            c = getchar();
            return (c == '\n');
        }else{
            i++;
            c = getchar();
        }
    }
    str[i] = '\0';

    return (c == '\n'); 
}

/* lê o input até ao fim sem guardar nada*/
void leAteAoFim(){
    char c = getchar();
    while(c != '\n'){
        c = getchar();
    }
}
 /* lê palavra(s) até ao fim da linha e guarda*/
void leFimLinha(char str[]){
    char c = getchar();
	int i = 0;
	while (c != '\n') {
		str[i++] = c;
		c = getchar();
	}
	str[i] = '\0';
}

/* FUNÇÕES DO COMANDO 'c' */


/* função lista todas as carreiraS do sistema, uma por linha*/
void listaTodasAsCarreiras(linkedCrr *head){
    linkedCrr aux;
    for(aux = *head; aux != NULL; aux = aux->next){
        if(aux->crr->numParagens == 0){ /* caso a carreira não tenha nenhuma paragem ignorasse os campos com os nomes das paragens*/
            printf("%s %d %.2f %.2f\n", aux->crr->nome, aux->crr->numParagens,
            aux->crr->custo, aux->crr->duracao);
        }else{
            printf("%s %s %s %d %.2f %.2f\n", aux->crr->nome,
            aux->crr->origem, aux->crr->destino,
            aux->crr->numParagens, aux->crr->custo, aux->crr->duracao );
        }
    }
}

/* função lista todos os nomes das paregens de uma determinada carreira
 por ordem de  origem -> destino*/ 
void listaParagensCarreira(int numPrg, linkedPrg head){
    int i= 0;
    while(head != NULL){
        printf("%s", head->prg->nome);
        head = head->next;
        if(i != numPrg-1){
            printf(", ");
        }else{
            putchar('\n'); /* caso seja a  ultima paragem da carreira, muda de linha*/
        }
        i++;
    }
}

/* função verifica se uma determinada carreira com nome str pertence ao sistema, 
retornado a mesma caso exista*/
Carreira* procuraCarreira(char *str, linkedCrr *head){
   linkedCrr aux;
   for(aux = *head; aux != NULL; aux = aux->next){
        if(strcmp(aux->crr->nome, str) == 0){
            return aux->crr;
        }
   }
   return NULL;
}

/* funcao adiciona carreira no fim da linked list*/
void adicionaFimCrr(linkedCrr *head, linkedCrr novo){
    linkedCrr aux;
    for(aux = *head; aux->next != NULL; aux = aux->next);
    aux->next = novo; /* nova carreira*/
}

/* função adiciona a carreira crr ao sistema*/
void adicionaCarreira(Carreira *crr, char* nome, linkedCrr *head){

    linkedCrr novo = malloc(sizeof(struct nodeCrr));
    crr = (Carreira*)malloc(sizeof(struct crr));
    crr->nome = (char*)malloc(sizeof(char)*(strlen(nome)+1));
    if(!novo || !crr || !crr->nome){ /*verifica se foi bem alocado*/
        printf("No memory.\n");
        exit(0);
    }
    strcpy(crr->nome, nome);
    crr->custo = 0;
    crr->duracao = 0;
    crr->numLigacoes = 0;
    crr->numParagens = 0;
    crr->paragens = NULL;
    novo->crr = crr;
    novo->next = NULL;
    if(*head == NULL){
        *head = novo; /* caso a lista esteja vazia*/
    }else{
        adicionaFimCrr(head, novo); /*adiciona carreira no fim da lista*/
    }

}


/* função lista as paragens de uma carreira por ordem inversa destino -> origem*/
void mostraInverso(Carreira *crr){
    int i= crr->numParagens-1;
    linkedPrg aux, head = crr->paragens;
    for(aux = head; aux->next != NULL; aux = aux->next);
    while(i >= 0){
        printf("%s", aux->prg->nome);
        if(i != 0){
            printf(", ");
        }else{
            putchar('\n'); /* caso seja o nome da ultima paragem*/
        }
        i--;
        aux = aux->prev;
    }
}

/* função verifica se o terceiro argumento do comando 'c' está nas condições 
para listar paragens  no sentido inverso*/
int condicaoInverso(char str[], Carreira *crr){
    /* verifica todas as possibilidades para prefixos da palavra inverso, caso alguma se verifica mostra o as paragens em sentido inverso*/
    if(strcmp(str, "inverso") == 0){
        mostraInverso(crr);
    }else if(strcmp(str, "inv") == 0){
        mostraInverso(crr);
    }else if(strcmp(str, "inve") == 0){
        mostraInverso(crr);
    }else if(strcmp(str, "inver") == 0){
        mostraInverso(crr);
    }else if(strcmp(str, "invers") == 0){
        mostraInverso(crr);
    }else{
        return 0;
    }
    return 1;
}

/* função principal do comando 'c' que distribui diferentes funções para diferentes inputs*/
void commandCarreira(linkedCrr *head, char buffer[]){
    Carreira *crr;
    char  resto[8];
    int palavra;

    palavra = lePalavra(buffer); /* lê nome da carreira */
    if(strlen(buffer) == 0){ /* se não se nenhum nome de carreira, então lista-se todas as carreiras do sistema*/
        listaTodasAsCarreiras(head);
    }else{
        crr = procuraCarreira(buffer, head);
        if(!palavra){ /* se o nome da carreira não for o ultimo argumeto então verifica-se se tem uma sort option valida*/
            if(crr !=NULL){
                leFimLinha(resto);
                if(!condicaoInverso(resto, crr)){
                    printf("incorrect sort option.\n");
                    return;
                }
            }
        }else{
            if(crr != NULL){ /* se o indice da paragem existir, então escrevemos  todas as paragens da carreira (origem -> destino)*/
                listaParagensCarreira(crr->numParagens, crr->paragens);
            }else{
                /* se não existir. adicionamos uma nova carreira*/
                    adicionaCarreira(crr, buffer, head);
                }
        }
    }
    memset(buffer,0, strlen(buffer)+1);
}

/* FUNÇÕES DO COMANDO 'p' */

/* função verifica se uma determinada paragem com nome str pertence ao sistema, 
retornado a mesma caso exista*/
Paragem* procuraParagem(char *str, linkedPrg *head){
   linkedPrg aux;
   for(aux = *head; aux != NULL; aux = aux->next){
        if(strcmp(aux->prg->nome, str) == 0){
            return aux->prg;
        }
   }
   return NULL;
}

/* funcao adiciona paragem no fim da linked list*/
void adicionaFimPrg(linkedPrg *head, linkedPrg novo){
    linkedPrg aux;
    for(aux = *head; aux->next != NULL; aux = aux->next);
    novo->prev = aux; /* paragem anterior à adicionada*/
    aux->next = novo;
}

/* função adiciona a paragem com o nome str ao sistema */
void adicionaParagem(Paragem *prg, char* nome, linkedPrg *head, char buffer[]){
    double longe, lat;
    linkedPrg novo;
    novo = malloc(sizeof(struct linkedPrg ));
    prg = (Paragem*)malloc(sizeof(Paragem));
    prg->nome = (char*)malloc(sizeof(char)*(strlen(nome)+1));
    if(!novo || !prg || !prg->nome){ /*verifica se a memora foi bem alocada*/
        printf("No memory.\n");
        exit(0);
    }
    strcpy(prg->nome, nome);
    lePalavra(buffer); /* lê e converte para float a latitude da paragem*/ 
    lat = atof(buffer);
    lePalavra(buffer); /* lê e converte para float a longitude da paragem*/ 
    longe = atof(buffer);
    prg->carreiras = NULL;
    prg->lat = lat;
    prg->longe = longe;
    prg->nCarreiras = 0;
    novo->prg = prg;
    novo->next = NULL;
    if(*head == NULL){
        *head = novo;  /*caso lista vazia*/
        novo->prev = NULL;
    }else{
         adicionaFimPrg(head, novo); 
    }
}

/* função lista todas as parages do sistema, uma por linha*/
void listaTodasAsParagens(linkedPrg *head){
    linkedPrg aux;
    for(aux = *head; aux != NULL; aux = aux->next){
        printf("%s: %16.12f %16.12f %d\n", aux->prg->nome, aux->prg->lat,
        aux->prg->longe, aux->prg->nCarreiras );
    }
}

/*função principal do comando 'p' que distribui diferentes funções para diferentes inputs
e no caso de haver alguma irregularidade dá print do erro*/
void commandParagem(linkedPrg *l, char buffer[]){
    Paragem *paragem;
    int palavra;
    palavra = lePalavra(buffer); /* lê argumento destinado ao nome da paragem*/
    if(strlen(buffer)== 0){
        listaTodasAsParagens(l);  /* lista todas as paragens do sistema se não for verificado nenhum nome de paragem*/
    }else{
        paragem = procuraParagem(buffer, l);
        if(!palavra){ /* caso o nome da paragem não seja o ultimo argumento*/
            if(paragem == NULL){
                adicionaParagem(paragem, buffer, l, buffer);
            }else{ /* se o indice já existir então lança-se um erro*/
                printf("%s: stop already exists.\n", buffer);
                leAteAoFim();
            }
        }else if(paragem != NULL){ /* caso o nome da paragem seja o ultimo argumento, entao escreve-se a latitude e longitude da paragem*/
            printf("%16.12f %16.12f\n",paragem->lat , paragem->longe);
        }else{ /* caso a  paragem não existir no sistema*/
            printf("%s: no such stop.\n", buffer);
        }
    }
    memset(buffer,0, strlen(buffer)+1);
}

/* FUNÇÕES DO COMANDO 'l' */

/* função verifica os três primeiros argumentos do input e lança os erros caso 
algo de errado se verifique */  
int verificaArgumentosLigacoes(Carreira *carr, Paragem *paraO, Paragem *paraD){
    if(carr->numParagens >= 2){ 
        if(strcmp(paraO->nome, 
        carr->destino) == 0 ||
        strcmp(paraD->nome, carr->origem) == 0){  /* a paragem de destino da ligação tem de corresponder à origem
                                    da carreira ou a paragem de origem da ligação tem de ser a paragem  de destino final da carreira */
            return 1;                                                                    
        }
        printf("link cannot be associated with bus line.\n");
        leAteAoFim();
        return 0;
    }else{
        return 1;
    }
}

/* função ordena o vetor de indices de carreiras pela ordem alfabética de nomes*/
linkedCrr ordenaNomesCarreiras(Carreira *crr, linkedCrr head){
    linkedCrr nova = (linkedCrr)malloc(sizeof(struct nodeCrr)),
    aux = head ,anterior = NULL;
    Carreira *crr_aux = crr;
    if(!nova){
        printf("No memory.\n");
        exit(0);
    }
    nova->crr = crr_aux;
    nova->next = NULL;
    while(aux != NULL && strcmp(aux->crr->nome, crr_aux->nome ) < 0){ /* percorre a lista até encontrar um elemento maior*/
        anterior = aux;
        aux = aux->next;
    }
    nova->next = aux;
    if(anterior == NULL){
        head = nova; /* caso a lista esteje vazia*/
    }else{
        anterior->next = nova;
    }
    return head;
}

/* funcao adiciona nova cabeça à lista*/
linkedPrg pushLigacao(linkedPrg head, linkedPrg novo, Paragem *prgO){
    novo->prg = prgO;
    novo->prev = NULL;
    novo->next = head;
    head->prev = novo;
    return novo;
}

/* funcao adiciona ligacao no fim da linked list*/
void adicionaLigLinked(linkedLig *head, char *origem, char *destino, float custo, float duracao, char *carreira){
    linkedLig nova = malloc(sizeof(struct linkedLig )), aux;
    Ligacao *lig = (Ligacao*)malloc(sizeof( Ligacao));
    if(!nova || !lig){ /* verifica se foi bem alocado*/
        printf("No memory.\n");
        exit(0);
    }
    lig->carreira = (char*)malloc(sizeof(char)*(strlen(carreira)+1));
    strcpy(lig->carreira, carreira);
    lig->destino = (char*)malloc(sizeof(char)*(strlen(destino)+1));
    strcpy(lig->destino, destino);
    lig->origem = (char*)malloc(sizeof(char)*(strlen(origem)+1));
    strcpy(lig->origem, origem);
    lig->custo = custo;
    lig->duracao = duracao;
    nova->lig = lig;
    nova->next = NULL;
    if(*head == NULL){ /*lista vazia*/
        *head = nova;
    }else{
        for(aux = *head; aux->next != NULL; aux = aux->next);
        aux->next = nova; /*nova ligacao no fim da lista*/
    }
}

/* função adiciona uma nova origem à carreira */
void adicionaNovaOrigem(Carreira *crr, Paragem *prgO){
    linkedPrg  aux = malloc(sizeof( struct linkedPrg));
    free(crr->origem);
    crr->origem = (char*)malloc(sizeof(char)*(strlen(prgO->nome)+1));
    strcpy(crr->origem, prgO->nome); /*nova origem*/
    if(strcmp(crr->destino, prgO->nome) != 0){
        if(procuraParagem(prgO->nome, &crr->paragens) == NULL){
            prgO->nCarreiras++;
            prgO->carreiras = ordenaNomesCarreiras(crr, prgO->carreiras);  /* ordena por ordem alfabetica os nomes das carreiras*/
        }
    }
    crr->paragens = pushLigacao(crr->paragens, aux, prgO); /* adiociona nova origem na lista*/
    crr->numParagens++;
}

/* função adiciona um novo destino final à carreira */
void adicionaNovoDestino(Carreira *crr, Paragem *prgD){
    linkedPrg novo = malloc(sizeof( struct linkedPrg)), head = crr->paragens;
    free(crr->destino);
    crr->destino = (char*)malloc(sizeof(char)*(strlen(prgD->nome)+1));
    strcpy(crr->destino, prgD->nome); /* novo destino*/
    if(strcmp(crr->origem, prgD->nome) != 0 ){
        if(procuraParagem(prgD->nome, &crr->paragens) == NULL){
            prgD->nCarreiras++;
            prgD->carreiras = ordenaNomesCarreiras(crr, prgD->carreiras);  /* ordena por ordem alfabetica os nomes das carreiras*/
        }
    }
        novo->prg = prgD;
        novo->next = NULL;

        adicionaFimPrg(&head, novo); /* adciona novo destino à carreira*/
        crr->numParagens++;
}

/* função adiciona origem e destino a um carreira, caso esta não tenha nenhuma paragem ainda */
void adicionaOrigemEDestino(Carreira *crr, Paragem *prgO, Paragem *prgD){
    linkedPrg aux =malloc(sizeof(struct linkedPrg)), head;
    crr->paragens = malloc(sizeof(struct linkedPrg));
    if(!aux || !crr->paragens){ /* verifica se foi bem alocado*/
        printf("No memory.\n");
        exit(0);
    }
    head = crr->paragens;
    head->prg = prgO; /*coloca origem*/
    aux->prg = prgD; /* coloca destino*/
    aux->prev = head;
    head->next = aux;
    crr->numParagens += 2;
    crr->origem = (char*)malloc(sizeof(char)*(strlen(prgO->nome)+1));
    strcpy(crr->origem, prgO->nome); 
    crr->destino = (char*)malloc(sizeof(char)*(strlen(prgD->nome)+1));
    strcpy(crr->destino, prgD->nome); 
    if(strcmp(prgD->nome, prgO->nome) == 0){ /* caso seja a mesma paragem a adicionar*/
        prgD->nCarreiras++;
    }else{
        prgO->nCarreiras++;
        prgD->nCarreiras++;
    }
    prgO->carreiras = ordenaNomesCarreiras(crr, prgO->carreiras); /* ordena por ordem alfabetica os nomes das carreiras*/
    prgD->carreiras = ordenaNomesCarreiras(crr, prgD->carreiras);
}

/* função adiciona nova ligação à carreira crr, adicionando nova paragem(s) */
void adicionaLigacao(Carreira *crr, Paragem *paraO, Paragem *paraD){
    if(crr->numLigacoes == 0){ /* se a carreira não tiver nenhuma ligação então adiciona nova o rigem e destino*/
        adicionaOrigemEDestino(crr, paraO, paraD);
    }else if(strcmp(paraO->nome, 
        crr->destino) == 0){ /* se a paragem de origem da ligação for igual à paragem de destino da carreira então
                                                        adiciona novo destino final à carreira*/
        adicionaNovoDestino(crr, paraD);
    }else if(strcmp(paraD->nome,
        crr->origem) == 0){ /* se a paragem de destino da ligação for igual à paragem de origem da carreira então
                                                        adiciona nova origem à carreira*/
        adicionaNovaOrigem(crr, paraO);
    }
    crr->numLigacoes++;
}

/* função principal do comando 'l' que verifica todos os argumentos do input e adciona nova ligação*/
void commandLigacoes(linkedPrg *head, linkedCrr *headcrr, linkedLig *headLig, char buffer[]){
    Carreira *carreira;
    Paragem *paragemO, *paragemD;
    float dur, vlr;
    lePalavra(buffer);
    if((carreira = procuraCarreira(buffer, headcrr)) == NULL){
        printf("%s: no such line.\n", buffer);
        leAteAoFim();
        return;
    }
    memset(buffer, 0, strlen(buffer)+1);
    lePalavra(buffer);
    if((paragemO = procuraParagem(buffer, head)) == NULL){
        printf("%s: no such stop.\n", buffer);
        leAteAoFim();
        return;
    }
    memset(buffer, 0, strlen(buffer)+1);
    lePalavra(buffer);
    if((paragemD = procuraParagem(buffer, head)) == NULL){
        printf("%s: no such stop.\n", buffer);
        leAteAoFim();
        return;
    }
    memset(buffer, 0, strlen(buffer)+1);
    if((verificaArgumentosLigacoes(carreira, paragemO, paragemD))){ /* verifica  os argumentos  das paragens e carreira do input*/
            lePalavra(buffer); /* lê o valor da ligação e converte para float*/
            vlr = atof(buffer);
            memset(buffer, 0, strlen(buffer)+1); /* reseta o vetor */
            lePalavra(buffer); /* lê a duração da ligação e converte para float*/
            dur = atof(buffer);
        if(vlr >= 0 && dur >= 0){ /* se a duração e o valor da ligação não forem negativos, adciona nova ligação*/
                carreira->custo += vlr;
                carreira->duracao += dur;
                adicionaLigacao(carreira, paragemO, paragemD);
                adicionaLigLinked(headLig, paragemO->nome, paragemD->nome, vlr, dur, carreira->nome);
        }else{
                printf("negative cost or duration.\n");
        }
    }
    memset(buffer, 0, strlen(buffer)+1);
}


/* FUNÇÃO DO COMANDO 'i' */

/* função lista todas as paragens (uma por linha), com os nomes de todas as carreiras que fazem intersecao
nessa mesma paragem por ordem alfabética*/
void commandInterseccoes(linkedPrg *l){
    int j;
    linkedPrg head;
    linkedCrr aux;
    leAteAoFim();
    if(l == NULL){
        return;
    }
    for(head = *l; head != NULL; head = head->next){
        aux =  head->prg->carreiras;
        if(head->prg->nCarreiras > 1){ /* se o numero de carreiras que passam na paragem é maior que 1 então entra na condição de intersecao*/
            printf("%s %d: ", head->prg->nome, head->prg->nCarreiras);
            j = 0;
            while(aux != NULL ){ /* ciclo para escrever os nomes das carreiras*/
                printf("%s", aux->crr->nome);
                aux = aux->next;
                if(j < head->prg->nCarreiras-1){
                    printf(" ");
                }else{
                    putchar('\n'); /* caso seja a ultima carreira do vetor */
                }
                j++;
            }
        }
    }
}