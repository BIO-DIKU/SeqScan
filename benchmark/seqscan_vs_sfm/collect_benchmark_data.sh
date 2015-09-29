#!/bin/bash

# Copyright (C) 2015 BIO-DIKU.

# Script for collecting benchmark data from all pat_* directories. Each such
# directory should contain a seqscan.txt and a sfm.txt file with the output
# and runtime from the execution of seqscan and scan_for_matches, respectively.

# The resulting table should have the format:

# Pattern	SeqScan	SeqScan	SFM	SFM
# PCR		23	18128	273	23423
# approx_003	668	808511	23	2323
# approx_030	4536	442693	1	34355
# approx_222	32	30680	3522	1232
# approx_300	35	7861	232	34235
# exact	248	3469	32	3423
# snoRNA	671	36637	245	2255

# Function to extract pattern name form dir name.
pattern_name() {
    local dir=$1
    local name=`echo "$dir" | sed -e 's/pat_//'`

    echo $name
}

# Function to parse the run time from a file. The time is a time -p timestamp
# at the end of the file.
parse_time() {
    local file=$1
    local time=`tail -n 3 "$file" | grep user | sed -e 's/user//' | strings`

    echo $time
}

# Function to parse number of hits from a scan_for_matches result file.
parse_hits_sfm() {
    local file=$1
    local hits=`grep '^>' "$file" | wc -l`

    echo $hits
}

# Function to parse number of hits from a seqscan result file.
# FIXME: the 4x sed is ugly as hell, but head -n -4 is not a universal option.
# TODO: possibly we need a grep -v '^LOG' as well.
parse_hits_seqscan() {
    local file=$1
    local hits=`cat "$file" | sed '$d' | sed '$d' | sed '$d' | sed '$d' | wc -l`

    echo $hits
}

[ $# -eq 0 ] &&
{
    echo "Usage: `basename $0` <dir(s)> > <output file>"

    exit 1
}

DIRS=$@

echo -e "Pattern\tSeqScan\tSeqScan\tSFM\tSFM"

for dir in $DIRS; do
    seqscan_file="$dir/seqscan.txt"
    sfm_file="$dir/sfm.txt"

    if [[ -f "$seqscan_file" && -f "$sfm_file" ]]; then
        name=$(pattern_name "$dir")
        time_seqscan=$(parse_time "$seqscan_file")
        time_sfm=$(parse_time "$sfm_file")
        hits_seqscan=$(parse_hits_seqscan "$seqscan_file")
        hits_sfm=$(parse_hits_sfm "$sfm_file")

        echo -e "$name\t$time_seqscan\t$time_sfm\t$hits_seqscan\t$hits_sfm"
    fi
done;

exit 0