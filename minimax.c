//
//  minimax.c
//  ProjecteFinal
//
//  Created by Mireia Gómez i Diaz on 10/10/2020.
//

#include "minimax.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int valoraForats(int numFitxesSeguides, int numFitxes, int numForats) {
    int pes[4];
    pes[0]=0;
    pes[1]=10;
    pes[2]=100;
    pes[3]=10000;
    return pes[numFitxesSeguides]+10*numFitxes+numForats;
}


int valoraTirada(int tauler[N][N]) {
    int puntuacio=0;
    int maq, per, hue, segmaq, segper, seghue;
    
    for (int i=0;i<N;i++) {             //mirem per files el num fitxes de cada jug
        maq=0;                          //nova fila, inicialitzem variables
        per=0;
        hue=0;
        segmaq=0;
        segper=0;
        seghue=0;
        
        for (int j=0;j<N;j++) {
            if (tauler[i][j]==JUG1) {
                maq = maq + 1;
                segmaq = segmaq + 1;
                if (per>0){
                    hue = seghue;
                    per=0;
                    segper=0;
                }
                seghue=0;
            }
            if (tauler[i][j]==JUG2) {
                per = per + 1;
                segper = segper + 1;
                if (maq>0){
                    hue = seghue;
                    maq=0;
                    segmaq=0;
                }
                seghue=0;
            }
            if (tauler[i][j]==BUIT) {
                hue++;
                seghue++;
                segmaq=0;
                segper=0;
            }
            if (hue+maq>=4) puntuacio = puntuacio + valoraForats(segmaq,maq,hue);
            if (hue+per>=4) puntuacio = puntuacio - valoraForats(segper,per,hue);
        }
    }
    return puntuacio;
}


double funcioHeuristica(int tauler[N][N], int nivell){
    double valor;
    if(busca4enRatlla(tauler, JUG1)==TRUE){ //mirem niv parells, si han guanyat els 2, primer ha guanyt JUG1
        valor= MAX_PUNT-10*nivell;
    }
    else if(busca4enRatlla(tauler, JUG2)==TRUE){
        valor= -MAX_PUNT+10*nivell;
    }
    else{
        valor=(double) valoraTirada(tauler); //+ valoraTiradaColumna(tauler);
    }
    return valor;
}


void mostraNode (Node *p, int nivell){
    for(int i=0;i<nivell;i++) printf("\t");
    printf("%f\n",p->valor);
}


void recorreArbreRecursiu(Node *p, int nivell){
    mostraNode(p,nivell);
    if(p->n_fills>0){
        for(int i=0;i<p->n_fills;i++){
            recorreArbreRecursiu(p->fills[i],nivell+1);
        }
    }
}


void recorre1Nivell(Node *pare,int nivell){
    for(int i=0;i<pare->n_fills;i++){
        mostraNode(pare->fills[i], nivell);
    }
}


void recorreArbre(Node *arrel){
    printf("%f\n",arrel->valor);
    recorre1Nivell(arrel,1);
    for(int i=0;i<arrel->n_fills;i++){
        recorre1Nivell(arrel->fills[i],2);
    }
}


void copiaTauler(int taulerCopia[N][N], int taulerOriginal[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            taulerCopia[i][j]=taulerOriginal[i][j];
        }
    }
}


int quantsFills(Node *p){
    int k=0;
    for(int i=0;i<N; i++){
        k=k+columnaValida(p->tauler,i);
    }
    return k;
}


Node *creaNode(Node *pare, int numFill, int nivell){
    Node *p=malloc(sizeof(Node));
    copiaTauler(p->tauler,pare->tauler);
    
    if(nivell%2 == 1) caureFitxa(p->tauler, JUG1, columnaReal(pare->tauler,numFill));
    else caureFitxa(p->tauler, JUG2, columnaReal(pare->tauler,numFill));
    
    if (nivell>=PROFUNDITAT || busca4enRatlla(p->tauler, JUG2)==TRUE || busca4enRatlla(p->tauler, JUG1)==TRUE){
        p->n_fills=0;
        p->fills=NULL;
        p->valor=funcioHeuristica(p->tauler, nivell);
    }
    
    else{
        p->n_fills=quantsFills(p);
        p->fills=malloc(p->n_fills*sizeof(Node*));
    }
    
    return p;
}


void crea1Nivell(Node *pare, int nivell){
    int i;
    for (i=0;i<pare->n_fills;i++){
        pare->fills[i]=creaNode(pare,i,nivell);
    }
}


void creaArbre(Node *arrel, int nivell){
    if(arrel->n_fills>0){
        crea1Nivell(arrel,nivell+1);
        for (int i=0;i<arrel->n_fills;i++){
            creaArbre(arrel->fills[i],nivell+1);
        }
    }
}


void esborraArbre(Node *arrel){
     if(arrel->n_fills>0){
         for (int i=0;i<arrel->n_fills;i++){
             esborraArbre(arrel->fills[i]);
             if (arrel->fills[i]->fills!=NULL)
                 free(arrel->fills[i]->fills);
             free(arrel->fills[i]);
         }
     }
}


void minimaxProfunditat(Node *arrel, int nivell){
    double minim, maxim;
    
    if(nivell%2 == 1){
        maxim=arrel->fills[0]->valor;
        for(int i=1;i<arrel->n_fills;i++){
            if(arrel->fills[i]->valor > maxim){
                maxim=arrel->fills[i]->valor;
            }
        }
        arrel->valor=maxim;
    }
    else {
        minim=arrel->fills[0]->valor;
        for(int i=1;i<arrel->n_fills;i++){
            if(arrel->fills[i]->valor < minim){
                minim=arrel->fills[i]->valor;
            }
        }
        arrel->valor=minim;
    }
}


void minimaxRecursiu(Node *arrel, int nivell){
    nivell++;
    if(arrel->n_fills>0){
        for (int i=0;i<arrel->n_fills;i++){
            minimaxRecursiu(arrel->fills[i],nivell);
            minimaxProfunditat(arrel,nivell);
        }
    }
}


int minimaxColumna(Node *arrel){
    minimaxRecursiu(arrel,0);
    for(int i=0;i<arrel->n_fills;i++){
        if(arrel->valor==arrel->fills[i]->valor) return columnaReal(arrel->tauler, i);
    }
    return 0;
}


void tiradaPersona(int tauler[N][N], int jugador, int modeJoc){
    int posicio;
    while(TRUE){
        if(modeJoc==PvsP) printf("Torn del jugador %i. ", jugador);
        printf("A quina columna vols tirar? \n");
        scanf("%i", &posicio);
        posicio=posicio-1;
        if(columnaValida(tauler, posicio)==TRUE && 0<=posicio && posicio<N) {
            caureFitxa(tauler, jugador, posicio);
            break;
        }
        else printf("Columna no vàlida.\n");
    }
}


void tiradaOrdinador(int tauler[N][N], int jugador){
    Node *arrel=malloc(sizeof(Node));
    if(jugador==JUG2) canviaJugadors(arrel->tauler);
    copiaTauler(arrel->tauler,tauler);
    arrel->n_fills=quantsFills(arrel);
    arrel->fills=malloc(arrel->n_fills*sizeof(Node*));
    arrel->valor=0;
    
    creaArbre(arrel,0);
    caureFitxa(tauler, jugador, minimaxColumna(arrel));
    
    esborraArbre(arrel);
    free(arrel);
}


int partidaAcabada(int tauler[N][N], int jugador, int modeJoc){
    if(busca4enRatlla(tauler, jugador)==TRUE){
        imprimirTauler(tauler);
        if(modeJoc==PvsP)
            printf("Partida acabada. Enhorabona, ha guanyat el jugador %i! \n", jugador);
        else if(modeJoc==PvsO){
            if(jugador==JUG1) printf("Partida acabada. Ha guanyat l'ordinador :( \n");
            else printf("Partida acabada. Enhorabona, has guanyat! \n");
        }
        else
            printf("Partida acabada. Ha guanyat l'ordinador %i. \n", jugador);
        return TRUE;
    }
    return FALSE;
}


void personaVsPersona(void){
    int tauler[N][N];
    inicialitza(tauler);
    
    while (TRUE) {
        imprimirTauler(tauler);
        tiradaPersona(tauler,JUG1,PvsP);
        if(partidaAcabada(tauler, JUG1,PvsP)) break;
        
        imprimirTauler(tauler);
        tiradaPersona(tauler,JUG2,PvsP);
        if(partidaAcabada(tauler, JUG2,PvsP)) break;
        
        if(taulerPle(tauler)) break;
    }
}


void personaVsOrdinador(void){
    int tauler[N][N];
    inicialitza(tauler);
    
    while (TRUE) {
        imprimirTauler(tauler);
        tiradaPersona(tauler,JUG2,PvsO);
        if(partidaAcabada(tauler,JUG2,PvsO)) break;
        
        imprimirTauler(tauler);
        tiradaOrdinador(tauler,JUG1);
        if(partidaAcabada(tauler,JUG1,PvsO)) break;
        
        if(taulerPle(tauler)) break;
    }
}


void canviaJugadors(int tauler[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(tauler[i][j]==JUG1) tauler[i][j]=JUG2;
            else if(tauler[i][j]==JUG2) tauler[i][j]=JUG1;
            else NULL;
        }
    }
}


void ordinadorVsOrdinador(void){
    int tauler[N][N];
    inicialitza(tauler);
    imprimirTauler(tauler);
    caureFitxa(tauler, JUG1, rand()%(N+1));
    
    while (TRUE) {
        imprimirTauler(tauler);
        tiradaOrdinador(tauler, JUG2);
        if(partidaAcabada(tauler, JUG2, OvsO)) break;
        
        if(taulerPle(tauler)) break;
        
        imprimirTauler(tauler);
        tiradaOrdinador(tauler, JUG1);
        if(partidaAcabada(tauler, JUG1, OvsO)) break;
    }
}


int main(){
    srand((unsigned int) time(0));                 // llavor aleatoria
    
    int modeDeJoc;
    
    printf("Quin mode de joc prefereixes? \n");
    printf("  1. Persona contra persona.\n");
    printf("  2. Persona contra ordinador.\n");
    printf("  3. Ordinador contra ordinador.\n\n");
    printf("Introdueix 1, 2 o 3: ");
    
    scanf("%i", &modeDeJoc);
    
    switch (modeDeJoc){
        case 1 :
            personaVsPersona();
            break;
        case 2 :
            personaVsOrdinador();
            break;
        case 3 :
            ordinadorVsOrdinador();
            break;
        default :
            printf("Mode de joc no vàlid.\n");
       }
    
    return 0;
}
