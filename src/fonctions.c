/*
    Copyright (C) 2002
    For non-commercial use only.

    File	: fonction.c
    Date	: 01/06/2002
    Author	: O. El Rhazi, G. Tagorti
    Contact	: senhadjielrhazi@gmail.com
    Projet	: Multimedia
    Ecole	: Ecole Nationale des Ponts et Chausses
*/

#include <stdio.h>
#include <math.h>



//un interpréteur des commandes du joueur pour déplacer les pièces

void interprete(int* depart, int* arrivee)
{
  char* move_request="Saisissez le coup à jouer\n";
  char* move_request_error="Erreur de saisie exemple : A4 b6\n";
  char* nothing_to_do="Il n'y a rien à faire\n";
    
  char c_depart,c_arrivee;  
  char saisie[6]; saisie[5]=0;


  int InputError=1;
  
  do {
    printf(move_request);
    scanf("%6c",saisie);
    saisie[5]=0;
 
    if (sscanf(saisie,"%c%d %c%d",&c_depart,&depart[1],&c_arrivee,&arrivee[1])==4)
      InputError=0;
    if (depart[1]>8 || depart[1] <1 || arrivee[1] < 1 || arrivee[1] >8)
      InputError=1;
    if (depart[1]>8 || depart[1] <1 || arrivee[1] < 1 || arrivee[1] >8)
      InputError=1;
     
    if (!InputError)
      {  
	switch (c_depart)
	  {
	  case 'a':
	    depart[0]=1;
	    break;
	  case 'b':
	    depart[0]=2;
	    break;
	  case 'c':
	    depart[0]=3;
	    break;
	  case 'd':
	    depart[0]=4;
	    break;
	  case 'e':
	    depart[0]=5;
	    break;
	  case 'f':
	    depart[0]=6;
	    break;
	  case 'g':
	    depart[0]=7;
	    break;      
	  case 'h':
	    depart[0]=8;
	    break;
	  default:
	    InputError=1;
	    break;
	  }
      }
    if (!InputError)
      {
	switch (c_arrivee)
	  {
	  case 'a':
	    arrivee[0]=1;
	    break;
	  case 'b':
	    arrivee[0]=2;
	    break;
	  case 'c':
	    arrivee[0]=3;
	    break;
	  case 'd':
	    arrivee[0]=4;
	    break;
	  case 'e':
	    arrivee[0]=5;
	    break;
	  case 'f':
	    arrivee[0]=6;
	    break;
	  case 'g':
	    arrivee[0]=7;
	    break;      
	  case 'h':
	    arrivee[0]=8;
	    break;
	  default:
	    InputError=1;
	    break;
	  }
      }
    if (!InputError && depart[0]==arrivee[0] && depart[1]==arrivee[1])
      {
	printf(nothing_to_do);
	InputError=1;
      }

  } while(InputError && printf(move_request_error));
  return;

}
//Calcul de la norme d'un vecteur

inline double norme(double* vecteur)
{
  return sqrt(vecteur[0]*vecteur[0]+vecteur[1]*vecteur[1]+vecteur[2]*vecteur[2]);
}

//Calculer l'angle entre deux vecteurs
inline double angle(double* vecteur1, double* vecteur2)
{
  double produit_scalaire=vecteur1[0]*vecteur2[0]+vecteur1[1]*vecteur2[1]+vecteur1[2]*vecteur2[2];
  return (180*(acos(produit_scalaire/(norme(vecteur1)*norme(vecteur2)))/M_PI));
}


#if 0
int main()

{
  int de[2];
  int ar[2];
  interprete(de,ar);
  printf("%d%d,%d%d\n",de[0],de[1],ar[0],ar[1]);
  return 0;
}
#endif
