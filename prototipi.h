#ifndef PROTOTIPI_H
#define PROTOTIPI_H

#ifdef __cplusplus
extern "C" {
#endif
/****  LIBRERIE  *****************************/
#include <stdio.h>
/****  COSTANTI  *****************************/
#define WINX 1200
#define WINY 800
#define DIM 100
#define N_COLORI 4
#define N_CARIMENTI 50
#define MAX_TEMPO 10
#define MAX_PRIORITA 4
#define QUANTO_DI_TEMPO 1000
#define DIM_CODA 500
#define ALTEZZA_CODA 100
#define ALTEZZA_PROCESSO 50
#define DISTANZA_CODE 50
#define DIM_CPU 300
#define X_CODE 30
#define X_CPU 800
/****  VARIABILI GLOBALI  ********************/
/****  TYPE  *********************************/
typedef char Tstringa[DIM];
typedef struct
{
  Tstringa nomeProcesso;
  int tempoTotale;
  int tempoRimanente;
} Tprocesso;
typedef struct Tnodo
{
  Tprocesso processo;
  struct Tnodo *next;
} Tnodo;
typedef Tnodo* TnodoPtr;
typedef struct
{
  TnodoPtr testa;
  TnodoPtr coda;
  int numElementi;
  char priorita;
} Tlista;
typedef Tlista* TlistaPtr;
typedef Tlista array[MAX_PRIORITA+1];
/****  PROTOTIPI FUNZIONI ********************/
void finestraAccesione(void);
void finestra(Tlista code[]);
void rotellaCaricamento(int x_centro, int y_centro);
void calcolaAltezza(int indice, int altezza, int spazio, int &y);
void stampaCoda(Tlista coda, int x, int altezza);
void stampaTesto(Tstringa testo, int x, int y, int font_size);

void inizializzaLista(Tlista &lista, int priorita);
Tprocesso generaProcessoCasuale(void);
TnodoPtr creaNodo(Tprocesso processo, TnodoPtr next);
void assegnaProcessoALista(Tlista code[], Tprocesso processo);
void inserisciInCoda(Tlista *lista, Tprocesso processo);
void eliminaTesta(Tlista &lista);
void aggiornaDatiCoda(Tlista coda);
void stampaCpu(TnodoPtr processoPtr);
void stampaBarraCarimento(Tprocesso processo);
void stampaPulsanti();
void disegnaPulsante(int x, int y, int colore);
int coloreBottonePremuto(int x, int y);
void processoInEntrata(Tlista coda);
TlistaPtr scegliCoda(Tlista code[]);	//return il processo da stampare.

#ifdef __cplusplus
}
#endif

#endif /* PROTOTIPI_H */
