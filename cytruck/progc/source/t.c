#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t.h"
#define MAX_CITY_NAME 50
#define MAX_LINE_LENGTH 1024

typedef struct node {
    char city_name[MAX_CITY_NAME];
    int nbRoute;
    int nbDeparture;
    struct node* pLeft;
    struct node* pRight;
    int height;
}Node;

typedef struct cityStats {
    char city_name[MAX_CITY_NAME];
    int nbRoute;
    int nbDeparture;
} CityStats;

Node* createNode(char city[MAX_CITY_NAME]){
    Node* pNew = (Node*)malloc(sizeof(Node));
    if(pNew == NULL){
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    strcpy(pNew->city_name, city);
    pNew->nbRoute = 1;
    pNew->nbDeparture = 0;
    pNew->pLeft = NULL;
    pNew->pRight = NULL;
    pNew->height = 1;
    return pNew;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *N){
    if (N == NULL)
        return 0;
    return N->height;
}

Node* rightRotate(Node* y){
    Node* x = y->pLeft;
    Node* tmp = x->pRight;

    x->pRight = y;
    y->pLeft = tmp;

    y->height = max(height(y->pLeft), height(y->pRight)) + 1;
    x->height = max(height(x->pLeft), height(x->pRight)) + 1;

    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->pRight;
    Node* tmp = y->pLeft;

    y->pLeft = x;
    x->pRight = tmp;

    x->height = max(height(x->pLeft), height(x->pRight)) + 1;
    y->height = max(height(y->pLeft), height(y->pRight)) + 1;

    return y;
}

int getBalance(Node* N){
    if (N == NULL)
        return 0;
    return height(N->pLeft) - height(N->pRight);
}

void freeTree(Node *node){
    if (node != NULL){
        freeTree(node->pLeft);
        freeTree(node->pRight);
        free(node);
    }
}

Node* insertNode(Node* node, char city[MAX_CITY_NAME], int nbR, int nbD) {
    if (node == NULL){
        return(createNode(city));
    }
    if (strcmp(city, node->city_name) < 0) {
        node->pLeft = insertNode(node->pLeft, city, nbR, nbD);
    } else if (strcmp(city, node->city_name) > 0) {
        node->pRight = insertNode(node->pRight, city, nbR, nbD);
    } else {
        node->nbRoute += nbR;
        node->nbDeparture += nbD;
        return node; 
    }

    node->height = 1 + max(height(node->pLeft), height(node->pRight));

    int balance = getBalance(node);

    // Rotations pour rééquilibrer l'arbre
    if (balance > 1 && strcmp(city, node->pLeft->city_name) < 0) {
        return rightRotate(node);
    }
    if (balance < -1 && strcmp(city, node->pRight->city_name) > 0) {
        return leftRotate(node);
    }
    if (balance > 1 && strcmp(city, node->pLeft->city_name) > 0) {
        node->pLeft = leftRotate(node->pLeft);
        return rightRotate(node);
    }
    if (balance < -1 && strcmp(city, node->pRight->city_name) < 0) {
        node->pRight = rightRotate(node->pRight);
        return leftRotate(node);
    }

    return node;
}

void collectCityStats(Node* node, CityStats** stats, int* size, int* capacity) {
    if (node == NULL) return;

    if (*size >= *capacity) {
        *capacity *= 2;
        *stats = (CityStats*)realloc(*stats, (*capacity) * sizeof(CityStats));
        if (*stats == NULL) {
            perror("Erreur de reallocation");
            exit(EXIT_FAILURE);
        }
    }

    collectCityStats(node->pLeft, stats, size, capacity);

    CityStats* currentStat = &((*stats)[*size]);
    strcpy(currentStat->city_name, node->city_name);
    currentStat->nbRoute = node->nbRoute;
    currentStat->nbDeparture = node->nbDeparture;
    (*size)++;

    collectCityStats(node->pRight, stats, size, capacity);
}

int compareNbRoute(const void* a, const void* b) {
    CityStats* cityA = (CityStats*)a;
    CityStats* cityB = (CityStats*)b;
    return cityB->nbRoute - cityA->nbRoute;
}

int compareCityName(const void* a, const void* b) {
    CityStats* cityA = (CityStats*)a;
    CityStats* cityB = (CityStats*)b;
    return strcmp(cityA->city_name, cityB->city_name);
}

void writeTopCitiesToFile(CityStats* stats, int totalCities, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    qsort(stats, totalCities, sizeof(CityStats), compareNbRoute);

    int topCities = totalCities > 10 ? 10 : totalCities;

    qsort(stats, topCities, sizeof(CityStats), compareCityName);

    for (int i = 0; i < topCities; i++) {
        fprintf(file, "%s, %d, %d\n", stats[i].city_name, stats[i].nbRoute, stats[i].nbDeparture);
    }

    fclose(file);
}

void readCSVandPopulateAVL(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char line[MAX_LINE_LENGTH];
    Node* node = NULL;
   
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        char departure_city[MAX_CITY_NAME], arrival_city[MAX_CITY_NAME];
        if (sscanf(line, "%*d,%*d,%[^,],%[^,],%*d,%*s", departure_city, arrival_city) == 2) {
            node = insertNode(node, departure_city, 1, 1);
            node = insertNode(node, arrival_city, 1, 0);
        }
    }
    fclose(file);

    CityStats* stats = (CityStats*)malloc(1 * sizeof(CityStats));
    int size = 10;
    int capacity = 1;
    collectCityStats(node, &stats, &size, &capacity);
    writeTopCitiesToFile(stats, size, "top_cities.txt");

    free(stats);
    freeTree(node);
}
