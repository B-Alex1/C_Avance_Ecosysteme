#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "ecosys.h"




/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  //Controle coordonnées de l'animal
  assert(x<SIZE_X && x>=0);
  assert(y<SIZE_Y && y>=0);

  Animal *a1 = creer_animal(x,y, energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, a1);
}

/* A Faire. Part 1, exercice 6, question 7 */
void enlever_animal(Animal **liste, Animal *animal) {
  if(!liste || !(*liste))
    return;

  Animal *tmp, *prec, *ani = *liste;

  if(ani == animal){ //Cas où l'animal à retirer est le premier de la liste
    tmp = *liste;
    ani = (*liste)->suivant;
    free(tmp);
    *liste = ani;
    return;
  }

  while(ani){ //Cas où l'animal à retirer est au milieu ou à la fin de la liste
    tmp = ani->suivant; //Pour ne pas perdre ce pointeur si ani doit être supprimé

    if(ani == animal){
      prec->suivant = tmp;
      free(ani);
      return ;
    }
    prec = ani; //Pour pouvoir sauter l'animal de la liste qu'il faut supprimer
    ani = tmp;
  }

  return ;
}

/* A Faire. Part 1, exercice 6, question 5 */
Animal* liberer_liste_animaux(Animal *liste) {
  if(!liste)
    return NULL;

  Animal *tmp;
   
  while(liste){
   tmp = liste;
   liste = liste->suivant;
   free(tmp);
  }

  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  while(la){
    if((float)(rand()/RAND_MAX)<p_ch_dir){ //Assigne directions
      la->dir[0] = (rand()%3)-1;
      la->dir[1] = (rand()%3)-1;
    }
    //Assurer qu'un animal ne sort pas du monde
    la->x = ((la->x)+(la->dir[0])+SIZE_X)%SIZE_X;
    la->y = ((la->y)+(la->dir[1])+SIZE_Y)%SIZE_Y;

    la = la->suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *ani = *liste_animal;

  while(ani){
    if((float)(rand())/RAND_MAX < p_reproduce){ //Assure que la reproduction se produise avec p_reproduce de chances
      ajouter_animal(ani->x, ani->y, (ani->energie)/2, liste_animal);
      ani->energie /= 2.0;
    }
    ani = ani->suivant;
  }
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    if(!liste_proie || !(*liste_proie)){
      return;
    }

    bouger_animaux(*liste_proie); //Etape 1

    Animal *tmp, *ani = *liste_proie;
    int herbe;
    while(ani){
      herbe = monde[ani->x][ani->y]; //Etape 2
      if(herbe > 0){
        ani->energie += herbe;
        monde[ani->x][ani->y] = temps_repousse_herbe;
      }
      ani->energie -= 1;
      tmp = ani->suivant; //Afin de ne pas perdre cette adresse si nous supprimons ani
      if(ani->energie < 0){
        enlever_animal(liste_proie, ani);
      }
      ani = tmp;
    }

    reproduce(liste_proie, p_reproduce_proie); //Etape 3
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *liste, int x, int y) {
  while(liste){
    if(liste->x == x && liste->y == y){
      return liste;
    }
    liste=liste->suivant;
  }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   if(!liste_predateur || !(*liste_predateur)){
      return;
    }

    bouger_animaux(*liste_predateur); //Etape 1

    Animal *proie, *tmp, *ani = *liste_predateur;
    while(ani){
      proie = animal_en_XY(*liste_proie, ani->x, ani->y); //Etape 2
      if(proie){
        ani->energie += proie->energie;
        enlever_animal(liste_proie, proie);
      }
      ani->energie -= 1;
      tmp = ani->suivant; //Afin de ne pas perdre cette adresse si nous supprimons ani
      if(ani->energie < 0){
        enlever_animal(liste_predateur, ani);
      }
      ani = tmp;
    }

    reproduce(liste_predateur, p_reproduce_predateur); //Etape 3

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for(int i=0; i<SIZE_X; i++){
    for(int j=0; j<SIZE_Y; j++){
      monde[i][j] += 1;
    }
  }
}

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateurs, Animal *liste_proies){
  FILE *f = fopen(nom_fichier, "w");
  if(f==NULL){
    printf("Erreur ouverture %s\n", nom_fichier);
    return;
  }
  Animal *ani;

  //Ecriture proies
  fprintf(f,"<proies>\n");
  ani = liste_proies;
  while(ani){
    fprintf(f,"x=%d y=%d dir=[%d %d] e=%.2f\n", ani->x, ani->y, ani->dir[0], ani->dir[1], ani->energie);
    ani = ani->suivant;
  }
  fprintf(f,"<\\proies>\n");

  //Ecriture predateurs
  fprintf(f,"<predateurs>\n");
  ani = liste_predateurs;
  while(ani){
    fprintf(f,"x=%d y=%d dir=[%d %d] e=%.2f\n", ani->x, ani->y, ani->dir[0], ani->dir[1], ani->energie);
    ani = ani->suivant;
  }
  fprintf(f,"<\\predateurs>\n");

  fclose(f);
}

void lire_ecosys(const char *nom_fichier, Animal** liste_predateurs, Animal** liste_proies){
  FILE *f = fopen(nom_fichier,"r");
  if(f==NULL){
    printf("Erreur ouverture %s\n", nom_fichier);
    return;
  }
  Animal *ani;
  char buffer[256];
  int x,y;
  int dir[2];
  float e;

  //Lecture des proies
  fgets(buffer, 256, f);
  assert(strncmp(buffer, "<proies>", 8)==0);
  fgets(buffer, 256, f);
  while(strncmp(buffer, "<\\proies>", 9)){
    sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%2f\n", &x, &y, &dir[0], &dir[1], &e);
    ani = creer_animal(x, y, e);
    ani->dir[0] = dir[0];
    ani->dir[1] = dir[1];
    *liste_proies = ajouter_en_tete_animal(*liste_proies, ani);
    fgets(buffer, 256, f);
  }

  //Lecture des predateurs
  fgets(buffer, 256, f);
  assert(strncmp(buffer, "<predateurs>", 12)==0);//predateurs
  fgets(buffer, 256, f);
  while(strncmp(buffer, "<\\predateurs>", 13)){
    sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%2f\n", &x, &y, &dir[0], &dir[1], &e);
    ani = creer_animal(x, y, e);
    ani->dir[0] = dir[0];
    ani->dir[1] = dir[1];
    *liste_predateurs = ajouter_en_tete_animal(*liste_predateurs, ani);
    fgets(buffer, 256, f);
  }
  fclose(f);
}