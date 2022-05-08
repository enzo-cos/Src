
#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <chrono>
#include <ctime> 
#include "PNG/ChargePngFile.h"
#include "Dir3D.h"
#include "CH3D.h"
#include "Tr3D.h"
#include "Pos3D.h"

/* Variables globales                           */

static int wTx = 480;              // Resolution horizontale de la fenetre
static int wTy = 480;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre

static GLenum face = GL_FRONT_AND_BACK;
static GLenum mode = GL_FILL;
static bool anim = false;


static bool reculer = false;
static bool cam = false;
static bool contrePierre = false;
static int nbCoup = 0;
static float rota = 0.0F;
static float turn = 0.0F;
static float nbTour = 0.0F;

static float r1 = 0.0f;
static float r2 = 90.0f;
static float angle = 0.0f;
static float angley = 0.0f;
static float anglex = 0.0f;
static bool droite = true;
float gris[4] = { 0.5F,0.5F,0.5F,1.0F };
float jaune[4] = { 1.0F,1.0F,0.0F,1.0F };
float noir[4] = { 0.0F,0.0F,0.0F,1.0F };
float marron[4] = { 0.54F,0.27F,0.07F,1.0F };


static float c1 = 1.0F;
static float c2 = 1.0F;
static float c3 = 1.0F;

static float avX = 20.0F;
static float avY = 3.0F;
static float avZ = 20.0F;


static double tailleMars = 512.0;
static float llong = tailleMars / 2.4;
static float posPmin = tailleMars / 3.43;
static float posPmax = tailleMars / 1.41;
static int MiddleMap = tailleMars / 2;

static int mat_obstacles[512][512] = { 0 };
static float mat_posY[512][512] = { 0 };

static int rotaR = 0;
static double prop = 10.0;
static double toRad = 3.14159 / 180.0;

Pos3D posRobot = Pos3D(tailleMars / 2, 3.0, tailleMars / 2);

static double tailleRobot = tailleMars/40;
static double posCameraRobotY = posRobot.y+ tailleRobot*0.6;
Dir3D dirRobot = Dir3D(sin(rotaR * toRad) * prop, 0.0, cos(rotaR * toRad) * prop);
Pos3D posCam3 = Pos3D(posRobot.x, posRobot.y + 30, posRobot.z-30);
static int rotaYeux = 0.0;

static int mouseX = 0.0;
static int mouseY = 0.0;

//Taille pour rochers :
static int TR1 = tailleRobot / 3;
static int TR2 = tailleRobot / 6;

//Ajout des potions des lumières

static float positionhaut[4] = {(float)MiddleMap,80.0F,(float)MiddleMap,0.0F };
static float positiondroite[4] = { 0.0F,10.0F,-tailleMars,0.0F };

static float diffuse[4] = { 1.0F,1.0F,1.0F,1.0F };
static float ambiant[4] = { 0.2F,0.2F,0.2F,1.0F };
static float spec[4] = { 1.0F,1.0F,1.0F,1.0F };



//Saut : 
static double ymin = 3.0;
static double maxSaut = 12.0; //=3,4m
static bool montee = false;
double poidsRobot = 150.0;
double graviteMars = 3.721;
//Vitesse supposé 5m/s
double vitesseSaut = 5.0;
//double accelSaut = 40.0;// accel supposé 40m/sec²
//1/2*m*v²=m*g*h, sur terre saut de 1.2m => sur Mars = 3,4 
//double forceSaut = (accelSaut + graviteMars) * poidsRobot;//force= (a+g)*M
auto startSaut = std::chrono::system_clock::now();


//RELIEF
static float** yMat=(float**)calloc(tailleMars + 1, sizeof(float*));
static int nVaria = 2;


/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */
static unsigned int textureID = 0;
static int texture =1;
static int nTexture = 0;

static void initTexture(void) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    { //int rx = 16;
      //int ry = 16;
        char* nomFichier = "textMars1.png";
        if(nTexture==2) nomFichier = "etoile3.png";
        int rx;
        int ry;
        printf("%s\n", nomFichier);
        unsigned char* img = chargeImagePng(nomFichier, &rx, &ry);
        printf("rx : %d, ry : %d\n",rx, ry);
        if (img) {
            glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            free(img);
            printf("Texture chargee %d\n", textureID);
        }
        else {
            glDeleteTextures(1, &textureID);
            textureID = 0;
            printf("Texture non chargee\n");
        } }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

static float** getYPos(float** y_pos, int alt_max, int rec, int xmin, int xmax, int zmin, int zmax) {
    if (xmax - xmin <= 1) {
        return y_pos;
    }

    int xmid = (xmax - xmin) / 2 + xmin;
    int zmid = (zmax - zmin) / 2 + zmin;

    if (rec == 0) {
        y_pos[xmin][zmin] = rand() % alt_max; y_pos[xmin][zmax] = rand() % alt_max;
        y_pos[xmax][zmin] = rand() % alt_max; y_pos[xmax][xmax] = rand() % alt_max;
    }
    y_pos[xmin][zmid] = (rand() % alt_max) / (pow(nVaria, rec)) + (y_pos[xmin][zmin] + y_pos[xmin][zmax]) / 2;
    y_pos[xmid][zmax] = (rand() % alt_max) / (pow(nVaria, rec)) + (y_pos[xmin][zmax] + y_pos[xmax][zmax]) / 2;
    y_pos[xmax][zmid] = (rand() % alt_max) / (pow(nVaria, rec)) + (y_pos[xmax][zmax] + y_pos[xmax][zmin]) / 2;
    y_pos[xmid][zmin] = (rand() % alt_max) / (pow(nVaria, rec)) + (y_pos[xmin][zmin] + y_pos[xmax][zmin]) / 2;
    y_pos[xmid][zmid] = (rand() % alt_max) / (pow(nVaria, rec)) + (y_pos[xmin][zmin] + y_pos[xmin][zmax] + y_pos[xmax][zmin] + y_pos[xmax][zmax]) / 4;

    rec++;
    getYPos(y_pos, alt_max, rec, xmin, xmid, zmin, zmid);
    getYPos(y_pos, alt_max, rec, xmid, xmax, zmin, zmid);
    getYPos(y_pos, alt_max, rec, xmin, xmid, zmid, zmax);
    getYPos(y_pos, alt_max, rec, xmid, xmax, zmid, zmax);

    return y_pos;
}
/* n -> taille du sol (doit être une puissance de 2) */
static void genSol(int n) {
    glPushMatrix();
    if (n < 257) nVaria = 3;
    for (int i = 0; i <= n; ++i)
    {
        yMat[i] = (float*)calloc(n + 1, sizeof(float));
    };

    yMat = getYPos(yMat, 20, 0, 0, n, 0, n);
    posRobot.y = yMat[(int)posRobot.x][(int)posRobot.z];
    posCam3.y = posRobot.y + 10;
    glPopMatrix();
   /* for (int i = 0; i < n; ++i)
    {
        free(y[i]);
    };
    free(y);*/
}
static void init(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2); 
    //glEnable(GL_LIGHT3);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    initTexture();
    genSol((int)tailleMars);
}

static void modifMatCube(int x, int z, int c, int val) {
    int l = c / 2;
    for (int i = x - l; i < x + l + 1; i++) {
        for (int j = z - l; j < z + l + 1; j++) {
            if (mat_obstacles[i][j] != -1) mat_obstacles[i][j] = val;
        }
    }
}
static void modifMatR1(int x, int z, int taille,int val) {
    int longueur = taille * 4.61;
    int larg = taille * 2;
    for (int i = x - longueur; i < x + longueur; i++) {
        for (int j = z - larg-5; j < z + larg+5; j++) {
            if (mat_obstacles[i][j] != -1) mat_obstacles[i][j] = val;
        }
    }
}
static void modifMatR2(int x, int z, int taille, int val) {
    int longueur = taille * 18;
    int larg = taille * 8;
    for (int i = x-1; i < x + longueur+2; i++) {
        for (int j = z-4; j < z + larg+2; j++) {
            if (mat_obstacles[i][j] != -1) mat_obstacles[i][j] = val;
        }
    }
}
//Point en bas à gauche
void rocher2(float x, float y, float z, float taille) {
    glPushMatrix();
    //glTranslatef(x, y, z);
    glScalef(1, 1, 1);

    glBegin(GL_POLYGON);
    glVertex3f(0 * taille, 0 * taille, 2 * taille); //1
    glVertex3f(2 * taille, 0 * taille, 5 * taille); //2
    glVertex3f(10 * taille, 0 * taille, 8 * taille); //3
    glVertex3f(17 * taille, 0 * taille, 6 * taille); //4
    glVertex3f(18 * taille, 0 * taille, 4 * taille); //5
    glVertex3f(16 * taille, 0 * taille, 3 * taille); //6
    glVertex3f(13 * taille, 0 * taille, 0 * taille); //7
    glVertex3f(5 * taille, 0 * taille, 0 * taille); //8
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(3 * taille, 4 * taille, 2 * taille); //9
    glVertex3f(6 * taille, 3 * taille, 5 * taille); //10
    glVertex3f(11 * taille, 5 * taille, 4 * taille); //11
    glVertex3f(13 * taille, 7 * taille, 6 * taille); //12
    glVertex3f(11 * taille, 4 * taille, 2 * taille); //13
    glVertex3f(7 * taille, 7 * taille, 4 * taille); //14
    glEnd();

    glBegin(GL_QUADS); //15
    glVertex3f(2 * taille, 0 * taille, 5 * taille); //2
    glVertex3f(10 * taille, 0 * taille, 8 * taille); //3
    glVertex3f(11 * taille, 5 * taille, 4 * taille); //11
    glVertex3f(6 * taille, 3 * taille, 5 * taille); //10

    glEnd();


    glBegin(GL_QUADS); //16
    glVertex3f(10 * taille, 0 * taille, 8 * taille); //3
    glVertex3f(17 * taille, 0 * taille, 6 * taille); //4
    glVertex3f(13 * taille, 7 * taille, 6 * taille); //12
    glVertex3f(11 * taille, 5 * taille, 4 * taille); //11


    glEnd();

    glBegin(GL_TRIANGLES); //17
    glVertex3f(17 * taille, 0 * taille, 6 * taille); //4
    glVertex3f(18 * taille, 0 * taille, 4 * taille); //5
    glVertex3f(13 * taille, 7 * taille, 6 * taille); //12
    glEnd();


    glBegin(GL_POLYGON); //18
    glVertex3f(18 * taille, 0 * taille, 4 * taille); //5
    glVertex3f(16 * taille, 0 * taille, 3 * taille); //6
    glVertex3f(13 * taille, 0 * taille, 0 * taille); //7
    glVertex3f(11 * taille, 4 * taille, 2 * taille); //13
    glVertex3f(13 * taille, 7 * taille, 6 * taille); //12

    glEnd();

    glBegin(GL_QUADS); //19
    glVertex3f(13 * taille, 0 * taille, 0 * taille); //7
    glVertex3f(5 * taille, 0 * taille, 0 * taille); //8
    glVertex3f(7 * taille, 7 * taille, 4 * taille); //14
    glVertex3f(11 * taille, 4 * taille, 2 * taille); //13

    glEnd();

    glBegin(GL_QUADS); //20
    glVertex3f(0 * taille, 0 * taille, 2 * taille); //1
    glVertex3f(5 * taille, 0 * taille, 0 * taille); //8
    glVertex3f(7 * taille, 7 * taille, 4 * taille); //14
    glVertex3f(3 * taille, 4 * taille, 2 * taille); //9

    glEnd();

    glBegin(GL_QUADS); //20
    glVertex3f(0 * taille, 0 * taille, 2 * taille); //1
    glVertex3f(2 * taille, 0 * taille, 5 * taille); //2
    glVertex3f(6 * taille, 3 * taille, 5 * taille); //10
    glVertex3f(3 * taille, 4 * taille, 2 * taille); //9

    glEnd();

    glBegin(GL_QUADS); //19
    glVertex3f(0 * taille, 0 * taille, 8 * taille); //7
    glVertex3f(0 * taille, 0 * taille, 0 * taille); //8
    glVertex3f(18 * taille, 0 * taille, 0 * taille); //14
    glVertex3f(18 * taille, 0 * taille, 8 * taille); //13

    glEnd();


    glPopMatrix();
}
//point au centre, 4,6*taille*2, 2*taille*2
void rocher(float x, float y, float z, float taille) {
    glPushMatrix();
    //glTranslatef(x, y, z);
    glScalef(1, 1, 1);
    // glRotatef(-45, 1.0f, 0.0f, 0.0f);
    float zz = 2.0f;
    float z2 = -2.0f;
    glBegin(GL_POLYGON);
    glVertex3f(-2.0f * taille, -2.0f * taille, zz * taille); //1
    glVertex3f(-2.5f * taille, -0.3f * taille, zz * taille);//2
    glVertex3f(0.0f * taille, 2.0f * taille, zz * taille);//3
    glVertex3f(2.0f * taille, 1.3f * taille, zz * taille);//4
    glVertex3f(2.2f * taille, -1.0f * taille, zz * taille);//5
    glVertex3f(1.8f * taille, -2 * taille, zz * taille);//6
    glVertex3f(-2.0f * taille, -2.0f * taille, zz * taille); //1
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.0f * taille, 1.3f * taille, zz * taille);//4
    glVertex3f(2.2f * taille, -1.0f * taille, zz * taille);//5
    glVertex3f(2.8f * taille, -2.0F * taille, z2 * taille);//7
    glVertex3f(3.0f * taille, -0.5F * taille, z2 * taille);//8
    glVertex3f(2.8f * taille, 1.5F * taille, z2 * taille);//9
    glVertex3f(2.0f * taille, 1.3f * taille, zz * taille);//4
    glEnd();

    glBegin(GL_POLYGON);

    glVertex3f(-2.5f * taille, -0.3f * taille, zz * taille);//2
    glVertex3f(0.0f * taille, 2.0f * taille, zz * taille);//3
    glVertex3f(-4.0f * taille, 1.8f * taille, z2 * taille);//10
    glVertex3f(-4.5f * taille, -1.0f * taille, z2 * taille);//11
    glVertex3f(-4.0f * taille, -2 * taille, z2 * taille);//12
    glVertex3f(-2.5f * taille, -0.3f * taille, zz * taille);//2
    glEnd();

    glBegin(GL_QUADS);

    glVertex3f(-4.0f * taille, 1.8f * taille, z2 * taille);//10
    glVertex3f(2.8f * taille, 1.5F * taille, z2 * taille);//9
    glVertex3f(2.8f * taille, -2.0F * taille, z2 * taille);//7
    glVertex3f(-4.0f * taille, -2 * taille, z2 * taille);//12

    glEnd();


    glBegin(GL_TRIANGLES);
    glVertex3f(2.0f * taille, 1.3f * taille, zz * taille);//4
    glVertex3f(2.8f * taille, 1.5F * taille, z2 * taille);//9
    glVertex3f(0.0f * taille, 2.0f * taille, zz * taille);//3
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-4.0f * taille, 1.8f * taille, z2 * taille);//10
    glVertex3f(2.8f * taille, 1.5F * taille, z2 * taille);//9
    glVertex3f(0.0f * taille, 2.0f * taille, zz * taille);//3
    glEnd();


    glBegin(GL_QUADS);
    glVertex3f(-4.6f * taille, -2.0f * taille, zz * taille);
    glVertex3f(-4.6f * taille, -2.0f * taille, z2 * taille);
    glVertex3f(4.6f * taille, -2.0f * taille, z2 * taille);
    glVertex3f(4.6f * taille, -2.0f * taille, zz * taille);
    glEnd();




    glBegin(GL_QUADS);
    glVertex3f(1.8f * taille, -2 * taille, zz * taille);//6
    glVertex3f(2.8f * taille, -2.0F * taille, z2 * taille);//7
    glVertex3f(-4.0f * taille, -2 * taille, z2 * taille);//12
    glVertex3f(-2.0f * taille, -2.0f * taille, zz * taille); //1

    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(1.8f * taille, -2 * taille, zz * taille);//6
    glVertex3f(2.8f * taille, -2.0F * taille, z2 * taille);//7
    glVertex3f(2.2f * taille, -1.0f * taille, zz * taille);//5
    glEnd();


    glBegin(GL_TRIANGLES);
    glVertex3f(-4.0f * taille, -2 * taille, z2 * taille);//12
    glVertex3f(-2.0f * taille, -2.0f * taille, zz * taille); //1
    glVertex3f(-2.5f * taille, -0.3f * taille, zz * taille);//2
    glEnd();


    glPopMatrix();
}
static void genTerrain() {
    glPushMatrix();
    nTexture = 0;
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,marron);
    /*initTexture();
    glEnable(GL_TEXTURE_2D);*/
    
    glNormal3f(0.0F, 1.0F, 0.0F);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0F, 0.0F);
    glVertex3f(0,0, 0);
    glTexCoord2f(1.0F, 0.0F);
    glVertex3f(tailleMars, 0, 0);
    glTexCoord2f(1.0F, 1.0F);
    glVertex3f(tailleMars, 0, tailleMars);
    glTexCoord2f(0.0F, 1.0F);
    glVertex3f(0, 0, tailleMars);
    glEnd();
    /*for (float x = 0; x < tailleMars - 1; x++) {
        for (float z = 0; z < tailleMars - 1; z++) {
            int x_tab = (int)x;
            int z_tab = (int)z;
            glBegin(GL_QUADS);
            glTexCoord2f(0.0F, 0.0F);
            glVertex3f(x, yMat[x_tab][z_tab], z);
            glTexCoord2f(1.0F, 0.0F);
            glVertex3f(x + 1, yMat[x_tab + 1][z_tab], z);
            glTexCoord2f(1.0F, 1.0F);
            glVertex3f(x + 1, yMat[x_tab + 1][z_tab + 1], z + 1);
            glTexCoord2f(0.0F, 1.0F);
            glVertex3f(x, yMat[x_tab][z_tab + 1], z + 1);
           
            glEnd();
        }
    }*/
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
}
static void genCote() {
    float y= 100.0F;
    nTexture = 2;
    glPushMatrix();
    /*initTexture();
    glEnable(GL_TEXTURE_2D);*/
    double mid = tailleMars / 2;
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, texture);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, spec);
    glTranslatef(mid, 0.0F, mid);
    glRotatef(90.0F, -1.0F, 0.0F,0.0F);
    gluCylinder(quad, mid, tailleMars / 5, 200.0, 10, 10);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
static int Destroy_rec(int x, int z) {
    int res = 0;
    if (mat_obstacles[x][z] == 1) {
        mat_obstacles[x][z] = -1;
        //printf("destroy x=%d , z= %d\n", x, z);
        res = 1;
    }
    return res;
}
static void DestroyPierre(int x, int z) {
    //ajouter avec rota + largeur du robot
    int l = 4/2;
    int r = 1;
    int x2 = x;
    int z2 = z;
    int nbcote = 0;
    while (nbcote<2) {
        r = 1;
        while (r != 0) {
            r = Destroy_rec(x2, z2);
            z2++;
        }
        r = 1;
        z2 = z - 1;
        while (r != 0) {
            r = Destroy_rec(x2, z2);
            z2--;
        }
        z2 = z;
        if (nbcote == 0) {
            x2++;
            if (mat_obstacles[x2][z] != 1) {
                nbcote++;
                x2 = x-1;
            }
        }
        else if (nbcote == 1) {
            x2--;
            if (mat_obstacles[x2][z] != 1) nbcote++;
        }
            
    }
}
static void PlacerObjets(void) {
    glPushMatrix();
    glScalef(1.0F, 1.0F, 1.0F);
    float y = 7.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);
    int x = 3; int z = 3; int c = 4;
    x = tailleMars/2+20;//Pos robot initial +30
    z = tailleMars / 2 +30;
    glTranslatef(x,y, z);
    /*double dist = sqrt((x - posRobot.x) * (x - posRobot.x) + (z - posRobot.z) * (z - posRobot.z));
    if (dist < TR1*5) PAS construire*/
    if (mat_obstacles[x][z] != -1) {
        /*modifMat(x, z, c, 1);
        glutSolidCube(c);*/
        // glTranslatef(x+30, 0.0, z+30);
        modifMatR1(x, z, TR1, 1);
        rocher(x,0.0,z, TR1);
         //glTranslatef(x-30, 0.0, z-30);
    }
    glTranslatef(-25, 0.0, 25);
    x -= 27;
    z += 27;
    if (mat_obstacles[x][z] != -1) {
        modifMatR1(x, z, TR1, 1);
        rocher(x, 0.0, z, TR1);
    }

    glTranslatef(0.0, 0.0, -100);
    x -= 0;
    z -= 100;
    if (mat_obstacles[x][z] != -1) {
        modifMatR2(x, z, TR2, 1);
        rocher2(x, 0.0, z, TR2);
    }
   /*for (int i = 0; i<3; i++) {
       if (i == 0) {
           glTranslatef(-5, 0.0, 10);
           x -= 5;
           z += 10;
       }
       else if (i == 2) {
           glTranslatef(-10, 0.0, 5);
           x -= 10;
           z += 5;
       }
       else {
           glTranslatef(-5, 0.0, 5);
           x -= 5;
           z += 5;
       }
       if (mat_obstacles[x][z] != -1) {
           modifMatR1(x, z, TR1, 1);
           rocher(x, 0.0, z, TR1);
       }
    }*/
   /*
   for (int i = 0; i < 3; i++) {
       if (i == 0) {
           glTranslatef(-5, 0.0, -10);
           x -= 5;
           z -= 10;
       }
       else if (i == 2) {
           glTranslatef(-10, 0.0, -5);
           x -= 10;
           z -= 5;
       }
       else {
           glTranslatef(-5, 0.0, -5);
           x -= 5;
           z -= 5;
       }
       if (mat_obstacles[x][z] != -1) {
           modifMat(x, z, c, 1);
           glutSolidCube(c);
       }
   }*/
    /*
   for (int i = 0; i < 3; i++) {
       if (i == 0) {
           glTranslatef(5, 0.0, -5);
           x += 5;
           z -= 5;
       }
       else if (i == 2) {
           glTranslatef(10, 0.0, -10);
           x += 10;
           z -= 10;
       }
       else {
           glTranslatef(5, 0.0, -5);
           x += 5;
           z -= 5;
       }
       if (mat_obstacles[x][z] != -1) {
           modifMat(x, z, c, 1);
           glutSolidCube(c);
       }
   }*/
   /*
   for (int i = 0; i < 3; i++) {
       if (i == 0) {
           glTranslatef(10, 0.0, 5);
           x += 10;
           z += 5;
       }
       else if (i == 2) {
           glTranslatef(5, 0.0, 10);
           x += 5;
           z += 10;
       }
       else {
           glTranslatef(5, 0.0, 5);
           x += 5;
           z += 5;
       }
       if (mat_obstacles[x][z] != -1) {
           modifMat(x, z, c, 1);
           glutSolidCube(c);
       }
   } */
 
  /*  glTranslatef(10, 0.0, 5);
    glutSolidCube(c);
    glTranslatef(5, 0.0, 5);
    glutSolidCube(c);
    glTranslatef(5, 0.0, 10);
    glutSolidCube(c);*/
    glPopMatrix();
}

static void cylindre(double h, double r, int n, int m) {
    glPushMatrix();
    glRotatef(90.0F, 1.0f, 0.0F, 0.0F);
    glTranslatef(0.0F, 0.0F, -h / 2);
    GLUquadricObj* qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluCylinder(qobj, r, r, h, n, m);
    gluDeleteQuadric(qobj);
    glPopMatrix();
}

void brasRobot(float r1, float r2, bool droite, double taille) {

    if (droite) {
        glPushMatrix();
        glTranslatef(0.0f, taille / 9 + taille / 6, 0.0f);
        glRotatef(r1, 0.0f, 1.0f, 0.0f);
        glTranslatef(taille / 3.6, 0.0f, 0.0f);
        glPushMatrix();
        /*  glScalef(2.0f, 1.0f, 1.0f);
          glutSolidCube(1.0);*/
        glRotatef(90.0F, 0.0F, 0.0F, 1.0F);
        cylindre(taille / 3, taille / 3 / 3 / 2, 12, 12);

        glPopMatrix();
        glTranslatef(taille / 3 / 2, 0.0f, 0.0f);
        glRotatef(r2, 0.0f, 1.0f, 0.0f);
        glTranslatef(taille / 3 / 2, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(90.0F, 0.0F, 0.0F, 1.0F);
        cylindre(taille / 3, taille / 18 - taille / 90, 12, 12);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);
        glTranslatef(0.0f, -taille / 6 - taille / 45, 0.0f);
        glutSolidSphere(taille / 18 + taille / 45, 20, 20);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jaune);
        /*glScalef(2.0f, 0.8f, 0.8f);
        glutSolidCube(1.0);*/
        glPopMatrix();
        glPopMatrix();
    }
    else {
        glPushMatrix();
        glTranslatef(0.0f, taille / 9 + taille / 6, 0.0f);
        glRotatef(r1, 0.0f, 1.0f, 0.0f);
        glTranslatef(-taille / 3.6, 0.0f, 0.0f);
        glPushMatrix();
        /* glScalef(2.0f, 1.0f, 1.0f);
         glutSolidCube(1.0);*/
        glRotatef(90.0F, 0.0F, 0.0F, 1.0F);
        cylindre(taille / 3, taille / 3 / 3 / 2, 12, 12);
        glPopMatrix();
        glTranslatef(-taille / 3 / 2, 0.0f, 0.0f);
        glRotatef(r2, 0.0f, 1.0f, 0.0f);
        glTranslatef(-taille / 3 / 2, 0.0f, 0.0f);
        glPushMatrix();
        /*glScalef(2.0f, 0.8f, 0.8f);
        glutSolidCube(1.0);*/
        glRotatef(90.0F, 0.0F, 0.0F, 1.0F);

        cylindre(taille / 3, taille / 18 - taille / 90, 12, 12);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);
        glTranslatef(0.0f, taille / 6 + taille / 45, 0.0f);
        glutSolidSphere(taille / 18 + taille / 45, 20, 20);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jaune);
        glPopMatrix();
        glPopMatrix();

    }

}

void cube(double taille) {
    glPushMatrix();
    glTranslatef(0.0f, taille / 3 / 2, 0.0f);
    float gris[4] = { 0.5F,0.5F,0.5F,1.0F };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);

    glutSolidCube(taille / 3);

    glPopMatrix();


}

void cou(double taille) {
    glPushMatrix();
    glTranslatef(0.0f, ((taille / 3)) + (taille / 3 / 2) / 2, 0.0f);
    glPushMatrix();
    glScalef(taille / 3 / 3, (taille / 3) / 2, 1.0F);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jaune);
    glutSolidCube(1);

    glPopMatrix();
    glPopMatrix();

}

void tete(double taille) {
    glPushMatrix();
    glTranslatef(0.0F, ((taille / 3)) + (taille / 3 / 2) + taille / 25, 0.0F);
    glPushMatrix();
    glTranslatef(taille / 3 / 3 - taille / 45, 0.0f, 0.0f);
    glPushMatrix();
    glutSolidSphere(taille / 3 / 3 / 2, 10, 10);
    glPopMatrix();
    glRotatef(90.0f, 90.0f, 0.0f, 1.0F);
    glRotatef(rotaYeux, 1.0, 0.0, 0.0);
    cylindre(taille / 3.0 / 2 + taille / 45, taille / 3 / 3 / 2, 12, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-taille / 3 / 3 + taille / 45, 0.0f, 0.0f);
    glPushMatrix();
    glutSolidSphere(taille / 3 / 3 / 2, 10, 10);
    glPopMatrix();
    glRotatef(90.0f, 90.0f, 0.0f, 1.0F);
    glRotatef(rotaYeux, 1.0, 0.0, 0.0);
    printf("rotaYeux : %d\n", rotaYeux);
    cylindre(taille / 3 / 2 + taille / 45, taille / 3 / 3 / 2, 12, 12);

    glPopMatrix();
    glPopMatrix();

}

void pied() {
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.f);
    glutSolidSphere(2.5, 20, 20);
    glPopMatrix();
}

void pied2(float _x, float _y, float _z, double taille) {

    glPushMatrix();

    glTranslatef(_x, _y, _z);
    glRotatef(90, 0, 1, 0);
    float x = taille / 3 / 2;
    float y = taille / 3 / 2 - taille / 45;
    float z = taille / 18;
    glBegin(GL_TRIANGLES);
    glVertex3f(-x, -y, z); //1
    glVertex3f(x, -y, z);//2
    glVertex3f(0.0f, y, z);//3
    glEnd();


    glBegin(GL_TRIANGLES);
    glVertex3f(-x, -y, -0.5); //4
    glVertex3f(x, -y, -0.5);//5
    glVertex3f(0.0f, y, -0.5);//6
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-x, -y, -0.5); //4
    glVertex3f(x, -y, -0.5);//5
    glVertex3f(x, -y, z);//2
    glVertex3f(-x, -y, z); //1
    glEnd();


    glBegin(GL_QUADS);
    glVertex3f(0.0f, y, z);//3
    glVertex3f(0.0f, y, -0.5);//6
    glVertex3f(x, -y, -0.5);//5
    glVertex3f(x, -y, z);//2
    glEnd();



    glBegin(GL_QUADS);
    glVertex3f(0.0f, y, z);//3
    glVertex3f(0.0f, y, -0.5);//6
    glVertex3f(-x, -y, -0.5); //4
    glVertex3f(-x, -y, z); //1
    glEnd();


    glPopMatrix();

}

void robot(double taille) {
    glPushMatrix();
    pied2(-taille / 3 / 2 - 0.5, 0, 0, taille);
    pied2(taille / 3 / 2 + 0.5, 0, 0, taille);
    cube(taille);
    cou(taille);
    tete(taille);

    glPushMatrix();
    glScalef(0.8f, 1.0f, 1.0f);
    brasRobot(r1, -r2, droite, taille);
    brasRobot(r1, r2, !droite, taille);
    glPopMatrix();

    glPopMatrix();
}

static int getLimite(int newposX, int newposZ) {
    //limite carré
    //if (newposX < 1 || newposZ <1 || newposX > tailleMars - 2 || newposZ > tailleMars - 2) return -1;
    //limite rayon
    double mid = tailleMars / 2;
    double dist = 0.0;
    dist = sqrt((newposX - mid) * (newposX - mid) + (newposZ - mid) * (newposZ - mid));
    if (dist > (double)MiddleMap - 20) {
        printf("Limite de la map atteinte\n");
        return -1;
    }
    if (mat_obstacles[newposX][newposZ] == 1) {
        printf("impossible d'avancer, un obstacle est present\n");
        contrePierre = true;
        return 1;
    }
    contrePierre = false;
    return 0;
}
/* Scene dessinee  */
static void avancer() {
    int newPosX = (int)(posRobot.x + dirRobot.x / prop);
    int newPosZ = (int)(posRobot.z + dirRobot.z / prop);
    
    if (getLimite(newPosX,newPosZ)!=0) return;
    posRobot.x += (dirRobot.x / prop);
    posRobot.z += (dirRobot.z / prop);
}

static void recule() {
    int newPosX = (int)(posRobot.x - dirRobot.x / prop);
    int newPosZ = (int)(posRobot.z - dirRobot.z / prop);
    if (getLimite(newPosX, newPosZ) != 0) return;
    posRobot.x -= (dirRobot.x / prop);
    posRobot.z -= (dirRobot.z / prop);
}

static void scene(void) {
    glPushMatrix();
    genTerrain();
    //genSol((int)tailleMars);
    genCote();
    PlacerObjets();
    //ROBOT
      glPushMatrix();
      //posRobot.y = yMat[(int)posRobot.x][(int)posRobot.z];
      posRobot.y =4.0;
      glTranslatef(posRobot.x, posRobot.y, posRobot.z);
      glRotatef(rotaR, 0.0f, 1.0F, 0.0f);
    glPushMatrix();
     robot(tailleRobot);
    glPopMatrix();
    glPopMatrix();
    //FIN ROBOT
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    printf("D\n");
    posCameraRobotY = posRobot.y + tailleRobot*0.6;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(face, mode);
    //Lumière représentant le soleil, en haut, lumière directionnelle
    glLightfv(GL_LIGHT1, GL_POSITION, positionhaut);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambiant);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spec);

    //Lumière factive pour mieux éclairer la scène
    glLightfv(GL_LIGHT2, GL_POSITION, positiondroite);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambiant);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, spec);

    float coulLum[4] = { 0.0F,0.0F,1.0F,1.0F };
    //Lumière sur la tête du robot
    float positionLum[4] = { (float)posRobot.x,(float)posCameraRobotY,(float)posRobot.z,1.0F };
    float directionLum[3] = { (float)posRobot.x + dirRobot.x/5 , (float)posCameraRobotY + dirRobot.y, (float)posRobot.z + dirRobot.z/5 };
    float  spotCutoff[1] = { 90.0F };
   
    glLightfv(GL_LIGHT3, GL_POSITION, positionLum);
    glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, spotCutoff);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, directionLum);
    glLightfv(GL_LIGHT3, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, coulLum);
    
    glPushMatrix(); 
    //Différent point de vue
    if (!cam) { //3ème personne
        gluLookAt(posCam3.x, posCam3.y, posCam3.z, posRobot.x, posRobot.y, posRobot.z, 0.0, 1.0, 0.0);
    }
    else { //1ère personne
       gluLookAt(posRobot.x+(dirRobot.x/5), posCameraRobotY, posRobot.z+ (dirRobot.z / 5), posRobot.x + dirRobot.x, posCameraRobotY+dirRobot.y, posRobot.z+ dirRobot.z, 0.0, 1.0, 0.0);
    }

    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx, int wy) {
    printf("R\n");
    wTx = wx;
    wTy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratioP = (double)wx / (double)wy;
    //Adaptation taille de l'écran
    if (ratioP > 1) {
        gluPerspective(90.0, ratioP, 1, tailleMars);
    }
    else {
        gluPerspective(90.0 / ratioP, ratioP, 1.0, tailleMars);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
    printf("I\n");
    //saut
    
    if (montee) {
        vitesseSaut = (maxSaut - posRobot.y)/30;
        if (vitesseSaut < 0.004) vitesseSaut = 0.004;
        if (posRobot.y < maxSaut) posRobot.y += vitesseSaut;
        else montee = false;
    }
    else {
        auto la = std::chrono::system_clock::now();
        std::chrono::duration<double> t_ec = la - startSaut;
    
        vitesseSaut = (graviteMars * t_ec.count())/50;
        
        if (vitesseSaut < 0.004) vitesseSaut = 0.004;
        if (posRobot.y > ymin) posRobot.y -= vitesseSaut;
        else {
            glutIdleFunc(NULL);
            anim = false;
        }
    }
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %4c %4d %4d\n", key, x, y);
    switch (key) {
    //Modifier le mode d'affichage avec espace
    case 0x20: //espace
        switch (mode) {
        case GL_FILL:
            mode = GL_POINT;
            break;
        case GL_POINT:
            mode = GL_LINE;
            break;
        case GL_LINE:
            mode = GL_FILL;
            break;
        }
        glutPostRedisplay();
        break;

    //Sauter avec la touche Entrer
    case 13: //enter
        if (anim) {
            glutIdleFunc(NULL);
            anim = false;
        }
        else {
            if (!anim) {
                ymin = yMat[(int)posRobot.x][(int)posRobot.z];
                maxSaut = ymin + 12.0;
            }
            startSaut = std::chrono::system_clock::now();
            glutIdleFunc(idle);
            anim = true;
            montee = true;

        }
        break;

    //ZQSD : mouvement caméra 3ème personne
    case 'z':
        if (getLimite(posCam3.x, posCam3.z - 1) > -1) {
            posCam3.z -= 1.0;
            glutPostRedisplay();
        }
        break;

    case 'q':
        if (getLimite(posCam3.x - 1, posCam3.z) > -1) {
            posCam3.x -= 1.0;
            glutPostRedisplay();
        }
        break;

    case 's':
        if (getLimite(posCam3.x, posCam3.z +1) > -1) {
            posCam3.z += 1.0;
            glutPostRedisplay();
        }
        break;

    case 'd':
        
        if (getLimite(posCam3.x +1, posCam3.z) > -1) {
            posCam3.x += 1.0;
            glutPostRedisplay();
        }
        break;

    //Hauteur caméra 3ème personne
    case 'y':
        posCam3.y += 1.0;
        glutPostRedisplay();
        break;

    case 'Y':
        posCam3.y -= 1.0;
        glutPostRedisplay();
        break;

     //Changer caméra
    case 'c':
        cam = !cam;
        glutPostRedisplay();
        break;

    //Détruire une pierre
    case 'f':
        if (contrePierre) {
            nbCoup++;
            if (nbCoup == 3) {
                int x1, z1;
                if (reculer) {
                    x1 = posRobot.x - dirRobot.x / prop;
                    z1 = posRobot.z - dirRobot.z / prop;
                }
                else {
                    x1 = posRobot.x + dirRobot.x / prop;
                    z1 = posRobot.z + dirRobot.z / prop;
                }
                DestroyPierre(x1, z1);
                nbCoup = 0;
            }
        }
        else {
            nbCoup = 0;
        }
        glutPostRedisplay();
        break;

    case 0x1B://echap
        exit(0);
        break;
    }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey, int x, int y) {
    printf("S  %4d %4d %4d\n", specialKey, x, y);
    /* Prendre compte largeur robot en avant arrière + en Z + coté du robot
    int posXadv = posRobot.x + dirRobot.x / prop + tailleRobot;
    int posXrec = posRobot.x - dirRobot.x / prop - tailleRobot;  */
    switch (specialKey) {
        //Tourner le robot à gauche
        case 100: //fleche gauche
          
            rotaR = (rotaR + 2) % 360;
            dirRobot.z = cos(rotaR * toRad) * prop;
            dirRobot.x = sin(rotaR * toRad) * prop;

            glutPostRedisplay();
            break;

        //Faire Avancer le robot
        case 101: //fleche haut
            reculer = false;
            avancer();        
            
            glutPostRedisplay();
            break;
        //Tourner le robot à droite
        case 102: //fleche droite
            rotaR = (rotaR - 2) % 360;
            dirRobot.z = cos(rotaR * toRad) * prop;
            dirRobot.x = sin(rotaR * toRad) * prop;

            glutPostRedisplay();
            break;
        //Reculer le robot à gauche
        case 103: //fleche bas
            reculer = true;
            recule();
            
            glutPostRedisplay();
            break;
    }
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button, int state, int x, int y) {
    printf("M  %4d %4d %4d %4d\n", button, state, x, y);
    mouseX = x;
    mouseY = y;
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    printf("MM %4d %4d\n", x, y);
    int diffX = mouseX - x;
    int diffY = mouseY - y;
    rotaR = (rotaR % 360) - (diffX / 2);
    dirRobot.z = cos(rotaR * toRad) * prop;
    dirRobot.x = sin(rotaR * toRad) * prop;
   // printf("Dir Z : %f\nDirX : %f\nDirY : %f\nRotaR = %d", dirRobot.z, dirRobot.x, dirRobot.y,rotaR);
    double n = (-diffY / 2);
    if (dirRobot.y + n < 15.0 && dirRobot.y + n>-15.0) {
        rotaYeux += (diffY / 2); dirRobot.y += n;
    }
    
    glutPostRedisplay();
    mouseX = x;
    mouseY = y;
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x, int y) {
    printf("PM %4d %4d\n", x, y);
}

/* Fonction exécutée automatiquement            */
/* lors de l'exécution de la fonction exit()    */

static void clean(void) {
    printf("Bye\n");
}

/* Fonction principale                          */

int main(int argc, char** argv) {

    atexit(clean); //exécution d'une fonction (static void clean(void)) lorsque l'application est interrompue par exécution de la fonction standard void exit(int)

    //configuration des paramètres OpenGL obligatoires qui n'auront pas à être reconfigurés au cours de la vie du programme
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    //configuration et création de la fenêtre de visualisation
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Gestion événementielle de GLUt");
    init();
    //programmation de la gestion des événements
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    //glutIdleFunc(idle);
    glutIdleFunc(NULL);
    //affichage de la fenêtre de visualisation et lancement de la boucle infinie de gestion des événements
    glutDisplayFunc(display);
    glutMainLoop();
    return(0);
}
