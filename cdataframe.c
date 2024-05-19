#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char* column_type_to_string(ENUM_TYPE type) {
    switch(type) {
        case INT: return "INT";
        case UINT: return "UINT";
        case CHAR: return "CHAR";
        case FLOAT: return "FLOAT";
        case DOUBLE: return "DOUBLE";
        case STRING: return "STRING";
        case STRUCTURE: return "STRUCTURE";
        default: return "UNKNOWN";
    }
}


ENUM_TYPE string_to_enum(const char *str) {
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


CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size) {
    CDATAFRAME *df = (CDATAFRAME *) malloc(sizeof(CDATAFRAME));

    df->head = NULL;
    df->tail = NULL;

    for (int i = 0; i < size; i++) {
        char *col_name = (char *)malloc(30 * sizeof(char));
        if (col_name == NULL) {
            printf("Error: Memory allocation failed for col_name\n");
            return NULL;
        }

        sprintf(col_name, "%d", i+1);
        COLUMN *new_col = create_column(cdftype[i], col_name);
        if (new_col == NULL) {
            printf("erreur colonne non initialisée\n");
            return NULL;
        }

        LNODE *new_node = lst_create_lnode(new_col);
        if (new_node == NULL) {
            printf("Erreur création de la node\n");
            return NULL;
        }

        lst_insert_tail(df, new_node);
    }
    return df;
}



CDATAFRAME *empty_cdataframe(){
    CDATAFRAME *df = (CDATAFRAME *) malloc(sizeof(CDATAFRAME));
    df->head = NULL;
    df->tail = NULL;
    return df;
}


CDATAFRAME *user_input_cdataframe(CDATAFRAME *cdf){
    LNODE *current = cdf->head;
    int nb_col;
    printf("combien de colonne voulez-vous créer ?\n");
    scanf("%d", &nb_col);
    for(int i = 0; i < nb_col; i++) {
        char scanf_type[25];
        char col_name[256];
        printf("\nQuel type pour la colonne %d ?\n", (i+1));
        scanf("%s", scanf_type);
        ENUM_TYPE type = string_to_enum(scanf_type);
        printf("\nQuel type pour la colonne %d ?\n", (i+1));
        scanf("%s", col_name);
        COLUMN *new_col = create_column(type, col_name);
        LNODE *new_node = lst_create_lnode(new_col);
        lst_insert_tail(cdf, new_node);
    }
    return cdf;
}


void add_line_dataframe_col(CDATAFRAME *cdf, char *col_name, void *value){
    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        if(strcmp(col->title, col_name) == 0){
            insert_value(col, value);
        }
        current = current->next;
    }
}


void delete_column_cd(CDATAFRAME *cdf, char *col_name) {
    if (cdf == NULL || col_name == NULL) {
        printf("Dataframe ou nom de la colonne vide\n");
        return;
    }

    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        if (col && strcmp(col->title, col_name) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                cdf->head = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                cdf->tail = current->prev;
            }

            LNODE *next_node = current->next;
            delete_column(&col);
            free(current);
            current = next_node;

            return;
        }
        current = current->next;
    }
}



void delete_cdataframe(CDATAFRAME **cdf) {
    if (cdf == NULL || *cdf == NULL) {
        return;
    }
    LNODE *current = (*cdf)->head;
    while (current != NULL) {
        LNODE *next = current->next;
        COLUMN *col = (COLUMN *) current->data;

        delete_column(&col); // Libérer la colonne
        free(current);      // Libérer le maillon

        current = next;
    }
    free(*cdf);
    *cdf = NULL;
}


int get_cdataframe_cols_size(CDATAFRAME *cdf){
    if (cdf == NULL) {
        return 0;
    }

    int count = 0;
    LNODE *current = cdf->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


void add_col_dataframe(CDATAFRAME *cdf, ENUM_TYPE type, char *col_name){
    COLUMN *new_col = create_column(type, col_name);
    LNODE *new_node = lst_create_lnode(new_col);
    lst_insert_tail(cdf, new_node);
}


void add_line_dataframe(CDATAFRAME *cdf) {
    if (cdf == NULL) {
        printf("dataframe non existant\n");
        return;
    }

    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        char user_input[256];
        printf("Ajouter une valeur pour la colonne %s de type %s:\n", col->title, column_type_to_string(col->column_type));
        scanf("%s", user_input);

        void *value = NULL;
        switch (col->column_type) {
            case INT:
                value = malloc(sizeof(int));
                if (value != NULL) {
                    *((int *)value) = atoi(user_input);
                }
                break;

            case UINT:
                value = malloc(sizeof(unsigned int));
                if (value != NULL) {
                    *((unsigned int *)value) = (unsigned int)atoi(user_input);
                }
                break;

            case CHAR:
                value = malloc(sizeof(char));
                if (value != NULL) {
                    *((char *)value) = user_input[0];
                }
                break;

            case FLOAT:
                value = malloc(sizeof(float));
                if (value != NULL) {
                    *((float *)value) = atof(user_input);
                }
                break;

            case DOUBLE:
                value = malloc(sizeof(double));
                if (value != NULL) {
                    *((double *)value) = atof(user_input);
                }
                break;

            case STRING:
                value = malloc(strlen(user_input) + 1);
                if (value != NULL) {
                    strcpy((char *)value, user_input);
                }
                break;

            case STRUCTURE:
                return;
        }

        if (value == NULL || insert_value(col, value) != 1) {
            printf("Valeur NULL, il n'est pas possible d'insérer la valeur dans la colonne %s\n", col->title);
            free(value);
            return;
        }

        free(value);
        current = current->next;
    }
}


void delete_line_dataframe(CDATAFRAME *cdf, int line) {
    if (cdf == NULL) {
        printf("Dataframe non existant\n");
        return;
    }

    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        if (line < 0 || line >= col->size) {
            printf("Invalid line number for column %s\n", col->title);
            return;
        }

        // Free the memory for the element to be deleted
        if (col->data[line] != NULL) {
            free(col->data[line]);
        }

        // Shift elements to fill the gap
        for (unsigned int i = line; i < col->size - 1; i++) {
            col->data[i] = col->data[i + 1];
        }

        // Nullify the last element after shifting
        col->data[col->size - 1] = NULL;

        // Decrease the size of the column
        col->size--;

        current = current->next;
    }
}



void rename_col(CDATAFRAME *cdf, char *current_name, char *new_name){
    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        if(strcmp(col->title, current_name) == 0){
            free(col->title);
            col->title = strdup(new_name);
            return;
        }
        current = current->next;
    }
}


void name_list_col(CDATAFRAME *cdf){
    if (cdf == NULL || cdf->head == NULL) {
        printf("erreur, dataframe vide\n");
        return;
    }
    int nb_col = 1;
    printf("Column names:\n");

    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN*)current->data;
        printf("nb_col : %d, name : %s\n", nb_col, col->title);
        current = current->next;
        nb_col++;
    }
    printf("\n");
}


void print_dataframe(CDATAFRAME *cdf){
    if(cdf->head == NULL && cdf->tail == NULL){
        printf("Dataframe vide\n");
    }
    LNODE *current_col = cdf->head;
    while (current_col != NULL) {
        COLUMN *col = (COLUMN*)current_col->data;
        printf("Column: %s\n", col->title);

        print_col(col);
        printf("\n");
        current_col = current_col->next;
    }
}


void cdataframe_print_col(CDATAFRAME *cdf, char *col_name){
    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        if(strcmp(col->title, col_name) == 0){
            printf("Colonne name : %s\n", col_name);
            print_col(col);
        }
        current = current->next;
    }
}


void cdataframe_print_line(CDATAFRAME *cdf, int line){
    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        printf("Colonne name : %s\n", col->title);
        print_col_line(col, line);
        current = current->next;
    }
}


void occurrence_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value){
    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        if(strcmp(col->title, col_name) == 0){
        int nb = occurrence_value(col, value);
        printf("Colonne nom : %s\n", col->title);
        printf("Le nombre d'occurence est de : %d", nb);
        }
        current = current->next;
    }
}


void superior_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value){
    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        if(strcmp(col->title, col_name) == 0){
            int nb = superior_value(col, value);
            printf("Colonne nom : %s\n", col->title);
            printf("Le nombre d'occurence de valeur supérieure est de : %d", nb);
        }
        current = current->next;
    }
}


void inferior_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value){
    LNODE *current = cdf->head;
    while (current != NULL) {
        COLUMN *col = (COLUMN *)current->data;
        if(strcmp(col->title, col_name) == 0){
            int nb = inferior_value(col, value);
            printf("Colonne nom : %s\n", col->title);
            printf("Le nombre d'occurence de valeur inférieure est de : %d", nb);
        }
        current = current->next;
    }
}
