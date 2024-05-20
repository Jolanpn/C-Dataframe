Dépôt github : https://github.com/Jolanpn/C-Dataframe.git

Fonctions de column.h :

COLUMN *create_column(ENUM_TYPE type, char *title);
    création d'une nouvelle colonne
    paramètre :
        Type de la nouvelle colonne
        Nom de la nouvelle colonne

int  insert_value(COLUMN *col, void *value);
    Insertion d'une nouvelle valeur dans une colonne
    paramètre :
        Pointeur de la colonne
        Pointeur de la valeur à inserrer

void delete_column(COLUMN **col);
    Suppression d'une colonne
    paramètre :
        Adresse du pointeur de la colonne

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
    Convertion des valeurs


void print_col(COLUMN* col);
    Impression de la colonne et de ses valeurs
    Paramètre :
        Adresse du pointeur de la colonne


void print_col_line(COLUMN* col, int line);
    Impression d'une ligne d'une colonne
        Paramètre :
            Adresse du pointeur de la colonne
            Numéro de la ligne

int occurrence_value(COLUMN *col,void *value);
    Retour du nombre d'occurrence d'une valeur dans une colonne
    Paramètre :
                Adresse du pointeur de la colonne
                Valeur à rechercher

int position_value(COLUMN *col,void *value);
    Retour de la position d'une valeur dans une colonne
        Paramètre :
            Adresse du pointeur de la colonne
            Valeur à rechercher

int superior_value(COLUMN *col, void *value);
    Retour du nombre de valeurs supérieur à la valeur comparée
            Paramètre :
                Adresse du pointeur de la colonne
                Valeur à comparer

int inferior_value(COLUMN *col, void *value);
    Retour du nombre de valeurs inférieur à la valeur comparée
            Paramètre :
                Adresse du pointeur de la colonne
                Valeur à comparer


Fonctions de cdataframe.h :

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);
    Création d'une dataframe avec colonne
    Les noms des colonnes par défaut seront 1 à n colonne
    paramètre :
        Les types des colonnes à créer
        Le nombre de colonne à créer

CDATAFRAME *empty_cdataframe();
    Création d'une dataframe vide

CDATAFRAME *user_input_cdataframe();

void delete_cdataframe(CDATAFRAME **cdf);
    Supression de la dataframe
    paramètre :
        Pointeur de la dataframe

void add_col_dataframe(CDATAFRAME *cdf, ENUM_TYPE type, char *col_name);
    Ajout d'une colonne dans la dataframe
    paramètre :
        pointeur de la dataframe
        le type de la colonne à ajouter
        le nom de la nouvelle colonne

void add_line_dataframe(CDATAFRAME *cdf);
    Ajout d'une ligne dans la dataframe, il y aura un ajout de valeur sur toutes les colonnes
    Paramètre :
        pointeur de la dataframe

void add_line_dataframe_col(CDATAFRAME *cdf, char *col_name, void *value);
    Ajout d'une nouvelle ligne sur une colonne spécifique
    paramètre :
        pointeur de la dataframe
        nom de la colonne
        pointeur pour la nouvelle valeur à ajouter

void delete_line_dataframe(CDATAFRAME *cdf, int line);
    suppression d'une ligne de la dataframe
    paramètre :
        pointeur de la dataframe
        numéro de la ligne à supprimer

void delete_column_cd(CDATAFRAME *cdf, char *col_name);
    suppression d'une colonne spécifique
    paramètre :
        pointeur de la dataframe
        nom de la colonne à supprimer

int get_cdataframe_cols_size(CDATAFRAME *cdf);
    valeur int du nombre de colonne dans la dataframe
    paramètre :
        pointeur de la dataframe

void name_list_col(CDATAFRAME *cdf);
    Impression de la liste des noms des colonnes
    paramètre :
        pointeur de la dataframe

void rename_col(CDATAFRAME *cdf, char *current_name, char *new_name);
    renommer une colonne
    paramètre :
        pointeur de la dataframe
        nom de la colonne actuelle
        nouveau nom pour la colonne ciblée

void print_dataframe(CDATAFRAME *cdf);
    impression de la dataframe entière
    paramètre :
        pointeur de la dataframe

void cdataframe_print_col(CDATAFRAME *cdf, char *col_name);
    Impression d'une colonne spécifique et ses valeurs
    paramètre :
        pointeur de la dataframe
        nom de la colonne à imprimer

void cdataframe_print_line(CDATAFRAME *cdf, int line);
    impression d'une ligne spécifique de la dataframe
    paramètre :
        pointeur de la dataframe
        numéro de la ligne à imprimer

void occurrence_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value);
    impression du nombre d'occurrence d'une valeur dans une colonne
    Paramètre :
        pointeur de la dataframe
        nom de la colonne
        Valeur à rechercher

void superior_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value);
    impression du nombre de valeur supérieur à la valeur indiquée
    paramètre :
        pointeur de la dataframe
        nom de la colonne
        valeur à comparer

void inferior_value_dataframe(CDATAFRAME *cdf,char *col_name,void *value);
    impression du nombre de valeur inférieur à la valeur indiquée
    paramètre :
        pointeur de la dataframe
        nom de la colonne
        valeur à comparer