#ifndef PROJETC_LIST_H
#define PROJETC_LIST_H

/**
* Élément lnode */
typedef struct lnode_ {
    void *data;
    struct lnode_ *prev;
    struct lnode_ *next;
} LNODE;

/**
* Une liste */
typedef struct list_ {
    LNODE *head;
    LNODE *tail;
} LIST;
typedef LIST CDATAFRAME;

/**
* création d'un noeud */
LNODE *lst_create_lnode(void *dat);
/**
* crée la liste et retourne un pointeur sur cette dernière */
LIST *lst_create_list();
/**
* supprimer la liste */
void lst_delete_list(LIST * lst);
/**
* Insère pnew au début de la liste lst */
void lst_insert_head(LIST * lst, LNODE * pnew);
/**
* Insère pnew à la fin de la liste lst */
void lst_insert_tail(LIST * lst, LNODE * pnew);
/**
* Insère l'élément pnew juste après ptr dans la liste lst */
void lst_insert_after(LIST * lst, LNODE * pnew, LNODE * ptr);
/**
* Supprime le premier élément de la liste */
void lst_delete_head(LIST * lst);
/**
* Supprime le dernier élément de la liste */
void lst_delete_tail(LIST * lst);
/**
* Supprime le lnode pointé par ptr */
void lst_delete_lnode(LIST * lst, LNODE * ptr);
/**
* Supprime tous les éléments de la liste lst */
void lst_erase(LIST * lst);
/**
* retourne le premier node s'il existe sinon NULL */
LNODE *get_first_node(LIST * lst);
/**
* retourne le denier node s'il existe sinon NULL */
LNODE *get_last_node(LIST * lst);
/**
* retourne le node suivant */
LNODE *get_next_node(LIST * lst, LNODE * lnode);
/**
* retourne le node precedent */
void *get_previous_elem(LIST * lst, LNODE * lnode);
#endif //PROJETC_LIST_H
