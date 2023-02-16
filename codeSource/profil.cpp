#include <stdio.h>
#include "image_ppm.h"

int main(int argc,char **argv){
    char nomImgLue[256];
    char lOuC[256];
    int index,nL,nC;
    
    if(argc!=4){
        printf("Usage: ImageIn.pgm l|c nbIndice\n"); 
        exit (1) ;
    }

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",lOuC);
    sscanf(argv[3],"%d",&index);

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nL,&nC);
    int nTaille=nL*nC;

    OCTET *ImgIn;
    int sizeRes;

    allocation_tableau(ImgIn,OCTET,nTaille);
    lire_image_pgm(nomImgLue,ImgIn,nTaille);

    if(strcmp(lOuC,"l")==0){
        sizeRes=nC;
        for(int i=0;i<nC;i++){
            printf("%d %d\n",i,ImgIn[index*nL+i]);
        }
    }else if(strcmp(lOuC,"c")==0){
        sizeRes=nL;
        for(int i=0;i<nL;i++){
            printf("%d %d\n",i,ImgIn[index*nC+i]);
        }
    }else{
        free(ImgIn);
        printf("Probleme au niveau du parametrage\n");
        return 1;
    }

    /*printf("point de repere\n");*/

    free(ImgIn);

    return 1;
}