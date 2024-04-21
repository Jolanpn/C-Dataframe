#include <stdio.h>
#include "column.h"
#include "cdataframe.h"
#include "sort.h"
#include "list.h"


int main() {
    COLUMN *mycol = create_column(CHAR, "Column 1");
    char a[] = "A", c[] = "c";
    insert_value(mycol, &c);
    insert_value(mycol, NULL);
    insert_value(mycol, &a);
    print_col(mycol);
    occurrence_value(mycol, &a);
    position_value(mycol, &a);
}