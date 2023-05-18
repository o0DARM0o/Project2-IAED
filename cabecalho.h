#ifndef CABECALHO_H
#define CABECALHO_H



#define MAX_BUFFER 65535

typedef struct crr Carreira;

typedef struct nodeCrr{
    Carreira* crr;
    struct nodeCrr *next;
} *linkedCrr;

typedef struct{
    double longe;
    double lat;
    int nCarreiras;
    char *nome;
    linkedCrr carreiras;
}Paragem;

typedef struct linkedPrg{
    Paragem *prg;
    struct linkedPrg *next, *prev;
} *linkedPrg;

struct crr{
    char *nome;
    int numLigacoes;
    int numParagens;
    double custo;
    double duracao;
    char *origem;
    char *destino;
    linkedPrg paragens;
};

typedef struct{
    double custo;
    double duracao;
    char *origem;
    char *destino;
    char *carreira;
}Ligacao;

typedef struct linkedLig{
    Ligacao *lig;
    struct linkedLig *next;
}*linkedLig;


int lePalavra(char str[]);
void leAteAoFim();
void listaTodasAsCarreiras(linkedCrr *head);
void listaParagensCarreira(int numPrg, linkedPrg head);
Carreira* procuraCarreira(char *str, linkedCrr *head);
void adicionaCarreira(Carreira *crr, char* nome, linkedCrr *head);
void commandCarreira(linkedCrr *l, char str[]);

Paragem* procuraParagem(char *str, linkedPrg *head);
void adicionaParagem(Paragem *prg, char* nome, linkedPrg *head, char buffer[]);
void listaTodasAsParagens(linkedPrg *head);
void commandParagem(linkedPrg *l, char str[]);

int verificaArgumentosLigacoes(Carreira *carr, Paragem *paraO, Paragem *paraD);
void adicionaNovaOrigem(Carreira *crr, Paragem *prgO);
void adicionaLigacao(Carreira *crr, Paragem *paraO, Paragem *paraD);
void adicionaOrigemEDestino(Carreira *crr, Paragem *prgO, Paragem *prgD);
void adicionaNovoDestino(Carreira *crr, Paragem *prgD);
void commandLigacoes(linkedPrg *head, linkedCrr *headcrr, linkedLig *headLig, char str[]);

void commandInterseccoes(linkedPrg *l);

linkedPrg *NewLinkedListPrg();
linkedCrr *NewLinkedListCrr();
linkedLig *newLinkedListLig();

void commandRemCarreira(linkedCrr* head, char buffer[]);
void commandLimpaSistema(linkedPrg *head, linkedCrr *headCrr, linkedLig *headLig);
linkedPrg eliminaParagem(linkedPrg head, Paragem *prg, linkedCrr *headCrr, int modo);
void commandRemParagem(linkedPrg *headPrg, linkedCrr *headCrr, linkedLig *headLig, char buffer[]);

linkedPrg deleteLinkedParagens(linkedPrg head);
linkedCrr deleteLinkedCarreiras(linkedCrr head);
linkedLig deleteLinkedLigacoes(linkedLig head);

linkedCrr removeCarreira(linkedCrr head, Carreira *crr, int modo);

#endif
