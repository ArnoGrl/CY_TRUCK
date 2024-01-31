#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "l.h" // Assurez-vous d'inclure le fichier d'en-tête correspondant

#define LINE_LENGTH 256
#define TOP_TRIPS 10

typedef struct route
{
    int routeID;
    float totalDistance;
    int height;
    struct route *left, *right;
} Route;

// Prototypes des fonctions (ajoutez des déclarations ici pour une meilleure organisation)
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Fonction pour obtenir la hauteur d'un nœud
int height(Route *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// Fonction pour créer un nouveau nœud
Route *newNode(int routeID, float distance)
{
    Route *node = (Route *)malloc(sizeof(Route));
    if (node == NULL)
    {
        perror("Erreur d'allocation mémoire");
        exit(1);
    }
    node->routeID = routeID;
    node->totalDistance = distance;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Rotation à droite d'un nœud y
Route *rightRotate(Route *y)
{
    Route *x = y->left;
    Route *T2 = x->right;

    // Effectuer la rotation
    x->right = y;
    y->left = T2;

    // Mettre à jour les hauteurs des nœuds
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotation à gauche d'un nœud x
Route *leftRotate(Route *x)
{
    Route *y = x->right;
    Route *T2 = y->left;

    // Effectuer la rotation
    y->left = x;
    x->right = T2;

    // Mettre à jour les hauteurs des nœuds
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Obtenir le facteur de balance d'un nœud N
int getBalance(Route *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insérer un nouvel élément dans l'arbre AVL
Route *insert(Route *node, int routeID, float distance)
{
    // Si le nœud est nul, créer un nouveau nœud
    if (node == NULL)
        return newNode(routeID, distance);

    // Effectuer une insertion récursive
    if (routeID < node->routeID)
        node->left = insert(node->left, routeID, distance);
    else if (routeID > node->routeID)
        node->right = insert(node->right, routeID, distance);
    else // Les clés égales ne sont pas autorisées
        return node;

    // Mettre à jour la hauteur du nœud actuel
    node->height = 1 + max(height(node->left), height(node->right));

    // Obtenir le facteur de balance du nœud actuel
    int balance = getBalance(node);

    // Cas de déséquilibre gauche-gauche
    if (balance > 1 && routeID < node->left->routeID)
        return rightRotate(node);

    // Cas de déséquilibre droit-droit
    if (balance < -1 && routeID > node->right->routeID)
        return leftRotate(node);

    // Cas de déséquilibre gauche-droit
    if (balance > 1 && routeID > node->left->routeID)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Cas de déséquilibre droit-gauche
    if (balance < -1 && routeID < node->right->routeID)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retourner le nœud inchangé
    return node;
}

// Fonction pour trouver les 10 routes les plus longues
void findTopRoutes(Route *node, Route topRoutes[], int *index)
{
    if (node == NULL)
        return;

    // Traversez l'arbre en ordre décroissant (droite-gauche-racine)
    findTopRoutes(node->right, topRoutes, index);

    // Triez les routes par distance décroissante en utilisant une insertion simple
    int i = (*index) - 1;
    while (i >= 0 && node->totalDistance > topRoutes[i].totalDistance)
    {
        topRoutes[i + 1] = topRoutes[i];
        i--;
    }
    topRoutes[i + 1] = *node;

    // Ne conservez que les 10 premières routes
    if (*index < 10)
    {
        (*index)++;
    }
    else
    {
        (*index) = 10;
    }

    // Continuez à parcourir l'arbre
    findTopRoutes(node->left, topRoutes, index);
}
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
