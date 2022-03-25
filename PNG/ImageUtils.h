/**
 * \file ImageUtils.h
 * Implante une structure de stockage et de manipulation d'image bitmap.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */

#ifndef ____IMAGEUTILS____
#define ____IMAGEUTILS____

#include "Espace3UC.h"

/**
 * Affecte une image a non allouée.
 *
 * @param dst le pointeur sur l'image a affecter.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void imageNulle(struct image *dst);

/**
 * Realise le "Ou" d'une image par une autre image de meme resolution.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @param image le pointeur sur l'image composee.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void ou(struct image *src,struct image *image);

/**
 * Copie une autre image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @param dst le pointeur sur l'image composee.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void copie(struct image *src,struct image *dst);

/**
 * Calcule la composante de rouge mediane des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de rouge mediane des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float rougeMedian(struct image *src);

/**
 * Calcule la composante de vert mediane des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de vert mediane des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float vertMedian(struct image *src);

/**
 * Calcule la composante de bleu mediane des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de bleu mediane des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float bleuMedian(struct image *src);

/**
 * Calcule la composante de rouge moyenne des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de rouge moyenne des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float rougeMoyen(struct image *src);

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
void couleurMediane(struct image *src,float *r,float *v,float *b);

/**
 * Calcule la composante de vert moyenne des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de vert moyenne des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float vertMoyen(struct image *src);

/**
 * Calcule la composante de bleu moyenne des pixels de l'image.
 *
 * @param src le pointeur sur l'image source et resultat.
 * @return la composante de bleu moyenne des pixels de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
float bleuMoyen(struct image *src);

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
void couleurMoyenne(struct image *src,float *r,float *v,float *b);

/**
 * Calcule le nombre de pixels de couleur blanche de l'image.
 *
 * @param src le pointeur sur l'image source.
 * @return le nombre de pixels de couleur blanche de l'image.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
int nombrePixelsBlanc(struct image *src);

/**
 * Transforme l'image en une image a deux couleurs : noir et blanc par seuillage sur le niveau 127.5.
 *
 * @param src le pointeur sur l'image a transformer.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void noirEtBlanc(struct image *src);

/**
 * Efface une image a la couleur noire.
 *
 * @param src le pointeur sur l'image a effacer.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void effaceImage(struct image *src);

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
void effaceImage(struct image *src,int r,int v,int b);

/**
 * Convertit une image par transformation en matrice.
 *
 * @param p le pointeur sur l'image convertir.
 * @param tx la resolution en x.
 * @param ty la resolution en y.
 * @param tp le tableau obtenu par conversion.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void conversionImage(int *p,int tx,int ty,unsigned char ***tp);

/**
 * Convertit une image par transformation en un Espace3UC.
 *
 * @param p le pointeur sur l'image convertir.
 * @param tx la resolution en x.
 * @param ty la resolution en y.
 * @param e l'Espace3UC obtenu par conversion.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void conversionImage(unsigned char *p,int tx,int ty,Espace3UC **e);

/**
 * Desallocation memoire.
 *
 * @param tp le tableau a desallouer.
 * @param ty la resolution en y.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void desallocationImage(unsigned char **tp,int ty);

#endif
