
/* ============================================================
   film.h — Déclarations de la structure Film et des fonctions
   Projet Final – Programmation C & Gestion Mémoire – L1 LDIA
 ============================================================ */

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

/*
  Charge tous les films depuis le fichier CSV.
  Alloue dynamiquement un tableau et met à jour *nb_films.
  Retourne le tableau (à libérer par l'appelant), ou NULL si vide / erreur.
 */
Film *charger_films(const char *fichier, int *nb_films);

/*
  Sauvegarde le tableau de films dans le fichier CSV .
 */
void sauvegarder_films(const char *fichier, Film *films, int nb_films);

/* ── Fonctionnalités obligatoires ── */

/* 4.1 — Demande  infos à l'utilisateur et ajout dans le CSV. */
void ajouter_films(const char *fichier);

/* 4.2 — Affichage tous les films du catalogue. */
void afficher_tous(const char *fichier);

/* 4.3 — Recherche et affiche un film par son ID. */
void rechercher_par_id(const char *fichier);

/* 4.4 — Recherche et affiche les films dont le titre contient une sous-chaîne. */
void rechercher_par_titre(const char *fichier);

/* 4.5 — Affichage tous les films d'un genre donné. */
void afficher_par_genre(const char *fichier);

/* 4.6 — Modification des champs d'un film sélectionné par ID. */
void modifier_films(const char *fichier);

/** 4.7 — Suppression d'un film sélectionné par ID. */
void supprimer_films(const char *fichier);

/* ── Fonctionnalités bonus ── */

/* 7.1 — Affichage des films triés par note décroissante. */
void trier_par_note(const char *fichier);

/* 7.2 — Affichage des films triés par ordre alphabétique du titre. */
void trier_alphabetique(const char *fichier);

/* 7.3 — Affichage  Top 5 des films les mieux notés. */
void top5(const char *fichier);

/* 7.4 — Affichage des statistiques globales sur le catalogue. */
void statistiques(const char *fichier);

/* ── Utilitaires internes ── */

/* Convertit une chaîne en minuscules dans le buffer dest (de taille n). */
void to_lower(const char *src, char *dest, int n);

/* Affichage d'un séparateur horizontal. */
void afficher_separateur(void);

/* Affichage d'un film de façon lisible. */
void afficher_films(const Film *f);

