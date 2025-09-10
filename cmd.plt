set title "DFS Comparisons: Best vs Worst Case"
set xlabel "Input Size (n)"
set ylabel "Comparison Count"
set grid
set xrange [1:10]
set yrange [1:1000]
plot "warshallbest.txt" using 1:2 with linespoints title "Best Case", \
     "warshallworst.txt" using 1:2 with linespoints title "Worst Case"

