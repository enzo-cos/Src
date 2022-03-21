/* 64 cubes de coté 0.5 places en un cube       */
/* de 4 x 4 x 4 cubes (taille globale = 6.5)    */
/* et colores en fonction de leur position      */
/* dans ce cube                                 */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Fevrier 2019                                 */

#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables et constantes globales             */

static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };

static int aff = 1;

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
    glClearColor(0.25F, 0.25F, 0.25F, 1.0F);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, blanc);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

/* Scene dessinee                               */

static void scene() {
    const GLfloat light0_direction[] = { 0.0,0.0,1.0,0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    glPushMatrix();
    glTranslatef(0.0F, 0.0F, -100.0F);
    for (int x = -3; x <= 3; x += 2)
        for (int y = -3; y <= 3; y += 2)
            for (int z = -3; z <= 3; z += 2) {
                glPushMatrix();
                glTranslatef((float)x, (float)y, (float)z);
                float couleur[4] = { (x + 3) / 6.0F,(y + 3) / 6.0F,(z + 3) / 6.0F,1.0F };
                glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur);
                glutSolidCube(0.5);
                glPopMatrix();
            }
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, (aff) ? GL_FILL : GL_LINE);
    glPushMatrix();
    gluLookAt(0.0, 0.0, -90.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Erreur OpenGL: %d\n", error);
}

//////////////////////////////////////////////////

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */
/* -> Ajustement de la camera de visualisation  */

static void reshape(int tx, int ty) {
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   
    double ratio = (double)ty / tx;
    double ratio2 = (double)tx / ty;

    if (ratio2 > 1.0) {
        gluPerspective(6, ratio2, 80, 100.0);
    }
    else {
        gluPerspective(6/ratio2, ratio2, 80, 100);
    }
    /*if (ratio > 1.0) {
        glOrtho(-4, 4, -4 * ratio, 4 * ratio, 90, 110);
    }
    else {
        glOrtho(-4/ratio, 4/ratio, -4 , 4, 90, 110);
    }*/
           
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//////////////////////////////////////////////////

/* Fonction executee lors de la frappe          */
/* d'une touche du clavier                      */

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 0x20:
        aff = (aff + 1) % 2;
        glutPostRedisplay();
        break;
    case 0x1B:
        exit(0);
        break;
    }
}

/* Fonction principale                          */

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(360, 360);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("64 cubes");
    init();
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return(0);
}