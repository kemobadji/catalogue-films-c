/* ============================================================
 *  main.c — Point d'entrée et menu principal
 *  Projet Final – Programmation C & Gestion Mémoire – L1 LDIA
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>

#include "film.h"

/* Affichage de menu principal et  le choix de l'utilisateur */
static int afficher_menu(void)
{
    int choix;
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║     CATALOGUE PERSONNEL DE FILMS     ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  1. Ajouter un film                  ║\n");
    printf("║  2. Afficher tous les films           ║\n");
    printf("║  3. Rechercher par ID                 ║\n");
    printf("║  4. Rechercher par titre              ║\n");
    printf("║  5. Afficher par genre                ║\n");
    printf("║  6. Modifier un film                  ║\n");
    printf("║  7. Supprimer un film                 ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║           ★  BONUS  ★                ║\n");
    printf("║  8. Trier par note décroissante       ║\n");
    printf("║  9. Trier alphabétiquement            ║\n");
    printf("║ 10. Top 5 des films                   ║\n");
    printf("║ 11. Statistiques                      ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  0. Quitter                           ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    getchar(); 
    return choix;
}

int main(void)
{
    int choix;

    printf("Bienvenue dans votre catalogue de films !\n");
    printf("Fichier de données : %s\n", FICHIER_CSV);

    do {
        choix = afficher_menu();

        switch (choix) {
            case 1:  ajouter_film(FICHIER_CSV);      break;
            case 2:  afficher_tous(FICHIER_CSV);      break;
            case 3:  rechercher_par_id(FICHIER_CSV);  break;
            case 4:  rechercher_par_titre(FICHIER_CSV); break;
            case 5:  afficher_par_genre(FICHIER_CSV); break;
            case 6:  modifier_film(FICHIER_CSV);      break;
            case 7:  supprimer_film(FICHIER_CSV);     break;
            case 8:  trier_par_note(FICHIER_CSV);     break;
            case 9:  trier_alphabetique(FICHIER_CSV); break;
            case 10: top5(FICHIER_CSV);               break;
            case 11: statistiques(FICHIER_CSV);       break;
            case 0:  printf("Au revoir !\n");         break;
            default: printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);

    return EXIT_SUCCESS;
}