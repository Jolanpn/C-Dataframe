//
// Created by Jolan on 28/03/2024.
//

#ifndef PROJETC_COLUMN_H
#define PROJETC_COLUMN_H

enum enum_type
{
    NULLVAL = 1 , UINT, INT,  CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;


union column_type{
    unsigned int    uint_value;
    signed   int    int_value;
    char            char_value;
    float           float_value;
    double          double_value;
    char*           string_value;
    void*           struct_value;
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


/*
* Create a new column
* @param1 : Column type
* @param2 : Column title
* @return : Pointer to the created column
*/
COLUMN *create_column(ENUM_TYPE type, char *title);

#endif //PROJETC_COLUMN_H


/**
  * @brief: Insert a new value into a column
  * @param1: Pointer to the column
  * @param2: Pointer to the value to insert
  * @return: 1 if the value is correctly inserted 0 otherwise
*/
int  insert_value(COLUMN *col, void *value);