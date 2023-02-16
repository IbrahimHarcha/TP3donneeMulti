// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nL, nC, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nL, &nC);
   nTaille = nL * nC;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nL * nC);
   allocation_tableau(ImgOut, OCTET, nTaille3);
    
   int nR,nG,nB,nR2;

   for (int i=nC*3+3; i < nTaille3-nC*3-3; i++){
        ImgOut[i]=(ImgIn[i]+ImgIn[i-nC*3]+ImgIn[i+nC*3]+ImgIn[i+3]+ImgIn[i-3])/5;
  }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nL, nC);
   free(ImgIn);
   
   return 1;
}