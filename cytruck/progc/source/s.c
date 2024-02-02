#include <stdio.h>
#include <stdlib.h>
#include "s.h"
#define MAX_LINE_LENGTH 1024
#define MAX_ROUTES 50

int Max(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int Height(Node *N)
{

    if (N == NULL)
        return 0;
    return N->height;
}

Node *createNode(int routeId, float dist)
{

    Node *pNew = malloc(sizeof(Node));
    if (pNew == NULL)
    {
        printf("Erreur d'allocation mémoire");
        exit(1);
    }
    pNew->route_id = routeId;
    pNew->max_distance = dist;
    pNew->min_distance = dist;
    pNew->total_distance = dist;
    pNew->step_count = 1;
    pNew->height = 1;
    pNew->pLeft = NULL;
    pNew->pRight = NULL;
    return pNew;
}

Node *RightRotate(Node *y)
{
    Node *x = y->pLeft;
    Node *tmp = x->pRight;

    x->pRight = y;
    y->pLeft = tmp;

    // Mettre à jour les hauteurs des nœuds
    y->height = Max(Height(y->pLeft), Height(y->pRight)) + 1;
    x->height = Max(Height(x->pLeft), Height(x->pRight)) + 1;

    return x;
}

Node *LeftRotate(Node *x)
{

    Node *y = x->pRight;
    Node *tmp = y->pLeft;

    y->pLeft = x;
    x->pRight = tmp;

    x->height = Max(Height(x->pLeft), Height(x->pRight)) + 1;
    y->height = Max(Height(y->pLeft), Height(y->pRight)) + 1;

    return y;
}

int GetBalance(Node *N)
{

    if (N == NULL)
        return 0;
    return Height(N->pLeft) - Height(N->pRight);
}

void FreeTree(Node *node)
{
    if (node != NULL)
    {
        FreeTree(node->pLeft);
        FreeTree(node->pRight);
        free(node);
    }
}

// function to update the maximal and mina
void updateRoute(Node *node, float dist)
{
    if (node->step_count == 0)
    {
        node->max_distance = dist;
        node->min_distance = dist;
    }
    else
    {
        if (dist < node->min_distance)
        {
            node->min_distance = dist;
        }
        else if (dist > node->max_distance)
        {
            node->max_distance = dist;
        }
    }
    node->total_distance += dist;
    node->step_count++;
}

// Insérer un nouvel élément dans l'arbre AVL
Node *insertNode(Node *node, int routeID, float distance)
{

    if (node == NULL)
        return createNode(routeID, distance);

    if (routeID < node->route_id)
    {
        node->pLeft = insertNode(node->pLeft, routeID, distance);
    }
    else if (routeID > node->route_id)
    {
        node->pRight = insertNode(node->pRight, routeID, distance);
    }
    else
    {
        updateRoute(node, distance);
        return node;
    }
    // Mettre à jour la hauteur du nœud actuel
    node->height = 1 + Max(Height(node->pLeft), Height(node->pRight));

    // Obtenir le facteur de balance du nœud actuel
    int balance = GetBalance(node);

    // Cas de déséquilibre gauche-gauche
    if (balance > 1 && routeID < node->pLeft->route_id)
        return RightRotate(node);

    // Cas de déséquilibre droit-droit
    if (balance < -1 && routeID > node->pRight->route_id)
        return LeftRotate(node);

    // Cas de déséquilibre gauche-droit
    if (balance > 1 && routeID > node->pLeft->route_id)
    {
        node->pLeft = LeftRotate(node->pLeft);
        return RightRotate(node);
    }

    // Cas de déséquilibre droit-gauche
    if (balance < -1 && routeID < node->pRight->route_id)
    {
        node->pRight = RightRotate(node->pRight);
        return LeftRotate(node);
    }

    return node;
}

// Fonction de comparaison pour le tri
int compareRouteDiff(const void *a, const void *b)
{
    const RouteInfo *routeA = (const RouteInfo *)a;
    const RouteInfo *routeB = (const RouteInfo *)b;
    float diffA = routeA->max_distance - routeA->min_distance;
    float diffB = routeB->max_distance - routeB->min_distance;

    // Retourner un entier négatif si diffA < diffB, positif si diffA > diffB, et 0 si égaux
    return (diffA < diffB) - (diffA > diffB);
}

// Fonction récursive pour parcourir l'arbre et collecter les données
void traverseAndCollect(Node *node, RouteInfo routeInfos[], int *i)
{
    if (node == NULL || *i >= MAX_ROUTES)
    {
        return;
    }
    traverseAndCollect(node->pLeft, routeInfos, i);

    if (*i < MAX_ROUTES)
    {
        routeInfos[*i].route_id = node->route_id;
        routeInfos[*i].max_distance = node->max_distance;
        routeInfos[*i].min_distance = node->min_distance;
        routeInfos[*i].avg_distance = node->step_count > 0 ? node->total_distance / node->step_count : 0;
        (*i)++;
    }

    traverseAndCollect(node->pRight, routeInfos, i);
}

// Fonction principale pour obtenir les 50 premières routes
void get50routes(Node *node, const char *outputFilename)
{
    RouteInfo routeInfos[MAX_ROUTES];
    int index = 0;

    // Parcourir l'arbre et collecter les différences
    traverseAndCollect(node, routeInfos, &index);

    // Trier le tableau de différences
    qsort(routeInfos, index, sizeof(RouteInfo), compareRouteDiff);

    // Écrire les 50 premières (ou moins) routes dans un fichier
    FILE *file = fopen(outputFilename, "w");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        return;
    }
    for (int i = 0; i < index && i < MAX_ROUTES; i++)
    {
        fprintf(file, "Route ID: %d, Distance max: %f, Distance min: %f, Distance moyenne: %f\n",
                routeInfos[i].route_id, routeInfos[i].max_distance, routeInfos[i].min_distance, routeInfos[i].avg_distance);
    }
    fclose(file);
}

void readCSVAndPopulateAVL2(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    Node *node = NULL;

    // Ignore the first line;
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        int routeID;
        float distance;
        if (sscanf(line, "%d;%*d;%*[^;];%*[^;];%f;%*s", &routeID, &distance) == 2)
        {
            node = insertNode(node, routeID, distance);
        }
    }
    fclose(file);

    FILE *outputFile = fopen("50_Routes.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        FreeTree(node); // Libérer la mémoire avant de quitter
        exit(1);
    }
    get50routes(node, "50_Routes.txt");
    FreeTree(node);
}