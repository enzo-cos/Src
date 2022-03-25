#include <stdio.h>
#include <stdlib.h>

#include "PNG/ChargePngFile.h"

int main(void) {
  { char nomFichier[32] = "Test.png";
    int rx;
    int ry;
    printf("%s\n",nomFichier);
    unsigned char *img = chargeImagePng(nomFichier,&rx,&ry);
    if ( img ) {
      printf("Resolution en x : %8d\n",rx);
      printf("Resolution en y : %8d\n",ry);
      printf("Adresse         : %p, %d octets\n",img,3*rx*ry);
      free(img); }
      else {
      printf("Adresse         : %p\n",img); } }
  printf("\n");
  getchar();
  return 0;
}