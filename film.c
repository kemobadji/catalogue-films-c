
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "film.h"

/* ── GESTION DES FILMS ── */

Film* charger_films(const char *nomFichier, int *nbFilms) {
    FILE *f = fopen(nomFichier, "r");
    *nbFilms = 0;

    if (f == NULL) {
        f = fopen(nomFichier, "w");
        if (f) fclose(f);
        return NULL;
    }

    char ligne[300];
    while (fgets(ligne, sizeof(ligne), f)) {
        (*nbFilms)++;
    }

    Film *films = malloc((*nbFilms) * sizeof(Film));
    if (films == NULL) {
        fclose(f);
        return NULL;
    }

    rewind(f);
    int i = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        ligne[strcspn(ligne, "\n")] = '\0';
        sscanf(ligne, "%d;%99[^;];%49[^;];%d;%f",
               &films[i].id,
               films[i].titre,
               films[i].genre,
               &films[i].annee,
               &films[i].note);
        i++;
    }

    fclose(f);
    return films;
}

void sauvegarder_films(const char *nomFichier, Film *films, int nbFilms) {
    FILE *f = fopen(nomFichier, "w");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    for (int i = 0; i < nbFilms; i++) {
        fprintf(f, "%d;%s;%s;%d;%.1f\n",
                films[i].id,
                films[i].titre,
                films[i].genre,
                films[i].annee,
                films[i].note);
    }

    fclose(f);
}

/* ── MODIFICATIONS ── */

void ajouter_films(Film **films, int *nbFilms, Film nouveauFilm) {
    Film *nouveauTableau = realloc(*films, (*nbFilms + 1) * sizeof(Film));
    if (nouveauTableau == NULL) {
        printf("Erreur : impossible d'allouer de la mémoire.\n");
        return;
    }
    nouveauTableau[*nbFilms] = nouveauFilm;
    (*nbFilms)++;
    *films = nouveauTableau;
}

void modifier_films(Film *films, int nbFilms, int id, Film filmModifie) {
    for (int i = 0; i < nbFilms; i++) {
        if (films[i].id == id) {
            films[i] = filmModifie;
            return;
        }
    }
    printf("Film avec l'ID %d non trouvé.\n", id);
}

void supprimer_films(Film **films, int *nbFilms, int id) {
    int index = -1;
    for (int i = 0; i < *nbFilms; i++) {
        if ((*films)[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Film avec l'ID %d non trouvé.\n", id);
        return;
    }

    for (int i = index; i < *nbFilms - 1; i++) {
        (*films)[i] = (*films)[i + 1];
    }

    Film *nouveauTableau = realloc(*films, (*nbFilms - 1) * sizeof(Film));
    if (nouveauTableau == NULL && *nbFilms > 1) {
        printf("Erreur : impossible de réallouer de la mémoire.\n");
        return;
    }

    (*nbFilms)--;
    *films = nouveauTableau;
}

/* ── CONSULTATION ── */

void afficher_tous(Film *films, int nbFilms) {
    if (nbFilms == 0) {
        printf("Aucun film à afficher.\n");
        return;
    }
    printf("\n%-4s %-30s %-20s %-6s %-5s\n", "ID","Titre","Genre","Annee","Note");
    printf("%-4s %-30s %-20s %-6s %-5s\n","----","------------------------------","--------------------","------","-----");
    for (int i = 0; i < nbFilms; i++) {
        printf("%-4d %-30s %-20s %-6d %-5.1f\n",
               films[i].id,
               films[i].titre,
               films[i].genre,
               films[i].annee,
               films[i].note);
    }
    printf("\n");
}

void rechercher_par_id(Film *films, int nbFilms, int id) {
    for (int i = 0; i < nbFilms; i++) {
        if (films[i].id == id) {
            printf("%-4d %-30s %-20s %-6d %-5.1f\n",
                   films[i].id,
                   films[i].titre,
                   films[i].genre,
                   films[i].annee,
                   films[i].note);
            return;
        }
    }
    printf("Film avec l'ID %d non trouvé.\n", id);
}

void rechercher_par_titre(Film *films, int nbFilms, const char *titre) {
    int trouve = 0;
    char titreLow[100], rechercheLow[100];
    int k;

    for (k = 0; titre[k]; k++)
        rechercheLow[k] = tolower((unsigned char)titre[k]);
    rechercheLow[k] = '\0';

    for (int i = 0; i < nbFilms; i++) {
        for (k = 0; films[i].titre[k]; k++)
            titreLow[k] = tolower((unsigned char)films[i].titre[k]);
        titreLow[k] = '\0';

        if (strstr(titreLow, rechercheLow)) {
            printf("%-4d %-30s %-20s %-6d %-5.1f\n",
                   films[i].id,
                   films[i].titre,
                   films[i].genre,
                   films[i].annee,
                   films[i].note);
            trouve = 1;
        }
    }
    if (!trouve)
        printf("Aucun film avec le titre '%s' trouvé.\n", titre);
}

void afficher_par_genre(Film *films, int nbFilms, const char *genre) {
    int trouve = 0;
    char genreLow[50], filmGenreLow[50];
    int k;

    for (k = 0; genre[k]; k++)
        genreLow[k] = tolower((unsigned char)genre[k]);
    genreLow[k] = '\0';

    for (int i = 0; i < nbFilms; i++) {
        for (k = 0; films[i].genre[k]; k++)
            filmGenreLow[k] = tolower((unsigned char)films[i].genre[k]);
        filmGenreLow[k] = '\0';

        if (strcmp(filmGenreLow, genreLow) == 0) {
            printf("%-4d %-30s %-20s %-6d %-5.1f\n",
                   films[i].id,
                   films[i].titre,
                   films[i].genre,
                   films[i].annee,
                   films[i].note);
            trouve = 1;
        }
    }
    if (!trouve)
        printf("Aucun film avec le genre '%s' trouvé.\n", genre);
}

/* ── BONUS ── */

void trier_par_note(Film *films, int nbFilms) {
    for (int i = 0; i < nbFilms - 1; i++) {
        for (int j = 0; j < nbFilms - i - 1; j++) {
            if (films[j].note < films[j + 1].note) {
                Film temp = films[j];
                films[j] = films[j + 1];
                films[j + 1] = temp;
            }
        }
    }
}

void trier_alphabetique(Film *films, int nbFilms) {
    for (int i = 0; i < nbFilms - 1; i++) {
        for (int j = 0; j < nbFilms - i - 1; j++) {
            if (strcasecmp(films[j].titre, films[j + 1].titre) > 0) {
                Film temp = films[j];
                films[j] = films[j + 1];
                films[j + 1] = temp;
            }
        }
    }
}

void top5(Film *films, int nbFilms) {
    if (nbFilms == 0) {
        printf("Aucun film à afficher.\n");
        return;
    }
    trier_par_note(films, nbFilms);
    int n = nbFilms < 5 ? nbFilms : 5;
    printf("=== Top %d films ===\n", n);
    afficher_tous(films, n);
}

void statistiques(Film *films, int nbFilms) {
    if (nbFilms == 0) {
        printf("Aucun film pour calculer les statistiques.\n");
        return;
    }

    float sommeNotes = 0.0;
    float max = films[0].note, min = films[0].note;
    int iMax = 0, iMin = 0;

    for (int i = 0; i < nbFilms; i++) {
        sommeNotes += films[i].note;
        if (films[i].note > max) { max = films[i].note; iMax = i; }
        if (films[i].note < min) { min = films[i].note; iMin = i; }
    }

    printf("Nombre total de films : %d\n", nbFilms);
    printf("Note moyenne          : %.2f\n", sommeNotes / nbFilms);
    printf("Meilleur film         : %s (%.1f)\n", films[iMax].titre, max);
    printf("Film moins noté       : %s (%.1f)\n", films[iMin].titre, min);
}
>>>>>>> 9b2cdf9f788ef87618f8f3e054c23f7eea01c539
