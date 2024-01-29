#!/bin/bash

d2() {
    file=$1
    output_file="total_distance.txt"

    #addition de tout les trajet par conducteur
    awk -F';' '{sum[$6]+=$5} END {for (driver in sum) printf "%6d %s\n", sum[driver], driver}' "$file" | sort -k1,1nr | head -10 >"$output_file"

    #creation du graphique avec GNU plot
    gnuplot <<EOF
    
set terminal pngcairo enhanced font "arial,10" size 1200,1000
set output 'trajet_count.png'
set title ''

set label 1 "Distance total par conducteur (en km)" at screen 0.98,0.30 rotate by 90 font "arial,16" # Reglage de la position, l'orientation et la taille du titre

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

    convert 'trajet_count.png' -rotate 90 d2.jpg
}
