#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 50
#define NB_PREDATEURS 50
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.2;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe= -9;


int main(void) {
 
  /* A completer. Part 2:*/
  //Initialisations variable, etc
  Animal *liste_proies = NULL;
  int cpt_proies = 0;

  Animal *liste_predateurs = NULL;
  int cpt_pred = 0;

  int energie=10;
  unsigned int cptAnimals=0;

  int monde[SIZE_X][SIZE_Y];
  for(int i=0; i<SIZE_X; i++){
    for(int j=0; j<SIZE_Y; j++){
      monde[i][j]=0;
    }
  }

  srand(time(NULL));

  FILE *f = fopen("Evol_Pop.txt", "w"); //Ouverture du fichier pour graphique

  //-------------------------Création listes d'animaux----------------------------

  //Création de NB_PROIES proies et NBPREDATEURS predateurs
  for(int i=0;i<NB_PROIES;i++){
     ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie, &liste_proies);
  } 
  cpt_proies = compte_animal_it(liste_proies);
  assert(cpt_proies == NB_PROIES); //Test nombre de proies

  for(int i=0;i<NB_PREDATEURS;i++){
     ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie, &liste_predateurs);
  } 
  cpt_pred = compte_animal_it(liste_predateurs);
  assert(cpt_pred == NB_PREDATEURS); //Test nombre de predateurs

  cptAnimals = cpt_pred + cpt_proies;

  //--------------------------Evolution du monde----------------------------------

  //Histoire
  system("./story.sh || (echo 'Téléchargez cowsay pour avoir une histoire' && sleep 2)");
  afficher_ecosys(liste_proies, liste_predateurs);


  for(int i=0; i<200; i++){  //Boucle raffraichissement
    //Compteurs
    cpt_proies = compte_animal_it(liste_proies);
    cpt_pred = compte_animal_it(liste_predateurs);
    cptAnimals = cpt_pred + cpt_proies;

    //Sauvegarde données dans fichier pour graphe
    fprintf(f,"%d %d %d\n", i, cpt_proies, cpt_pred);

    //Contrôle cpt_proies
    if(cpt_proies == 0){
      printf("Il n'y a plus de proies\n");
      break;
    }

    //Rafraichissments
    rafraichir_monde(monde);
    rafraichir_predateurs(&liste_predateurs, &liste_proies);
    rafraichir_proies(&liste_proies, monde);

    //Affichage avec pause à chaque tour
    usleep(T_WAIT);
    afficher_ecosys(liste_proies, liste_predateurs);
  }

  //Liberation mémoire, fermeture fichiers
  liberer_liste_animaux(liste_predateurs);
  liberer_liste_animaux(liste_proies);
  fclose(f);

  return 0;
}
