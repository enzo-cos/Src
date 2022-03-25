/**
 * \file Image.cpp
 * Implante une structure de stockage et de manipulation d'image bitmap.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Image.h"
#include "ImageUtils.h"

/**
 * Initialise une image a une certaine resolution avec la couleur noire.
 *
 * @param tx la resolution horizontale de l'image.
 * @param ty la resolution verticale de l'image.
 * @param dst le pointeur sur l'image a initialiser.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(int tx,int ty,struct image *dst) {
  int size = tx*ty*3;
  dst->tx = tx;
  dst->ty = ty;
  dst->p =(int *) calloc(size,sizeof(int));
}

/**
 * Initialise une image a une certaine resolution sans effacement a la couleur noire.
 *
 * @param tx la resolution horizontale de l'image.
 * @param ty la resolution verticale de l'image.
 * @param dst le pointeur sur l'image a initialiser.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocImage(int tx,int ty,struct image *dst) {
  int size = tx*ty*3;
  dst->tx = tx;
  dst->ty = ty;
  dst->p =(int *) malloc(size*sizeof(int));
}

/**
 * Alloue une image a une certaine resolution avec initialisation ou non a la couleur noire.
 *
 * @param tx la resolution horizontale de l'image.
 * @param ty la resolution verticale de l'image.
 * @param dst le pointeur sur l'image a initialiser.
 * @param init booleen indiquant l'initialisation ou non.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(int tx,int ty,struct image *dst,int init) {
  int size = tx*ty*3;
  dst->tx = tx;
  dst->ty = ty;
  if ( init )
    dst->p =(int *) calloc(size,sizeof(int));
    else
    dst->p =(int *) malloc(size*sizeof(int));
}

/**
 * Initialise une image a une certaine resolution avec une certaine couleur.
 *
 * @param tx la resolution horizontale de l'image.
 * @param ty la resolution verticale de l'image.
 * @param dst le pointeur sur l'image a initialiser.
 * @param r la valeur de rouge de la couleur d'initialisation.
 * @param v la valeur de vert de la couleur d'initialisation.
 * @param b la valeur de bleu de la couleur d'initialisation.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(int tx,int ty,struct image *dst,int r,int v,int b) {
  int nb = tx*ty;
  int size = nb*3;
  dst->tx = tx;
  dst->ty = ty;
  dst->p =(int *) malloc(size*sizeof(int));
  int *dp = dst->p;
  for ( register int i = 0 ; i < nb ; i++ ) {
    *dp = r;
    dp++;
    *dp = v;
    dp++;
    *dp = b;
    dp++; }
}

/**
 * Initialise une image par recopie d'une autre image.
 *
 * @param src le pointeur sur l'image source.
 * @param dst le pointeur sur l'image destination a initialiser avec une copie de l'image source.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(struct image *src,struct image *dst) {
  copie(src,dst);
}

/**
 * Desalloue une image.
 *
 * @param dst le pointeur sur l'image a desallouer.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void desallocationImage(struct image *dst) {
  if ( dst->p )
    free(dst->p);
  imageNulle(dst);
}

/**
 * Initialise une image par recopie d'une autre image.
 *
 * @param tx La resolution en x de l'image source.
 * @param ty La resolution en y de l'image source.
 * @param p Le tableau des lignes de l'image source.
 * @param dst le pointeur sur l'image destination a initialiser avec une copie de l'image source.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(int tx,int ty,unsigned char *p,struct image *dst) {
  allocImage(tx,ty,dst);
  int *ti = dst->p;
  dst->bits = 8;
  dst->max = 255;
  dst->med = 127;
  dst->nbn = 256;
  for ( int y = 0 ; y < ty ; y++ ) {
    unsigned char *tc = &p[y*tx*3];
    for ( int x = 0 ; x < tx*3 ; x++ ) {
      *ti = *tc;
      ti++;
      tc++; } }
}

/**
 * Initialise une image par recopie d'une autre image.
 *
 * @param tx La resolution en x de l'image source.
 * @param ty La resolution en y de l'image source.
 * @param p Le tableau des lignes de l'image source.
 * @param dst le pointeur sur l'image destination a initialiser avec une copie de l'image source.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(int tx,int ty,unsigned char **p,struct image *dst) {
  allocImage(tx,ty,dst);
  int *ti = dst->p;
  for ( int y = 0 ; y < ty ; y++ ) {
    unsigned char *tc = p[ty-y-1];
    for ( int x = 0 ; x < tx*3 ; x++ ) {
      *ti = *tc;
      ti++;
      tc++; } }
}

/**
 * Initialise une image a une certaine resolution avec la couleur noire.
 *
 * @param tx la resolution horizontale de l'image.
 * @param ty la resolution verticale de l'image.
 * @param bits le nombre de bits de profondeur de chaque composante coloree.
 * @param dst le pointeur sur l'image a initialiser.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(int tx,int ty,int bits,struct image *dst) {
  int size = tx*ty*3;
  dst->tx = tx;
  dst->ty = ty;
  dst->p =(int *) calloc(size,sizeof(int));
  dst->bits = bits;
  dst->nbn = 1<<bits;
  dst->max = dst->nbn-1;
  dst->med = dst->max/2.0F;
}

/**
 * Initialise une image a une certaine resolution sans effacement a la couleur noire.
 *
 * @param tx la resolution horizontale de l'image.
 * @param ty la resolution verticale de l'image.
 * @param bits le nombre de bits de profondeur de chaque composante coloree.
 * @param dst le pointeur sur l'image a initialiser.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocImage(int tx,int ty,int bits,struct image *dst) {
  int size = tx*ty*3;
  dst->tx = tx;
  dst->ty = ty;
  dst->p =(int *) malloc(size*sizeof(int));
  dst->bits = bits;
  dst->nbn = 1<<bits;
  dst->max = dst->nbn-1;
  dst->med = dst->max/2.0F;
}

/**
 * Alloue une image a une certaine resolution avec initialisation ou non a la couleur noire.
 *
 * @param tx la resolution horizontale de l'image.
 * @param ty la resolution verticale de l'image.
 * @param bits le nombre de bits de profondeur de chaque composante coloree.
 * @param dst le pointeur sur l'image a initialiser.
 * @param init booleen indiquant l'initialisation ou non.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(int tx,int ty,int bits,struct image *dst,int init) {
  int size = tx*ty*3;
  dst->tx = tx;
  dst->ty = ty;
  if ( init )
    dst->p =(int *) calloc(size,sizeof(int));
    else
    dst->p =(int *) malloc(size*sizeof(int));
  dst->bits = bits;
  dst->nbn = 1<<bits;
  dst->max = dst->nbn-1;
  dst->med = dst->max/2.0F;
}

/**
 * Initialise une image a une certaine resolution avec une certaine couleur.
 *
 * @param tx la resolution horizontale de l'image.
 * @param ty la resolution verticale de l'image.
 * @param bits le nombre de bits de profondeur de chaque composante coloree.
 * @param dst le pointeur sur l'image a initialiser.
 * @param r la valeur de rouge de la couleur d'initialisation.
 * @param v la valeur de vert de la couleur d'initialisation.
 * @param b la valeur de bleu de la couleur d'initialisation.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(int tx,int ty,int bits,struct image *dst,int r,int v,int b) {
  int nb = tx*ty;
  int size = nb*3;
  dst->tx = tx;
  dst->ty = ty;
  dst->p =(int *) malloc(size*sizeof(int));
  int *dp = dst->p;
  for ( register int i = 0 ; i < nb ; i++ ) {
    *dp = r;
    dp++;
    *dp = v;
    dp++;
    *dp = b;
    dp++; }
  dst->bits = bits;
  dst->nbn = 1<<bits;
  dst->max = dst->nbn-1;
  dst->med = dst->max/2.0F;
}
