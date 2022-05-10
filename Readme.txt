Projet Informatique Graphique : Découverte sur Mars
Participants : 
GURBULAK Bilal
VERA AULARD Nathan
COSTANTINI Enzo

PARTIE 1 - Doc d'utilisation :
Un robot est placé au centre de la map (taille de la map = variable tailleMars dans le code). La caméra par défaut est une caméra à la 3ème personne placé derrière le robot.
Cette caméra peut être déplacer via les touches : 'z', 'q', 's', 'd'. Cette caméra est centrée sur le robot.
Ces touches bougent la caméra respectivement en z, x, -z et -x.
Les touches 'y' ou 'Y' permettent de gérer la hauteur de cette caméra.
Il est possible de changer de caméra grâce à la touche 'c'. Cette deuxième caméra est une vue depuis le robot, à la 1ère personne.
Cette caméra suit les mouvements de la tête du robot. Le robot tourne sur lui-même avec les flèches directionnelles gauche et droite, ou bien avec un balayage de la souris.
Le robot peut avancer et reculer grâce aux flèches directionnelles haut et bas.
Le robot peut effectuer un saut sur place avec la touche 'ENTRER' (Ce saut peut fonctionner très lentement, notamment avec les textures)
Le robot s'arrête au contacte d'un obstacle, mais il peut "détruire" cette obstacle en appuyant 3 fois d'affilé sur la touche 'f' lorsqu'il est collé à cet obstacle.
Il est possible de modifier le mode d'affichage en appuyant sur la touche 'espace'.


Partie 2 - Fonctionnalitées openGL à implanter :

Modélisation :
On peut retrouver de la modélisation géométrique dans le projet dans la construction du robot (fonction robot), ainsi que des les fonctions rocher et rocher2, dessinant des rochers.
Le terrain est également constitué de multiple facettes. La fonction genTerrain() le dessine et la fonction genSol() initialise les valeurs.

Lumières et matériaux :
3 lumières sont ajoutées, on peut les consulter au début de la fonction "display()".
La première représentant le soleil, c'est une lumière directionnelle positionnée en hauteur. (GL_LIGHT1)
La deuxième est une lumière factive permettant d'améliorer la visibilité de la scène. (GL_LIGHT2)
La troisième est une lumière placée dans les yeux du robot, afin d'éclairer ce qu'il voit.

La modélisation des matériaux est effectuée à chaque objet, pour spécifier la couleur diffusée et refléchie des objets. On les retrouve dans les fonctions genTerrain, genCote, robot, rocher et rocher1.

Textures : 
Les textures sont gérées via la fonction initTexture. On retrouve 3 textures, celle du sol représentant Mars (textMars1.png), celle du ciel représentant les étoiles (etoile3.png) et celle représentant les rochers (rocher1.png). Un numéro de texture est attribué avant l'appel de initTexture pour déterminer la texture convenant à l'objet.

Caméras :
Deux caméras sont disponibles, la caméra vue Robot (1ère personne) et la caméra à la 3ème personne. On peut alterner les caméras grâce à la touche 'c'. Les paramètres des caméras se situent au début de la fonction display, après le paramètrage des lumières. A cet endroit, nous définissions la position et la direction de la caméra. Afin de respecter la perspective des objets, nous avons également définis la fonction gluPerspective dans la fonction "reshape()".
La caméra à la 3ème personne est mobile via les touches 'z', 'q', 's', 'd'.
La caméra à la 1ère personne suit donc les mouvements du robot, donc via les flèches direcctionnelles du clavier ou bien grâce au glissement de la souris.

Animation : 
Le robot bouge via les touches directionnelles, mais il existe deux animations en plus. Il y a le saut, disponible avec la touche 'Entrée', puis il y a la frappe, disponible avec la touche'f'. Cette touche permet de supprimer un rocher en appuyant trois fois lorsqu'on est collé à un rocher.
Malheureusement, la lenteur de notre projet une fois le sol mis en place enlève toute la fluidité de ces animations. Elles sont définis dans la fonction idle().

Modèle Physique :
La détection d'obstacles est définis dans la fonction "getLimite", en regardant si la nouvelle position du robot ne touche pas un obstacle grâce à une matrice d'obstacles. Cette fonction est appelée lorsque le robot avance ou recule.
La gravité est légèrement utilisée lors de la retombée du saut (fonction "idle()").



Partie 3 - Listes des ressources à compiler ensemble :
Nous sommes repartis de l'exemple donné en début d'année. 
Les fichiers dans le dossier "ImageTexture" sont à ajouter dans le dossier "Bin".
Les fichiers suivants sont à ajouter dans le dossier "Src".
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
adler32.c
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
