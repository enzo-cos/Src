Projet Informatique Graphique : Découverte sur Mars
Participants : 
GURBULAK Bilal
VERA AULARD Nathan
COSTANTINI Enzo

PARTIE 1 - Doc d'utilisation :
Un robot est placé au centre de la map (((METTRE APRES (taille de la map = variable tailleMars dans le code). La caméra par défaut est une caméra à la 3ème personne placé derrière le robot.
Cette caméra peut être déplacer via les touches : 'z', 'q', 's', 'd'. Cette caméra est centrée sur le robot. Les touches 'y' ou 'Y' permettent de gérer la hauteur de cette caméra.
Il est possible de changer de caméra grâce à la touche 'c'. Cette deuxième caméra est une vue depuis le robot, à la 1ère personne.
Cette caméra suit les mouvements de la tête du robot. Le robot tourne sur lui-même avec les flèches directionnelles gauche et droite, ou bien avec un balayage de la souris.
Le robot peut avancer et reculer grâce aux flèches directionnelles haut et bas.
Le robot peut effectuer un saut sur place avec la touche 'ENTRER' (Ce saut peut fonctionner très lentement, notamment avec les textures)
Le robot s'arrête au contacte d'un obstacle, mais il peut "détruire" cette obstacle en appuyant 3 fois d'affilé sur la touche 'f' lorsqu'il est collé à cet obstacle.
Il est possible de modifier le mode d'affichage en appuyant sur la touche 'espace'.


Partie 2 - Fonctionnalité openGL à implanter :



Partie 3 - Listes des ressources à compiler ensemble :

//main :
InteractionRobot.cpp
//Librairie
CH3D.cpp
Pos3D.ccpp
Dir3D.cpp
Rt3D.cpp
//Fichier pour textures données
//Dossier PNG
ChargePngFile.cpp
ChargePngFile.h
PngFile.cpp
Espace3UC.cpp
PngFile.h
Espace3UC.h
Image.cpp
ImageUtils.cpp
Image.h
ImageUtils.h
//Dossier PNG/Png*
compress.c
crc32.c
deflate.c
gzio.c
infback.c
inffast.c
inflate.c
inftrees.c
png.c
pngerror.c
pngget.c
pngmem.c
pngpread.c
pngread.c
pngrio.c
pngrtran.c
pngrutil.c
pngset.c
pngtrans.c
pngwio.c
pngwrite.c
pngwtran.c
pngwutil.c
trees.c
uncompr.c
zutil.c


Problèmes rencontrées : 
Lenteur après la mise en place du sol avec relief.
Forte Lenteur lors de l'utilisation des textures.
