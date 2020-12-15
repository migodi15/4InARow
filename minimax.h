//
//  minimax.h
//  ProjecteFinal
//
//  Created by Mireia Gómez i Diaz on 10/10/2020.
//

#ifndef minimax_h
#define minimax_h
#include "4enratlla.h"

#define PROFUNDITAT 6
#define MAX_PUNT 10000000
#define PvsP 1
#define PvsO 2
#define OvsO 3


typedef struct node {
    int tauler[N][N];
    struct node **fills;
    int n_fills;
    double valor;
}Node;


int valoraForats(int numFitxesSeguides, int numFitxes, int numForats);
int valoraTirada(int tauler[N][N]);
double funcioHeuristica(int tauler[N][N], int nivell);
void mostraNode (Node *p, int nivell);
void recorreArbreRecursiu(Node *p, int nivell);
void recorre1Nivell(Node *pare,int nivell);
void recorreArbre(Node *arrel);
void copiaTauler(int taulerCopia[N][N], int taulerOriginal[N][N]);
int quantsFills(Node *p);
Node *creaNode(Node *pare, int numFill, int nivell);
void crea1Nivell(Node *pare, int nivell);
void creaArbre(Node *arrel, int nivell);
void esborraArbre(Node *arrel);
void minimaxProfunditat(Node *arrel, int nivell);
void minimaxRecursiu(Node *arrel, int nivell);
int minimaxColumna(Node *arrel);
void tiradaPersona(int tauler[N][N], int jugador, int modeJoc);
void tiradaOrdinador(int tauler[N][N], int jugador);
int partidaAcabada(int tauler[N][N], int jugador, int modeJoc);
void personaVsPersona(void);
void personaVsOrdinador(void);
void canviaJugadors(int tauler[N][N]);
void ordinadorVsOrdinador(void);


#endif 
