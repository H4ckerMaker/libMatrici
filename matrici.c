#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

void visualizzaMatrice(int ORDINE,float Mat[][ORDINE]){
    for(int i=0;i<ORDINE;i++){
        for(int j=0;j<ORDINE;j++)
            printf("%lf ",*((*Mat)+i*ORDINE+j));
        printf("\n");
    }
} 

void trasponiMatQuadrata(int ORDINE,float Mat[][ORDINE]){
    float temp;
    for(int i=0;i<ORDINE;i++){
        for(int j=i;j<ORDINE;j++){
            temp = *((*Mat)+i*ORDINE+j);
            *((*Mat)+i*ORDINE+j) = *((*Mat)+j*ORDINE+i);
            *((*Mat)+j*ORDINE+i) = temp;
        }
    }
}

static float scambiaRighe(int riga1,int riga2,int ORDINE,float Mat[][ORDINE]){
    float temp;
    if(riga1 == riga2)
        return 1;
    else{
        for(int i=0;i<ORDINE;i++){
            temp = *((*Mat)+riga1*ORDINE+i);
            *((*Mat)+riga1*ORDINE+i) = *((*Mat)+riga2*ORDINE+i);
            *((*Mat)+riga2*ORDINE+i) = temp;
        }
        return -1;
    }
}

static void moltiplicaRigaReale(float Reale,int riga,int ORDINE,float Mat[][ORDINE]){
    for(int i=0;i<ORDINE;i++)
        *((*Mat)+riga*ORDINE+i) = Reale * *((*Mat)+riga*ORDINE+i);
}

static void sostituzioneSomma(int riga1,int riga2,int op,int ORDINE,float Mat[][ORDINE]){
    for(int i=0;i<ORDINE;i++){
        if(op == 1)
            *((*Mat)+riga1*ORDINE+i) = *((*Mat)+riga1*ORDINE+i) + *((*Mat)+riga2*ORDINE+i);
        else 
            *((*Mat)+riga1*ORDINE+i) = *((*Mat)+riga1*ORDINE+i) - *((*Mat)+riga2*ORDINE+i);
    }
}

static int cercaRigaPrimoNonNullo(int rigaPartenza,int colonna,int ORDINE,float Mat[][ORDINE]){ 
    int i;
    for(i=rigaPartenza;i<ORDINE&&*((*Mat)+i*ORDINE+colonna) == 0;i++);
    if(i == ORDINE)
        return -1;
    return i;
}

static float riduciRiga(int riga1,int riga2,int colonna,int ORDINE,float Mat[][ORDINE]){
    float num1 = *((*Mat)+riga1*ORDINE+colonna);
    float num2 = *((*Mat)+riga2*ORDINE+colonna);
    float moltiplicatore = num1/num2;
    if(!isinf(moltiplicatore) && !isnan(moltiplicatore)){
        moltiplicaRigaReale(moltiplicatore,riga2,ORDINE,Mat);
        sostituzioneSomma(riga2,riga1,0,ORDINE,Mat);
        return 1/moltiplicatore;
    }
    return 1;
}

float riduzioneGaussJordan(int ORDINE,float Mat[][ORDINE]){
    float det = 1;
    int rigaNoZero = -1;
    int rigaPartenzaCheck = 0;
    int colonna = 0;
    float a;
    for(int i=0;i<ORDINE-1;i++){
        rigaNoZero = cercaRigaPrimoNonNullo(rigaPartenzaCheck,colonna,ORDINE,Mat);
        if(rigaNoZero != -1)
            det = det * scambiaRighe(rigaNoZero,rigaPartenzaCheck,ORDINE,Mat);
        while (rigaNoZero != -1){
            rigaPartenzaCheck++;
            rigaNoZero = cercaRigaPrimoNonNullo(rigaPartenzaCheck,colonna,ORDINE,Mat);
            if(rigaNoZero != -1)
                det = det * riduciRiga(i,rigaNoZero,colonna,ORDINE,Mat);
        };
        colonna = i+1;
        rigaPartenzaCheck = i+1;
    }
    return det;
}

float calcolaDetScala(int ORDINE,float Mat[][ORDINE]){
    float det = 1;
    for(int i=0;i<ORDINE;i++){
        det *= *((*Mat)+i*ORDINE+i);
    }
    return det;
}

int randomMat(int max,int volte,int ORDINE){
    srand((unsigned int)time(NULL));
    FILE *fptr;
    if ((fptr = fopen("matrice.txt","w")) == NULL)
       return -1;
    for(int k=0;k<volte;k++){
        for(int i=0;i<ORDINE;i++){
            for(int j=0;j<ORDINE;j++){
                if(((int)rand()%max) > max/2)
                    fprintf(fptr,"%f ",((float)rand()/(float)(RAND_MAX)) * max * -1);
                else
                    fprintf(fptr,"%f ",((float)rand()/(float)(RAND_MAX)) * max);
            }
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
    return 0;
}

int caricaMat(int ORDINE,float Mat[][ORDINE]){
    FILE *fptr;
    if((fptr = fopen("matrice.txt","r")) == NULL)
        return -1;
    while(!feof(fptr))
        for(int j=0;j<ORDINE;j++)   
            for(int k=0;k<ORDINE;k++)
                fscanf(fptr,"%f",(*Mat)+j*ORDINE+k);
    fclose(fptr);
    return 0;
}

int scriviMat(int ORDINE,float Mat[][ORDINE]){
    FILE *fptrsol;
    if((fptrsol = fopen("matriceSol.txt","w")) == NULL)
        return -1;
    for(int l=0;l<ORDINE;l++)
            for(int n=0;n<ORDINE;n++)
                fprintf(fptrsol,"%f ",*((*Mat)+l*ORDINE+n));
    fprintf(fptrsol,"\n");
    fclose(fptrsol);
    return 0;
}

float calcolaDet(int ORDINE,float Mat[][ORDINE]){
    float det = 0;
    det = riduzioneGaussJordan(ORDINE,Mat);
    det = det * calcolaDetScala(ORDINE,Mat);
    return det;
} 


