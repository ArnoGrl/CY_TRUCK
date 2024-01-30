l() {
    # Compilation du programme
    echo "compilation du programme...."
    make

    # Vérifier si la compilation a réussi
    if [ $? -ne 0 ]; then
        echo "Erreur lors de la compilation."
        return 1
    fi

    # Exécution du programme compilé avec le fichier CSV en argument
    echo "compilation réussie"
    echo "execution du programme..."
    fichier_entree="$1"

    ./bin/progc "$fichier_entree"

    # Vérifier si l'exécution s'est terminée avec succès
    if [ $? -ne 0 ]; then
        echo "Erreur lors de l'exécution du programme."
        return 1
    fi

    echo "execution finie"
    # Nettoyage, si nécessaire
    # make clean
}
