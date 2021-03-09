/****  LIBRERIE  *****************************/
#include <graphics.h>
#include <time.h>
#include "prototipi.h"
/****  PROGRAMMA PRINCIPALE  *****************/
main()
{
  srand(time(NULL));
  initwindow(WINX,WINY);
  setbkcolor(WHITE);
  cleardevice();
  array code;
  Tprocesso processo;
  TnodoPtr processo_precedente=NULL;
  TlistaPtr processo_corrente;
  int i, x, y, colore;

  finestraAccesione();
  delay(3000);
  cleardevice();
  rotellaCaricamento(WINX/2, WINY/2);
  cleardevice();

  for(i=0; i<MAX_PRIORITA+1; i++)
    inizializzaLista(code[i], i);
  finestra(code);

  while(true)
  {
    for(i=0; i<QUANTO_DI_TEMPO/10; i++)
    {
      delay(10);
      if(ismouseclick(WM_LBUTTONDOWN))
      {
        getmouseclick(WM_LBUTTONDOWN, x, y);
        colore = coloreBottonePremuto(x, y);
        if(colore == LIGHTGREEN || colore == GREEN)
        {
          processo = generaProcessoCasuale();
          assegnaProcessoALista(code, processo);
          clearmouseclick(WM_LBUTTONDOWN);
        }
        else if(colore == LIGHTRED || colore == RED)
        {
          cleardevice();
          stampaTesto("I processi sono finiti vai in pace nel nome del signore. AMEN", 10, WINY/2-20, 4);
          getch();
          exit(0);
        }
      }
    }
    processo_corrente = scegliCoda(code);
    if(processo_corrente)
    {
      if(processo_corrente->testa != processo_precedente)
        processoInEntrata(*processo_corrente);
      processo_corrente->testa->processo.tempoRimanente--;
      stampaCpu(processo_corrente->testa);
      if(!processo_corrente->testa->processo.tempoRimanente)
      {
        eliminaTesta(code[processo_corrente->priorita]);
        processo_corrente->numElementi--;
        aggiornaDatiCoda(*processo_corrente);
      }
      processo_precedente=processo_corrente->testa;
    }
    else
    {
      stampaCpu(NULL);
      processo_precedente=NULL;
    }
  }

  closegraph();
}
