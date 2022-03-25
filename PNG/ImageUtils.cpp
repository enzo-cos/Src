/**
 * \file ImageUtils.cpp
 * Implante des fonctions de manipulation d'image bitmap.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Image.h"
#include "Espace3UC.h"

/**
 * Affecte une image a non allouée.
 *
 * @param dst le pointeur sur l'image a affecter.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void imageNulle(struct image *dst) {
  dst->p = NULL;
  dst->tx = 0;
  dst->ty = 0;
}

/**
 * Realise le "Ou" d'une image par une autre image de meme resolution.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @param image le pointeur sur l'image composee.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void ou(struct image *src,struct image *image) {
  int l = src->tx*src->ty*3;
  for ( int i = 0 ; i < l ; i++ )
    src->p[i] |= image->p[i];
}

/**
 * Copie une autre image.
 *
 * @param src le pointeur sur l'image source.
 * @param dst le pointeur sur l'image a copier.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void copie(struct image *src,struct image *dst) {
  allocationImage(src->tx,src->ty,dst);
  memcpy(dst->p,src->p,sizeof(int)*dst->tx*dst->ty*3);
}

static float mediane(int *ef,int med) {
  int t = *ef;
  int c = 0;
  while ( t < med ) {
    c++;
    ef++;
    t += *ef; }
  int mt = t - *ef;
  return(c-1+(float) (med-mt)/ *ef);
}

/**
 * Calcule la composante de rouge mediane des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de rouge mediane des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float rougeMedian(struct image *src) {
  int ef[256];
  memset(ef,0x00,sizeof(int)<<8);
  int size = src->tx*src->ty;
  int *sp = src->p;
  for ( int i = 0 ; i < size ; i++ ) {
    ef[*sp]++;
    sp += 3; }
  float v = mediane(ef,size/2);
  return(v);
}

/**
 * Calcule la composante de vert mediane des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de vert mediane des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float vertMedian(struct image *src) {
  int ef[256];
  memset(ef,0x00,sizeof(int)<<8);
  int size = src->tx*src->ty;
  int *sp = src->p;
  sp++;
  for ( int i = 0 ; i < size ; i++ ) {
    ef[*sp]++;
    sp += 3; }
  float v = mediane(ef,size/2);
  return(v);
}

/**
 * Calcule la composante de bleu mediane des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de bleu mediane des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float bleuMedian(struct image *src) {
  int ef[256];
  memset(ef,0x00,sizeof(int)<<8);
  int size = src->tx*src->ty;
  int *sp = src->p;
  sp += 2;
  for ( int i = 0 ; i < size ; i++ ) {
    ef[*sp]++;
    sp += 3; }
  float v = mediane(ef,size/2);
  return(v);
}

/**
 * Calcule les composantes de la couleur medianes des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @param r l'adresse de la composante de rouge mediane des pixels de l'image.
 * @param v l'adresse de la composante de vert mediane des pixels de l'image.
 * @param b l'adresse de la composante de bleu mediane des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void couleurMediane(struct image *src,float *r,float *v,float *b) {
  int efr[256];
  int efv[256];
  int efb[256];
  memset(efr,0x00,sizeof(int)<<8);
  memset(efv,0x00,sizeof(int)<<8);
  memset(efb,0x00,sizeof(int)<<8);
  int size = src->tx*src->ty;
  int *sp = src->p;
  for ( register int i = 0 ; i < size ; i++ ) {
    efr[*sp]++;
    sp++;
    efv[*sp]++;
    sp++;
    efb[*sp]++;
    sp++; }
  size >>= 1;
  *r = mediane(efr,size);
  *v = mediane(efv,size);
  *b = mediane(efb,size);
}

/**
 * Calcule la composante de rouge moyenne des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de rouge moyenne des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float rougeMoyen(struct image *src) {
  long r1 = 0;
  long r2 = 0;
  int size = src->tx*src->ty;
  int *sp = src->p;
  for ( int i = 0 ; i < size ; i++ ) {
    r1 += (*sp>>6);
    r2 += ((*sp)%64);
    sp += 3; }
  float v = r1*64.0F+r2;
  return(v/size);
}

/**
 * Calcule la composante de vert moyenne des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de vert moyenne des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float vertMoyen(struct image *src) {
  long r1 = 0;
  long r2 = 0;
  int size = src->tx*src->ty;
  int *sp = src->p;
  sp++;
  for ( int i = 0 ; i < size ; i++ ) {
    r1 += (*sp>>6);
    r2 += ((*sp)%64);
    sp += 3; }
  float v = r1*64.0F+r2;
  return(v/size);
}

/**
 * Calcule la composante de bleu moyenne des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de bleu moyenne des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float bleuMoyen(struct image *src) {
  long r1 = 0;
  long r2 = 0;
  int size = src->tx*src->ty;
  int *sp = src->p;
  sp += 2;
  for ( int i = 0 ; i < size ; i++ ) {
    r1 += (*sp>>6);
    r2 += ((*sp)%64);
    sp += 3; }
  float v = r1*64.0F+r2;
  return(v/size);
}

/**
 * Calcule les composantes de la couleur moyenne des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @param r l'adresse de la composante de rouge moyenne des pixels de l'image.
 * @param v l'adresse de la composante de vert moyenne des pixels de l'image.
 * @param b l'adresse de la composante de bleu moyenne des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void couleurMoyenne(struct image *src,float *r,float *v,float *b) {
  long tr1 = 0;
  long tv1 = 0;
  long tb1 = 0;
  long tr2 = 0;
  long tv2 = 0;
  long tb2 = 0;
  int size = src->tx*src->ty;
  int *sp = src->p;
  for ( register int i = 0 ; i < size ; i++ ) {
    tr1 += (*sp>>6);
    tr2 += ((*sp)%64);
    sp++;
    tv1 += (*sp>>6);
    tv2 += ((*sp)%64);
    sp++;
    tb1 += (*sp>>6);
    tb2 += ((*sp)%64);
    sp++; }
  *r = (tr1*64.0F+tr2)/size;
  *v = (tv1*64.0F+tv2)/size;
  *b = (tb1*64.0F+tb2)/size;
}

/**
 * Calcule le nombre de pixels de couleur blanche de l'image.
 *
 * @param src le pointeur sur l'image source.
 * @return le nombre de pixels de couleur blanche de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
int nombrePixelsBlanc(struct image *src) {
  int cpt = 0 ;
  int l = src->tx*src->ty;
  int *sp = src->p;
  for ( int i = 0 ; i < l ; i++ ) {
    if ( *sp+sp[1]+sp[2] == 765 )
      cpt++;
    sp += 3; }
  return(cpt);
}

/**
 * Transforme l'image en une image a deux couleurs : noir et blanc par seuillage sur le niveau 127.5.
 *
 * @param src le pointeur sur l'image a transformer.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void noirEtBlanc(struct image *src) {
  int size = src->tx*src->ty;
  int *sp = src->p;
  for ( int i = 0 ; i < size ; i++ ) {
    int c = (*sp+sp[1]+sp[2]);
    *sp = sp[1] = sp[2] = ( c >= 382 ) ? 0xFF : 0x00 ;
    sp += 3; }
}

/**
 * Efface une image a la couleur noire.
 *
 * @param src le pointeur sur l'image a effacer.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void effaceImage(struct image *src) {
  memset(src->p,0,3*src->tx*src->ty*sizeof(int));
}

/**
 * Efface une image.
 *
 * @param src le pointeur sur l'image a effacer.
 * @param r la composante de rouge de la couleur d'effacement.
 * @param v la composante de rouge de la couleur d'effacement.
 * @param b la composante de rouge de la couleur d'effacement.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void effaceImage(struct image *src,int r,int v,int b) {
  register int size = src->tx*src->ty;
  register int *sp = src->p;
  for ( register int i = 0 ; i < size ; i++ ) {
    *sp = r;
    sp++;
    *sp = v;
    sp++;
    *sp = b;
    sp++; }
}

/**
 * Convertit une image par transformation en matrice.
 *
 * @param p le pointeur sur l'image convertir.
 * @param tx la resolution en x.
 * @param ty la resolution en y.
 * @param tp la matrice obtenue par conversion.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void conversionImage(int *p,int tx,int ty,unsigned char ***tp) {
  unsigned char **t =(unsigned char **) calloc(ty,sizeof(unsigned char *));
  *tp = t;
  int k = 0;
  for ( int i = 0 ; i < ty ; i++ ) {
    t[i] =(unsigned char *) calloc(3*tx,sizeof(unsigned char));
    for ( int j = 0 ; j < 3*tx ; j += 3 ) {
      t[i][j] =(unsigned char) p[k];
      t[i][j+1] =(unsigned char) p[k+1];
      t[i][j+2] =(unsigned char) p[k+2];
      k += 3; } }
}

/**
 * Convertit une image par transformation en matrice.
 *
 * @param p le pointeur sur l'image convertir.
 * @param tx la resolution en x.
 * @param ty la resolution en y.
 * @param tp la matrice obtenue par conversion.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void conversionImage(unsigned char *p,int tx,int ty,Espace3UC **e) {
  Espace3UC *esp = new Espace3UC(tx,ty);
  *e = esp;
  int k = 0;
  for ( int i = 0 ; i < ty ; i++ ) {
    for ( int j = 0 ; j < 3*tx ; j += 3 ) {
      esp->p[i][j] = p[k];
      esp->p[i][j+1] = p[k+1];
      esp->p[i][j+2] = p[k+2];
      k += 3; } }
}

/**
 * Desallocation memoire.
 *
 * @param tp le tableau a desallouer.
 * @param ty la resolution en y.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void desallocationImage(unsigned char **tp,int ty) {
  if ( !tp )
    return;
  for ( int i = 0 ; i < ty ; i++ )
    if ( tp[i] )
      free(tp[i]);
  free(tp);
}
