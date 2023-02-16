#include <stdio.h>
#include "image_ppm.h"

// Pour afficher sur GnuPlot faire : plot "histoLena.dat" using 1:2 with lines, "histoLena.dat" using 1:3 with lines, "histoLena.dat" using 1:4 with lines

int main(int argc,char **argv){
    char nomImgLue[256],nomFichier[256];
    int nL,nC;

    if(argc!=3){
        printf("Usage: ImageIn.pgm FileName.dat\n"); 
        exit (1) ;
    }

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomFichier);

    lire_nb_lignes_colonnes_image_ppm(nomImgLue,&nL,&nC);
    int nTaille=nL*nC;

    int nTaille3=3*nTaille;

    OCTET *ImgIn,*ImgInR,*ImgInG,*ImgInB;
    int *resR,*resG,*resB;

    allocation_tableau(ImgIn,OCTET,nTaille3);
    lire_image_ppm(nomImgLue,ImgIn,nTaille);
    allocation_tableau(ImgInR,OCTET,nTaille);
    allocation_tableau(ImgInG,OCTET,nTaille);
    allocation_tableau(ImgInB,OCTET,nTaille);
    allocation_tableau(resR,int,256);
    allocation_tableau(resG,int,256);
    allocation_tableau(resB,int,256);

    for(int i=0;i<256;i++){
        resR[i]=0;
        resG[i]=0;
        resB[i]=0;
    } 

    int nR,nG,nB;

    for(int i=0;i<nTaille;i++){
        ImgInR[i]=ImgIn[3*i];
        ImgInG[i]=ImgIn[3*i+1];
        ImgInB[i]=ImgIn[3*i+2];
    }

    for(int i=0;i<nTaille;i++){
        resR[ImgInR[i]]+=1;
        resG[ImgInG[i]]+=1;
        resB[ImgInB[i]]+=1;
    }

    FILE *f_histo;

    if((f_histo= fopen(nomFichier, "wb")) == NULL){
        printf("\nPas d'acces en ecriture sur l'image %s \n", nomImgLue);
        exit(EXIT_FAILURE);
    }
    else{
        int index=0;
        //fprintf(f_histo,"indice     occurrence\r"); /*ecriture entete*/
        for(int i=0;i<256;i++){
            fprintf(f_histo,"%d %d %d %d\r",index,resR[i],resG[i],resB[i]); // Mettre un seul espace entre chaque nombre, sinon gnuplot ne marche pas tres bien...
            index++;
        }

        fclose(f_histo);
    }

    free(resR); free(ImgInR);
    free(resG); free(ImgInG);
    free(resB); free(ImgInB);
    free(ImgIn);

    return 1;
}