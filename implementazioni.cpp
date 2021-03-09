/****  LIBRERIE  *****************************/
#include <graphics.h>
#include <string.h>
#include <math.h>
#include "prototipi.h"
/****  IMPLEMENTAZIONE FUNZIONI  *************/
void finestraAccesione(void)
{
  stampaTesto("Process Simulator", 160, WINY/2-50, 8);
}
//---------------------------------------------
void rotellaCaricamento(int x_centro, int y_centro)
{
  double t, passo = (2*M_PI)/8, i=0;
  int x, y, cont, time = 0, colori[N_COLORI] = {BLACK, DARKGRAY, LIGHTGRAY, WHITE};
  stampaTesto("Loading...", x_centro-90, y_centro+200, 4);
  while(time < N_CARIMENTI)
  {
    for(t = 0, cont = 0; t<2*M_PI; t += passo, cont++)
    {
      x = x_centro+cos(t-i)*100;
      y = y_centro-sin(t-i)*100;
      setcolor(colori[cont/2]);
      circle(x, y, 15);
      setfillstyle(SOLID_FILL, colori[cont/2]);
      floodfill(x, y, colori[cont/2]);
    }
    delay(50);
    i+=passo;
    time++;
  }
}
//---------------------------------------------
void finestra(Tlista code[])
{
  int i, y;
  for(i=0; i<=MAX_PRIORITA; i++)
    stampaCoda(code[i], X_CODE, ALTEZZA_CODA);
  stampaCpu(NULL);
  stampaPulsanti();
}
//---------------------------------------------
void calcolaAltezza(int indice, int altezza, int spazio, int &y)
{
  y = spazio+indice*(altezza+spazio);
}
//---------------------------------------------
void stampaCoda(Tlista coda, int x, int altezza)
{
  int y;
  Tstringa priorita, num_processi;
  calcolaAltezza(coda.priorita, ALTEZZA_CODA, DISTANZA_CODE, y);
  setlinestyle(SOLID_LINE, 0, 5);
  setcolor(BLACK);
  rectangle(x, y, x+DIM_CODA, y+altezza);
  sprintf(priorita, "Coda Priorita: %d", coda.priorita);
  stampaTesto(priorita, x+20, y+20, 2);
  sprintf(num_processi, "Numeri dei processi contenuti: %d", coda.numElementi);
  stampaTesto(num_processi, x+20, y+60, 2);
}
//---------------------------------------------
void stampaTesto(Tstringa testo, int x, int y, int font_size)
{
  setcolor(BLACK);
  settextstyle(EUROPEAN_FONT, 0, font_size);
  outtextxy(x, y, testo);
}
//---------------------------------------------
void inizializzaLista(Tlista &lista, int priorita)
{
  lista.testa = NULL;
  lista.coda = NULL;
  lista.priorita = priorita;
  lista.numElementi = 0;
}
//---------------------------------------------
Tprocesso generaProcessoCasuale(void)
{
  Tprocesso processo;
  strcpy(processo.nomeProcesso, "stringa test");
  processo.tempoTotale = rand()%(MAX_TEMPO-1)+1;
  processo.tempoRimanente = processo.tempoTotale;
  return processo;
}
//---------------------------------------------
void assegnaProcessoALista(Tlista code[], Tprocesso processo)
{
  int priorita = rand()%(MAX_PRIORITA+1);
  inserisciInCoda(&code[priorita], processo);
  code[priorita].numElementi++;
  stampaCoda(code[priorita], X_CODE, ALTEZZA_CODA);
}
//---------------------------------------------
void inserisciInCoda(Tlista *lista, Tprocesso processo)
{
  if(!lista->testa)											//Se la lista e' vuota:
  {
    lista->testa = creaNodo(processo, NULL);
    lista->coda = lista->testa;
  }
  else
  {
    lista->coda->next = creaNodo(processo, NULL);
    lista->coda = lista->coda->next;
  }
}
//---------------------------------------------
TnodoPtr creaNodo(Tprocesso processo, TnodoPtr next)
{
  TnodoPtr temp;
  temp = (TnodoPtr) malloc(sizeof(Tnodo));
  temp->processo = processo;
  temp->next = next;
  return temp;
}
//---------------------------------------------
void eliminaTesta(Tlista &lista)
{
  TnodoPtr temp;
  temp = lista.testa;
  lista.testa = lista.testa->next;
  free(temp);
}
//---------------------------------------------
void aggiornaDatiCoda(Tlista coda)
{
  stampaCoda(coda, X_CODE, ALTEZZA_CODA);
}
//---------------------------------------------
void stampaCpu(TnodoPtr nodoPtr)
{
  Tstringa quanti_tempo;
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, WHITE);
  bar(X_CPU, WINY/2-DIM_CPU/2, X_CPU+DIM_CPU, WINY/2+DIM_CPU/2);
  rectangle(X_CPU, WINY/2-DIM_CPU/2, X_CPU+DIM_CPU, WINY/2+DIM_CPU/2);
  if(nodoPtr)
  {
    sprintf(quanti_tempo, "Quanti di tempo: %d", nodoPtr->processo.tempoRimanente);
    stampaTesto(nodoPtr->processo.nomeProcesso, X_CPU+20, WINY/2-80, 3);
    stampaTesto(quanti_tempo, X_CPU+20, WINY/2-30, 3);
    stampaBarraCarimento(nodoPtr->processo);
  }
  else
  {
    setcolor(BLACK);
    stampaTesto("Nessun Processo", X_CPU+30, WINY/2-35, 3);
    stampaTesto("In Esecuzione", X_CPU+50, WINY/2+5, 3);
  }
}
//---------------------------------------------
void stampaBarraCarimento(Tprocesso processo)
{
  int offset = (DIM_CPU-40)/processo.tempoTotale;
  setcolor(BLACK);
  rectangle(X_CPU+20, WINY/2+40, X_CPU+DIM_CPU-20, WINY/2+ALTEZZA_PROCESSO+40);
  if(processo.tempoRimanente)
    line(X_CPU+20+offset*(processo.tempoTotale-processo.tempoRimanente), WINY/2+40, X_CPU+20+offset*(processo.tempoTotale-processo.tempoRimanente), WINY/2+ALTEZZA_PROCESSO+40);
  setfillstyle(SOLID_FILL, YELLOW);
  floodfill(X_CPU+26, WINY/2+70, BLACK);
}
//---------------------------------------------
void stampaPulsanti()
{
  disegnaPulsante(X_CPU+50, 650, LIGHTGREEN);
  stampaTesto("Aggiungi", X_CPU-5, 715, 2);
  stampaTesto("Processo", X_CPU-5, 740, 2);
  disegnaPulsante(X_CPU+250, 650, LIGHTRED);
  stampaTesto("Termina", X_CPU+200, 715, 2);
  stampaTesto("Processi", X_CPU+200, 740, 2);
}
//---------------------------------------------
void disegnaPulsante(int x, int y, int colore)
{
  setcolor(colore-8);
  circle(x, y, 50);
  setfillstyle(SOLID_FILL, colore);
  floodfill(x, y, colore-8);
}
//---------------------------------------------
int coloreBottonePremuto(int x, int y)
{
  return getpixel(x, y);
}
//---------------------------------------------
void processoInEntrata(Tlista coda)
{
  int x, y1, y2;
  calcolaAltezza(coda.priorita, ALTEZZA_CODA, DISTANZA_CODE, y1);
  y1+=(ALTEZZA_CODA-ALTEZZA_PROCESSO)/2;
  y2=(WINY/2-25-y1)/5;
  for(x=DIM_CODA+50; x<X_CPU-50; x+=50, y1+=y2)
  {
    setcolor(BLACK);
    rectangle(x, y1, x+50, y1+50);
    delay(500);
    setcolor(WHITE);
    rectangle(x, y1, x+50, y1+50);
  }
}
//---------------------------------------------
TlistaPtr scegliCoda(Tlista code[])	//return il processo da stampare.
{
  int i = 0;
  while(i < MAX_PRIORITA+1)
  {
    if(code[i].testa)	return &code[i];
    i++;
  }
  return NULL;
}
//---------------------------------------------
