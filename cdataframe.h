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
