#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void affiche_plateau(int** p) {
     for (int i=0; i < 9; i+=1) {
          printf(" ");
          for (int j=0; j < 9; j+=1) {
               if (p[i][j]!=0) printf("%d ",p[i][j]);
               else printf(". ");
          }
          printf("\n");
     }
}

bool est_valide(int** grille, int ligne, int colonne, int num) {
     for (int i=0;i<9;i++){
          if (grille[ligne][i]==num){
               return false;
          }
     }
     for(int j=0;j<9;j++){
          if(grille[j][colonne]==num){
               return false;
          }
     }
     int i_n=ligne-ligne%3;
     int j_n=colonne-colonne%3;
     for (int i=i_n;i<i_n+3;i++){
          for(int j=j_n;j<j_n+3;j++){
               if(grille[i][j]==num){
                    return false;
               }
          }
     }
     return true;
}

bool trouve_case_vide(int** grille, int* ligne, int* colonne) {
    for (*ligne = 0; *ligne <9; (*ligne)++) {
        for (*colonne = 0; *colonne < 9; (*colonne)++) {
            if (grille[*ligne][*colonne] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool resoudre_sudoku(int** grille) {
     int ligne, colonne;
     if (!trouve_case_vide(grille, &ligne, &colonne)) {
          return true;
     }
     for (int num = 1; num <= 9; num++) {
          if (est_valide(grille, ligne, colonne, num)) {
               grille[ligne][colonne] = num;
               if (resoudre_sudoku(grille)) {
                    return true;
               }
               grille[ligne][colonne] = 0;
          }
     }
     return false;
}

void initialiser_grille(int** grille) {

     int grille_ini[81][81]={
     {0,0,0,1,0,0,0,5,0},
     {0,5,0,0,4,0,0,0,0},
     {4,7,0,0,5,2,0,0,0},
     {0,0,8,0,0,4,1,3,0},
     {3,0,2,0,0,9,0,7,0},
     {0,9,0,3,0,0,5,0,2},
     {2,0,0,0,6,0,0,0,0},
     {0,0,0,0,0,5,0,2,1},
     {6,0,0,0,3,1,0,0,0}
     };
     for(int i=0;i<9;i++){
          for(int j=0;j<9;j++){
               grille[i][j]=grille_ini[i][j];
          }
     }
     return;
}

int main(){
     int** grille=malloc(9*sizeof(int*));
     for(int i=0;i<9;i++){
          grille[i]=malloc(9*sizeof(int));
          for(int j=0;j<9;j++){
               grille[i][j]=0;
          }
     }

     initialiser_grille(grille);
     printf("Grille initiale :\n");
     affiche_plateau(grille);

     if (resoudre_sudoku(grille)) {
          printf("\nGrille résolue :\n");
          affiche_plateau(grille);
     } else {
          printf("Aucune solution trouvée.\n");
     }
     for (int i = 0; i <9; i++) {
          free(grille[i]);
     }
     free(grille);
}