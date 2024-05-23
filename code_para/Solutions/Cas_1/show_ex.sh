#!/bin/bash

# Trouver la valeur maximale de X
max_X=$(ls sol*.0.dat | awk -F'[.]' '{print substr($1, 4)}' | sort -n | tail -n 1)

# Boucle sur tous les X jusqu'à la valeur maximale trouvée
for ((X=0; X<=max_X; X++)); do
    # Concatène tous les fichiers solX.*.dat en solX.dat
    cat sol_ex${X}.*.dat > sol_ex${X}.dat
done

gnuplot plot_ex.txt
