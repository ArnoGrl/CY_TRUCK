#!/bin/bash

d1() {

    file=$1
    output_file="conducteur_counts.txt"

    # Compter les trajets par conducteur
    time (awk -F';' '{print $6}' "$file" | sort | uniq -c | sort -rn | head -10 >"$output_file" && echo "La commande a pris $(date +%s.%N -d@$SECONDS) secondes")
    echo -e "\nliste des 10 plus gros conducteur : \n"

    cat conducteur_counts.txt

    gnuplot <<EOF
set terminal pngcairo enhanced font "arial,10" size 800,600
set output 'conducteur_counts_horizontal.png'
set title 'Nombre de trajets par conducteur'
set ylabel 'Conducteur'
set xlabel 'Nombre de trajets'
set style data histogram
set style fill solid border -1
set ytics nomirror
set yrange [0:*]
set xrange [0:*]
set boxwidth 0.5 relative
set key off
plot '$output_file' using 1:xtic(2) with boxes title ''
EOF
}
