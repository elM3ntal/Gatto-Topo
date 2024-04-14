#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 7
void gioco (int);
int main(void)
{
	int ncani, scelta;
	//introduzione
	printf("Ciao! Ti do il benvenuto nel gioco \"Il Gatto e il Topo\"\nSarai nei panni del gatto e il tuo obiettivo sara' quello di raggiungere il topo.\n\n");
	printf("I cani ostacoleranno il tuo percorso, ricordati che i gatti hanno 7 vite :)\nOgni volta che il gatto incontrera' un cane, ne perdera' una\n\n");
	printf("Tutto chiaro? Quando sei pronto digita il numero corrispondente al livello che desideri giocare\n");
	printf("0)Super facile (5 cani)\n1)Facile (10 cani)\n2)Medio (18 cani)\n3)Difficile (23 cani)\n4)Estremo (30 cani)\n5)Personalizzato\n");
	printf("Fai la tua scelta: ");
	scanf("%d",&scelta);
	while (scelta>5 || scelta<0)
	{
		printf("Livello non esistente\n");
		printf("Fai la tua scelta: ");
		scanf("%d",&scelta);
	}
	//decisione numero di cani
	switch (scelta)
	{
		case (0):
			ncani=5;
			gioco (ncani);
			break;
		case (1):
			ncani=10;
			gioco (ncani);
			break;
		case (2):
			ncani=18;
			gioco (ncani);
			break;
		case (3):
			ncani=23;
			gioco (ncani);
			break;
		case (4):
			ncani=35;
			gioco (ncani);
			break;
		case (5):
			printf("\nInserisci il numero di cani (max 30, altrimenti diventerebbe quasi impossibile): ");
			scanf("%d",&ncani);
			while (ncani>30)
			{
				printf("Errore, numero massimo superato\n");
				printf("Inserisci il numero di cani (max 30): ");
				scanf("%d",&ncani);
			}
			gioco (ncani);
	}

	system("pause");
	return 0;
}

void gioco (int ncani)
{
	srand(time(NULL));
	int nvite=7, direzione, x=0, y=0, riga, col, i=0;
	bool mangiato=false;
	char m[N][N];
	system("CLS"); //pulizia del cmd
	//creazione matrice
	for (riga=0; riga<N; riga++)
		for (col=0; col<N; col++)
			m[riga][col]='-';
	m[0][0]='G'; //posizionamento Gatto
	m[N-1][N-1]='T'; //poszionamento Topo
	while (i<ncani) //Generazione Cani
	{
		riga=rand()%7;
		col=rand()%7;
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
				printf("%4c",'-');
			else
				printf("%4c",m[riga][col]);
		printf("\n");
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
		if (m[x][y]=='T') //controllo se il gatto ha mangiato il topo
			mangiato=true;
		else if (m[x][y]=='C') //controllo se il gatto ha incontrato un cane
		{
			nvite--;
			printf("Il gatto ha incontrato una cane e ha perso una vita\n");
		}
		m[x][y]='G'; //posizionamento Gatto
		system("CLS"); //pulizia cmd
		printf("Il gatto va alla posizione %d,%d\n",x,y); //stampa della posizione attuale
		printf("Numero di vite: %d\n",nvite); //stampa del numero di vite rimaste
		for (riga=0; riga<N; riga++) //stampa della matrice senza C
		{
			for (col=0; col<N; col++)
				if (m[riga][col]=='C')
					printf("%4c",'-');
				else
					printf("%4c",m[riga][col]);
			printf("\n");
		}
	}
	//fine del ciclo
	if (mangiato)
		printf("Congratulazioni!! Il gatto ha mangiato il topo ;)\n");
	else
		printf("Purtroppo il gatto non ce l'ha fatta :(\n");
}