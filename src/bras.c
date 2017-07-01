/*
    Copyright (C) 2002
    For non-commercial use only.

    File	: bras.c
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

#define METAL 13

void DrawArm(GLfloat a,GLfloat b,GLfloat h,GLfloat H,GLfloat alpha,GLfloat beta,GLfloat gamma,GLfloat zeta,GLfloat slices)
{

/*********************Paramètres du levier**********************/
  
    
  /***a/4 represente la base du levier, b le rayon du bras, h la hauteur de la base du levier,
      H la heuteur du levier.alpha, beta, gama,zeta represantent des angles de rotations.***/
  

/*******************Definition du materiau********************/

 //couleur de la tache lumineuse à la surface de l'objet
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  // largeur de la tache lumineuse
  GLfloat mat_shininess[] = { 10.0 };
  //couleur renvoyée par l'objet due à la partie ambiante de la source lumineuse
  GLfloat mat_ambient[]= {0.2, 0.2 ,0.2 ,1.0};
  //couleur renvoyée par l'objet due à la couleur de lumière incidente 
  GLfloat mat_diffuse[]={192/256,230/256,211/256,1.0};
  //Pour simuler une sorte de luminescence propre à l'objet
  GLfloat mat_emission[]={0.0,0.0,0.0,1.0};

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  

  /********************Definition de la texture*************/
  
  char* metal="textures/alumox.tga"; 
  loadTGA(metal,METAL);
  
  GLUquadricObj* cone;
  cone=gluNewQuadric();
  
  GLUquadricObj* tige;
  tige=gluNewQuadric();

  GLUquadricObj* rotule;
  rotule=gluNewQuadric();

  GLUquadricObj* disque;
  disque=gluNewQuadric();

  gluQuadricTexture(cone,GL_TRUE); 
  gluQuadricTexture(tige,GL_TRUE);
  gluQuadricTexture(rotule,GL_TRUE);
  gluQuadricTexture(disque,GL_TRUE);
  
  
/*********Debut du dessin**************/
  glMatrixMode(GL_MODELVIEW);
  //glPushMatrix(); //mgt
  GLfloat bras1[4][3] = {
    {-b/2,-b/4,0},
    {-b/2,-b/4,2*b},
    {-b/2,b/4,2*b},
    {-b/2,b/4,0},
  };
  GLfloat bras2[4][3] = {
    {b/2,-b/4,0},
    {b/2,-b/4,2*b},
    {b/2,b/4,2*b},
    {b/2,b/4,0},
  };

  //mise a niveau du bras dans le repere//
  glTranslatef(-a/2,a/2,0);
  /////////////////////////////////////////////
  glPushMatrix(); //ajoute par mgt
  gluCylinder(cone,a/6,a/10,h,slices,slices);//cone
  glTranslatef(0.0,0.0,h);
  gluCylinder(tige,a/10,a/10,H,slices,slices);//tige
  glTranslatef(0.0,0.0,H);
  gluSphere(rotule,1.05*a/10,slices,slices);//rotule0/1
  glRotatef(zeta,0.0,0.0,1.0);
  glRotatef(alpha,1.0,1.0,0.0);
  gluCylinder(tige,b,b,2*a/3,slices,slices);//bras du levier01
  glTranslatef(0.0,0.0,2*a/3);
  gluSphere(rotule,b,slices,slices);//rotule1/2
  glRotatef(beta,1.0,1.0,0.0);
  gluCylinder(tige,b,b,2*a/3,slices,slices);//bras du levier12
  glTranslatef(0.0,0.0,2*a/3);
  gluSphere(rotule,b,slices,slices);//rotule2/3
  glRotatef(gamma,1.0,1.0,0.0);
  gluCylinder(tige,b,b/2,a/3,slices,slices);//bras du levier23
  glTranslatef(0.0,0.0,a/3);
  gluDisk(disque,0,b/2,slices,slices);//disk du levier
  
  //les mains du levier
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3fv(bras1[0]);
  glTexCoord2f(0.0, 16.0);
  glVertex3fv(bras1[1]);
  glTexCoord2f(16.0, 16.0);
  glVertex3fv(bras1[2]);
  glTexCoord2f(16.0, 0.0);
  glVertex3fv(bras1[3]);
  glEnd();
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3fv(bras2[0]);
  glTexCoord2f(0.0, 16.0);
  glVertex3fv(bras2[1]);
  glTexCoord2f(16.0, 16.0);
  glVertex3fv(bras2[2]);
  glTexCoord2f(16.0, 0.0);
  glVertex3fv(bras2[3]);
  glEnd();

  glPopMatrix();
}




