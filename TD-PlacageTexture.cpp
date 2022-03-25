/* Placage d'une texture sur un rectangle       */
/* ou sur un cylindre                           */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Fevrier 2021                                 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "PNG/ChargePngFile.h"
/* Variables et constantes globales             */

static const float blanc[]       = { 1.0F,1.0F,1.0F,1.0F };
static const float noir[]        = { 0.0F,0.0F,0.0F,1.0F };

static int illumination = 1;
static int deuxFaces = 1;
static int anim = 0;
static int question = 0;
static int texture = 1;
static float rx = 0.0F;
static float ry = 0.0F;
static float rz = 0.0F;

//////////////////////////////////////////////////

static unsigned int textureID = 0;

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static unsigned char *image(int nc,int nl) {
  unsigned char *img =(unsigned char *) calloc(3*nc*nl,sizeof(unsigned char));
  if ( !img )
    return NULL;
  unsigned char *p = img;
  for ( int l = 0 ; l < nl ; l++ )
    for ( int c = 0 ; c < nc ; c++ ) {
      if ( l%2 == 0 ) {
        if ( c%2 == 0 ) {
          p[0] = 0x00;
          p[1] = 0x00;
          p[2] = 0x00; }
          else {
          p[0] = 0xFF;
          p[1] = 0x00;
          p[2] = 0x00; } }
        else {
        if ( c%2 == 0 ) {
          p[0] = 0x00;
          p[1] = 0xFF;
          p[2] = 0x00; }
          else {
          p[0] = 0x00;
          p[1] = 0x00;
          p[2] = 0xFF; } }
      p += 3; }
  return img;
}

static void initTexture(void) {
  glPixelStorei(GL_UNPACK_ALIGNMENT,1); 
  glGenTextures(1,&textureID);
  glBindTexture(GL_TEXTURE_2D,textureID);
  { //int rx = 16;
    //int ry = 16;
    char *nomFichier = "Test.png";
    int rx;
    int ry;
    printf("%s\n", nomFichier);
    unsigned char* img = chargeImagePng(nomFichier, &rx, &ry);
    if ( img ) {
      glTexImage2D(GL_TEXTURE_2D,0,3,rx,ry,0,GL_RGB,GL_UNSIGNED_BYTE,img);
      free(img);
      printf("Texture chargee %d\n",textureID); }
      else {
      glDeleteTextures(1,&textureID);
      textureID = 0;
      printf("Texture non chargee\n"); } }
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
}

static void init(void) {
  glClearColor(0.25F,0.25F,0.25F,1.0F);
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,noir);
  initTexture();
}

/* Dessin d'un rectangle                        */

static void rectangle(float largeur,float hauteur) {
  largeur /= 2.0F;
  hauteur /= 2.0F;
  glPushMatrix();
  glBegin(GL_QUADS);
  glNormal3f(0.0F,0.0F,1.0F);
  glTexCoord2f(0.0F,0.0F);
  glVertex3f(-largeur,-hauteur,0.0F);
  glTexCoord2f(1.0F,0.0F);
  glVertex3f(largeur,-hauteur,0.0F);
  glTexCoord2f(1.0F,1.0F);
  glVertex3f(largeur,hauteur,0.0F);
  glTexCoord2f(0.0F,1.0F);
  glVertex3f(-largeur,hauteur,0.0F);
  glEnd();
  glPopMatrix();
}

/* Dessin d'un cylindre                         */

#ifndef M_PI
  #define M_PI 3.14159
#endif

static void mySolidCylinder(double hauteur,double rayon,int ns) {
  glPushMatrix();
  hauteur /= 2.0F;
  glBegin(GL_QUAD_STRIP);
  for ( int i = 0 ; i <= ns ; i++ ) {
    float rp =(float) i/ns;
    float a = 2.0*M_PI*rp;
    float cs = cos(a);
    float sn = -sin(a); 
    glNormal3f(cs,0.0F,sn);
    float x = rayon*cs;
    float z = rayon*sn;
    glTexCoord2f(rp,1.0F);
    glVertex3f(x,hauteur,z);
    glTexCoord2f(rp,0.0F);
    glVertex3f(x,-hauteur,z); }
  glEnd();
  glPopMatrix();
}

/* Scene dessinee : rectangle                    */

static void sceneRectangle() {
  glPushMatrix();
  rectangle(7.5F,5.0F);
  glPopMatrix();
}

/* Scene dessinee : cylindre                    */

static void sceneCylindre() {
  glPushMatrix();
  mySolidCylinder(5.0,2.5,72);
  glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  if ( texture ) 
    glEnable(GL_TEXTURE_2D);
    else
    glDisable(GL_TEXTURE_2D);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,( deuxFaces ) ? 1 : 0);
  if ( illumination )
    glEnable(GL_LIGHTING);
    else
    glDisable(GL_LIGHTING);
  const GLfloat light0_position[] = { 0.0,0.0,1.0,0.0 };
  glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
  glRotatef(rx,1.0F,0.0F,0.0F);
  glRotatef(rz,0.0F,0.0F,1.0F);
  glRotatef(ry,0.0F,1.0F,0.0F);
  switch (question) {
    case 0 :
      sceneRectangle();
      break;
    case 1 :
      sceneCylindre();
      break; }
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
  int error = glGetError();
  if ( error != GL_NO_ERROR )
    printf("Erreur OpenGL: %d\n",error);
}

/* Desallocation de la texture                  */

static void clean(void) {
  if ( textureID != 0 )
    glDeleteTextures(1,&textureID);
}

//////////////////////////////////////////////////

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */
/* -> Ajustement de la camera de visualisation  */

static void reshape(int tx,int ty) {
  glViewport(0,0,tx,ty); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double ratio =(double) tx/ty;
  if ( ratio >= 1.0 )
    gluPerspective(50.0,ratio,0.01,200.0);
    else
    gluPerspective(50.0/ratio,ratio,0.01,200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0,0.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

static void idle(void) {
  rx += 0.51F;
  ry += 0.28F;
  rz += 0.37F;
  glutPostRedisplay();
}

/* Fonction executee lors de la frappe          */
/* d'une touche du clavier                      */

static void keyboard(unsigned char key,int x,int y) {
  switch ( key ) {
    case 'd' :
      deuxFaces = !deuxFaces;
      glutPostRedisplay(); 
      break;
    case 'l' :
      illumination = !illumination;
      glutPostRedisplay(); 
      break;
    case 'a' :
      anim = !anim;
      glutIdleFunc(( anim ) ? idle : NULL);
      break;
    case 0x0D :
      question = (question+1)%2;
      glutPostRedisplay(); 
      break;
    case 0x20 :
      texture = (texture+1)%2;
      glutPostRedisplay(); 
      break;
    case 0x1B :
      exit(0); 
      break; }
}

/* Fonction principale                          */

int main(int argc,char **argv) {

  atexit(clean);

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(480,360); 
  glutInitWindowPosition(50,50); 
  glutCreateWindow("Plaçage d'une texture"); 
  init();
  glutIdleFunc(( anim ) ? idle : NULL);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMainLoop();

      /* { char nomFichier[32] = "Test.png";
      int rx;
      int ry;
      printf("%s\n", nomFichier);
      unsigned char* img = chargeImagePng(nomFichier, &rx, &ry);
      if (img) {
          printf("Resolution en x : %8d\n", rx);
          printf("Resolution en y : %8d\n", ry);
          printf("Adresse         : %p, %d octets\n", img, 3 * rx * ry);
          free(img);
      }
      else {
          printf("Adresse         : %p\n", img);
      } }
      printf("\n");
      getchar();
      */
      return 0;
  }
