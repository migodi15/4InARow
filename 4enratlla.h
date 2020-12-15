//
//  4enratlla.h
//  ProjecteFinal
//
//  Created by Mireia Gómez i Diaz on 10/10/2020.
//

#ifndef _enratlla_h
#define _enratlla_h

#define N 8
#define BUIT 0
#define JUG1 1 // ordinador == x
#define JUG2 2 // huma == o
#define TRUE 1
#define FALSE 0


void inicialitza(int tauler[N][N]);
void neteja(void);
void imprimirTauler(int tauler[N][N]);
int columnaValida(int tauler[N][N], int columna);
int columnaReal(int tauler[N][N], int numFill);
void caureFitxa(int tauler[N][N], int jugador, int columna);
int busca4enRatllaHoritzontal(int tauler[N][N], int jugador);
int busca4enRatllaVertical(int tauler[N][N], int jugador);
int busca4enRatllaDiagonal(int tauler[N][N], int jugador);
int busca4enRatlla(int tauler[N][N], int jugador);
int taulerPle(int tauler[N][N]);

#endif /* _enratlla_h */
