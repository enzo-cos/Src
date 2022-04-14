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
static GLenum node = GL_FILL;
static int pos = 0;
static float c1 = 0.5f;
static float c2 = 0.7f;
static float c3 = 0.6f;
static float r1 = 0.0f;
static float r2 = 90.0f;
static float angle = 0.0f;
static float angley = 0.0f;
static float anglex = 0.0f;
static bool anim = true;
static bool droite = true;
float gris[4] = { 0.5F,0.5F,0.5F,1.0F };
float jaune[4] = { 1.0F,1.0F,0.0F,1.0F };


static void init(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);  
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

void brasRobot(float r1, float r2,bool droite) {
   
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
        glutSolidSphere(0.6,20,20);
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




void tete(){
    glPushMatrix();
    glTranslatef(0.0F, 4.0F, 0.0F);
    glPushMatrix();
    glTranslatef(0.8f, 0.0f, 0.0f);
    glPushMatrix();
    glutSolidSphere(0.5,10,10);
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

/* Scene dessinee                               */

static void scene(void) {
    glPushMatrix();
    cube();
    cou();
    tete();
    pied();
    glPushMatrix();
    glScalef(0.8f, 1.0f, 1.0f);
    brasRobot(r1, -r2,droite);
    brasRobot(r1,r2,!droite);
    glPopMatrix();
   
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    printf("D\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float t[4] = { c1, c2,c3,1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, t);
    glPolygonMode(face, node);
    //glColor3f(c1, c2, c3);
    glPushMatrix();
    glRotatef(angley, 0.0f, 1.0f, 0.0f);
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glRotatef(anglex, 1.0f, 0.0f, 0.0f);
    glScalef(0.2f, 0.2f, 0.2f);
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
    angle += 2.0f;
    //glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %4c %4d %4d\n", key, x, y);
    switch (key) {
    case 0x1B:
        exit(0);
        break;
    case 0x20:
        switch (node)
        {
        case GL_FILL:
            node = GL_LINE;
            break;
        case GL_LINE:
            node = GL_POINT;
            break;
        case GL_POINT:
            node = GL_FILL;
            break;
        }
        glutPostRedisplay();
        break;

    case 13:
        anim = !anim;
        if (anim) {
            glutIdleFunc(idle);
        }
        else {
            glutIdleFunc(NULL);
        }

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
    case 100:
        angley += 1.0f;
        c2 += 0.01f;

        glutPostRedisplay();
        break;

    case 102:
        angley -= 1.0f;
        c2 -= 0.01f;

        glutPostRedisplay();
        break;

    case 101:
        anglex += 1.0f;
        c3 += 0.01f;
        glutPostRedisplay();
        break;


    case 103:
        anglex -= 1.0f;
        c3 += 0.01f;
        glutPostRedisplay();
        break;

    case 0x1B:
        exit(0);
        break;
    case 49: //1
        r1 -= 0.5f;
        glutPostRedisplay();
        break;
    case 52: //4

        r1 += 0.5f;
        glutPostRedisplay();
        break;
    case 50: //2
        r2 -= 0.5f;
        glutPostRedisplay();
        break;
    case 53: //5

        r2 += 0.5f;
        glutPostRedisplay();
        break;


    }
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button, int state, int x, int y) {
    printf("M  %4d %4d %4d %4d\n", button, state, x, y);
    pos = x;
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    printf("MM %4d %4d\n", x, y);
  
    glutPostRedisplay();
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

    atexit(clean); // exécution d'une fonction (static void clean(void)) lorsque l'application est interrompue par exécution de la fonction standard void exit(int),

    glutInit(&argc, argv); //configuration des paramètres OpenGL obligatoires qui n'auront pas à être reconfigurés au cours de la vie du programme (appels regroupés dans la fonction static void init(void)),
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //configuration des paramètres OpenGL obligatoires qui n'auront pas à être reconfigurés au cours de la vie du programme (appels regroupés dans la fonction static void init(void)),
    glutInitWindowSize(wTx, wTy); //configuration et création de la fenêtre de visualisation,
    glutInitWindowPosition(wPx, wPy); //configuration et création de la fenêtre de visualisation,
    glutCreateWindow("Gestion événementielle de GLUt"); //configuration et création de la fenêtre de visualisation,
    init();
    glutKeyboardFunc(keyboard); //programmation de la gestion des événements
    glutSpecialFunc(special); //programmation de la gestion des événements
    glutMouseFunc(mouse); //programmation de la gestion des événements
    glutMotionFunc(mouseMotion); //programmation de la gestion des événements
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutIdleFunc(NULL);
    glutDisplayFunc(display); //affichage de la fenêtre de visualisation et lancement de la boucle infinie de gestion des événements.
    glutMainLoop(); //affichage de la fenêtre de visualisation et lancement de la boucle infinie de gestion des événements.
    return(0);
}