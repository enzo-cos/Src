
#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "PNG/ChargePngFile.h"
#include "Dir3D.h"

/* Variables globales                           */

static int wTx = 480;              // Resolution horizontale de la fenetre
static int wTy = 480;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre

static GLenum face = GL_FRONT_AND_BACK;
static GLenum mode = GL_FILL;
static bool anim = false;
static bool cam = false;
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
float marron[4] = { 0.54F,0.27F,0.07F,1.0F };


static float c1 = 1.0F;
static float c2 = 1.0F;
static float c3 = 1.0F;

static float avX = 20.0F;
static float avY = 3.0F;
static float avZ = 20.0F;

static double posX = 0.0;
static double posY = 10.0;
static double posZ = 80.0;

static double posRobotX = 0.0;
static double posRobotY = 10.0;
static double posRobotZ = 0.0;

static double dirX=0.0;
static double dirY=0.0;
static double dirZ=10.0;

static int rotaR = 0;
static double prop = 10.0;
static double toRad = 3.14159 / 180.0;

static int mouseX = 0.0;
static int mouseY = 0.0;

static float position1[4] = { 100.0F,0.0F,0.0F,0.0F };
static float position2[4] = { 0.0F,0.0F,100.0F,0.0F };
static float diffuse[4] = { 1.0F,1.0F,1.0F,1.0F };
static float ambiant[4] = { 0.2F,0.2F,0.2F,1.0F };
static float spec[4] = { 1.0F,1.0F,1.0F,1.0F };
static float tJaune[4] = { 1.0F,1.0F,1.0F,1.0F };

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */
static unsigned int textureID = 0;
static int texture =1;

static void initTexture(void) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    { //int rx = 16;
      //int ry = 16;
        char* nomFichier = "textMars2.png";
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

static void init(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    initTexture();
}


/** cube trou  */
static void cubeFacette() {
    
    //face
    glNormal3f(0.0F, 0.0F, 1.0F);
    glBegin(GL_QUADS);
    glVertex3f(-0.5F, 0.5F,0.5F); //1
    glVertex3f(-0.5F, -0.5F,0.5F); //2 
    glVertex3f(0.5F, -0.5F, 0.5F); //3 
    glVertex3f(0.5F, 0.5F, 0.5F); //4
    glEnd();
    //droite
    glNormal3f(1.0F, 0.0F, 0.0F);
    glBegin(GL_QUADS);
    glVertex3f(0.5F, 0.5F, 0.5F); //4
    glVertex3f(0.5F, -0.5F, 0.5F); //3
    glVertex3f(0.5F, -0.5F, -0.5F); //7
    glVertex3f(0.5F, 0.5F, -0.5F); //8
    glEnd();
    //derriere
    glNormal3f(0.0F, 0.0F, -1.0F);
    glBegin(GL_QUADS);
    glVertex3f(0.5F, 0.5F, -0.5F); //8
    glVertex3f(0.5F, -0.5F, -0.5F); //7
    glVertex3f(-0.5F, -0.5F, -0.5F); //6
    glVertex3f(-0.5F, 0.5F, -0.5F); //5
    glEnd();
    //bas
    glNormal3f(0.0F, -1.0F, 0.0F);
    glBegin(GL_QUADS);
    glVertex3f(0.5F, -0.5F, 0.5F); //3 
    glVertex3f(-0.5F, -0.5F, 0.5F); //2 
    glVertex3f(-0.5F, -0.5F, -0.5F); //6
    glVertex3f(0.5F, -0.5F, -0.5F); //7
    glEnd();
    //gauche
    glNormal3f(-1.0F, 0.0F, 0.0F);
    glBegin(GL_QUADS);
    glVertex3f(-0.5F, -0.5F, 0.5F); //2 
    glVertex3f(-0.5F, 0.5F, 0.5F); //1
    glVertex3f(-0.5F, 0.5F, -0.5F); //5
    glVertex3f(-0.5F, -0.5F, -0.5F); //6
    glEnd();
    //haut
    glNormal3f(0.0F, 1.0F, 0.0F);
    glBegin(GL_QUADS);
    glVertex3f(-0.5F, 0.5F, 0.5F); //1
    glVertex3f(0.5F, 0.5F, 0.5F); //4
    glVertex3f(0.5F, 0.5F, -0.5F); //8
    glVertex3f(-0.5F, 0.5F, -0.5F); //5
    glEnd();

}

static void genTerrain() {
    glPushMatrix();
    initTexture();
    glEnable(GL_TEXTURE_2D);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, marron);
    float y = 0.0F;
    float x=-50.0F;
    float z = -50.0F;
    float c = 2.0f;
    //bool dec = false;
    //    while (x < 55.0) {
    //        z = -50.0f;
    //        while (z < 53.0) {

    //            glNormal3f(0.0F, 1.0F, 0.0F);
    //            glBegin(GL_QUADS);
    //            glTexCoord2f(0.0F, 0.0F);
    //            glVertex3f(x, y, z);
    //            //glTexCoord2f(1.0F, 0.0F);
    //            glVertex3f(x + c, y, z);
    //            //Modif y pour relief
    //            //glTexCoord2f(1.0F, 1.0F);
    //            glVertex3f(x + c, y, z + c);
    //            //glTexCoord2f(0.0F, 1.0F);
    //            glVertex3f(x, y, z + c);
    //            glEnd();
    //            z += c;
    //        }
    //        x += c;
    //    }
    glNormal3f(0.0F, 1.0F, 0.0F);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0F, 1.0F);
    glVertex3f(-80, y, 80);
    glTexCoord2f(1.0F, 1.0F);
    glVertex3f(80, y, 80);
    glTexCoord2f(1.0F, 0.0F);
    glVertex3f(80, y, -80);   
    glTexCoord2f(0.0F, 0.0F);
    glVertex3f(-80, y, -80);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

static void DeplSph(void) {
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);
    glTranslatef(avX, avY, avZ);
    glutSolidSphere(3.5, 250, 250);
    glTranslatef(avX+10, avY, avZ+5);
    glutSolidSphere(2.5, 150, 150);
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

void brasRobot(float r1, float r2, bool droite) {

    if (droite) {
        glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f);
        glRotatef(r1, 0.0f, 1.0f, 0.0f);
        glTranslatef(2.5f, 0.0f, 0.0f);
        glPushMatrix();
        /*  glScalef(2.0f, 1.0f, 1.0f);
          glutSolidCube(1.0);*/
        glRotatef(90.0F, 0.0F, 0.0F, 1.0F);
        cylindre(3.0, 0.5, 12, 12);

        glPopMatrix();
        glTranslatef(1.5f, 0.0f, 0.0f);
        glRotatef(r2, 0.0f, 1.0f, 0.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(90.0F, 0.0F, 0.0F, 1.0F);
        cylindre(3.0, 0.4, 12, 12);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);
        glTranslatef(0.0f, -1.7f, 0.0f);
        glutSolidSphere(0.6, 20, 20);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jaune);
        /*glScalef(2.0f, 0.8f, 0.8f);
        glutSolidCube(1.0);*/
        glPopMatrix();
        glPopMatrix();
    }
    else {
        glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f);
        glRotatef(r1, 0.0f, 1.0f, 0.0f);
        glTranslatef(-2.5f, 0.0f, 0.0f);
        glPushMatrix();
        /* glScalef(2.0f, 1.0f, 1.0f);
         glutSolidCube(1.0);*/
        glRotatef(90.0F, 0.0F, 0.0F, 1.0F);
        cylindre(3.0, 0.5, 12, 12);
        glPopMatrix();
        glTranslatef(-1.5f, 0.0f, 0.0f);
        glRotatef(r2, 0.0f, 1.0f, 0.0f);
        glTranslatef(-1.0f, 0.0f, 0.0f);
        glPushMatrix();
        /*glScalef(2.0f, 0.8f, 0.8f);
        glutSolidCube(1.0);*/
        glRotatef(90.0F, 0.0F, 0.0F, 1.0F);

        cylindre(3.0, 0.4, 12, 12);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);
        glTranslatef(0.0f, 1.7f, 0.0f);
        glutSolidSphere(0.6, 20, 20);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jaune);
        glPopMatrix();
        glPopMatrix();

    }

}


void cube() {
    glPushMatrix();
    float gris[4] = { 0.5F,0.5F,0.5F,1.0F };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);

    glutSolidCube(3.0);

    glPopMatrix();


}

void cou() {
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glPushMatrix();
    glScalef(1.0F, 2.0F, 1.0F);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jaune);
    glutSolidCube(1);

    glPopMatrix();
    glPopMatrix();

}




void tete() {
    glPushMatrix();
    glTranslatef(0.0F, 4.0F, 0.0F);
    glPushMatrix();
    glTranslatef(0.8f, 0.0f, 0.0f);
    glPushMatrix();
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
    glRotatef(90.0f, 90.0f, 0.0f, 1.0F);
    cylindre(1.5, 0.6, 12, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8f, 0.0f, 0.0f);
    glPushMatrix();
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
    glRotatef(90.0f, 90.0f, 0.0f, 1.0F);
    cylindre(1.5, 0.6, 12, 12);

    glPopMatrix();
    glPopMatrix();

}

void pied() {
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.f);
    glutSolidSphere(2.5, 20, 20);
    glPopMatrix();
}
/* Scene dessinee  */

static void scene(void) {
    glPushMatrix();
    genTerrain();
    DeplSph();
    //ROBOT
    glPushMatrix();
    glTranslatef(posRobotX, 3.0, posRobotZ);
    glRotatef(90, 0.0f, 1.0F,0.0f);
    //glutSolidCube(5);
    //glPopMatrix();
    //glPushMatrix();
    cube();
    cou();
    tete();
    pied();
    glPushMatrix();
    glScalef(0.8f, 1.0f, 1.0f);
    brasRobot(r1, -r2, droite);
    brasRobot(r1, r2, !droite);
    glPopMatrix();
    glPopMatrix();
    //FIN ROBOT

    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    /*if (texture)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);*/
    printf("D\n");
    /*rota = 25.0;
    turn = 10.0;*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(face, mode);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0F);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambiant);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, tJaune);

    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 180.0F);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambiant);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, tJaune);

   
    float t[4] = { c1,c2,c3,1.0F };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, t);
    glPushMatrix(); 
    if (!cam) {
        gluLookAt(posX, posY, posZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else {
       gluLookAt(posRobotX, posRobotY, posRobotZ, posRobotX + dirX, 3.0, posRobotZ+dirZ, 0.0, 1.0, 0.0);
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
    if (!cam) {
        

        double posModif = (posZ) * -1;
        //multA = -100 / posZ;
        printf("pos = %f\n", posModif);
        /*if (ratioP > 1) {
            gluPerspective(45.0 * 1.0, ratioP, posZ-40, posZ-120);
        }
        else {
            gluPerspective(45.0 * 1.0/ratioP, ratioP, posZ - 40, posZ - 120);
        }*/
        //glOrtho(posX-30, posX+30, posY-20, posY+20, posZ-100, posZ);
        gluPerspective(45.0 * 1.0 / ratioP, ratioP, posZ - 40, posZ - 120);
    }
    else {
        gluPerspective(90, ratioP, -60.0, 0.0);
        //glOrtho(-51.0, 51.0, -51.0, 51.0, -51.0, 51.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
    printf("I\n");
    turn += 2.0F;
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %4c %4d %4d\n", key, x, y);
    switch (key) {
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

    case 13: //enter
        if (anim) {
            glutIdleFunc(NULL);
            anim = false;
        }
        else {
            glutIdleFunc(idle);
            anim = true;
        }
        break;


    //COLOR
    case 0x52: //R
        if (c1 > 0) c1 -= 0.1F;
        glutPostRedisplay();
        break;
    case 0x72: //r
        if (c1 < 1) c1 += 0.1F;
        glutPostRedisplay();
        break;

    case 0x56: //V
        if (c2 > 0) c2 -= 0.1F;
        glutPostRedisplay();
        break;
    case 0x76: //v
        if (c2 < 1) c2 += 0.1F;
        glutPostRedisplay();
        break;

    case 0x42: //B
        if (c3 > 0) c3 -= 0.1F;
        glutPostRedisplay();
        break;
    case 0x62: //b
        if (c2 < 1) c3 += 0.1F;
        glutPostRedisplay();
        break;

    case 'z':
        posZ -= 1.0;
        glutPostRedisplay();
        break;

    case 'q':
        posX -= 1.0;
        glutPostRedisplay();
        break;

    case 's':
        posZ += 1.0;
        glutPostRedisplay();
        break;

    case 'd':
        posX += 1.0;
        glutPostRedisplay();
        break;

    case 'y':
        posY += 1.0;
        glutPostRedisplay();
        break;

    case 'Y':
        posY -= 1.0;
        glutPostRedisplay();
        break;

    case 'c':
        cam = !cam;
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
    switch (specialKey) {
        case 100: //fleche gauche
            //avZ -= 1.0F;
            posRobotZ--;
            //turn--;
            glutPostRedisplay();
            break;

        case 101: //fleche haut
            
            //avX += 1.0F;
            posRobotX++;
            //rota++;
            glutPostRedisplay();
            break;

        case 102: //fleche droite
            //avZ += 1.0F;
            posRobotZ++;
            //turn++;
            glutPostRedisplay();
            break;

        case 103: //fleche bas
            //avX -= 1.0F;
            posRobotX--;
            //rota--;
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
    dirZ = cos(rotaR * toRad) * prop;
    dirX = sin(rotaR * toRad) * prop;
    posZ += (-diffY / 2);
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
