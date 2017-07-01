/*
    Copyright (C) 2002
    For non-commercial use only.

    File	: pion.c
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

#define PION_BOIS 9


// dessiner le pion  

void DrawPion(GLfloat param)
{
  //#if 0
  // glNewList(materiau, GL_COMPILE);
  /*******************Definition du materiau************/
  
  //couleur de la tache lumineuse à la surface de l'objet
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  // largeur de la tache lumineuse
  GLfloat mat_shininess[] = { 50.0 };
  //couleur renvoyée par l'objet due à la partie ambiante de la source lumineuse
  GLfloat mat_ambient[]= {0.305, 0.115 ,0.05 ,1};
  //couleur renvoyée par l'objet due à la couleur de lumière incidente 
  GLfloat mat_diffuse[]={0.305,0.115,0.05,1.0};
  //Pour simuler une sorte de luminescence propre à l'objet
  GLfloat mat_emission[]={0.0,0.0,0.0,1.0};
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
  //glEndList();
  //#endif
/*********************Paramètres du Pion**********************/
  
  GLint slices=50;
  
  //glNewList(texture,GL_COMPILE);
  
  /********************Definition de la texture*************/
  
  char* bois="textures/wood3.tga"; 
  loadTGA(bois,PION_BOIS);
  
  GLUquadricObj* tete;
  tete=gluNewQuadric();

  GLUquadricObj* tige;  
  tige=gluNewQuadric();

  GLUquadricObj* base;
  base=gluNewQuadric();

  GLUquadricObj* socle;
  socle=gluNewQuadric();

  GLUquadricObj* couronne;
  couronne=gluNewQuadric();

  GLUquadricObj* disque1;
  disque1=gluNewQuadric();

  GLUquadricObj* disque2;
  disque2=gluNewQuadric();
  //#if 0
  gluQuadricTexture(tige,GL_TRUE);
  gluQuadricTexture(tete,GL_TRUE);
  gluQuadricTexture(base,GL_TRUE);
  gluQuadricTexture(socle,GL_TRUE);
  gluQuadricTexture(couronne,GL_TRUE);
  gluQuadricTexture(disque1,GL_TRUE);
  gluQuadricTexture(disque2,GL_TRUE);
  //#endif
  //glEndList();
/*********Debut du dessin**************/


  
  //glNewList(dessin,GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  
 
  gluSphere(tete,param,slices,slices);
 
  glRotatef(-90.0,1.0,0.0,0.0);
  glTranslatef(0.0,0.0,-5.0*param);
  gluCylinder(tige,0.5*param,0.5*param,5*param,slices,slices);//tige
  glTranslatef(0.0,0.0,-2.0*param);
  gluCylinder(base,2.5*param,0.5*param,2*param,slices,slices);
  glTranslatef(0.0,0.0,-0.5*param);
  gluCylinder(socle,2.5*param,2.5*param,0.5*param,slices,slices);//base
  gluDisk(disque1,0,2.5*param,slices,slices);
  glTranslatef(0.0,0.0,4*param);
  gluCylinder(couronne,0.5*param,1.5*param,1*param,slices,slices);//couronne
  glTranslatef(0.0,0.0,param);
  gluDisk(disque2,0,1.5*param,slices,slices);
  glPopMatrix();
  
  //glEndList();

  // glCallList(materiau);
  //glCallList(texture);
  //glCallList(dessin);
}

