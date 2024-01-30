#!/bin/bash

# Fonction pour compiler et exécuter le programme C
l() {
    echo "Compilation du programme..."
    make # Assurez-vous que le Makefile est configuré pour compiler main.c

    if [ $? -eq 0 ]; then
        echo "Compilation réussie."
        echo "Exécution du programme..."

        fichier_entree="$1"
        echo "on est la"
        ./bin/progc "$fichier_entree" # Exécution avec les arguments appropriés

        echo "Exécution terminée."
    else
        echo "Erreur de compilation."
    fi

    # Nettoyage, si nécessaire
    # make clean
}

# Appel de la fonction l avec le chemin du fichier CSV comme argument
l "chemin/vers/votre/fichier.csv"
