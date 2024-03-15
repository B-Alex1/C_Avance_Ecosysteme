set terminal png size 1280,960 crop
set output "graphe.gnu"

plot "Evol_Pop.txt" using 1:2 with lines title "proies", \
     "Evol_Pop.txt" using 1:3 with lines title "predateurs"
