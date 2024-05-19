#include "column.h"
#include "list.h"
#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H

// cdataframe liste doublement chainée
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);
CDATAFRAME *empty_cdataframe();
CDATAFRAME *user_input_cdataframe();
void delete_cdataframe(CDATAFRAME **cdf);
void add_col_dataframe(CDATAFRAME *cdf, ENUM_TYPE type, char *col_name);
void add_line_dataframe(CDATAFRAME *cdf);
void add_line_dataframe_col(CDATAFRAME *cdf, char *col_name, void *value);
void delete_line_dataframe(CDATAFRAME *cdf, int line);
void delete_column_cd(CDATAFRAME *cdf, char *col_name);
int get_cdataframe_cols_size(CDATAFRAME *cdf);
void name_list_col(CDATAFRAME *cdf);
void rename_col(CDATAFRAME *cdf, char *current_name, char *new_name);
void print_dataframe(CDATAFRAME *cdf);
void cdataframe_print_col(CDATAFRAME *cdf, char *col_name);
void cdataframe_print_line(CDATAFRAME *cdf, int line);
void occurrence_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value);
void superior_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value);
void inferior_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value);


#endif