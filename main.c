
/* ============================================================
 *  main.c — Point d'entrée et menu principal
 *  Projet Final – Programmation C & Gestion Mémoire – L1 LDIA
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "film.h"

/* Affichage du menu principal et retour du choix de l'utilisateur */
static int afficher_menu(void)
{
    int choix;
    printf("\n+======================================+\n");
    printf("|     CATALOGUE PERSONNEL DE FILMS     |\n");
    printf("+======================================+\n");
    printf("|  1. Ajouter un film                  |\n");
    printf("|  2. Afficher tous les films          |\n");
    printf("|  3. Rechercher par ID                |\n");
    printf("|  4. Rechercher par titre             |\n");
    printf("|  5. Afficher par genre               |\n");
    printf("|  6. Modifier un film                 |\n");
    printf("|  7. Supprimer un film                |\n");
    printf("+======================================+\n");
    printf("|            ** BONUS **               |\n");
    printf("|  8. Trier par note decroissante      |\n");
    printf("|  9. Trier alphabetiquement           |\n");
    printf("| 10. Top 5 des films                  |\n");
    printf("| 11. Statistiques                     |\n");
    printf("+======================================+\n");
    printf("|  0. Quitter                          |\n");
    printf("+======================================+\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    getchar();
    return choix;
}

int main(void)
{
    int    nbFilms = 0;
    Film  *films   = NULL;
    int    choix;

    printf("Bienvenue dans votre catalogue de films !\n");
    printf("Fichier de données : %s\n", FICHIER_CSV);

    /* Chargement initial depuis le fichier CSV */
    films = charger_films(FICHIER_CSV, &nbFilms);

    do {
        choix = afficher_menu();

        switch (choix) {

            case 1: {
                Film nouveau;
                nouveau.id = (nbFilms > 0) ? films[nbFilms - 1].id + 1 : 1;
                printf("Titre  : "); fgets(nouveau.titre, MAX_TITRE, stdin);
                nouveau.titre[strcspn(nouveau.titre, "\n")] = '\0';
                printf("Genre  : "); fgets(nouveau.genre, MAX_GENRE, stdin);
                nouveau.genre[strcspn(nouveau.genre, "\n")] = '\0';
                printf("Année  : "); scanf("%d", &nouveau.annee); getchar();
                printf("Note   : "); scanf("%f", &nouveau.note);  getchar();
                ajouter_films(&films, &nbFilms, nouveau);
                sauvegarder_films(FICHIER_CSV, films, nbFilms);
                printf("Film ajouté avec l'ID %d.\n", nouveau.id);
                break;
            }

            case 2:
                afficher_tous(films, nbFilms);
                break;

            case 3: {
                int id;
                printf("ID recherché : "); scanf("%d", &id); getchar();
                rechercher_par_id(films, nbFilms, id);
                break;
            }

            case 4: {
                char titre[MAX_TITRE];
                printf("Titre (ou sous-chaîne) : "); fgets(titre, MAX_TITRE, stdin);
                titre[strcspn(titre, "\n")] = '\0';
                rechercher_par_titre(films, nbFilms, titre);
                break;
            }

            case 5: {
                char genre[MAX_GENRE];
                printf("Genre : "); fgets(genre, MAX_GENRE, stdin);
                genre[strcspn(genre, "\n")] = '\0';
                afficher_par_genre(films, nbFilms, genre);
                break;
            }

            case 6: {
                int id;
                printf("ID du film à modifier : "); scanf("%d", &id); getchar();
                Film modifie;
                modifie.id = id;
                printf("Nouveau titre  : "); fgets(modifie.titre, MAX_TITRE, stdin);
                modifie.titre[strcspn(modifie.titre, "\n")] = '\0';
                printf("Nouveau genre  : "); fgets(modifie.genre, MAX_GENRE, stdin);
                modifie.genre[strcspn(modifie.genre, "\n")] = '\0';
                printf("Nouvelle année : "); scanf("%d", &modifie.annee); getchar();
                printf("Nouvelle note  : "); scanf("%f", &modifie.note);  getchar();
                modifier_films(films, nbFilms, id, modifie);
                sauvegarder_films(FICHIER_CSV, films, nbFilms);
                printf("Film modifié.\n");
                break;
            }

            case 7: {
                int id;
                printf("ID du film à supprimer : "); scanf("%d", &id); getchar();
                supprimer_films(&films, &nbFilms, id);
                sauvegarder_films(FICHIER_CSV, films, nbFilms);
                printf("Film supprimé.\n");
                break;
            }

            case 8:
                trier_par_note(films, nbFilms);
                afficher_tous(films, nbFilms);
                break;

            case 9:
                trier_alphabetique(films, nbFilms);
                afficher_tous(films, nbFilms);
                break;

            case 10:
                top5(films, nbFilms);
                break;

            case 11:
                statistiques(films, nbFilms);
                break;

            case 0:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);

    free(films);
    return EXIT_SUCCESS;
}
