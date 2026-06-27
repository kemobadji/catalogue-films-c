

/* ============================================================
   film.h — Déclarations de la structure Film et des fonctions
   Projet Final – Programmation C & Gestion Mémoire – L1 LDIA
 ============================================================ */

#ifndef FILM_H
#define FILM_H

#define MAX_TITRE  100
#define MAX_GENRE   50
#define FICHIER_CSV "catalogue.csv"

/* ── Structure principale ── */
typedef struct {
    int   id;
    char  titre[MAX_TITRE];
    char  genre[MAX_GENRE];
    int   annee;
    float note;
} Film;

/* ── Gestion du fichier CSV ── */
Film *charger_films(const char *nomFichier, int *nbFilms);
void  sauvegarder_films(const char *nomFichier, Film *films, int nbFilms);

/* ── Fonctionnalités obligatoires ── */
void ajouter_films(Film **films, int *nbFilms, Film nouveauFilm);
void afficher_tous(Film *films, int nbFilms);
void rechercher_par_id(Film *films, int nbFilms, int id);
void rechercher_par_titre(Film *films, int nbFilms, const char *titre);
void afficher_par_genre(Film *films, int nbFilms, const char *genre);
void modifier_films(Film *films, int nbFilms, int id, Film filmModifie);
void supprimer_films(Film **films, int *nbFilms, int id);

/* ── Fonctionnalités bonus ── */
void trier_par_note(Film *films, int nbFilms);
void trier_alphabetique(Film *films, int nbFilms);
void top5(Film *films, int nbFilms);
void statistiques(Film *films, int nbFilms);

#endif

