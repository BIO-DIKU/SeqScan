#!/usr/bin/env gnuplot

# Copyright (C) 2015 BIO-DIKU.

# Create a multiplot for comparing benchmarks of SeqScan and scan_for_matches.
# The top plot is a histogram of SeqScan vs scan_for_matches where the x axis
# show the different patterns being tested and the y axis shows the time.
# The bottom plot is a histogram of SeqScan vs scan_for_matches with the same
# x axis as above, but where the y axis shows the number of hits reported.

# Example data below (benchmark.dat):

# Pattern	SeqScan	SeqScan	SFM	SFM
# PCR		23	18128	273	23423
# approx_003	668	808511	23	2323
# approx_030	4536	442693	1	34355
# approx_222	32	30680	3522	1232
# approx_300	35	7861	232	34235
# exact	248	3469	32	3423
# snoRNA	671	36637	245	2255

set termopt noenhanced
set multiplot layout 2,1
set title "Benchmark"
set key autotitle column box samplen 1 noenhanced
set style data histogram
set style fill solid 0.5 border
set grid ytics
set ytics scale 0
set xtics scale 0 rotate by -45
set lmargin 15
set ylabel "Seconds"
plot 'benchmark.dat' using 2:xtic(1) noenhanced lt 1 lc rgb "#2BCE48", '' using 4 lt 2 lc rgb "#0075DC"

unset title
set ylabel "Hits"
set xlabel "Patterns"
plot 'benchmark.dat' using 3:xtic(1) lt 1 lc rgb "#2BCE48", '' using 5 lt 2 lc rgb "#0075DC"
