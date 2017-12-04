#!/usr/bin/gnuplot -p
set term post enh eps color font "Times,24" 
set style line 1 lw 2.5 lt 2 pt 6 lc rgb 'blue'

set output 'trajectory.eps'
set size square
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'

set xrange [-5:5]
set yrange [-10:0]
set zrange [0:10]

set xtics 5
set ytics 5
set ztics 5

splot 'trajectory.dat' u 2:3:4 w l lc rgb 'blue'

!fixbb trajectory.eps
!evince trajectory.eps &
