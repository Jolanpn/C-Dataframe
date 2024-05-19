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


        int print_once = 0, command, nb_col;
        printf("Créer une dataframe vide : 0\n");
        printf("Créer une dataframe avec colonne : 1\n");
        printf("Ajouter une colonne : 2\n");
        printf("Supprimer une colonne : 3\n");
        printf("Afficher le nombre de colonne dans la dataframe : 4\n");
        printf("Afficher les noms des colonnes de la dataframe : 5\n");
        printf("Afficher les données d'une colonne : 6\n");
        printf("Afficher les données d'une ligne de la dataframe : 7\n");
        printf("Afficher l'entièretée de la dataframe : 8\n");
        printf("Renommer une colonne : 9\n");
        printf("Ajouter une valeur dans une colonne : 10\n");
        printf("Numéro de la ligne à supprimer : 11\n");
        printf("Ajouter une nouvelle ligne de valeur dans toutes les colonnes : 12\n");
        printf("Trouver le nombre d'occurence d'une valeur dans une colonne : 13\n");
        printf("Trouver le nombre d'occurence de valeur supérieur dans une colonne : 14\n");
        printf("Trouver le nombre d'occurence de valeur inférieur dans une colonne : 15\n");
        printf("Supprimer la dataframe : 16\n");
        printf("quitter le programme : écrire 100\n");
        scanf("%d", &command);

        ENUM_TYPE type;
        ENUM_TYPE types[50];
        char col_name[256], new_name[256], scanf_type[25];;
        int num_columns, line, type_int;
        char *value;
        switch (command) {
            case 0 :
                empty_cdataframe();
            case 1 :
                printf("\nCombien de colonne à ajouter ? ");
                scanf("%d", &nb_col);
                for(int i = 0; i < nb_col; i++){
                    printf("\nQuel type pour la colonne %d ?\n", (i+1));
                    scanf("%s", scanf_type);
                    type = string_to_enum2(scanf_type);
                }
                CDATAFRAME *df = create_cdataframe(types, nb_col);
                printf("\n");
            case 2 :
                printf("\nNom de la colonne à ajouter\n");
                scanf("%s", col_name);
                printf("\nType de colonne à ajouter\n");
                scanf("%d", &type);
                add_col_dataframe(df, type, col_name);
            case 3:
                printf("\nNom de la colonne à supprimer\n");
                scanf("%s", col_name);
                delete_column_cd(df, col_name);
            case 4:
                num_columns = get_cdataframe_cols_size(df);
                printf("\nNumber of columns in the dataframe: %d\n", num_columns);
            case 5:
                name_list_col(df);
            case 6:
                printf("\nNom de la colonne à afficher\n");
                scanf("%s", col_name);
                cdataframe_print_col(df, col_name);
            case 7:
                printf("\nNuméro de la ligne à afficher\n");
                scanf("%d", &line);
                cdataframe_print_line(df, line);
            case 8:
                print_dataframe(df);
            case 9:
                printf("\nNom de la colonne à changer de nom:\n");
                scanf("%s", col_name);
                printf("Nouveau nom de la colonne :\n");
                scanf("%s", col_name);
                rename_col(df, col_name, new_name);
            case 10:
                printf("\nNom de la colonne à ajouter la valeur:\n");
                scanf("%s", col_name);
                printf("\nValeur à ajouter:\n");
                scanf("%s", value);
                add_line_dataframe_col(df, col_name, value);
            case 11:
                printf("\nNuméro de la ligne à supprimer\n");
                scanf("%d", &line);
                delete_line_dataframe(df, line);
            case 12:
                add_line_dataframe(df);
            case 13:
                printf("\nNom de la colonne à rechercher :\n");
                scanf("%s", col_name);
                printf("\nValeur à utiliser pour l'occurence:\n");
                scanf("%s", value);
                occurrence_value_dataframe(df, col_name, value);
            case 14:
                printf("\nNom de la colonne à rechercher :\n");
                scanf("%s", col_name);
                printf("\nValeur à trouver pour les valeurs supérieures:\n");
                scanf("%s", value);
                superior_value_dataframe(df, col_name, value);
            case 15:
                printf("\nNom de la colonne à rechercher :\n");
                scanf("%s", col_name);
                printf("\nValeur à trouver pour les valeurs inférieures:\n");
                scanf("%s", value);
                inferior_value_dataframe(df, col_name, value);
            case 16:
                delete_cdataframe(&df);
            case 100:
                start = 1;
                return 0;
        }
        return 0;
}