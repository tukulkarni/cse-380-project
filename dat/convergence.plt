#!/bin/bash
set term post enh eps color font "Times,24" dash
datafile1 = 'test_imprk1.dat'
datafile2 = 'test_exprk2.dat'
datafile3 = 'test_exprk4.dat'
outfile  = 'convergence.eps'
set out outfile

set size square
set style line 1 lw 3 dt 1 ps 2 pt 3 lc rgb 'blue'
set style line 2 lw 3 dt 2 ps 2 pt 7 lc rgb 'red'
set style line 3 lw 3 dt 3 ps 2 pt 9 lc rgb 'green'

set key inside vert left Left
set key nobox samplen 3 width -3 spacing 1.2
set key on

set xlabel 'log_{10}({/Symbol D}t)' offset 0,0 font "Times,26"
set xtics 1   
set ylabel 'log_{10}|| {/Symbol e} ||' offset 0,0 font "Times,26"
set ytics 3

set yrange[-16:4]

plot datafile1 u (log10($1)):(log10($6)) w lp ls 1 t 'Euler Backward',\
	 datafile2 u (log10($1)):(log10($6)) w lp ls 2 t 'RK2-3',\
	 datafile3 u (log10($1)):(log10($6)) w lp ls 3 t 'RK4'

!fixbb @outfile 
!evince @outfile & 
