#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REALOC_SIZE 256

enum enum_type
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};

typedef union column_type COL_TYPE ;

struct column {
    char *title;
    unsigned int size; //logical size
    unsigned int max_size; //physical size
    ENUM_TYPE column_type;
    COL_TYPE **data; // array of pointers to stored data
    unsigned long long int *index; // array of integers
};
typedef struct column COLUMN;

COLUMN *create_column(ENUM_TYPE type, char *title)
{
    COLUMN *tab = (COLUMN*)malloc(sizeof(COLUMN));
    tab->title = title;
    tab->column_type = type;
    tab->data = NULL;
    tab->max_size = 0;
    tab->index = NULL;
    tab->size = 0;
}

int insert_value(COLUMN *col, void *value)
{
    // Ensure there is enough space in the array for a new value
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
            *((int*)col->data[col->size]) = *((int*)value);
            break;

        case UINT:
            col->data[col->size] = malloc(sizeof(unsigned int));
            if (col->data[col->size] == NULL) {
                return 0; // Memory allocation failed
            }
            *((unsigned int*)col->data[col->size]) = *((unsigned int*)value);
            break;

        case CHAR:
            col->data[col->size] = malloc(sizeof(char));
            if (col->data[col->size] == NULL) {
                return 0; // Memory allocation failed
            }
            *((char*)col->data[col->size]) = *((char*)value);
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
            col->data[col->size] = malloc(strlen((char*)value) + 1);
            if (col->data[col->size] == NULL) {
                return 0; // Memory allocation failed
            }
            strcpy((char*)col->data[col->size], (char*)value);
            break;

        case STRUCTURE:
            // Handling for STRUCTURE can be added here as needed
            break;
    }


    col->size++;
    return 1;
}

void delete_column(COLUMN **col)
{
    // Ne peux pas free une structure parce que certain élément ne sont pas
    free((*col)->title);
    // Data (tableau de pointeurs)
    for(unsigned int i = 0; i<(*col)->size;i++)
    {
        free((*col)->data[i]);
    }
    free((*col)->index);
    free((*col));
    *col = NULL;
}
