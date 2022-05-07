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

void brasRobot(float r1, float r2, bool droite, float taille) {

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


void cube(float taille) {
    glPushMatrix();
    glTranslatef(0.0f, taille / 3 / 2, 0.0f);
    float gris[4] = { 0.5F,0.5F,0.5F,1.0F };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gris);

    glutSolidCube(taille / 3);

    glPopMatrix();


}

void cou(float taille) {
    glPushMatrix();
    glTranslatef(0.0f, ((taille / 3)) + (taille / 3 / 2) / 2, 0.0f);
    glPushMatrix();
    glScalef(taille / 3 / 3, (taille / 3) / 2, 1.0F);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jaune);
    glutSolidCube(1);

    glPopMatrix();
    glPopMatrix();

}




void tete(float taille) {
    glPushMatrix();
    glTranslatef(0.0F, ((taille / 3)) + (taille / 3 / 2) + taille / 25, 0.0F);
    glPushMatrix();
    glTranslatef(taille / 3 / 3 - taille / 45, 0.0f, 0.0f);
    glPushMatrix();
    glutSolidSphere(taille / 3 / 3 / 2, 10, 10);
    glPopMatrix();
    glRotatef(90.0f, 90.0f, 0.0f, 1.0F);
    cylindre(taille / 3 / 2 + taille / 45, taille / 3 / 3 / 2, 12, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-taille / 3 / 3 + taille / 45, 0.0f, 0.0f);
    glPushMatrix();
    glutSolidSphere(taille / 3 / 3 / 2, 10, 10);
    glPopMatrix();
    glRotatef(90.0f, 90.0f, 0.0f, 1.0F);
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

void pied2(float _x, float _y, float _z, float taille) {

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

void rocher2(float x, float y, float z, float taille) {
    glPushMatrix();
    glTranslatef(x, y, z);
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
    glVertex3f(18 * taille, 0 * taille, 0* taille); //14
    glVertex3f(18 * taille, 0 * taille, 8 * taille); //13

    glEnd();


    glPopMatrix();
}


void rocher(float x, float y, float z, float taille) {
    glPushMatrix();
    glTranslatef(x, y, z);
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


void robot(float taille) {
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

/* Scene dessinee                               */

static void scene(void) {
   // robot(10.0f);
    //robot(18);
   /* glPushMatrix();
    rocher2(-10, 0, 0, 1);
    glPopMatrix();*/
    glPushMatrix();
     rocher(0, -5, 0,2);
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
    glScalef(0.1f, 0.1f, 0.1f);
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