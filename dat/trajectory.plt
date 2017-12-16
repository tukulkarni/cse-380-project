#!/usr/bin/gnuplot -p
set term post enh eps color font "Times,22" 
datafile = 'trajectory.dat'
set output 'trajectory.eps'

set style line 1 lw 4.5 lt 2 pt 6 lc rgb 'blue'

set view equal xy
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z' offset 3,0

#set xrange [-5:5]
#set yrange [-10:0]
#set zrange [0:15]

set xtics 4
set ytics 4
set ztics 5

splot datafile u 2:3:4 w l lc rgb 'blue' t ''

!fixbb trajectory.eps
!evince trajectory.eps &
