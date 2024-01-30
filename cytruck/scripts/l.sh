#!/bin/bash

l() {

    # Compilation du programme
    echo "compilation du programme...."
    make

    # Exécution du programme compilé avec le fichier CSV en argument
    echo "compilation réussie"
    echo "execution du programme..."
    fichier_entree="$1"
    ./bin/progc "$fichier_entree"
    echo "execution finis"
    # Nettoyage, si nécessaire
    # make clean

}
