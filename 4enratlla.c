//
//  4enratlla.c
//  ProjecteFinal
//
//  Created by Mireia Gómez i Diaz on 10/10/2020.
//

#include "4enratlla.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void inicialitza(int tauler[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            tauler[i][j]=BUIT;
        }
    }
}


void neteja(void){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


void imprimirTauler(int tauler[N][N]){
    neteja();
    printf("  1   2   3   4   5   6   7   8 \n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(tauler[i][j]==BUIT) printf("|   ");
            if(tauler[i][j]==JUG1) printf("| x ");
            if(tauler[i][j]==JUG2) printf("| o ");
        }
        printf("|\n");
    }
}


int columnaValida(int tauler[N][N], int columna){
    if(tauler[0][columna]==BUIT){
        return TRUE;
    }
    else{
        return FALSE;
    }
}


int columnaReal(int tauler[N][N], int numFill){
    int t=-1;
    
    for(int i=0;i<N;i++){
        if(columnaValida(tauler, i)==TRUE){
            t++;
            if(t==numFill) return i;
        }
    }
    return 0;
}


void caureFitxa(int tauler[N][N], int jugador, int columna){
    for(int i=(N-1);i>=0;i--){
        if(tauler[i][columna]==0){
            tauler[i][columna]=jugador;
            break;
        }
    }
}


int busca4enRatllaHoritzontal(int tauler[N][N], int jugador){
    for(int i=0;i<N;i++){
        for(int j=0;j<(N-3);j++){
            if(tauler[i][j]==tauler[i][j+1] && tauler[i][j]==tauler[i][j+2] && tauler[i][j]==tauler[i][j+3] && tauler[i][j]==jugador) return TRUE;
        }
    }
    return FALSE;
}


int busca4enRatllaVertical(int tauler[N][N], int jugador){
    for(int j=0;j<N;j++){
        for(int i=0;i<(N-3);i++){
            if(tauler[i][j]==tauler[i+1][j] && tauler[i][j]==tauler[i+2][j] && tauler[i][j]==tauler[i+3][j] && tauler[i][j]==jugador) return TRUE;
        }
    }
    return FALSE;
}


int busca4enRatllaDiagonal(int tauler[N][N], int jugador){
    for(int j=(-N+1);j<N;j++){
        for(int i=0;i<(N-3);i++){
            if( 0<=j && (j+3)<N ){
                if(tauler[i][j]==tauler[i+1][j+1] && tauler[i][j]==tauler[i+2][j+2] && tauler[i][j]==tauler[i+3][j+3] && tauler[i][j]==jugador) return TRUE;
            }
        }
    }
    for(int j=(2*N-2);j>=0;j--){
        for(int i=0;i<(N-3);i++){
            if( j<N && 0<= (j-3) ){
                if(tauler[i][j]==tauler[i+1][j-1] && tauler[i][j]==tauler[i+2][j-2] && tauler[i][j]==tauler[i+3][j-3] && tauler[i][j]==jugador) return TRUE;
            }
        }
    }
    return FALSE;
}


int busca4enRatlla(int tauler[N][N], int jugador){
    if(busca4enRatllaHoritzontal(tauler,jugador)==TRUE) return TRUE;
    if(busca4enRatllaVertical(tauler,jugador)==TRUE) return TRUE;
    if(busca4enRatllaDiagonal(tauler,jugador)==TRUE) return TRUE;
    return FALSE;
}


int taulerPle(int tauler[N][N]){
    int aux=0;
    for(int i=0;i<N;i++){
        aux=aux+columnaValida(tauler,i);
    }
    
    if(aux==0){
        imprimirTauler(tauler);
        printf("Tauler ple. Empat! \n");
        return TRUE;
    }
    return FALSE;
}
