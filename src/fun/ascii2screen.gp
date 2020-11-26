set xrange [0:11]
set yrange [0:110]
set terminal qt persist 
set datafile separator "\t"
plot 'test.tsv' using 1:2

