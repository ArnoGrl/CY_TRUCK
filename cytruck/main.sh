#!/bin/bash

# Inclusion des fonctions
source scripts/d1.sh
source scripts/d2.sh
source scripts/l.sh
source scripts/t.sh
source scripts/s.sh

# Fonction d'aide
aide() {
    echo "Usage: $0 [options] [chemin/vers/fichier] "
    echo "Voici la list des options disponibles:"
    echo "  -h   : Affichee l'aide"
    echo "  -d1  : Affiche le conducteur avec le plus de trajets"
    echo "  -d2  : Affiche le conducteurs avec la plus grande distance"
    echo "  -l   : Affiche la liste des 10 plus longs trajets"
    echo "  -t   : Affiche les 10 villes les plus traversées"
    echo "  -s   : Affiche les statistiques sur chaque étape"
}

# Si -h est present dans les arguments, afficher l'aide
if [[ " $@ " == *" -h "* ]]; then
    aide
    exit 0
fi

# Si aucun argument n'est present ou qu'un seul est present, afficher l'aide
if [ $# -eq 0 ] || [ $# -eq 1 ]; then
    aide
    exit 1
fi

# Creation des dossiers tmp images data
mkdir -p temporaire images data

# Suppression des fichiers temporaires
rm -f temporaire/*

# Récupérer le nom du fichier sans le chemin absolu
fichier_entree="$2"
fichier_sortie=$(basename "$fichier_entree")

# Copier le fichier dans le dossier data
cp "$fichier_entree" "data/${fichier_sortie}"

# Choix des options
validation=1
while [ "$#" -gt 0 ]; do
    case "$1" in
    -d1)
        echo "Exécution du traitement d1..."
        time d1 "$fichier_entree"
        validation=0
        ;;
    -d2)
        echo "Exécution du traitement d2..."
        time d2 "$fichier_entree"
        validation=0
        ;;
    -l)
        echo "Exécution du traitement l..."
        time l "$fichier_entree"
        validation=0
        ;;
    -t)
        echo "Exécution du traitement t..."
        time t "$fichier_entree"
        validation=0
        ;;
    -s)
        echo "Execution du traitement s..."
        time s "$fichier_entree"
        validation=0
        ;;
    *)
        validation=1
        ;;
    esac
    shift
done

# Si aucune option n'est valide, afficher l'aide
if [ "$validation" -eq 1 ]; then
    echo "Aucune option valide"
    aide
    exit 1
fi
