#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRIPS 1000
#define TOP_TRIPS 10
#define LINE_LENGTH 256

typedef struct
{
    int routeID;
    float totalDistance;
} Route;

int compareTotalDistance(const void *a, const void *b)
{
    Route *routeA = (Route *)a;
    Route *routeB = (Route *)b;
    return (routeB->totalDistance > routeA->totalDistance) - (routeA->totalDistance > routeB->totalDistance);
}

int compareRouteID(const void *a, const void *b)
{
    Route *routeA = (Route *)a;
    Route *routeB = (Route *)b;
    return routeA->routeID - routeB->routeID;
}

void l(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    Route routes[MAX_TRIPS] = {0};
    int routeCount = 0;
    char line[LINE_LENGTH];
    fgets(line, sizeof(line), file); // Ignorer la première ligne (en-têtes)

    while (fgets(line, sizeof(line), file))
    {
        int routeID;
        float distance;
        sscanf(line, "%d;%*d;%*[^;];%*[^;];%f;%*s", &routeID, &distance);

        int found = 0;
        for (int i = 0; i < routeCount; i++)
        {
            if (routes[i].routeID == routeID)
            {
                routes[i].totalDistance += distance;
                found = 1;
                break;
            }
        }

        if (!found)
        {
            routes[routeCount].routeID = routeID;
            routes[routeCount].totalDistance = distance;
            routeCount++;
        }
    }
    fclose(file);

    qsort(routes, routeCount, sizeof(Route), compareTotalDistance);

    Route topRoutes[TOP_TRIPS];
    for (int i = 0; i < TOP_TRIPS && i < routeCount; i++)
    {
        topRoutes[i] = routes[i];
    }

    qsort(topRoutes, TOP_TRIPS, sizeof(Route), compareRouteID);

    FILE *outputFile = fopen("resultats.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        exit(1);
    }

    for (int i = 0; i < TOP_TRIPS && i < routeCount; i++)
    {
        fprintf(outputFile, "Route ID: %d, Total Distance: %.2f\n", topRoutes[i].routeID, topRoutes[i].totalDistance);
    }
    fclose(outputFile);
}