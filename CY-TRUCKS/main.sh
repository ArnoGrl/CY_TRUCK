#!/bin/bash


display_help() {
    echo "Usage: $0 <chemin_fichier_CSV> [options]"
    echo "Options:"
    echo "  -h  Display help"
    echo "  -d1 Perform processing [D1]"
    echo "  -d2 Perform processing [D2]"
    echo "  -l  Perform processing [L]"
    echo "  -t  Perform processing [T]"
    echo "  -s  Perform processing [S]"
}


if [ "$#" -lt 1 ]; then
    echo "Error: The CSV file path is required."
    display_help
    exit 1
fi


input_file="$1"



mkdir -p images
mkdir -p tmp


    case $2 in
    -h)
        display_help
        exit 0
        ;;
    d1 | d2 | l | t | s)
        echo "To do processing for option: -$opt"
        ;;
    \?)
        echo "Invalid option: -$OPTARG"
        display_help
        exit 0
        ;;
    esac



rm -rf temp

echo "Script completed."
