/**
 * \file PngFile.h
 * Implante des fonctions de chargement et de sauvegarde de fichiers au format png dans et depuis des structures image.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
#ifndef ____PNGFILE____
#define ____PNGFILE____

#include "Image.h"

/**
 * Charge un fichier png dans une structure image.
 *
 * @param file la chaine de caracteres contenant le nom du fichier.
 * @param image l'image recevant les pixels du fichier png
 * @param red l'adresse d'un octet destine a recueillir la valeur de composante rouge de la couleur de fond.
 * @param green l'adresse d'un octet destine a recueillir la valeur de composante verte de la couleur de fond.
 * @param blue l'adresse d'un octet destine a recueillir la valeur de composante bleue de la couleur de fond.
 * @return un entier booleen indiquant si la chargement a abouti ou non.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
int chargeImagePng(char *file,struct image *image,unsigned char *red,unsigned char *green,unsigned char *blue);

/**
 * Sauvegarde une structure image dans un fichier png.
 *
 * @param file la chaine de caracteres contenant le nom du fichier.
 * @param image l'image a sauvegarder.
 * @return un entier booleen indiquant si la chargement a abouti ou non.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
int sauveImagePng(char *file,struct image *image);

#endif
