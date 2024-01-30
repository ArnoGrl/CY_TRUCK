#include <stdio.h>
#include <string.h>

// Inclusions des fichiers d'en-tête
#include "../header/d1.h"
#include "../header/d2.h"
#include "../header/t.h"
#include "../header/s.h"
#include "../header/l.h"

// La fonction 'l' doit être définie dans l'un de vos fichiers d'en-tête, probablement dans 'l.h'.

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Utilisation: %s <fichier> <commande>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[2], "-l") == 0)
    {
        readCSVAndPopulateAVL(argv[1]);
    }
    else if (strcmp(argv[2], "-t") == 0)
    {
        // Appelez la fonction correspondant à la commande -t
        // t(argv[1]);
    }
    else
    {
        fprintf(stderr, "Commande non reconnue: %s\n", argv[2]);
        return 1;
    }

    return 0;
}
