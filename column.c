#include "column.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define REALOC_SIZE 256

COLUMN *create_column(ENUM_TYPE type, char *title){
    COLUMN *col = (COLUMN *)malloc(sizeof(COLUMN));
    if(col == NULL){
        return NULL;
    }
    col->title = title;
    col->size = 0;
    col->max_size = 0;
    col->column_type = type;
    col->data = NULL;
    col->index = NULL;
    return col;
}


int insert_value(COLUMN *col, void *value){
    if(col == NULL){
        return 0;
    }

    if (col->size >= col->max_size) {
        col->max_size += REALOC_SIZE;
        col->data = realloc(col->data, col->max_size * sizeof(COL_TYPE*));
        if (col->data == NULL) {
            // Memory allocation failed
            return 0;
        }
    }
    // Allocate memory for the new data entry
    switch (col->column_type)
    {
        case INT:
            col->data[col->size] = malloc(sizeof(int));
            if (col->data[col->size] == NULL) {
                return 0; // Memory allocation failed
            }
            *((int *)col->data[col->size]) = *((int *) value);
            printf("Inserted value: %d\n", *((int *)col->data[col->size-1]));
            break;

        case UINT:
            col->data[col->size] = malloc(sizeof(unsigned int));
            if (col->data[col->size] == NULL) {
                return 0; // Memory allocation failed
            }
            *((unsigned int*)col->data[col->size]) = *((unsigned int*)value);
            break;

        case CHAR:
            if (value == NULL) {
                col->data[col->size] = NULL;}
            else {
                col->data[col->size] = malloc(sizeof(char));
                if (col->data[col->size] == NULL) {
                    return 0; // Memory allocation failed
                }
                *((char *) col->data[col->size]) = *((char *) value);
            }
            break;

        case FLOAT:
            col->data[col->size] = malloc(sizeof(float));
            if (col->data[col->size] == NULL) {
                return 0; // Memory allocation failed
            }
            *((float*)col->data[col->size]) = *((float*)value);
            break;

        case DOUBLE:
            col->data[col->size] = malloc(sizeof(double));
            if (col->data[col->size] == NULL) {
                return 0; // Memory allocation failed
            }
            *((double*)col->data[col->size]) = *((double*)value);
            break;

        case STRING:
            if (value == NULL) {
                col->data[col->size] = NULL;}
            else{
                col->data[col->size] = malloc(strlen((char*)value) + 1);
                if (col->data[col->size] == NULL) {
                    return 0; // Memory allocation failed
                }
                strcpy((char*)col->data[col->size], (char*)value);
            }
            break;

        case STRUCTURE:
            break;
    }


    col->size++;
    return 1;
}




void delete_column(COLUMN **col){
    free((*col)->title);
    for(unsigned int i = 0; i < (*col)->size; i++) {
        free((*col)->data[i]);
    }
    free((*col)->data);
    free((*col)->index);
    free(*col);
    *col = NULL;
}


void convert_value(COLUMN *col, unsigned long long int i, char *str, int size){
    if(i >= col->size){
        printf("error : out of bound");
    }
    switch(col->column_type){
        case INT:
            snprintf(str, size, "%d", *((int *)(col->data[i])));
            printf("%s\n", str);
            break;
        case UINT:
            snprintf(str, size, "%u", *((unsigned int *)col->data[i]));
            break;
        case CHAR:
            if(col->data[i] == NULL){
                snprintf(str, size, "NULL");
            }
            else {
                snprintf(str, size, "%c", *((char *) col->data[i]));
            }
            break;
        case FLOAT:
            snprintf(str, size, "%f", *((float *)col->data[i]));
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double *)col->data[i]));
            break;
        case STRING:
            if(col->data[i] == NULL){
                snprintf(str, size, "NULL");
            }
            else{
                strncpy(str, (char *)col->data[i], size-1);
                str[size-1] = '\0';
            }
            break;
        default:
            printf("error display type");
    }
}


void print_col(COLUMN* col){
    if(col == NULL){
        printf("Error pointer null");
        return;
    }
    for(int i = 0; i < col->size; i++){
        char str[256];
        convert_value(col, i, str, sizeof(str));
        printf("[%d] %s\n", i, str);
    }
}


void occurrence_value(COLUMN *col, void *value) {
    if(value == NULL){
        printf("error NULL value");
    }
    int nb = 0;
    switch (col->column_type) {
        case INT:
            for (unsigned int i = 0; i < col->size; i++) {
                if (*((int *) col->data[i]) == *((int *) value)) {
                    nb++;
                }
            }
            break;
        case UINT:
            for (unsigned int i = 0; i < col->size; i++) {
                if (*((unsigned int *) col->data[i]) == *((unsigned int *) value)) {
                    nb++;
                }
            }
            break;
        case CHAR:
            for (unsigned int i = 0; i < col->size; i++) {
                if(col->data[i] == NULL){
                    continue;
                }
                else{
                    if(*((char *) col->data[i]) == *((char *) value)){
                        nb++;
                    }
                }
            }
            break;
        case FLOAT:
            for (unsigned int i = 0; i < col->size; i++) {
                if (*((float *) col->data[i]) == *((float *) value)) {
                    nb++;
                }
            }
            break;
        case DOUBLE:
            for (unsigned int i = 0; i < col->size; i++) {
                if (*((double *) col->data[i]) == *((double *) value)) {
                    nb++;
                }
            }
            break;
        case STRING:
            for (unsigned int i = 0; i < col->size; i++) {
                if (strcmp((char *) col->data[i], (char *) value) == 0) {
                    nb++;
                }
            }
            break;
    }
    printf("Le nombre d'occurrence est : %d\n", nb);
}


void position_value(COLUMN *col,void *value){
    if(value == NULL){
        printf("error NULL value");
    }
    int nb = -1;
    switch (col->column_type) {
        case INT:
            for (int i = 0; i < col->size; i++) {
                if (*((int *) col->data[i]) == *((int *) value)) {
                    nb = i;
                }
            }
            break;
        case UINT:
            for (int i = 0; i < col->size; i++) {
                if (*((unsigned int *) col->data[i]) == *((unsigned int *) value)) {
                    nb = i;
                }
            }
            break;
        case CHAR:
            for (int i = 0; i < col->size; i++) {
                if(col->data[i] == NULL){
                    continue;
                }
                else{
                    if(*((char *) col->data[i]) == *((char *) value)){
                        nb = i;
                    }
                }
            }
            break;
        case FLOAT:
            for (int i = 0; i < col->size; i++) {
                if (*((float *) col->data[i]) == *((float *) value)) {
                    nb = i;
                }
            }
            break;
        case DOUBLE:
            for (int i = 0; i < col->size; i++) {
                if (*((double *) col->data[i]) == *((double *) value)) {
                    nb = i;
                }
            }
            break;
        case STRING:
            for (int i = 0; i < col->size; i++) {
                if (strcmp((char *) col->data[i], (char *) value) == 0) {
                    nb = i;
                }
            }
            break;
    }
    if(nb == -1){
        printf("la valeur n'est pas présente");
    }
    printf("La position de la valeur est : %d", nb);
}


