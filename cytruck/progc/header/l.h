#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 256
#define TOP_TRIPS 10

// Définition de la structure Route
typedef struct Route
{
    int routeID;
    float totalDistance;
    int height;
    struct Route *left, *right;
} Route;

// Prototypes de fonctions
int max(int a, int b);
int height(Route *N);
Route *newNode(int routeID, float distance);
Route *rightRotate(Route *y);
Route *leftRotate(Route *x);
int getBalance(Route *N);
Route *insert(Route *node, int routeID, float distance);
void findTopRoutes(Route *node, Route topRoutes[], int *index);
void readCSVAndPopulateAVL(const char *filename);
void freeTree(Route *node); // Ajout d'une fonction pour libérer la mémoire de l'arbre

#endif // AVL_H
