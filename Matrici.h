#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

/*
Ogni funzione che ha come parametro l'intero ORDINE si
riferisce all' ORDINE della Matrice quadrata passata.
Ogni funzione che ha come parametro float Mat[][ORDINE]
si riferisce al riferimento della Matrice sulla quale 
vogliamo fare dei calcoli. 
*/

void visualizzaMatrice(int ORDINE,float Mat[][ORDINE]);

/*
La funzione visualizzaMatrice() viene utilizzata per printare a 
schermo la Matrice float passata di ordine ORDINE.
*/

void trasponiMatQuadrata(int ORDINE,float Mat[][ORDINE]);

/*
La funzione trasponiMatQuadrata() viene utilizzata per trasformare 
la Matrice float passata di ordine ORDINE nella sua trasposta.
*/

static float scambiaRighe(int riga1,int riga2,int ORDINE,float Mat[][ORDINE]);

/*

La funzione scambiaRighe viene utilizzata dalla funzione 
riduzioneGaussJordan() e viene utilizzata per scambiare 
la riga riga1 con la riga riga2 nella Matrice float 
passata di ordine ORDINE.
Inoltre viene ritornato un valore float -1 nel caso 
le due righe passata non coincidono.
Questo valore servirà per il calcolo del determinante
della Matrice iniziale.
*/

static void moltiplicaRigaReale(float Reale,int riga,int ORDINE,float Mat[][ORDINE]);

/*
La funzione moltiplicaRigaReale viene utilizzata dalla
funzione riduciRiga() e viene utilizzata per
moltiplicare la riga riga per uno scalare Reale nella 
Matrice float passata di ordine ORDINE.
*/

static void sostituzioneSomma(int riga1,int riga2,int op,int ORDINE,float Mat[][ORDINE]);

/*
La funzione sostituzioneSomma() viene utilizzata dalla
funzione riduciRiga() e viene utilizzata per
sostituire la riga1 con la differenza/somma della riga riga1
con la riga riga2 nella Matrice float passata di ordine ORDINE.
L'intero op passato viene utilizzato per specificare nel caso
sia 1 la somma e nel caso sia un altro valore la differenza.
*/

static int cercaRigaPrimoNonNullo(int rigaPartenza,int colonna,int ORDINE,float Mat[][ORDINE]);

/*
La funzione cercaRigaPrimoNonNullo() viene utilizzata 
dalla funzione riduzioneGaussJordan() e viene utilizzata
per ritornare un intero che vale quanto l'indice 
della riga del primo float non nullo trovato a partire
dalla riga rigaPartenza nella colonna colonna nella 
Matrice float passata di ordine ORDINE.
*/

static float riduciRiga(int riga1,int riga2,int colonna,int ORDINE,float Mat[][ORDINE]);

/*
La funzione riduciRiga() viene utilizzata dalla
funzione riduzioneGaussJordan() e viene utilizzata
per portare il float della riga riga2 nella colonna
colonna a 0 con l'ausilio di alcune trasformazioni 
fatte con la riga riga1 nella colonna colonna nella
Matrice float passata di ordine ORDINE.
Inoltre ritorna un valore float utile per trovare
il determinante della Matrice iniziale.
*/

float riduzioneGaussJordan(int ORDINE,float Mat[][ORDINE]);

/*
La funzione riduzioneGaussJordan() viene utilizzata
per ridurre a Scala una qualsiasi Matrice float quadrata
passata di ordine ORDINE.
*/

float calcolaDetScala(int ORDINE,float Mat[][ORDINE]);

/*
La funzione calcolaDetScala() viene utilizzata per
calcolare il determinante di una qualsiasi Matrice
float quadrata a Scala
*/

int randomMat(int max,int volte,int ORDINE);

/*
La funzione randomMat() viene utilizzata per 
creare un/scrivere su un file nella quale 
verranno generate n volte matrici float quadrate 
random di ordine ORDINE con i valori compresi 
tra 0 e max.
La funzione ritorna -1 se ci sono stati degli errori.
*/ 

int caricaMat(int ORDINE,float Mat[][ORDINE]);

/*
La funzione caricaMat() viene utilizzara per 
caricare nella Matrice float passata di ordine 
ORDINE la prima Matrice trovata nel file matrice.txt.
*/

int scriviMat(int ORDINE,float Mat[][ORDINE]);

/*
La funzione scriviMat() viene utilizzata per
scrivere nel file matrice.txt la Matrice float 
passata di ordine ORDINE.
*/

float calcolaDet(int ORDINE,float Mat[][ORDINE]);

/*
La funzione calcolaDet calcola il determinante di 
una qualsiasi Matrice float quadrata di ordine ORDINE
passata.
*/
