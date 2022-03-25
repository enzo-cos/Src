/**
 * \file ChargePngFile.cpp
 * Implante des fonctions de chargement et de sauvegarde de fichiers au format png dans et depuis des structures image.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 11/11/07
 */

#include <stdlib.h>
#include <stdio.h>

#include "Image.h" 
#include "PngFile.h" 

/**
 * Charge un fichier png dans un tableau d'octets non signes alloue pour.
 *
 * @param filename La chaine de caracteres contenant le nom du fichier.
 * @param rx Le pointeur sur un int destine a retourner la resolution en x de l'image chargee.
 * @param ry Le pointeur sur un int destine a retourner la resolution en y de l'image chargee.
 * @return Un tableau d'unsigned char contenant l'image chargee, NULL si le chargement echoue.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
unsigned char *chargeImagePng(char *filename,int *rx,int *ry) {
  struct image img;      
  unsigned char red,green,blue;
  if ( chargeImagePng(filename,&img,&red,&green,&blue) ) {
    int size = img.tx*img.ty*3;
    *rx = img.tx;
    *ry = img.ty;
    unsigned char *image =(unsigned char *) malloc(size*sizeof(unsigned char));
    unsigned char *tc = image;
    for ( int y = 0 ; y < img.ty ; y++ ) {
      int *ti = &img.p[3*(img.ty-y-1)*img.tx];
      for ( int x = 0 ; x < img.tx*3 ; x++ ) {
        *tc =(unsigned char) *ti;
        ti++;
        tc++; } }
    desallocationImage(&img);
    return(image); }
    else {
    *rx = *ry = 0;
    return(NULL); }
}

/**
 * Sauve un fichier png a partir un tableau d'octets non signes.
 *
 * @param filename La chaine de caracteres contenant le nom du fichier.
 * @param rx La resolution en x de l'image sauvee.
 * @param ry La resolution en y de l'image sauvee.
 * @param image Le tableau d'unsigned char contenant les octets de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void sauveImagePng(char *filename,int rx,int ry,unsigned char **image) {
  struct image img;
  allocationImage(rx,ry,image,&img);
  sauveImagePng(filename,&img);
  desallocationImage(&img);
}
