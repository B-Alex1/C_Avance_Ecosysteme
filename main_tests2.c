#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;

int main(void) {

  Animal *liste_proies = NULL;
  Animal *liste_predateurs = NULL;
  int energie=10;
  unsigned int cptAnimals=0;

  srand(time(NULL));

    Animal *a1 = creer_animal(10,25, energie);
    liste_proies = a1;
    liste_proies->suivant = NULL;

  for(int i=0;i<20;i++){
     ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie, &liste_proies);
  } 

  for(int j=0;j<20;j++){
     ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie, &liste_predateurs);
  }


  cptAnimals+=compte_animal_rec(liste_proies);
  assert(cptAnimals==21);

  cptAnimals+=compte_animal_rec(liste_predateurs);
  assert(cptAnimals==41);

  afficher_ecosys(liste_proies, liste_predateurs);

  enlever_animal(&liste_proies, a1);
  afficher_ecosys(liste_proies, liste_predateurs);

  enlever_animal(&liste_proies, liste_proies->suivant->suivant->suivant);
  afficher_ecosys(liste_proies, liste_predateurs);

  printf("---------------------\n");

  ecrire_ecosys("ecosys_main-tests2.txt", liste_proies, liste_predateurs);

  Animal *liste_proies2 = NULL;
  Animal *liste_predateurs2 = NULL;
  lire_ecosys("ecosys_main-tests2.txt", &liste_proies2, &liste_predateurs2);
  afficher_ecosys(liste_proies2, liste_predateurs2);

  liberer_liste_animaux(liste_predateurs);
  liberer_liste_animaux(liste_proies);
  liberer_liste_animaux(liste_predateurs2);
  liberer_liste_animaux(liste_proies2);

  return 0;
  
}