#include <stdio.h>
#include "cdataframe.h"
#include <string.h>


ENUM_TYPE string_to_enum2(const char *str) {
    if (strcmp(str, "NULLVAL") == 0) return NULLVAL;
    if (strcmp(str, "UINT") == 0) return UINT;
    if (strcmp(str, "INT") == 0) return INT;
    if (strcmp(str, "CHAR") == 0) return CHAR;
    if (strcmp(str, "FLOAT") == 0) return FLOAT;
    if (strcmp(str, "DOUBLE") == 0) return DOUBLE;
    if (strcmp(str, "STRING") == 0) return STRING;
    if (strcmp(str, "STRUCTURE") == 0) return STRUCTURE;
    return -1;
}

int main() {
    int start = 0;

    while (!start) {
        int command;
        printf("\nMenu:\n");
        printf("0. Créer une dataframe vide\n");
        printf("1. Créer une dataframe avec des colonnes\n");
        printf("2. Ajouter une colonne\n");
        printf("3. Supprimer une colonne\n");
        printf("4. Afficher le nombre de colonnes dans la dataframe\n");
        printf("5. Afficher les noms des colonnes de la dataframe\n");
        printf("6. Afficher les données d'une colonne\n");
        printf("7. Afficher les données d'une ligne de la dataframe\n");
        printf("8. Afficher toute la dataframe\n");
        printf("9. Renommer une colonne\n");
        printf("10. Ajouter une valeur dans une colonne\n");
        printf("11. Supprimer une ligne de la dataframe\n");
        printf("12. Ajouter une nouvelle ligne de valeur dans toutes les colonnes\n");
        printf("13. Trouver le nombre d'occurence d'une valeur dans une colonne\n");
        printf("14. Trouver le nombre d'occurence de valeur supérieur dans une colonne\n");
        printf("15. Trouver le nombre d'occurence de valeur inférieur dans une colonne\n");
        printf("16. Supprimer la dataframe\n");
        printf("100. Quitter le programme\n");

        printf("\nEntrez votre choix : ");
        scanf("%d", &command);

        // Variables for storing user inputs
        ENUM_TYPE types[50];
        char col_name[256], new_name[256], scanf_type[25], value[256];
        int nb_col, num_columns, line;

        switch (command) {
            case 0:
                empty_cdataframe();
                break;
            case 1:
                printf("\nCombien de colonnes à ajouter ? ");
                scanf("%d", &nb_col);
                for(int i = 0; i < nb_col; i++){
                    printf("\nQuel type pour la colonne %d ? ", (i+1));
                    scanf("%s", scanf_type);
                    types[i] = string_to_enum2(scanf_type);
                }
                CDATAFRAME *df = create_cdataframe(types, nb_col);
                break;
            case 2:
                printf("\nNom de la colonne à ajouter : ");
                scanf("%s", col_name);
                printf("\nType de colonne à ajouter : ");
                scanf("%s", scanf_type);
                add_col_dataframe(df, string_to_enum2(scanf_type), col_name);
                break;
            case 3:
                printf("\nNom de la colonne à supprimer : ");
                scanf("%s", col_name);
                delete_column_cd(df, col_name);
                break;
            case 4:
                num_columns = get_cdataframe_cols_size(df);
                printf("\nNombre de colonnes dans la dataframe : %d\n", num_columns);
                break;
            case 5:
                name_list_col(df);
                break;
            case 6:
                printf("\nNom de la colonne à afficher : ");
                scanf("%s", col_name);
                cdataframe_print_col(df, col_name);
                break;
            case 7:
                printf("\nNuméro de la ligne à afficher : ");
                scanf("%d", &line);
                cdataframe_print_line(df, line);
                break;
            case 8:
                print_dataframe(df);
                break;
            case 9:
                printf("\nNom de la colonne à renommer : ");
                scanf("%s", col_name);
                printf("Nouveau nom de la colonne : ");
                scanf("%s", new_name);
                rename_col(df, col_name, new_name);
                break;
            case 10:
                printf("\nNom de la colonne à ajouter la valeur : ");
                scanf("%s", col_name);
                printf("\nValeur à ajouter : ");
                scanf("%s", value);
                add_line_dataframe_col(df, col_name, value);
                break;
            case 11:
                printf("\nNuméro de la ligne à supprimer : ");
                scanf("%d", &line);
                delete_line_dataframe(df, line);
                break;
            case 12:
                add_line_dataframe(df);
                break;
            case 13:
                printf("\nNom de la colonne à rechercher : ");
                scanf("%s", col_name);
                printf("\nValeur à utiliser pour l'occurrence : ");
                scanf("%s", value);
                occurrence_value_dataframe(df, col_name, value);
                break;
            case 14:
                printf("\nNom de la colonne à rechercher : ");
                scanf("%s", col_name);
                printf("\nValeur à trouver pour les valeurs supérieures : ");
                scanf("%s", value);
                superior_value_dataframe(df, col_name, value);
                break;
            case 15:
                printf("\nNom de la colonne à rechercher : ");
                scanf("%s", col_name);
                printf("\nValeur à trouver pour les valeurs inférieures : ");
                scanf("%s", value);
                inferior_value_dataframe(df, col_name, value);
                break;
            case 16:
                delete_cdataframe(&df);
                break;
            case 100:
                start = 1;
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    }

    return 0;
}
