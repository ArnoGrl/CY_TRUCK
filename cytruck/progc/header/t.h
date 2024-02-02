#ifndef T_H
#define T_H

#include <stdio.h>

#define MAX_CITY_NAME 50
#define MAX_LINE_LENGTH 1024

typedef struct TownNode
{
    char name[MAX_CITY_NAME];
    int routeCount;
    int departureCount;
    struct TownNode *leftChild;
    struct TownNode *rightChild;
    int height;
} TownNode;

typedef struct TownStatistics
{
    char name[MAX_CITY_NAME];
    int routeCount;
    int departureCount;
} TownStatistics;

// Prototypes des fonctions
TownNode *createTownNode(char city[MAX_CITY_NAME]);
int getMax(int a, int b);
int getNodeHeight(TownNode *node);
TownNode *rotateRight(TownNode *root);
TownNode *rotateLeft(TownNode *root);
int getBalanceFactor(TownNode *node);
void destroyTownTree(TownNode *root);
TownNode *insertTownData(TownNode *root, char city[MAX_CITY_NAME], int routes, int departures);
void compileTownStatistics(TownNode *root, TownStatistics **stats, int *size, int *capacity);
int compareRouteCount(const void *a, const void *b);
int compareTownName(const void *a, const void *b);
void generateTopTownReport(TownStatistics *stats, int totalTowns, const char *filename);
void processCSVandBuildTree(const char *filename);

#endif