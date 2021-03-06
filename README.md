# SeqScan

![](https://github.com/BIO-DIKU/SeqScan/blob/develop/logo.png)

Table of Contents
=================

  * [SeqScan](#seqscan)
    * [Synopsis](#synopsis)
    * [Download](#download)
    * [Installation](#installation)
    * [Pattern syntax](#pattern-syntax)
    * [Output](#output)
    * [Examples](#examples)
    * [Advanced](#advanced)
    * [Filter](#filter)
    * [Copyright](#copyright)
    * [License](#license)
    * [Disclaimer](#disclaimer)
    * [Acknowledgement](#acknowledgement)
    * [Contact](#contact)
    * [Cite](#cite)
    * [Bugs](#bugs)

## Synopsis

SeqScan locate pattern matches in nucleotide and protein sequences. A pattern
consists of one or more pattern units (see pattern section). A pattern match is
a substring of the sequence that satisfies the criteria of all pattern units.

    Usage: seqscan [options] <file(s)>

       [options]:
       -h --help                               Print this help menu.
       -p --pattern <pattern>                  Pattern to use, see the pattern
                                               section in the documentation.
       -P --pattern_file <string>              File with list of patterns, one
                                               per line.
       -c --complement <forward|reverse|both>  Scan the forward, reverse or
                                               both strands
                                               (default=forward).
       -d --direction <forward|reverse>        Scan direction
                                               (default=forward).
       -s --start <int>                        Start scanning position
                                               (default=1).
       -e --end <int>                          End scanning position.
       -t --threads <int>                      Threads to use (default=1).
       -E --score_encoding <Phred33|Phred64>   Specify FASTQ score encoding
                                               (default=Phred33).
       -S --score_min <int>                    Minimum Phred score in matches.
       -a --ambiguate                          Ambiguate residues with score
                                               below the minimum Phred score.
       -m --match_type <int>                   Match type used (default=6):

          Features:
             N: Nucleotide.
             P: Protein.
             A: Ambiguity codes.
             I: Case insensitive.

          Match type   Sequence   Pattern
          ----------   --------   -------
          1            N          N
          2            NI         NI
          3            NA         N
          4            NIA        NI
          5            N          NA
          6            NI         NIA (default)
          7            NA         NA
          8            NIA        NIA
          9            P          P
          10           PI         PI

       -M --match_file <string>                File with custom match type
                                               matrices.
       -o --output <string>                    Output file.
       -O --overlap                            Output overlapping matches.
       -f --filter <filter>                    Filter matches, see the filter
                                               section in the documentation.
       -v --version                            Output program version.
       -V --verbose                            Enable verbose messages.

    Documentation: https://github.com/BIO-DIKU/SeqScan

## Download

Below links are currently not functional - do ignore.

* [Linux x86_64](http://github.com/BIO-DIKU/SeqScan/download/SeqScan-linux-latest-x86_64.tar.gz)
* [MacOSX x86_64](http://github.com/BIO-DIKU/SeqScan/download/SeqScan-macosx-latest-x86_64.tar.gz)
* [Source code](http://github.com/BIO-DIKU/SeqScan/download/SeqScan-latest-src.tar.gz)

## Installation



### Compiling source

SeqScan compiles with C++11 support but has no dependencies on other external
libraries. To prepare makefiles for release versions of the library and
executable, download the source code (see above) and type:

    $ tar -xzvf SeqScan-latest-src.tar.gz
    $ cd SeqScan-latest-src
    $ mkdir SeqScan-build
    $ cd SeqScan-build
    $ cmake ../SeqScan-latest-src

After running `make`, the static library will be in SeqScan-build/libseqscan.a
and the executable in SeqScan-build/seqscan. To install in the system folders
type `make install`.

To prepare makefiles for debugging, instead type:

    $ mkdir SeqScan-debug
    $ cd SeqScan-debug
    $ cmake -DCMAKE_BUILD_TYPE=Debug ../SeqScan-latest-src

## Pattern syntax

Patterns consist of one or more pattern units of the types: exact, approximate,
range, and match group. One or more pattern units can be collected in
composites and both pattern units and composites can have named backreferences.
Below `=~` indicates a search for a match and `=>` indicates the resulting
matches. Matches are given as match position, match length, edit distance, and
matched sequence substring.

### Exact

An exact pattern unit is the simplest form of pattern, and will match a
sequence (to the left of `=~`) if the pattern (to the right of `=~`) is a
subsequence:

    GAGATCGAG =~ ATC => 4,3,0,ATC

### Approximate

An approximate pattern unit is any pattern unit with edit modifiers except
composites.

**Mismatches:** allow a number of non-matching residues:

    ATGCA =~ TAC/1,0,0 => 2,3,1,TGC

**Insertions:** allow a number of extra pattern residues:

    GTAACG =~ TAC/0,1,0 => 2,4,1,TAAC

**Deletions:** allow a number of missing pattern residues:

    GTCG =~ TAC/0,0,1 => 2,2,1,TC

**Edits:** allow a number of mismatches, insertions and deletions:

    TAACGTCGTGC =~ TAC/1 => 1,2,1,TA and 1,3,1,TAA and 2,3,1,AAC and 1,4,1,TAAC
    and 6,2,1,TC and 9,3,1,TGC

**Mismatches, indels:** allow a number of mismatches and a number of insertions
and deletions (indels):

    TAACGTCGTGC =~ TAC/0,1 => 1,2,1,TA and 3,1,1,AC and 1,4,1,TAAC and 6,2,1,TC

### Reverse/Complement

The reverse and reverse-complement operators can be applied to exact and
approximate pattern units as well as composites and backreferences.

The reverse operator `<` indicates that the pattern unit will match the reverse
sequence:

    GAGCTAGAG =~ <ATC => 4,3,0,CTA

The reverse-complement operator `~` indicates that the pattern unit will match
the reverse-complement sequence:

    GAGGATGAG =~ ~ATC => 4,3,0,GAT

It is possible to combine the reverse and reverse-complement operators (in any
order) to match the complement sequence:

    GAGTAGGAG =~ <~ATC => 4,3,0,TAG

### Or

The or operator `|` can be used to evaluate multiple pattern units, composites,
and backreferences such that if any match, then the pattern matches:

    TAGATAC =~ TAC|TAG => 1,3,0,TAG and 4,3,0,TAC

### Composite

Multiple pattern units can be collected in composite pattern units using
parentheses:

    ACTGTGT =~ (T ~AC)|ACT => 1,3,0,ACT and 5,1,0,T;6,2,0,GT

### Repetitions

Repetitions can be added to pattern units and backreferences so a series of
submatches must occur.

**Repetitions:** allows a number of repetitions:

    GTACTACG =~ TAC{2} => 2,3,0,TAC;5,3,0TAC

**Closed repetitions:** allows a minimum and a maximum of repetitions:

    GTACTACTACTACG =~ TAC{2,3} => 2,3,0,TAC;5,3,0,TAC;8,3,0,TAC

NB. SeqScan have greedy behavior so it will match as much as possible.

**Open repetitions:** allow a minimum of repetitions:

    GTACTACTACTACG =~ TAC{2,} => 2,3,0,TAC;5,3,0,TAC;8,3,0,TAC;11,3,0,TAC

This allows for shorthands using the Kleene `*` and `+` modifiers indicating
zero or more matches, and one or more matches, respectively. E.g. `TAC*` is
equal to `TAC{0,}` and `TAC+` is equal to `TAC{1,0}`.

It is also possible to add edit modifiers to repetitions:

**Exact repetitions:**

    ATGCTGCA =~ TAC/1,0,0{2} => 2,3,1,TGC;5,3,1,TGC
    (but it will not match the sequence ATGCTACA)

**Approximate repetitions:**

    ATGCTACA =~ TAC{2}/1,0,0 => 2,3,1,TGC;5,3,0,TAC

### Wildcard

The `.` character can be used as a wildcard in exact and approximate pattern
units:

    GAGTGCG =~ A.T.C => 2,5,0,AGTGC

### Range

A range pattern unit can be used between exact and approximate pattern units to
indicate a range of matching sequence. A range unit is basically a wildcard
with a closed repetition e.g. `.{20,30}` which can be replaced by the shorthand
`20..30` or the synonym `20...30`.

    CAGCCCTGC =~ AG 2..4 TG => 2,2,0,AG;4,3,0,CCC;7,2,0,TG

### Backreferences

It is possible to assign pattern units to named variables, which can be used as
backreferences.

**Named pattern:**

    GATATG =~ p1=.A p1 => 2,2,0,AT;4,2,0,AT

**Named composite:**

    ATGTTGTA =~ p1=(T ~AC) p1 => 2,3,0,TGT;5,3,0,TGT

**Nested named pattern:**

    GACGTACGTG =~ p2=(p1=AC ~p1) p2 => 2,2,0,AC;4,2,0,GT;6,2,0,AC;8,2,0,GT

**Nested named composite:**

    ATGTTGTTGTTGTA =~ p2=(p1=(T ~AC) p1) p2 =>
    2,1,0,T;3,2,0,GT;5,1,0,T;6,2,0,GT;8,1,0,T;9,2,0,GT;11,1,0,T;12,2,0,GT

### Match groups

Match groups are pattern units that match a set of specified residues. It is
possible to use the non-match operator `^` as the first character to indicate
that no residues in the match group will be matched (do not confuse with the
match anchor `^`):

    ACTT =~ [AT]        => 1,1,0,A and 3,1,0,T and 4,1,0,T

    GCAGTTAAG =~ [AT]+  => 3,1,0,A and 5,4,0,TTAA

    GCAGTTAAG =~ [^AT]+ => 1,2,0,GC and 4,1,0,G and 9,1,0,G

### Anchors

Anchors can be applied to any pattern unit. The start anchor `^` only accept
pattern unit matches at the start of the sequence:

    ATCATC =~ ^ATC => 1,3,0,ATC

The end anchor `$` only accept pattern unit matches at the end of the
sequences:

    ATCATC =~ ATC$ => 4,3,0,ATC

Using both anchors will only accept patterns units matching the full sequence:

    ATC =~ ^ATC$ => 1,3,0,ATC

### Ambiguity codes and case

Pattern units may contain ambiguity codes for nucleotides in the pattern and
sequence as defined in the Match Matrix. Pattern units may be case insensitive
as defined in the Match Matrix. See Match Matrix section for details.

## Output

The SeqScan output is a four column table separated by tabs and with the
following columns:

1. ID - ID of sequence matched.
2. Strand - Strand matched:
  * + is forward strand.
  * - is reverse strand.
  * . is used for proteins.
3. Match - Semicolon separated list of submatches from the pattern units of
   the pattern. Each submatch is a comma separated list of:
  * Submatch start position (1-indexed).
  * Length of submatch.
  * Edit distance of submatch.
  * Submatch sequence.
4. Length - Total length of pattern match.

Each line in the output contains one pattern match.

### Sample output

    seq1   +   3,4,0,TGCG;8,4,0,TGAT     8
    seq1   +   51,4,1,TACG;56,4,0,TGAT   8
    seq1   -   20,4,0,TGCG;25,4,1,TGAA   8

## Examples

### Hybridization probe

Here we illustrate how to locate all matches for a 20 bases hybridization probe
allowing for 3 mismatches and 2 indels. Imagine a FASTA file named input.fna
with the following entry:

    >test
    TCAGTACGACACTACTAGCSGGTRTGAACTAGTGACTGATCGACTCAGTT

To search for the hybridization probe we do (`$` indicates command-line
prompt):

    $ seqscan -p 'TAGCTAGCSGCTRTGACTAG/3,2' input.fna

And we get the following output:

    test   +   12,21,3,CTACTAGCSGGTRTGAACTAG   21

An alignment of the pattern and the hit demonstrates that this was procured by
using one mismatch and two indels:

    pattern -TAGCTAGCSGCTRTGACTAG-
             || ||||||| |||||||||
    hit     GTA-CTAGCSGGTRTGaACTAG

### Tetraloops

Tetraloops are short hairpins capped by a four nucleotide loop:

https://en.wikipedia.org/wiki/Tetraloop

To find all tetraloops in the FASTA file named input.fna with the following
entries:

    >test1
    AGATGATAGTATGGTGNRAACCATAGATGATGAT
    >test2
    AGATGATAGTATGGTGNRAACGATAGATGATGAT
    >test3
    AGATGATAGTATGGTGNRAACGAAGATGATGAT

Now we run SeqScan with the following pattern where we save any 4 to 6
residues in the variable p1 (`p1=4..6`), then allow any 4 residues (`.{4}`),
which must be followed by a match of the reverse-complement of p1 (`~p1`):

    $ seqscan -p 'p1=4..6 .{4} ~p1' -o hits.tsv input.fna

Which will give the following output in the hits.tsv file:

    test1   +   11,5,0,ATGGT;16,4,0,GNRA;20,5,0,ACCAT   14

We can also allow a mismatch in the stem by adding an edit modifier to the
backreference:

    $ seqscan -p 'p1=4..6 .{4} ~p1/1,0,0' -o hits.tsv input.fna

So now we get:

    test1   +   11,5,0,ATGGT;16,4,0,GNRA;20,5,0,ACCAT   14
    test2   +   11,5,0,ATGGT;16,4,0,GNRA;20,5,1,ACGAT   14

Or we can allow a mismatch and an indel, the latter allowing a bulge in the
stem:

    $ seqscan -p 'p1=4..6 .{4} ~p1/1,1' -o hits.tsv input.fna

And so getting:

    test1   +   11,5,0,ATGGT;16,4,0,GNRA;20,5,0,ACCAT   14
    test2   +   11,5,0,ATGGT;16,4,0,GNRA;20,5,1,ACGAT   14
    test3   +   11,5,0,ATGGT;16,4,0,GNRA;20,4,1,ACGA    13

### Protein motif

Here we search for a particular protein motif consisting of 0 to 4 residues in
the variable p1 (`p1=0..4`) that must by exactly 1 of the residues H, Q or D
(`[HQD]`), followed by any 1 to 3 residues (`1..3`), followed by exactly 1
residue that cannot be H or K (`[^HK]`) and finally followed by p1. So for the
following FASTA entry in the file input.faa:

    >test
    MENDQYWVDAACYWVPSTRNE

We use SeqScan like this:

    $ seqscan -p 'p1=0..4 [HQD] 1..3 [^HK] p1' input.faa

And we get the following hit:

    test   .   6,3,0,YWV;9,1,0,D;10,2,0,AA;12,1,0,C;13,3,0,YWV  10

### PCR

_In silico_ PCR is a search for two approximate pattern units separated by a
range:

https://en.wikipedia.org/wiki/In_silico_PCR

It can be done like this (`\` denotes a line break):

    $ seqscan -p 'GACTAGCTAGCTTGACGTAG/2,1 500..3000 \
      ~GTTAGCTAGGGGCTGACGTG/2,1' -c both input.fna

Notice that the primers in the pattern are specified in the 5'-3' orientation,
and that we use the reverse-complement operator `~` on the reverse primer.

### H/ACA snoRNA

The H/ACA box small nucleolar RNA have a secondary structure with a rabbit
ear-like secondary structure:

https://en.wikipedia.org/wiki/Small_nucleolar_RNA

It is possible to locate these like this:

    $ seqscan -p 'p1=4..8 4..8 p2=4..8 .{4} ~p2/1 4..8 ~p1/1 0..4 ANANNA \
                  0..4 p3=4..8 4..8 p4=4..8 .{4} ~p4/1 4..8 ~p3/1 0..4 \
                  ACANNN' -c both input.fna

## Advanced

### Overlap

Using the `-o/--overlap` option causes SeqScan to output all overlapping
matches.

Imagine a FASTA file with the following entry:

    >test1
    AAAA

If we search without the `--overlap` option:

    $ seqscan -p 'AA'

We get the output:

    test1   +   1,2,0,AA   2
    test1   +   3,2,0,AA   2

But with the `--overlap` option:

    $ seqscan -o -p 'AA'

We get:

    test1   +   1,2,0,AA   2
    test1   +   2,2,0,AA   2
    test1   +   3,2,0,AA   2

### Minimum Phred score

If the input data is in FASTQ format then the quality scores will be considered
when matching residues if the `-s/--score_min` option is used. When the
`-s/--score_min` option is used then a pattern will fail to match any residue
with a score below the minimum score. However, if the `-a/--ambiguate` option
is used then all residues with a score below the minimum score will match.

Read about quality scores here:

https://en.wikipedia.org/wiki/FASTQ_format

###  Match matrix

Use the `-M/--match_file` to read a given match matrix. The file must contain
one or two matrices, where the first describes how sequences match, and the
second optional matrix describes how complemented sequences match. The latter is
only relevant for nucleotide sequences.

The first row denotes sequence residues and the first column denotes pattern
residues. Below is an example of a match file with matrices for matching only
uppercase DNA/RNA and complement matching of the same (if the `~` operator is
used a complement matrix must also be defined). Matching residues are indicated
by `+` in the row and column intersection.

     ACGTU
    A+
    C +
    G  +
    T   ++
    U   ++

    ~ACGTU
    A   ++
    C  +
    G +
    T+
    U+

Below are the default (`--match_type 6`) match matrices used for the
case-insensitive matching of nucleotides allowing for ambigius residues in the
pattern but not in the scanned sequence:

     ACGTUacgtu
    A+    +
    C +    +
    G  +    +
    T   ++   ++
    U   ++   ++
    R+ +  + +
    Y + ++ + ++
    W+  +++  ++
    S ++   ++
    M++   ++
    K  +++  +++
    H++ ++++ ++
    D+ ++++ +++
    V+++  +++
    B ++++ ++++
    N++++++++++
    a+    +
    c +    +
    g  +    +
    t   ++   ++
    u   ++   ++
    r+ +  + +
    y + ++ + ++
    w+  +++  ++
    s ++   ++
    m++   ++
    k  +++  +++
    h++ ++++ ++
    d+ ++++ +++
    v+++  +++
    b ++++ ++++
    n++++++++++

    ~ACGTUacgtu
    A   ++   ++
    C  +    +
    G +    +
    T+    +
    U+    +
    R + ++ + ++
    Y+ +  + +
    W+  +++  ++
    S ++   ++
    M  +++  +++
    K++   ++
    H+ ++++ +++
    D++ ++++ ++
    V ++++ ++++
    B+++  +++
    N++++++++++
    a   ++   ++
    c  +    +
    g +    +
    t+    +
    u+    +
    r + ++ + ++
    y+ +  + +
    w+  +++  ++
    s ++   ++
    m  +++  +++
    k++   ++
    h+ ++++ +++
    d++ ++++ ++
    v ++++ ++++
    b+++  +++
    n++++++++++

## Filter

Results can be filtered using arithmetic predicates on reference variables.
Multiple predicates can be combined with the logical operators AND (`&&`) and
OR (`||`).

### Functions

The following functions are defined on a reference, p:

* length(p) - The lengths of substrings matched by p.
* rescount(p, r) - The number of residues of type r in substrings matched by p.

### Examples

Match length must be greater than 6:

    $ seqscan -p 'p1=(A 0..4 GC 0..4 T)' -f 'length(p1) > 6'

Range lengths must be greater than 4:

    $ seqscan -p 'A p1=0..4 GC p2=0..4 T' -f 'length(p1) + length(p2) > 4'

First range must be at least twice the length of the second range:

    $ seqscan -p 'A p1=0..4 GC p2=0..4 T' -f 'length(p1) >= 2 * length(p2)'

ATG repeats that are either 9 or 18 residues:

    $ seqscan -p 'p1=ATG{3,6}' -f 'length(p1) == 9 || length(p1) == 18'

GC-content of match must be at least 0.75:

    $ seqscan -p 'p1=(A p2=0..4 GC p3=0..4 T)' \
              -f 'rescount(p1, G) + rescount(p1, C) >= 0.75 * length(p1)'

## Copyright

Copyright (C) 2015 BIO-DIKU - All rights reserved.

## License

GNU General Public License version 2

http://www.gnu.org/copyleft/gpl.html

## Disclaimer

All generic disclaimers apply.

## Acknowledgement

SeqScan is based on ideas from scan_for_matches which was developed in 1987 by
Ross Overbeek, David Joerg and Morgan Price and based on earlier ideas from
David Searls.

## Contact

https://github.com/BIO-DIKU/SeqScan

## Cite

Manuscript is in preparation. Until published, please cite:

https://github.com/BIO-DIKU/SeqScan

## Bugs

Please report bugs:

https://github.com/BIO-DIKU/SeqScan/issues
