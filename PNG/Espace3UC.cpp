#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Espace3UC.h"

Espace3UC::Espace3UC(int dx,int dy) {
  this->dx = dx ;
  this->dy = dy ;
  p =(unsigned char **) calloc(dy,sizeof(unsigned char *)) ;
  for ( int i = 0 ; i < dy ; i++ ) {
    p[i] =(unsigned char *) calloc(3*(dx+1),sizeof(unsigned char)) ; }
}

Espace3UC::~Espace3UC(void) {
  for ( int i = 0 ; i < dy ; i++ )
    if ( p[i] )
      free(p[i]) ;
  if ( p )
    free(p) ;
}

void Espace3UC::init(unsigned char v) {
  for ( int i = 0 ; i < dy ; i++ )
    memset(p[i],(int) v,3*(dx+1)*sizeof(unsigned char)) ;
}

void Espace3UC::init(unsigned char v1,unsigned char v2,unsigned char v3) {
  for ( int i = 0 ; i < dy ; i++ )
    for ( int j = 0 ; j < 3*(dx+1) ; j += 3 ) {
      p[i][j] = v1;
      p[i][j+1] = v2;
      p[i][j+2] = v3; }
}

void Espace3UC::cherche(int x,int y,unsigned char *c) {
  c[0] = p[y][3*x] ;
  c[1] = p[y][3*x+1] ;
  c[2] = p[y][3*x+2] ;
}

void Espace3UC::sauve(unsigned char *c,int x,int y) {
  p[y][3*x] = c[0] ;
  p[y][3*x+1] = c[1] ;
  p[y][3*x+2] = c[2] ;
}

long Espace3UC::getUsedMemory(void) {
  long cpt = sizeof(Espace3UC);
  cpt += dy*3*(dx+1)*sizeof(unsigned char) ;
  cpt += dy*sizeof(unsigned char *) ;
  return(cpt);
}

int Espace3UC::getUsedHandles(void) {
  int cpt = 1;
  cpt += dy ;
  cpt++ ;
  return(cpt);
}

int Espace3UC::alloue(void) {
  if ( !p )
    return(0);
  for ( int i = 0 ; i < dy ; i++ )
    if ( !p[i] )
      return(0);
  return(1);
}

