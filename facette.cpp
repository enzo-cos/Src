
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
static float nbTour = 0.0F;

static float c1 = 1.0F;
static float c2 = 1.0F;
static float c3 = 1.0F;

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
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

/** carre facette trouée   */
static void carreFacette() {
    
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(1.0F, -1.0F); //1
    glVertex2f(0.0F, -0.5F); //2

    glVertex2f(-1.0F, -1.0F); //3
    glVertex2f(-0.5F, 0.0F); //4
    glVertex2f(-1.0F, 1.0F); //5 
    glVertex2f(0.0F, 0.5F); //6
    glVertex2f(1.0F, 1.0F); //7 
    glVertex2f(0.5F, 0.0F); //8

    glVertex2f(1.0F, -1.0F); //9 
    glVertex2f(0.0F, -0.5F); //10

    glEnd();
}

static void cubeTroue() {
    glNormal3f(0.0F, 0.0F, 1.0F);
    carreFacette(); //bas 
    glRotatef(90.0F, 0.0F, 1.0F, 0.0F);
    glTranslatef(0.0F, 0.0F, 1.0F);
    
    glNormal3f(1.0F, 0.0F, 0.0F);
    carreFacette(); //droite 
}

/* Scene dessinee  */

static void scene(void) {
    glPushMatrix();
    //cubeFacette();
    cubeTroue();
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    printf("D\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(face, mode);
    float t[4] = { c1,c2,c3,1.0F };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, t);
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
