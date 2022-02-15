
#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables globales                           */

static int wTx = 480;              // Resolution horizontale de la fenetre
static int wTy = 480;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre

static GLenum face = GL_FRONT_AND_BACK;
static GLenum mode = GL_FILL;
static bool anim = false;
static float rota = 0.0F;
static float turn = 0.0F;

static float c1 = 1.0F;
static float c2 = 1.0F;
static float c3 = 1.0F;

static int nbf = 50;
static float position0[4] = { 2.0F,0.0F,0.0F,1.0F };
static float position1[4] = { -2.0F,0.0F,0.0F,0.0F };
static float diffuse[4] = { 1.0F,1.0F,1.0F,1.0F };
static float ambiant[4] = { 0.2F,0.2F,0.2F,1.0F };
static float spec[4] = { 1.0F,1.0F,1.0F,1.0F };
static float ponctCenter[4] = {0.0F,0.0F,0.0F,1.0F };

static float angleSpot = 5.0F;
static float position2[4] = { 5.0F,5.0F,5.0F,1.0F };

static float ambiant3[4] = { 1.0F,1.0F,1.0F,1.0F };

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}


/* Scene dessinee  */

static void scene(void) {
    glPushMatrix();    
    glutSolidSphere(0.8, nbf, nbf);
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
   
    printf("D\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(face, mode);

    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0F);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiant);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0F);

    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0F);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambiant);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);

    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF,angleSpot);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambiant);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spec);


    float t[4] = { c1,c2,c3,1.0F };
    float t1[4] = { 1.0F,1.0F,1.0F,1.0F };
    float t2[4] = { 0.4F,0.6F,0.8F,1.0F };
    float tJaune[4] = { 1.0F,1.0F,0.0F,1.0F };
    float tVert[4] = { 0.0F,1.0F,0.0F,1.0F };
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, t);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, t);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, tJaune);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, tVert);
    

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, t1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, t2);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64.F);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiant3);

    glPushMatrix();
    glRotatef(rota, 1.0F, 0.0F, 0.0F);
    glRotatef(turn, 0.0F, 1.0F, 0.0F);
    
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
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
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
    case '+' :
        nbf++;
        glutPostRedisplay();
        break;

    case '-':
        nbf--;
        glutPostRedisplay();
        break;

    case 'O':
        angleSpot++;
        glutPostRedisplay();
        break;

    case 'o':
        angleSpot--;
        glutPostRedisplay();
        break;

    case 'à':
        glDisable(GL_LIGHT0);
        glutPostRedisplay();
        break;
    case '0':
        glEnable(GL_LIGHT0);
        glutPostRedisplay();
        break;

    case '&':
        glDisable(GL_LIGHT1);
        glutPostRedisplay();
        break;
    case '1':
        glEnable(GL_LIGHT1);
        glutPostRedisplay();
        break;

    case 'é':
        glDisable(GL_LIGHT2);
        glutPostRedisplay();
        break;
    case '2':
        glEnable(GL_LIGHT2);
        glutPostRedisplay();
        break;

    case '"':
        glDisable(GL_LIGHT3);
        glutPostRedisplay();
        break;
    case '3':
        glEnable(GL_LIGHT3);
        glutPostRedisplay();
        break;

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
            turn -= 2.0F;
            glutPostRedisplay();
            break;

        case 101: //fleche haut
            rota -= 2.0F;
            glutPostRedisplay();
            break;

        case 102: //fleche droite
            turn += 2.0F;
            glutPostRedisplay();
            break;

        case 103: //fleche bas
            rota += 2.0F;
            glutPostRedisplay();
            break;
    }
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button, int state, int x, int y) {
    printf("M  %4d %4d %4d %4d\n", button, state, x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    printf("MM %4d %4d\n", x, y);
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
