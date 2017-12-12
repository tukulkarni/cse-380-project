#!/bin/bash
set term post enh eps color font "Times,24" dash
datafile = 'testout.dat'
outfile  = 'testode.eps'
set out outfile

set size square
set style line 1 lw 3 dt 1 ps 2 pt 4 lc rgb 'blue'
set style line 2 lw 3 dt 2 ps 2 pt 7 lc rgb 'red'

set key inside vert left Left
set key nobox samplen 1.2 width -3 spacing 1.5
set key on

set xlabel 'log_{10}({/Symbol D}t)' offset 0,0 font "Times,26"
set xtics 1   
set ylabel 'log_{10}|| {/Symbol e} ||' offset 0,0 font "Times,26"
set ytics 1

plot datafile u (log10($1)):(log10($5)) w lp ls 1 t 'Euler fwd (user)',\
	 datafile u (log10($1)):(log10($6)) w lp ls 2 t 'Euler back (GSL)',\

!evince @outfile & 
