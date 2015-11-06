#!/usr/bin/env gnuplot

# Copyright (C) 2015 BIO-DIKU.

# Create a multiplot for comparing benchmarks of SeqScan and scan_for_matches.
# The top plot is a histogram of SeqScan vs scan_for_matches where the x axis
# show the different patterns being tested and the y axis shows the time.
# The bottom plot is a histogram of SeqScan vs scan_for_matches with the same
# x axis as above, but where the y axis shows the number of hits reported.

# Example data below (benchmark.dat):

# Pattern	SeqScan	SeqScan	SFM	SFM	PyRegex	PyRegex
# PCR	53	154.21	22	7.84	0	0.01
# approx_003	1317	18.44	1226	3.07	1141	5.61
# approx_030	29	17.62	19	2.95	12	5.52
# approx_222	1039267	1870.37	377191	29.04	317380	311.29
# approx_300	822	13.30	822	2.78	822	5.83
# exact	9	3.42	9	2.28	9	0.15

set termopt noenhanced
set multiplot layout 2,1
set title "Benchmark"
set key autotitle column box samplen 1
set style data histogram
set style fill solid 0.5 border
set grid ytics
set ytics scale 0
set xtics scale 0 rotate by -45
set lmargin 15
set ylabel "Seconds"
set logscale y
unset xtics
plot 'benchmark.dat' using 3:xtic(1) lt 1 lc rgb "#2BCE48", '' using 5 lt 2 lc rgb "#0075DC", '' using 7 lt 3 lc rgb "#FFCC33"

unset title
set tmargin 0
set ylabel "Hits"
set xlabel "Patterns"
set yrange [*:*] reverse
set xtics scale 0 rotate by -30 font "Arial,9"
unset key
plot 'benchmark.dat' using 2:xtic(1) lt 1 lc rgb "#2BCE48", '' using 4 lt 2 lc rgb "#0075DC", '' using 6 lt 3 lc rgb "#FFCC33"
unset multiplot

