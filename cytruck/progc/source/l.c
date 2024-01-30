#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256
#define TOP_TRIPS 10

typedef struct Route
{
    int routeID;
    float totalDistance;
    int height;
    struct Route *left, *right;
} Route;

// Prototypes des fonctions (ajoutez des déclarations ici pour une meilleure organisation)
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

// ... (Implémentations des fonctions)

// Libérer la mémoire de l'arbre AVL
void freeTree(Route *node)
{
    if (node != NULL)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

void readCSVAndPopulateAVL(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    char line[LINE_LENGTH];
    Route *root = NULL;

    fgets(line, sizeof(line), file); // Ignorer la première ligne

    while (fgets(line, sizeof(line), file))
    {
        int routeID;
        float distance;
        if (sscanf(line, "%d;%*d;%*[^;];%*[^;];%f;%*s", &routeID, &distance) == 2)
        {
            root = insert(root, routeID, distance);
        }
    }
    fclose(file);

    Route topRoutes[TOP_TRIPS] = {0};
    int index = 0;
    findTopRoutes(root, topRoutes, &index);

    FILE *outputFile = fopen("resultats.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        freeTree(root); // Libérer la mémoire avant de quitter
        exit(1);
    }

    for (int i = 0; i < index; i++)
    {
        fprintf(outputFile, "Route ID: %d, Total Distance: %.2f\n", topRoutes[i].routeID, topRoutes[i].totalDistance);
    }
    fclose(outputFile);

    freeTree(root); // Libérer la mémoire de l'arbre AVL
}