#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=1.0;
float p_reproduce_predateur=1.0;
int temps_repousse_herbe=-15;


int main(void) {

  Animal *liste_proies = NULL;
  Animal *liste_predateurs = NULL;

  int energie=10;
  unsigned int cptAnimals=0;

  srand(time(NULL));

  //Création animal au bord du monde
  Animal *a1 = creer_animal(10,25, energie);
  a1->x = 19;
  a1->y = 49;
  a1->dir[0] = 1;
  a1->dir[1] = 1;
  liste_proies = a1;
  liste_proies->suivant = NULL;

  printf("Avant bouger, a1->x = %d, a1->y = %d, a1->dir[0] = %d, a1->dir[1] = %d\n", a1->x, a1->y, a1->dir[0], a1->dir[1]);

  cptAnimals+=compte_animal_rec(liste_proies);
  assert(cptAnimals==1);

  afficher_ecosys(liste_proies, liste_predateurs); //Affichage de l'animal après test de ces coordonnées

  bouger_animaux(a1);
  printf("Apres bouger, a1->x = %d, a1->y = %d, a1->dir[0] = %d, a1->dir[1] = %d\n", a1->x, a1->y, a1->dir[0], a1->dir[1]);

  afficher_ecosys(liste_proies, liste_predateurs); //Affichage de l'animal après l'avoir bougé

  //Test de la reproduction
  printf("------Reproduction------------\n");

  reproduce(&liste_proies, p_reproduce_proie); //Reproduction de l'animal a 100% de chance
  afficher_ecosys(liste_proies, liste_predateurs);

  bouger_animaux(a1); //Deplacement de l'animal pour montrer les 2 animaux séparés
  afficher_ecosys(liste_proies, liste_predateurs);

  //Libération mémoire
  liberer_liste_animaux(liste_predateurs);
  liberer_liste_animaux(liste_proies);

  return 0;
}
