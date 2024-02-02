#ifndef S_H
#define S_H

#include <stdio.h>

// Constantes globales
#define MAX_LINE_LENGTH 1024
#define MAX_ROUTES 50

// Définition de la structure pour un nœud de l'arbre AVL
typedef struct node
{
    int route_id;
    float min_distance;
    float max_distance;
    float total_distance;
    int step_count;
    struct node *pLeft;
    struct node *pRight;
    int height;
} Node;

// Définition de la structure pour stocker les informations d'une route
typedef struct
{
    int route_id;
    float max_distance;
    float min_distance;
    float avg_distance;
} RouteInfo;

// Prototypes des fonctions
int Max(int a, int b);
int Height(Node *N);
Node *createNode(int routeId, float dist);
Node *RightRotate(Node *y);
Node *LeftRotate(Node *x);
int GetBalance(Node *N);
void FreeTree(Node *node);
void updateRoute(Node *node, float dist);
Node *insertNode(Node *node, int routeID, float distance);
int compareRouteDiff(const void *a, const void *b);
void traverseAndCollect(Node *node, RouteInfo routeInfos[], int *i);
void get50routes(Node *node, const char *outputFilename);
void readCSVAndPopulateAVL2(const char *filename);

#endif // S_H
