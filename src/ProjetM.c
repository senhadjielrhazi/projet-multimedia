/*
    Copyright (C) 2002
    For non-commercial use only.

    File	: ProjetM.c
    Date	: 01/06/2002
    Author	: O. El Rhazi, G. Tagorti
    Contact	: senhadjielrhazi@gmail.com
    Projet	: Multimedia
    Ecole	: Ecole Nationale des Ponts et Chausses
*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include "tga.h"
#include "assert.h"

#define PLAN 18
#define MARBRE 19
#define CIEL 20
#define GALAXY 21
#define BOIS_FOND 22

GLdouble phi=50;
GLfloat r=10;
GLfloat theta=0;

GLint materiau=1;
GLint texture=2;
GLint dessin =3;
GLfloat slices=50;

/****paramètres du l'échiquier********/

GLfloat a=4.0;
GLfloat e=0.5;

/************Lumière******************/

GLfloat light_ambient[]= {1.0,1.0,1.0,1.0};
GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
GLfloat height=6.0;
GLfloat spot_direction[]= {0.0,0.0,-1.0};

/************paramètres du bras*******/

GLfloat zeta=10;
GLfloat alpha=45;
GLfloat beta=40;
GLfloat gama=60;

/***********Stockage des paramètres du mouvement******/

typedef struct pos_carac
{
  float zeta;
  float alpha;
  float beta;
  float gama; 
} pos_carac;

pos_carac* table;

/***paramètres du pion**/

int pion_pos[2]={8,1};
int scene_change=1;


/***paramètres de changement de point de vue*******/
int debut;
int mvt=0;

/**paramètres du mouvement***/
int pas=1,k;

/***tetxures du fond ***/

char* water="textures/water.tga";
char* marbre="textures/marble2.tga"; 
char* boisfond="textures/coppwir.tga"; 
char* galaxy="textures/galaxy.tga"; 

char* plan_fond;
/********Déclarations de fonctions*********/

void DrawArm(GLfloat a,GLfloat b,GLfloat h,GLfloat H,GLfloat alpha,GLfloat beta,GLfloat gama,GLfloat zeta,GLfloat slices);
void DrawChessBoard(GLfloat a,GLfloat e,GLfloat slices);
void DrawPion(GLfloat a);
inline double angle(double* vecteur1, double* vecteur2);
void interprete(int* depart, int* arrivee);
inline double norme(double* vecteur);
void display();
void posPrecalc(pos_carac* table);
void Idle();
void vitesse_chg(int valeur);
void texture_chg(int valeur);
 
void myinit()
{
 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable (GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_SMOOTH);
  glBindTexture(GL_TEXTURE_2D,PLAN);
  glClearColor(0.0,0.0,0.0,1.0);
  table=(pos_carac*)malloc(8*8*sizeof(pos_carac));
  plan_fond=water;
  posPrecalc(table);
}

SetLight(GLfloat* position, GLfloat* ambient, GLfloat* diffuse, GLfloat* direction, GLfloat spotlarg)
{
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotlarg);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,direction);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  
  //déclenche le calcul pour la lumière
  glEnable(GL_LIGHTING);
  //allume la source lumineuse GL_LIGHT0
  glEnable(GL_LIGHT0);
}
//Calculer zeta alpha beta gamma pour les différentes positions de l'échiquier

void posPrecalc(pos_carac* table)
{
  /* Cette fonction effectue tous les calculs 
     des angles zeta, alpha, beta, gamma pour
     rendre le jeu plus rapide*/

  // paramètres du bras

  double l1=2*a/3; 
  double l2=2*a/3;
  double l3=a/3;
  double default_pos[]={a/2,-a/2,0};


  // les variables d'angle locales
  
  float zeta=0; 
  float alpha=45; 
  float gama=40;
  float beta=60;

  //les variables de la boucle
  int i;
  int j;

  // Des constantes pour le calcul

  for(i=0;i<8;i++) {
    
    for(j=0;j<8;j++) {
      //printf("point : %d , %d\n",i,j);
      
      double point_depart[]={a*i/8+a/2+a/16,a*j/8-a/2+a/16,0};
      double dis=norme(point_depart);
      
     //Calcul de l'angle zeta
  
      zeta=angle(default_pos,point_depart);
      double zeta_rad=M_PI*zeta/180;
      //printf("zeta=%f\n",zeta);
      
      //Calcul de l'angle alpha

      double alpha_rad;
      assert(dis < (l1+l2+l3));
      
      double c1=(l1*l1+dis*dis-(l2+l3)*(l2+l3))/(2*l1*dis);
      assert(c1 <1);
      c1=(c1<0) ? 0 :c1;


      double c2=(l1*l1+dis*dis-(l2-l3)*(l2-l3))/(2*l1*dis);
      assert(c2 >0);
      c2=(c2>1) ? 1 :c2;
     
            
      alpha_rad=(asin(c1)+asin(c2))*0.5; 
      alpha=180*(alpha_rad)/M_PI;
      //printf("alpha=%f\n",alpha);

      double d=sqrt(l1*l1+dis*dis-2*dis*l1*sin(alpha_rad));
      assert((l3*l3-l2*l2-d*d)/(2*l2*d) < 1);
      //printf("tfouh=%f\n",(l3*l3-l2*l2-d*d)/(2*l2*d));
      assert((l3*l3-l2*l2-d*d)/(2*l2*d) > -1);
      
      //Calcul de l'angle beta
      //#if 0      

      double beta_rad;
      double interm=((l1-a*sin(alpha_rad))/d > 0) ? asin(dis*cos(alpha_rad)/d):(M_PI-asin(dis*cos(alpha_rad)/d)); 
      beta_rad=acos((l3*l3-l2*l2-d*d)/(2*l2*d))-interm;
      beta=180*(beta_rad)/M_PI;
      
 
      
      //      double point12[]={l1*sin(alpha_rad)*cos(zeta_rad-M_PI_2)-a/2-point_depart[0],
      //			l1*sin(alpha_rad)*sin(zeta_rad-M_PI_2)+a/2-point_depart[1],
      //		l1*cos(alpha_rad)};
      //printf("%f,%f,%f\n",point12[0],point12[1],point12[2]);
      //float d=norme(point12);//distance au carre entre 1/2 et le point final
      //assert(norme(point12) < (l2+l3));
      //printf("d=%f\n",(d*d-l3*l3+l2*l2)/(2*l2*d));
      //beta+=180*(acos((d*d-l3*l3+l2*l2)/(2*l2*d))*0.95)/M_PI;
      //printf("beta=%f\n",beta);
      //#endif 

      //Calcul de l'angle gama
      double vect1[]={l2*sin(alpha_rad+beta_rad),l2*cos(alpha_rad+beta_rad)};
      double vect2[]={dis-l1*sin(alpha_rad)-l2*sin(alpha_rad+beta_rad),-l1*cos(alpha_rad)-l2*cos(alpha_rad+beta_rad)};
      
      gama=angle(vect1,vect2);
      //printf("gama=%f\n",gama);
      //Stocker tous dans la table
      table[8*i+j].zeta=zeta;
      table[8*i+j].alpha=alpha;
      table[8*i+j].beta=beta;
      table[8*i+j].gama=gama;
    } 
  }
}

void move(int* depart, int* arrivee)
{
  /*
    La fonction move fonctionne comme suit:
    -On calcule les caractéristiques (les angles alpha, beta, 
    gama, zeta) du bras à l'état finale.
    -On fait évoluer ces valeurs de façons linéaires et on parallèle
    pour avoir un mouvement le plus fluide possible du bras
  */
  // tester s'il y a un pion en depart

  if (depart[0]!=pion_pos[0] || depart[1]!=pion_pos[1]) {
    printf("il n'y a de pièce dans cette position\n");
    return;
  }
  
  double zeta_default=zeta;
  double alpha_default=alpha;
  double beta_default=beta;
  double gama_default=gama;

  //nombre de frame


  // Coordonnees du point de départ et d'arrivé dans le repère du bras;

  int i=depart[0]-1;
  int j=depart[1]-1;

  for (k=0; k< pas; k++)
    {
      zeta+=(table[8*i+j].zeta-zeta_default)/pas;
      alpha+=(table[8*i+j].alpha-alpha_default)/pas;
      beta+=(table[8*i+j].beta-beta_default)/pas;
      gama+=(table[8*i+j].gama-gama_default)/pas;
      
      display();
    }
  
  i=arrivee[0]-1;
  j=arrivee[1]-1;

  zeta=table[8*i+j].zeta;
  alpha=table[8*i+j].alpha;
  beta=table[8*i+j].beta;
  gama=table[8*i+j].gama;
  
  pion_pos[0]=arrivee[0]; 
  pion_pos[1]=arrivee[1];
  display();

  //position initiale
    for (k=0; k< pas; k++)
    {
      zeta+=(-table[8*i+j].zeta+zeta_default)/pas;
      alpha+=(-table[8*i+j].alpha+alpha_default)/pas;
      beta+=(-table[8*i+j].beta+beta_default)/pas;
      gama+=(-table[8*i+j].gama+gama_default)/pas;
      display();
    }
}

void plan()
{ 
 /**definition du plan***/

  loadTGA(plan_fond,PLAN);
  
  
  //glBindTexture(GL_TEXTURE_2D,PLAN);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(0.0,0.0,-e);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);glVertex3f(-10.0*a,10*a,0.0);
  glTexCoord2f(64.0, 0.0);glVertex3f(-10.0*a,-10*a,0.0);
  glTexCoord2f(0.0, 64.0);glVertex3f(10.0*a,-10*a,0.0);
  glTexCoord2f(64.0,64.0);glVertex3f(10.0*a,10*a,0.0);
  glEnd();
  glPopMatrix();

}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
   //DrawPion(0.5); 
  
  GLfloat spotlarg=6*(atan(a/(2*height))/(M_PI))*180;
  GLfloat light_position[] = {a/2,a/2,height,1.0};

  
  SetLight(light_position, light_ambient, light_diffuse, spot_direction, spotlarg);
  
  plan();
  DrawChessBoard(a,e,slices);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef((pion_pos[0]-1)*a/8+a/16,(pion_pos[1]-1)*a/8+a/16,0.0);
  glRotatef(90.0,1.0,0.0,0.0);
  glTranslatef(0.0,7.5*(a/40),0.0);
  DrawPion(a/40);  
  glPopMatrix();
  
  glPushMatrix(); 
  //DrawArm(GLfloat a,GLfloat b,GLfloat h,GLfloat H,GLfloat alpha,GLfloat beta,GLfloat gama,GLfloat zeta,GLfloat slices);
  glTranslatef(0.0,0.0,-e);
  DrawArm(a,2.5*(a/40),e,7.5*a/40,alpha,beta,gama,zeta,slices);
  //glTranslatef(0.0,5.0,0.0);  
  //DrawArm(135.0,0,5,7,1);
  //glCallList(materiau);
  //glCallList(texture);
  //glCallList(dessin);
  //DrawPion(0.5); 
  glPopMatrix(); 
  glutSwapBuffers();
 
}
void chg_ptvue(int value)
{ 
  switch (value) {
    
  case 1:
    theta-=10;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(r*sin(phi*M_PI/180)*cos(theta*M_PI/180)+a/2,r*sin(phi*M_PI/180)*sin(theta*M_PI/180)+a/2,r*cos(phi*M_PI/180),a/2,a/2,0.0,-cos(phi*M_PI/180)*cos(theta*M_PI/180),-cos(phi*M_PI/180)*sin(theta*M_PI/180),sin(phi*M_PI/180));    
  glutPostRedisplay();      
  break;
  case 2:
    theta+=10;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(r*sin(phi*M_PI/180)*cos(theta*M_PI/180)+a/2,r*sin(phi*M_PI/180)*sin(theta*M_PI/180)+a/2,r*cos(phi*M_PI/180),a/2,a/2,0.0,-cos(phi*M_PI/180)*cos(theta*M_PI/180),-cos(phi*M_PI/180)*sin(theta*M_PI/180),sin(phi*M_PI/180));    
    glutPostRedisplay();      
    break; 
  }
}
void menu(int value)
{
  switch(value)
    {
    case 2:
      Idle();
      break;
    case 5:
      printf("Merci! Au revoir\n");
      exit(0);
      break;
    }
} 
void requete()
{
  int vitesse_change=glutCreateMenu(vitesse_chg);
  glutAddMenuEntry("diminuer",3);
  glutAddMenuEntry("augmenter",4);

  int texture=glutCreateMenu(texture_chg);
  glutAddMenuEntry("marbre",1);
  glutAddMenuEntry("cuivre",2); 
  glutAddMenuEntry("galaxy",3);
  glutAddMenuEntry("eau",4);

  int chgpoinvue=glutCreateMenu(chg_ptvue);
  glutAddMenuEntry("gauche",1);
  glutAddMenuEntry("droite",2);

  glutCreateMenu(menu);
  glutAddSubMenu("changer le point de vue", chgpoinvue);
  glutAddMenuEntry("jouer", 2);
  glutAddSubMenu("vitesse", vitesse_change);
  glutAddSubMenu("texture", texture);
  glutAddMenuEntry("Quitter", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON); 
}
void vitesse_chg(int valeur)
{
  switch(valeur)
   {
   case 3:
     pas+=2;
     printf("la vitesse est de %d images pour le déplacement\n",pas); 
     break;
   case 4:
     if (pas >= 3)
       {
	 pas-=2;
	 printf("la vitesse est de %d images pour le déplacement\n",pas); 
       }
     else
       {
	 printf("la vitesse est deja maximale\n");
       }
     break;
   }
}

void texture_chg(int valeur)
{
  switch(valeur)
    {
    case 1: 
      plan_fond=marbre;
      break;
    case 2:
      plan_fond=boisfond;
      break;
    case 3:
      plan_fond=galaxy;
       break;
    case 4:
      plan_fond=water;
      break;
   }
  display();
}
void Idle()
{
  //theta+=0.05;
  display();
  int de[2];
  int ar[2];
  interprete(de,ar);
  move(de,ar);
 
 
  // glPushMatrix();
  // display();
   //glPopMatrix();
  //gluLookAt(r*sin(phi)*cos(theta)+a/2,r*sin(phi)*sin(theta)+a/2,r*cos(phi),a/2,a/2,0.0,-cos(phi)*cos(theta),-cos(phi)*sin(theta),sin(phi));    
  //DrawPion(0.5);
  //glutPostRedisplay();
}
void myreshape(GLsizei w, GLsizei h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  gluLookAt(r*sin(phi*M_PI/180)*cos(theta*M_PI/180)+a/2,r*sin(phi*M_PI/180)*sin(theta*M_PI/180)+a/2,r*cos(phi*M_PI/180),a/2,a/2,0.0,-cos(phi*M_PI/180)*cos(theta*M_PI/180),-cos(phi*M_PI/180)*sin(theta*M_PI/180),sin(phi*M_PI/180));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45,1,1,50);
}
 
main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowPosition (0, 0);
  glutInitWindowSize(500,500);
  glutCreateWindow("pion");
  myinit();
  glutReshapeFunc(myreshape);
  glutDisplayFunc(display);
  requete();
  glutMainLoop();
  return 0;
}
