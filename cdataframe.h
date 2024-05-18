#include "column.h"
#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H
// Structure maillon 
struct mailllon
{
    COLUMN *col; // Pointeur structure column
    struct mailllon *succ;
};
typedef struct mailllon MAILLON; // Utilisation de typedef pour créer un alias pour la structure maillon
typedef MAILLON* CDATAFRAME;

// Alimentation de la structure maillon
CDATAFRAME creation_cdataframe_vide(MAILLON* premiere_colonne);
void remplir_cdataframe_saisi(CDATAFRAME data);
void remplir_cdataframe_dur(CDATAFRAME data);
// Affichage cdataframe
void affiche_tout_cdataframe(CDATAFRAME data);
void affiche_ligne_cdataframe(CDATAFRAME data, int deb, int fin);
void affiche_colonne_cdataframe(CDATAFRAME data, int deb, int fin);
