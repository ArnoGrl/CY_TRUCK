#!/bin/bash

d1() {

    file=$1
    output_file="conducteur_counts.txt"

    # Compter les trajets par conducteur
    awk -F';' '{print $6}' "$file" | sort | uniq -c | sort -rn | head -10 >"$output_file"

    gnuplot <<EOF
    
set terminal pngcairo enhanced font "arial,10" size 1200,1000
set output 'conducteur_counts.png'
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

    convert 'conducteur_counts.png' -rotate 90 d1.jpg
    mv d1.jpg images/
    rm conducteur_counts.txt
    rm conducteur_counts.png
}
