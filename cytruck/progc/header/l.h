#ifndef L_H
#define L_H

// Structure pour un nœud dans l'arbre AVL
typedef struct route
{
    int routeID;
    float totalDistance;
    int height;
    struct route *left, *right;
} Route;

// Prototypes des fonctions
int max(int a, int b);
int height(Route *N);
Route *newNode(int routeID, float distance);
Route *rightRotate(Route *y);
Route *leftRotate(Route *x);
int getBalance(Route *N);
Route *insert(Route *node, int routeID, float distance);
void findTopRoutes(Route *node, Route topRoutes[], int *index);
void freeTree(Route *node);
void readCSVAndPopulateAVL(const char *filename);

#endif
