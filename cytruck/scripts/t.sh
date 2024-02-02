#!/bin/bash

t() {
    make

    fichier_csv=$1

    # Chemin vers le programme compilé
    chemin_programme="./bin/progc"

    # Exécutions du programme avec les arguments
    $chemin_programme -t "$fichier_csv"

    exit 0
}
