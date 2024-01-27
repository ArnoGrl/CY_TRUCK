#!/bin/bash

d2() {
    file=$1
    output_file="total_distance.txt"

    #Total distance made by each drivers
    time(awk -F';' '{distance[$6]+=$5} END {for(drivers in distance) print distance[drivers], drivers}' "$file" | sort -rn | head -10 >"$output_file" && echo "La commande a pris $(date +%s.%N -d@$SECONDS) secondes")

    #create the graphic
    gnuplot <<EOF
set terminal pngcairo enhanced font "arial,10" size 800,600
set output 'total_horizontal_distance.png'
set title 'Total distance travelled per drivers'
set ylabel 'Drivers'
set xlabel 'Total distance(km)'
set style data histogram
set style fill solid border -1
set ytics nomirror
set yrange [0:*]
set xrange [0:*]
set boxwidth 0.5 relative
set key off
plot '$output_file' using 1:xtic(2) with boxes title ''
EOF

    convert 'total_horizontal_distance.png' -rotate 90 distance_total.jpg
}

