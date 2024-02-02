#!/bin/bash

l() {

    make

    fichier_csv=$1

    # Chemin vers le programme compilé
    chemin_programme="./bin/progc"

    # Exécution du programme avec les arguments
    $chemin_programme -l "$fichier_csv"

    sed -e 's/Route ID: \([0-9]*\), Total Distance: \([0-9]*\.[0-9]*\)/\1 \2/' resultats.txt >donne.txt
    output_file='donne.txt'

    #creation du graphique avec GNU plot

    gnuplot <<EOF
    
set terminal pngcairo enhanced font "arial,10" size 1200,1000
set output 'l.jpg'
set title "Les 10 trajets les plus longs"


set ylabel 'Distance (en km)'
set xlabel 'Route ID'
set style data histogram
set style fill solid border -1

set ytics nomirror
set xtics nomirror offset 0,-9  # Décalage vers la gauche

set yrange [0:*]
set xrange [0:10] 

set boxwidth 0.5 relative
set key off

set lmargin 10  # Marge gauche
set rmargin 10  # Marge droite
set tmargin 10  # Marge supérieure
set bmargin 10  # Marge inférieure

set ytics rotate by 90 # Rotation des étiquettes de l'axe des ordonnées
set xtics rotate by 90  # Rotation des étiquettes de l'axe des abscisses

set arrow 1 from 0.5,0 to 0.5,1 nohead lt 0 lw 2  # Ligne de référence verticale
set arrow 2 from 1.5,0 to 1.5,1 nohead lt 0 lw 2  # Ligne de référence verticale

plot '$output_file' using 2:xticlabels(stringcolumn(1)) with boxes title ''
EOF

    mv l.jpg images/
    rm resultats.txt
    rm donne.txt

    echo " "
    echo "éxecution réussie"
    echo "Graphique l.jpg créer dans le dossier images/"
    echo "retour au menu"

    exit 0

}
