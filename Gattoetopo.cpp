#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 7
/*Nel gioco � presente una matrice quadrata N x N, ove N � una costante che vale 7.
Nell'angolo in alto a sinistra � piazzato un gatto. Nell'angolo in basso a destra � piazzato un topo. 
Lo scopo del gioco � che il gatto arrivi a mangiarsi il topo.
Ad ogni passo il gatto pu� muoversi di una posizione in una delle 4 direzioni.
La direzione � inserita dall'utente (ad esempio: 1 sinistra, 2 destra, �).
Occorre anche controllare che la direzione inserita sia praticabile.
Nella matrice sono sparsi in modo casuale dei cani (non visibili).
Il numero dei cani � inserito dall'utente e rappresenta il livello di difficolt� del gioco.
Il massimo numero di cani nella mia versione �
 (N*N-2)/2 (perch�??)
Il gatto, come tutti i gatti, possiede 7 vite. Ogni volta che incontra un cane, ne perde una.
Riuscir� il nostro micio a mangiarsi il topo senza fare una brutta fine lungo la strada?*/
int main(void)
{
	int nvite=7, direzione, x=0, y=0, riga, col, ncani, i=0;
	bool mangiato=false;
	char m[N][N];
	srand(time(NULL));
	//creazione matrice
	for (riga=0; riga<N; riga++)
		for (col=0; col<N; col++)
			m[riga][col]='-';
	m[0][0]='G'; //posizionamento Gatto
	m[N-1][N-1]='T'; //poszionamento Topo
	printf("Inserisci il numero di cani (max 23): ");
	scanf("%d",&ncani);
	while (ncani>23)
	{
		printf("Errore, numero massimo superato\n");
		printf("Inserisci il numero di cani (max 23): ");
		scanf("%d",&ncani);
	}
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
		printf("Congratulazioni!! Il gatto ha mangiato il topo e gli sono rimaste %d vite\n",nvite);
	else
		printf("Purtroppo il gatto non ce l'ha fatta :(\n");

	system("pause");
	return 0;
}