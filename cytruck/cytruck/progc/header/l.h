#ifndef L_H
#define L_H

typedef struct
{
    int routeID;
    float totalDistance;
} Route;

void l(const char *filename);
int compareTotalDistance(const void *a, const void *b);
int compareRouteID(const void *a, const void *b);

#endif
