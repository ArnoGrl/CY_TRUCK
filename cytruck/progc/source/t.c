#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t.h"
#define MAX_CITY_NAME 50
#define MAX_LINE_LENGTH 1024

TownNode *createTownNode(char city[MAX_CITY_NAME])
{
    TownNode *newNode = (TownNode *)malloc(sizeof(TownNode));
    if (newNode == NULL)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    strcpy(newNode->name, city);
    newNode->routeCount = 1;
    newNode->departureCount = 0;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->height = 1;
    return newNode;
}

int getMax(int a, int b)
{
    return (a > b) ? a : b;
}

int getNodeHeight(TownNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

TownNode *rotateRight(TownNode *root)
{
    TownNode *newRoot = root->leftChild;
    TownNode *transferNode = newRoot->rightChild;

    newRoot->rightChild = root;
    root->leftChild = transferNode;

    root->height = getMax(getNodeHeight(root->leftChild), getNodeHeight(root->rightChild)) + 1;
    newRoot->height = getMax(getNodeHeight(newRoot->leftChild), getNodeHeight(newRoot->rightChild)) + 1;

    return newRoot;
}

TownNode *rotateLeft(TownNode *root)
{
    TownNode *newRoot = root->rightChild;
    TownNode *transferNode = newRoot->leftChild;

    newRoot->leftChild = root;
    root->rightChild = transferNode;

    root->height = getMax(getNodeHeight(root->leftChild), getNodeHeight(root->rightChild)) + 1;
    newRoot->height = getMax(getNodeHeight(newRoot->leftChild), getNodeHeight(newRoot->rightChild)) + 1;

    return newRoot;
}

int getBalanceFactor(TownNode *node)
{
    if (node == NULL)
        return 0;
    return getNodeHeight(node->leftChild) - getNodeHeight(node->rightChild);
}

void destroyTownTree(TownNode *root)
{
    if (root != NULL)
    {
        destroyTownTree(root->leftChild);
        destroyTownTree(root->rightChild);
        free(root);
    }
}

TownNode *insertTownData(TownNode *root, char city[MAX_CITY_NAME], int isDeparture)
{
    if (root == NULL)
    {
        return (createTownNode(city));
    }
    if (strcmp(city, root->name) < 0)
    {
        root->leftChild = insertTownData(root->leftChild, city, isDeparture);
    }
    else if (strcmp(city, root->name) > 0)
    {
        root->rightChild = insertTownData(root->rightChild, city, isDeparture);
    }
    else
    {
        // If the city is a departure city
        if (isDeparture) {
            node->nbDeparture += 1;
        }
        // Update the number of route passes through the city
        node->nbRoute += 1;
    }

    root->height = 1 + getMax(getNodeHeight(root->leftChild), getNodeHeight(root->rightChild));

    int balance = getBalanceFactor(root);

    // Rotations for rebalancing
    if (balance > 1 && strcmp(city, root->leftChild->name) < 0)
    {
        return rotateRight(root);
    }
    if (balance < -1 && strcmp(city, root->rightChild->name) > 0)
    {
        return rotateLeft(root);
    }
    if (balance > 1 && strcmp(city, root->leftChild->name) > 0)
    {
        root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }
    if (balance < -1 && strcmp(city, root->rightChild->name) < 0)
    {
        root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    return root;
}

void compileTownStatistics(TownNode *root, TownStatistics **stats, int *size, int *capacity)
{
    if (root == NULL)
        return;

    if (*size >= *capacity)
    {
        *capacity *= 2;
        *stats = (TownStatistics *)realloc(*stats, (*capacity) * sizeof(TownStatistics));
        if (*stats == NULL)
        {
            perror("Reallocation error");
            exit(EXIT_FAILURE);
        }
    }

    compileTownStatistics(root->leftChild, stats, size, capacity);

    TownStatistics *currentStat = &((*stats)[*size]);
    strcpy(currentStat->name, root->name);
    currentStat->routeCount = root->routeCount;
    currentStat->departureCount = root->departureCount;
    (*size)++;

    compileTownStatistics(root->rightChild, stats, size, capacity);
}

int compareRouteCount(const void *a, const void *b)
{
    TownStatistics *statA = (TownStatistics *)a;
    TownStatistics *statB = (TownStatistics *)b;
    return statB->routeCount - statA->routeCount;
}

void processCSVandBuildTree(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("File opening error");
        return;
    }

    char line[MAX_LINE_LENGTH];
    TownNode *root = NULL;

    // Skip header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        char departure_city[MAX_CITY_NAME], arrival_city[MAX_CITY_NAME];
        if (sscanf(line, "%*d;%*d;%[^;];%[^;];%*d;%*s", departure_city, arrival_city) == 2)
        {
            root = insertTownData(root, departure_city, 1);
            root = insertTownData(root, arrival_city, 0);
        }
    }
    fclose(file);

    TownStatistics *stats = (TownStatistics *)malloc(1 * sizeof(TownStatistics));
    int size = 0;     // Initialize size to 0 for accurate statistics collection
    int capacity = 1; // Start with a capacity of 1 and dynamically increase as needed
    compileTownStatistics(root, &stats, &size, &capacity);
    generateTopTownReport(stats, size, "top_towns.txt");

    free(stats);
    destroyTownTree(root);
}

int compareTownName(const void *a, const void *b)
{
    TownStatistics *statA = (TownStatistics *)a;
    TownStatistics *statB = (TownStatistics *)b;
    return strcmp(statA->name, statB->name);
}

void generateTopTownReport(TownStatistics *stats, int totalTowns, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("File opening error");
        return;
    }

    qsort(stats, totalTowns, sizeof(TownStatistics), compareRouteCount);

    int topTowns = totalTowns > 10 ? 10 : totalTowns;

    qsort(stats, topTowns, sizeof(TownStatistics), compareTownName);

    for (int i = 0; i < topTowns; i++)
    {
        fprintf(file, "%s, %d, %d\n", stats[i].name, stats[i].routeCount, stats[i].departureCount);
    }

    fclose(file);
}
