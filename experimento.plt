set terminal pngcairo size 1920,1080
set output "experimento.png"

set title "Insertion sort vs Merge sort"
set xlabel "n"
set ylabel "Tiempo(microsegundos)"
set key top left
set grid

plot "resultados.dat" using 1:2 with linespoints title "iSort", "resultados.dat" using 1:3 with linespoints title "mSort"
