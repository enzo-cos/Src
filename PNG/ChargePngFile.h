/**
 * \file ChargePngFile.h
 * Implante une fonction de chargement de fichiers au format png.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 11/11/07
 */
#ifndef ____CHARGEPNGFILE____
#define ____CHARGEPNGFILE____

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
unsigned char *chargeImagePng(char *filename,int *rx,int *ry);

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
void sauveImagePng(char *filename,int rx,int ry,unsigned char **image);

#endif
