#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>

CDATAFRAME creation_cdataframe_vide(MAILLON* premiere_colonne)
{
    premiere_colonne->succ = NULL;
    premiere_colonne->col = NULL;
    
    return premiere_colonne;
}

void remplir_cdataframe_saisi(CDATAFRAME data)
{
    MAILLON *col = data;
    char *titre = NULL;
    int nombre_val;
    int val;
    
    while (col != NULL)
    {
        printf("Saisir le titre de la colonne souhaité :\n");
        scanf("%s",titre);
        
        col->col = create_column(titre);
        
        printf("Saisir le nombre de valeur souhaité :\n");
        scanf(" %d",&nombre_val);
        
        for (int i=0;i<nombre_val;i++){
            printf("Saisir la valeur à ajouter à la colonne :\n");
            scanf(" %d",&val);
            
            insert_value(col->col,val);
        }
        col=col->succ;
    }    
}

void remplir_cdataframe_dur(CDATAFRAME data)
{
    MAILLON *col = data;
    
    while (col != NULL)
    {
        col->col = create_column("colonne");
        
        insert_value(col->col,1);
        insert_value(col->col,2);
        insert_value(col->col,3);
        insert_value(col->col,4);
        insert_value(col->col,5);
        insert_value(col->col,6);
        
        col=col->succ;
    }
}

void affiche_tout_cdataframe(CDATAFRAME data)
{
    MAILLON *col = data;
    int ligne = 0;
    int ligne_max = data->col->size;
    
    while (col != NULL)
    {
        printf("%s\t", col->col->title);
        col = col->succ;
    }
    printf("\n");

    while (ligne < ligne_max) {
        col = data;
        while (col != NULL)
        {
            if (ligne < col->col->size) 
            {
                printf("%d\t", col->col->data[ligne]);

            } 
            else 
            {
                printf("\t");
            }
            col = col->succ;
        }
        ligne++;
    }
}

void affiche_ligne_cdataframe(CDATAFRAME data, int deb, int fin)
{
    MAILLON *col = data;
    
    while (col != NULL)
    {
        for(int i=deb;i<=fin && col->col->size;i++)
        {
            position_value((col->col, i);
        }
        col=col->succ;
    }
}
