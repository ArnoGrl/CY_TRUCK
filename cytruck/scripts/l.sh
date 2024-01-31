#!/bin/bash

# Fonction pour compiler et exécuter le programme C
l() {
    echo "compilation..."

    make # Assurez-vous que le Makefile est configuré pour compiler main.c

    echo "compilation réussie..."

    # Assigner les arguments à des variables pour plus de clarté
    fichier_csv=$1

    echo "execution..."
    # Chemin vers votre programme compilé
    chemin_programme="./bin/progc"

    # Exécuter le programme avec les arguments
    $chemin_programme -l "$fichier_csv"
    echo "execution réussie"

    sed -e 's/Route ID: \([0-9]*\), Total Distance: \([0-9]*\.[0-9]*\)/\1 \2/' resultats.txt >donne.txt
    output_file='donne.txt'

    gnuplot <<EOF
    
set terminal pngcairo enhanced font "arial,10" size 1200,1000
set output 'l.jpg'
set title ''

set label 1 "nombre de trajet par conducteur" at screen 0.98,0.30 rotate by 90 font "arial,16" # Reglage de la position, l'orientation et la taille du titre

set ylabel ''
set xlabel ''
set style data histogram
set style fill solid border -1

set ytics nomirror
set xtics nomirror offset 0,-9  # Décalage vers la gauche

set yrange [0:*]
set xrange [0:*]

set boxwidth 0.5 relative
set key off

set lmargin 6  # Marge gauche
set rmargin 6  # Marge droite
set tmargin 10  # Marge supérieure
set bmargin 10  # Marge inférieure

set ytics rotate by 90 # Rotation des étiquettes de l'axe des ordonnée
set xtics rotate by 90  # Rotation des étiquettes de l'axe des abscisses

set arrow 1 from 0.5,0 to 0.5,1 nohead lt 0 lw 2  # Ligne de référence verticale
set arrow 2 from 1.5,0 to 1.5,1 nohead lt 0 lw 2  # Ligne de référence verticale

plot '$output_file' using 1:xticlabels(stringcolumn(2)." ".stringcolumn(3)) with boxes title ''
EOF

    mv l.jpg images/
    rm resultats.txt
    rm donne.txt
    exit 1
}
