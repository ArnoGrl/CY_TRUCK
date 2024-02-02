#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclusions des fichiers d'en-tête pour la modularité et l'accès aux fonctions définies ailleurs
#include "../header/d1.h"
#include "../header/d2.h"
#include "../header/t.h"
#include "../header/s.h"
#include "../header/l.h"

int main(int argc, char const *argv[])
{
    // Vérifier si le nombre d'arguments passés est suffisant
    // argc compte le nombre total d'arguments, y compris le nom du programme
    if (argc < 3)
    {
        // Si le nombre d'arguments est insuffisant, afficher un message d'erreur et la syntaxe d'utilisation correcte
        fprintf(stderr, "Usage: %s <option> <argument>\n", argv[0]);
        return 1; // Retourner 1 indique une erreur
    }

    // Comparer le premier argument après le nom du programme pour déterminer l'action à effectuer
    if (strcmp(argv[1], "-l") == 0)
    {
        // Si l'option est "-l", appeler une fonction pour lire un fichier CSV et peupler une structure de données AVL
        readCSVAndPopulateAVL(argv[2]); // argv[2] contient l'argument passé à l'option, le fichier data.csv
    }
    else if (strcmp(argv[1], "-t") == 0)
    {
        printf("Malheuresement nous n'avons pas pu finir le traitement -t dans le temp impartie.\nnous l'avons pourtant commencé (voir t.c, t.sh)\n\n");
        processCSVandBuildTree(argv[2]);
        }
    else if (strcmp(argv[1], "-s") == 0)
    {

        readCSVAndPopulateAVL2(argv[2]);
    }
    else
    {
        // Si aucune des options reconnues n'est fournie, afficher un message d'erreur
        fprintf(stderr, "Option non reconnue : %s\n", argv[1]);
        return 1; // Retourner 1 pour indiquer une erreur
    }

    return 0; // Si tout se passe bien, retourner 0 pour indiquer une exécution réussie
}