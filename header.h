#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

typedef struct Node Node;
struct Node
{
    char *key;
    Node *right;
    Node *left;
    Node *pre;
};

typedef struct DicoABR DicoABR;
struct DicoABR
{
    Node *root;
    int size;
};

typedef struct Element Element;
struct Element
{
    int n;
    char *key;
    Element *next;
    Element *pre;
};

typedef struct List List;
struct List
{
    Element *head;
    Element *tail;
};

typedef struct Car *Mot;
typedef struct Car Car;
struct Car
{
    char c;
    Car *suiv;
};

typedef struct Cellule *Dico;
typedef struct Cellule Cellule;
struct Cellule
{
    char c;
    Cellule *succ;
    Cellule *alt;
};

DicoABR *initDico();

int ajoutMot(DicoABR *tree, char *s);

Node *rechercheMot(DicoABR *tree, char *s);

int supprimeMot(DicoABR *tree, char *s);

void suggestionMots(DicoABR *tree, int k, char *souschaine);

void affichageDico(DicoABR *tree, Node *node, int n);

#endif // TP4_H_INCLUDED
