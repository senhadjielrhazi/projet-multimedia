/*
    Copyright (C) 2002
    For non-commercial use only.

    File	: echiquier.c
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

#define CHESS_BOARD 1
#define CHESS_BOARD_BOIS 10
#define WHITE_CASE 11
#define BLACK_CASE 12
#define PLAN 18
#define MARBRE 19
#define CIEL 20
#define GALAXY 21
#define BOIS_FOND 22


void DrawChessBoard(GLfloat a,GLfloat e,GLfloat slices)
{
  
  
  /*********************Paramètres de l'echequier**********************/
  
  
  
  /*** e represente l'epesseur de la table d'echec et a ca langeur**/
  
  
  /*******************Definition du materiau************/
  
  //couleur de la tache lumineuse à la surface de l'objet
  GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
  // largeur de la tache lumineuse
  GLfloat mat_shininess[] = { 0.0 };
  //couleur renvoyée par l'objet due à la partie ambiante de la source lumineuse
  GLfloat mat_ambient[]= {0.2, 0.2 ,0.2 ,1.0};
  //couleur renvoyée par l'objet due à la couleur de lumière incidente 
  GLfloat mat_diffuse[]={0.8,0.8,0.8,1.0};
  //Pour simuler une sorte de luminescence propre à l'objet
  GLfloat mat_emission[]={0.0,0.0,0.0,1.0};
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  

  /********************Definition de la texture*************/
  
  char* bois="textures/wood.tga"; 
  loadTGA(bois,CHESS_BOARD_BOIS);

  char* whitesilver="textures/whitecase.tga"; 
  loadTGA(whitesilver,WHITE_CASE);
  
  char* blacksilver="textures/blackcase.tga"; 
  loadTGA(blacksilver,BLACK_CASE);

 

  GLUquadricObj* bord;
  bord=gluNewQuadric();

  GLUquadricObj* coin;
  coin=gluNewQuadric();
  
  gluQuadricTexture(bord,GL_TRUE); 
  gluQuadricTexture(coin,GL_TRUE);
  
  
  /*********Debut du dessin**************/

  //le cadre en bois
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  //mise a niveau de l'echequier sur le repere//
  glTranslatef(0,0,-e);
  /////////////////////////////////////////////
  
  GLfloat floorVertices[4][3] = {
    {0,0,e},
    {a/8,0,e},
    {a/8,a/8,e},
    {0,a/8,e},
  };

  glBindTexture (GL_TEXTURE_2D, CHESS_BOARD_BOIS);
  gluSphere(coin,e,slices,slices);
  glTranslatef(a,0.0,0);
  gluSphere(coin,e,slices,slices);
  glTranslatef(-a,a,0);
  gluSphere(coin,e,slices,slices);
  glTranslatef(a,0,0);
  gluSphere(coin,e,slices,slices);
  glTranslatef(-a,-a,0);
  glRotatef(-90.0,1.0,0.0,0.0);
  gluCylinder(bord,e,e,a,slices,slices);
  glTranslatef(a,0,0);
  gluCylinder(bord,e,e,a,slices,slices);
  glTranslatef(-a,0,0);
  glRotatef(90.0,1.0,0.0,0.0);
  glRotatef(90.0,0.0,1.0,0.0);
  gluCylinder(bord,e,e,a,slices,slices);
  glTranslatef(0,a,0);
  gluCylinder(bord,e,e,a,slices,slices);
  glTranslatef(0,-a,0);
  glRotatef(-90.0,0.0,1.0,0.0);

  
  //le fond de la table en noir et blanc
  
  //premier rang
  int i;
  int j;
  for(i=0;i<4;i++){
    glTranslatef(i*a/4,0,0);
    for(j=0;j<4;j++){ 
      glBindTexture (GL_TEXTURE_2D, WHITE_CASE);
      glColor4f(1,1, 1, 1);
      glTranslatef(0,j*a/4,0);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3fv(floorVertices[0]);
      glTexCoord2f(0.0, 16.0);
      glVertex3fv(floorVertices[1]);
      glTexCoord2f(16.0, 16.0);
      glVertex3fv(floorVertices[2]);
      glTexCoord2f(16.0, 0.0);
      glVertex3fv(floorVertices[3]);
      glEnd();
      glTranslatef(0,-j*a/4,0);
      glBindTexture (GL_TEXTURE_2D, BLACK_CASE);
      glColor4f(0,0, 0, 0);
      glTranslatef(0,j*a/4+a/8,0);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3fv(floorVertices[0]);
      glTexCoord2f(0.0, 16.0);
      glVertex3fv(floorVertices[1]);
      glTexCoord2f(16.0, 16.0);
      glVertex3fv(floorVertices[2]);
      glTexCoord2f(16.0, 0.0);
      glVertex3fv(floorVertices[3]);
      glEnd();
      glTranslatef(0,-j*a/4-a/8,0);
    }
    glTranslatef(-i*a/4,0,0);
  }
  
  //deuxiemme rang

  for(i=0;i<4;i++){
    glTranslatef(i*a/4+a/8,0,0);
    for(j=0;j<4;j++){
      glColor4f(1.0,1.0,0.0,0.0);
      glBindTexture (GL_TEXTURE_2D, BLACK_CASE);
      glColor4f(0,0, 0, 0);
      glTranslatef(0,j*a/4,0);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3fv(floorVertices[0]);
      glTexCoord2f(0.0, 16.0);
      glVertex3fv(floorVertices[1]);
      glTexCoord2f(16.0, 16.0);
      glVertex3fv(floorVertices[2]);
      glTexCoord2f(16.0, 0.0);
      glVertex3fv(floorVertices[3]);
      glEnd();
      glTranslatef(0,-j*a/4,0);
      glBindTexture (GL_TEXTURE_2D, WHITE_CASE);
      glColor4f(1,1, 1, 1);
      glTranslatef(0,j*a/4+a/8,0);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3fv(floorVertices[0]);
      glTexCoord2f(0.0, 16.0);
      glVertex3fv(floorVertices[1]);
      glTexCoord2f(16.0, 16.0);
      glVertex3fv(floorVertices[2]);
      glTexCoord2f(16.0, 0.0);
      glVertex3fv(floorVertices[3]);
      glEnd();
      glTranslatef(0,-j*a/4-a/8,0);
    }
    glTranslatef(-i*a/4-a/8,0,0);
  }
  glPopMatrix();
  //glEndList();
}





