/**
 * \file Image.h
 * Implante des fonctions de manipulation d'image bitmap.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */

#ifndef ______IMAGE______
#define ______IMAGE______

/**
 * \struct image
 * Structure de stockage d'une image bitmap.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
struct image {
  /// La resolution horizontale de l'image
  int tx;
  /// La resolution verticale de l'image
  int ty;
  /// Le tableau des pixels (un integer par composante de rouge de vert et de bleu, entrelace)
  int *p;
  /// le nombre de bits de stockage de chacune des composantes
  int bits;
  /// le nombre de niveaux de gris de l'image
  int nbn;
  /// la valeur maximale d'une composante
  int max;
  /// la demi valeur maximale d'une composante
  float med; };

/**
 * \typedef image
 * Structure de stockage d'une image bitmap.
 * 
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
typedef struct image image;

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
void allocationImage(int tx,int ty,struct image *dst);

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
void allocationImage(int tx,int ty,int bits,struct image *dst);

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
void allocImage(int tx,int ty,struct image *dst);

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
void allocImage(int tx,int ty,int bits,struct image *dst);

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
void allocationImage(int tx,int ty,struct image *dst,int init);

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
void allocationImage(int tx,int ty,int bits,struct image *dst,int init);

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
void allocationImage(int tx,int ty,struct image *dst,int r,int v,int b);

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
void allocationImage(int tx,int ty,int bits,struct image *dst,int r,int v,int b);

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
void allocationImage(int tx,int ty,struct image *dst);

/**
 * Initialise une image par recopie d'une autre image.
 *
 * @param src le pointeur sur l'image source.
 * @param dst le pointeur sur l'image destination a initialiser avec une copie de l'image source.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void allocationImage(struct image *src,struct image *dst);

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
void allocationImage(int tx,int ty,unsigned char *p,struct image *dst);

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
void allocationImage(int tx,int ty,unsigned char **p,struct image *dst);

/**
 * Desalloue une image.
 *
 * @param dst le pointeur sur l'image a desallouer.
 * @author Nicolas Janey
 * @author nicolas.janey@univ-fcomte.fr
 * @version 1.0, 12/01/06
 */
void desallocationImage(struct image *dst);

#endif
