#include <stdio.h>
#include "column.h"

int main() {
    /*création d'une colonne*/
    COLUMN *mycol = create_column(CHAR, "My Column");
    printf("%p", mycol);
}