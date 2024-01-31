#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclusions des fichiers d'en-tête
#include "../header/d1.h"
#include "../header/d2.h"
#include "../header/t.h"
#include "../header/s.h"
#include "../header/l.h"

int main(int argc, char const *argv[])
{
    // Vérifier si le nombre d'arguments est suffisant
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <option> <argument>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-l") == 0)
    {
        printf("Exécution avec l...\n");
        readCSVAndPopulateAVL(argv[2]);
    }
    else if (strcmp(argv[1], "-t") == 0)
    {
        printf("Exécution avec t...\n");
        t();
    }
    else
    {
        fprintf(stderr, "Option non reconnue : %s\n", argv[1]);
        return 1;
    }

    return 0;
}