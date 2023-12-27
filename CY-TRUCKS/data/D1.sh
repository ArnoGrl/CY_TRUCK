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
time (awk -F';' '{print $6}' "$file" | sort | uniq -c | sort -rn > "$output_file" && echo "La commande a pris $(date +%s.%N -d@$SECONDS) secondes")
echo -e "\nliste des 10 plus gros conducteur : \n"

cat $output_file | head -10


# Utilisation des données dans le fichier temporaire pour générer le graphique Gnuplot
gnuplot << EOF
set terminal pngcairo enhanced font "arial,10" size 800,600
set output 'conducteur_counts.png'
set title 'Nombre de trajets par conducteur'
set xlabel 'Nombre de trajets'
set ylabel 'Conducteur'
set ytics nomirror
set yrange [0:*]
set style data histograms
set style fill solid border -1
plot '$output_file' using 1:xtic(2) title ''
EOF
