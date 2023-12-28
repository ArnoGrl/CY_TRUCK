#!/bin/bash

# Vérifier s'il y a un argument passé et que c'est un fichier
if [ $# -ne 1 ]; then
    echo "Usage: $0 notes.txt"
    exit 1
fi

file=$1

# Vérifier si le fichier existe et est un fichier régulier
if [ ! -f "$file" ]; then
    echo "Le fichier spécifié n'existe pas."
    exit 1
fi

# Chemin du fichier CSV
file=$1
output_file="conducteur_counts.txt"

# Compter les trajets par conducteur
time (awk -F';' '{print $6}' "$file" | sort | uniq -c | sort -rn | head -10 > "$output_file" && echo "La commande a pris $(date +%s.%N -d@$SECONDS) secondes")
echo -e "\nliste des 10 plus gros conducteur : \n"

cat conducteur_counts.txt


# Utilisation des données dans le fichier temporaire pour générer le graphique Gnuplot
gnuplot << EOF
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