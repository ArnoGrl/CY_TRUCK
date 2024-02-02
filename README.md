# CY_TRUCK

Guide d'utilisation de CY Truck
Introduction

CY Truck est un programme conçu pour gérer les données logistiques d'une entreprise nationale de transport routier. Ce script shell main.sh automatise l'analyse de fichiers de données CSV et génère des graphiques utiles pour résumer les activités de l'entreprise.
Prérequis

Avant de commencer, assurez-vous que les outils suivants sont installés sur votre système :

    GnuPlot : pour la génération de graphiques.
    Bash : pour exécuter le script shell.

Vous pouvez installer GnuPlot via le gestionnaire de paquets de votre système d'exploitation.


    sudo apt-get update
    sudo apt-get install gnuplot


Installation

Clonez le dépôt du projet :

    git clone [URL_DU_DEPOT]

Naviguez jusqu'au répertoire du projet cloné :



    cd [NOM_DU_REPERTOIRE]

Configuration

Accordez les permissions nécessaires au script pour permettre son exécution :

    chmod +x main.sh



Utilisation

Pour exécuter le programme, utilisez la commande suivante dans votre terminal, en remplaçant [CHEMIN_VERS_FICHIER_CSV] par le chemin réel vers votre fichier CSV.


    ./main.sh  [OPTION] [CHEMIN_VERS_FICHIER_CSV]

Options

Le script supporte plusieurs options qui déterminent le type de traitement à effectuer :

    -h : Affiche un message d'aide avec les options disponibles.
    -d1 : Génère un histogramme horizontal des 10 conducteurs ayant effectué le plus de trajets.
    -d2 : Produit un histogramme horizontal de la distance totale parcourue par les conducteurs.
    -l : Crée un histogramme vertical des 10 trajets les plus longs.
    -t : Compte le nombre de trajets passant par chaque ville et génère un histogramme groupé.
    -s : Collecte des statistiques sur les étapes de chaque trajet et crée un graphique de courbes.

Interprétation des Résultats

Après exécution, le script génère des graphiques qui sont sauvegardés dans le répertoire images et peuvent être consultés pour l'analyse.

ATTENTION : Chaque traitement doit être exécuté individuellement, le programme ne peut exécuter qu'un traitement à la fois.

