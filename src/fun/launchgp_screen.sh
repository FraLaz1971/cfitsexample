#!/usr/bin/env bash
echo 'executing launchgp_screen.sh $0 $@'
gnuplot << EOF
set terminal qt persist
set xlabel 'time (s)'
set ylabel 'counts #'
set title 'My Awesome Plot'
plot '-' using 1:2
  1	1
  2	4
  3	9
  4	16
  5	25
  6	36
  7	49
  8	64
  9	81
  10	100
  e
EOF
