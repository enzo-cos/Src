/* Une animation en OpenGL                      */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Septembre 2012                               */

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables et constantes globales             */
/* pour les angles et les couleurs utilises     */

static float r0 = 0.0F;
static float r1 = 0.0F;
static float r2 = 0.0F;
static float r3 = 0.0F;
static float r4 = 0.0F;
static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };

/* Affichage des informations relatives         */
/* a OpenGL                                     */

static void informationsOpenGL(void) {
  printf("GL_VENDOR     = %s\n",(const char *) glGetString(GL_VENDOR));
  printf("GL_VERSION    = %s\n",(const char *) glGetString(GL_VERSION));
  printf("GL_RENDERER   = %s\n",(const char *) glGetString(GL_RENDERER));
  printf("GL_EXTENSIONS = %s\n",(const char *) glGetString(GL_EXTENSIONS));
}

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

void init(void) {
  const GLfloat shininess[] = { 50.0 };
  glMaterialfv(GL_FRONT,GL_SPECULAR,blanc);
  glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,rouge);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,jaune);
  glLightfv(GL_LIGHT2,GL_DIFFUSE,bleu);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);
}

/* Scene dessinee                               */

void scene(void) {
  glPushMatrix();
  glRotatef(r0,0.0F,0.0F,1.0F);
  glRotatef(r1,0.0F,1.0F,0.0F);
  glutSolidTorus(0.7,10.0,18,72);
  glRotatef(r2,1.0F,0.0F,0.0F);
  glutSolidTorus(0.7,8.6F,18,72);
  glRotatef(90.0F,0.0F,0.0F,1.0F);
  glRotatef(r3,1.0F,0.0F,0.0F);
  glutSolidTorus(0.7,7.2F,18,72);
  glRotatef(90.0F,0.0F,0.0F,1.0F);
  glRotatef(r4,1.0F,0.0F,0.0F);
  glutSolidTorus(0.7,5.8F,18,72);
  glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

void display(void) {
  printf("D\n");
  glClearColor(0.5F,0.5F,0.5F,0.5F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  const GLfloat light0_position[] = { 0.0,0.0,0.0,1.0 };
  const GLfloat light1_position[] = { -1.0,1.0,1.0,0.0 };
  const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };
  glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
  glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
  glLightfv(GL_LIGHT2,GL_POSITION,light2_position);
  glPushMatrix();
  scene();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
  int error = glGetError();
  if ( error != GL_NO_ERROR )
    printf("Attention erreur %d\n",error);
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

void idle(void) {
  printf("I\n");
  r0 += 0.3355F;
  r1 += 0.6117F;
  r2 += 0.4174F;
  r3 += 0.5715F;
  r4 += 0.6433F;
  glutPostRedisplay();
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

void reshape(int x,int y) {
  printf("R\n");
  glViewport(0,0,x,y); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80.0F,(float) x/y,1.0,40.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0,0.0,20.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

void keyboard(unsigned char key,int x,int y) {
  printf("K\n");
  switch (key) {
    case 0x0D :
      { static int anim = 1;
        anim = !anim;
        glutIdleFunc(( anim ) ? idle : NULL); }
      break;
    case ' ' :
      { informationsOpenGL(); }
      break;
    case 0x1B :
      exit(0);
      break; }
}

/* Fonction principale                          */

int main(int argc,char **argv) {
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(300,300);
  glutInitWindowPosition(50,50);
  glutCreateWindow("Des anneaux en rotation");
  init();
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}
