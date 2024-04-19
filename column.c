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
    // Ne peux pas free une structure parce que certain élément ne sont pas des pointeurs
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

void convert_value(COLUMN* col, unsigned long long int i, char* str, int size)
{
    if (i >= col->size) {
        printf("Error: Index out of bounds!");
        return;
    }

    switch(col->column_type) {
        case INT:
            snprintf(str, size, "%d", *((int*)(col->data[i])));
            break;
        case UINT:
            snprintf(str, size, "%u", *((unsigned int*)(col->data[i])));
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char*)(col->data[i])));
            break;
        case FLOAT:
            snprintf(str, size, "%f", *((float*)(col->data[i])));
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)(col->data[i])));
            break;
        case STRING:
            snprintf(str, size, "%s", (char*)(col->data[i]));
            break;
        case STRUCTURE:
            // Unable to display structures
            printf("Cannot display structures.");
            break;
        default:
            printf("Unsupported data type.");
            break;
    }
}

void print_col(COLUMN* col, unsigned long long int i)
{
    if (i >= col->size) {
        printf("Error: Index out of bounds!\n");
        return;
    }

    // Créez un tampon de chaîne suffisamment grand pour stocker la valeur convertie.
    char str[256]; // Ajustez la taille selon vos besoins.

    // Appelez `convert_value` pour convertir la valeur en chaîne de caractères.
    convert_value(col, i, str, sizeof(str));

    // Imprimez la chaîne convertie.
    printf("%s\n", str);
}
