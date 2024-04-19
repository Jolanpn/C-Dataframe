//
// Created by Jolan on 28/03/2024.
//
#include "column.h"
#include <stdlib.h>
#include <string.h>

COLUMN *create_column(ENUM_TYPE type, char *title){
    COLUMN *col = (COLUMN *)malloc(sizeof(COLUMN));
    col->title = title;
    col->size = 0;
    col->max_size = 0;
    col->column_type = type;
    col->data = NULL;
    col->index = NULL;
    return col;
}


            }
            if (col->max_size <= col->size) {
                col->data = (void *) realloc(col, sizeof(col->data) + sizeof(int) * 64);
                col->max_size += 256;
            }
int insert_value(COLUMN *col, void *value) {
    switch (col->column_type) {
        case UINT:
            if (col->max_size == 0) {
                col->data = (void *) malloc(sizeof(int) * 64);
                col->max_size = 256;
            }
            if (col->max_size <= col->size) {
                col->data = (void *) realloc(col, sizeof(col->data) + sizeof(int) * 64);
                col->max_size += 256;
            }

        case INT:
            if (col->max_size == 0) {
                col->data = (void *) malloc(sizeof(int) * 64);
                col->max_size = 256;
            ((int *) col->data)[col->size++] = *((int *) value);
            break;

        case CHAR:
            if (col->max_size == 0) {
                col->data = (void *) malloc(sizeof(char) * 256);
                col->max_size = 256;
            }
            if (col->max_size <= col->size) {
                col->data = (void *) realloc(col, sizeof(col->data) + sizeof(char) * 256);
                col->max_size += 256;
            }
            ((char *) col->data)[col->size++] = *((char *) value);
            break;

        case FLOAT:
            if (col->max_size == 0) {
                col->data[col->size] = (void *) malloc(sizeof(float) * 256);
                col->max_size = 256;
            }
            if (col->max_size <= col->size) {
                col->data[col->size] = (void *) realloc(col, sizeof(col->data) + sizeof(float) * 32);
                col->max_size += 256;
            }
            ((float *) col->data)[col->size++] = *((float *) value);
            break;

        case DOUBLE:
            if (col->max_size == 0) {
                col->data[col->size] = (void *) malloc(sizeof(double) * 256);
                col->max_size = 256;
            }
            if (col->max_size <= col->size) {
                col->data[col->size] = (void *) realloc(col, sizeof(col->data) + sizeof(double) * 32);
                col->max_size += 256;
            }
            ((double *) col->data)[col->size++] = *((double *) value);
            break;

        case STRING:
            if (col->max_size == 0) {
                col->data[col->size] = (void *) malloc(sizeof(char) * 256);
                col->max_size = 256;
            }
            if (col->max_size <= (col->size + strlen((char *) value))) {
                col->data[col->size] = (void *) realloc(col, sizeof(col->data) + sizeof(double) * 32);
                col->max_size += 256;
            }
            strcat((char *) col->data[col->size], (char *) value);
            col->size += strlen((char *) value);
            break;

        case STRUCTURE:
            return 0;

    return 1;
    }
}