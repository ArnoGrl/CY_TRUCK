#!/bin/bash

s() {
    make

    fichier_csv=$1

    # Chemin vers le programme compilé
    chemin_programme="./bin/progc"

    # Exécutions du programme avec les arguments
    $chemin_programme -s "$fichier_csv"

    awk -F' ' '{print $3, $6, $9, $12}' 50_Routes.txt | tr -d ',' | sort -n -k1,1 >output.txt
    output_file='output.txt'

    #creation du graphique avec GNU plot

    gnuplot <<EOF
set terminal png size 800,600
set output 's.jpg'
set title "Statistiques des distances par route"
set xlabel "Route ID"
set ylabel "Distance"
set grid
set key left top
set style line 1 lc rgb 'blue' lt 1 lw 2 pt 7 ps 1.5
set style line 2 lc rgb 'red' lt 1 lw 2 pt 11 ps 1.5
set style line 3 lc rgb 'green' lt 1 lw 2 pt 9 ps 1.5
plot "$output_file" using 1:2 with lines ls 1 title 'Min', \
     "" using 1:3 with lines ls 2 title 'Max', \
     "" using 1:4 with lines ls 3 title 'Moyenne'
EOF

    rm 50_Routes.txt
    rm output.txt
    mv s.jpg images/

    echo " "
    echo "éxecution réussie"
    echo "Graphique s.jpg créer dans le dossier images/"
    echo "retour au menu"

    exit 0
}
