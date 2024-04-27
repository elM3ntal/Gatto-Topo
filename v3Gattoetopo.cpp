#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 7 //dimensione matrice quadrata N x N
void gioco (int, int, int);
int main(void)
{
	int ncani, scelta, x ,y;
	char sceltapos, risp;
	//introduzione
	do
	{
		printf("Ciao! Ti do il benvenuto nel gioco \"Il Gatto e il Topo\"\nSarai nei panni del gatto e il tuo obiettivo sara' quello di raggiungere il topo.\n\n");
		printf("I cani ostacoleranno il tuo percorso, ricordati che i gatti hanno 7 vite :)\nOgni volta che il gatto incontrera' un cane, ne perdera' una\n\n");
		printf("Tutto chiaro? Quando sei pronto digita il numero corrispondente al livello che desideri giocare\n");
		printf("1)Super facile (5 cani)\n2)Facile (10 cani)\n3)Medio (18 cani)\n4)Difficile (23 cani)\n5)Estremo (30 cani)\n6)Personalizzato\n0)Esci\n");
		printf("Fai la tua scelta: ");
		scanf("%d",&scelta);
		while (scelta>6 || scelta<0)
		{
			printf("Livello non esistente\n");
			printf("Fai la tua scelta: ");
			scanf("%d",&scelta);
		}
		//decisione numero di cani
		switch (scelta)
		{
			case (0):
				return 0;
			case (1):
				ncani=5;
				break;
			case (2):
				ncani=10;
				break;
			case (3):
				ncani=18;
				break;
			case (4):
				ncani=23;
				break;
			case (5):
				ncani=30;
				break;
			case (6):
				printf("\nInserisci il numero di cani (max 30, altrimenti diventerebbe quasi impossibile): ");
				scanf("%d",&ncani);
				while (ncani>30)
				{
					printf("Errore, numero massimo superato\n");
					printf("Inserisci il numero di cani (max 30): ");
					scanf("%d",&ncani);
				}
		}
		printf("Vuoi che la posizione del gatto sia casuale? (Non consigliato, di default e' all'estremo opposto del topo) (s/N): ");
		fflush(stdin);
		scanf("%c",&sceltapos);
		while (sceltapos!='s' && sceltapos!='n' && sceltapos!='S' && sceltapos!='N' && sceltapos!=10)
		{
			printf("Scelta non valida\n");
			printf("Vuoi che la posizione del gatto sia casuale? (Non consigliato, di default e' all'estremo opposto del topo) (s/N): ");
			fflush(stdin);
			scanf("%c",&sceltapos);
		}
		if (sceltapos=='s' || sceltapos=='S')
		{
			srand(time(NULL));
			do
			{
				x=rand()%N;
				y=rand()%N;
			} 
			while (x==N-1 && y==N-1);
		}
		else
		{
			x=0;
			y=0;
		}
		gioco(ncani, x, y); //chiamata alla funzione gioco
		printf("\nVuoi fare un'altra partita? (S/n): ");
		fflush(stdin);
		scanf("%c",&risp);
		while(risp!='s' && risp!='n' && risp!='S' && risp!='N' && risp!=10)
		{
			printf("Scelta non valida\n");
			printf("\nVuoi fare un'altra partita? (S/n): ");
			fflush(stdin);
			scanf("%c",&risp);
		}
		system("CLS");
	}
	while (risp=='s' || risp=='S' || risp==10);

	return 0;
}

void gioco (int ncani, int x, int y)
{
	srand(time(NULL));
	int nvite=7, direzione, riga, col, i=0;
	bool mangiato=false;
	char m[N][N];
	system("CLS"); //pulizia del cmd
	//creazione matrice
	for (riga=0; riga<N; riga++)
		for (col=0; col<N; col++)
			m[riga][col]='-';
	m[x][y]='G'; //posizionamento Gatto
	m[N-1][N-1]='T'; //poszionamento Topo
	while (i<ncani) //Generazione Cani
	{
		riga=rand()%N;
		col=rand()%N;
		if (m[riga][col]=='-')
		{
			m[riga][col]='C';
			i++;
		}
	}
	for (riga=0; riga<N; riga++)//stampa della matrice senza C
	{
		for (col=0; col<N; col++)
			if (m[riga][col]=='C')
				printf("%5c",'-');
			else
				printf("%5c",m[riga][col]);
		printf("\n\n");
	}
	//corpo del gioco
	while (nvite>0 && mangiato==false)
	{
		printf("\nDigita 1 per sinistra, 2 per destra, 3 per alto, 4 per basso: ");
		scanf("%d",&direzione);
		while (direzione>4 || direzione<1 || (direzione==1 && y==0) || (direzione==2 && y==N-1) || (direzione==3 && x==0) || (direzione==4 && x==N-1))
		{
			printf("Operazione impossibile\n");
			printf("\nDigita 1 per sinistra, 2 per destra, 3 per alto, 4 per basso: ");
			scanf("%d",&direzione);
		}
		m[x][y]='-'; //posizionamento vuoto per sostituire il gatto
		if (direzione==1)
			y--;
		else if (direzione==2)
			y++;
		else if (direzione==3)
			x--;
		else
			x++;
		system("CLS"); //pulizia cmd
		if (m[x][y]=='T') //controllo se il gatto ha mangiato il topo
			mangiato=true;
		else if (m[x][y]=='C') //controllo se il gatto ha incontrato un cane
		{
			nvite--;
			printf("Il gatto ha incontrato una cane e ha perso una vita :(\n");
		}
		m[x][y]='G'; //posizionamento Gatto
		printf("Il gatto va alla posizione %d,%d\n",x,y); //stampa della posizione attuale
		printf("Numero di vite: %d\n",nvite); //stampa del numero di vite rimaste
		for (riga=0; riga<N; riga++) //stampa della matrice senza C
		{
			for (col=0; col<N; col++)
				if (m[riga][col]=='C')
					printf("%5c",'-');
				else
					printf("%5c",m[riga][col]);
			printf("\n\n");
		}
	}
	//fine del ciclo
	if (mangiato)
		printf("Congratulazioni!! Il gatto ha mangiato il topo ;)\n");
	else
		printf("Purtroppo il gatto non ce l'ha fatta :(\n");
}