reset
set ylabel 'numbers'
set xlabel 'hash value'
set style fill solid
set title 'hash function distribute'
set term png enhanced font 'Verdana,10'
set output 'hashtime.png'

plot [:32800][:30]'hashdistribute.txt' using 2:xtic(1000) with linespoints title ''
