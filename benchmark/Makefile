# na = nucleic acid (DNA/RNA)
# aa = amino acid (Protein)
DATADIR      = data
NA_FILE      = $(DATADIR)/chr22.fa
AA_FILE      = $(DATADIR)/Aurpu2p4.faa

# Assumes that you put scan_for_matches and seqscan in your path
SFM_BIN      = scan_for_matches
SQS_BIN      = seqscan
PYX_BIN      = python pyRegexMatch.py

SFM_PATS     = $(wildcard pat_*/sfm_*.pat)
SQS_PATS     = $(wildcard pat_*/seqscan_*.pat)
PYX_PATS     = $(wildcard pat_*/pyRegex_*.pat)
ALL_PATS     = $(SFM_PATS) $(SQS_PATS) $(PYX_PATS)

OUTPUT_FILES = $(subst .pat,.txt,$(ALL_PATS))
OUTPUT_DIRS  = $(sort $(subst /,,$(dir $(OUTPUT_FILES)))) #sort removes duplicates (and sorts)

# Ensures that intermediate files dont get deleted after each target creation
.SECONDARY:

# Add any targets you want auto-generated here
all: $(OUTPUT_FILES) benchmark.png

# General wild-card rules
%.fa: %.fa.gz
	gunzip -k $<
	chmod a-w $<

# More general wild-card rules
%.faa: %.faa.gz
	gunzip -k $<
	chmod a-w $<

%/seqscan_na.txt: %/seqscan_na.pat $(NA_FILE)
	(time -p $(SQS_BIN) -P $< -V $(NA_FILE)) &> $@

%/sfm_na.txt: %/sfm_na.pat $(NA_FILE)
	(time -p $(SFM_BIN) -o 1 $< < $(NA_FILE)) &> $@

%/pyRegex_na.txt: %/pyRegex_na.pat $(NA_FILE)
	(time -p $(PYX_BIN) `cat $<` $(NA_FILE)) &> $@

%/seqscan_aa.txt: %/seqscan_aa.pat $(AA_FILE)
	(time -p $(SQS_BIN) -m 10 -P $< -V $(AA_FILE)) &> $@

%/sfm_aa.txt: %/sfm_aa.pat $(AA_FILE)
	(time -p $(SFM_BIN) -p -o 1 $< < $(AA_FILE)) &> $@

%/pyRegex_aa.txt: %/pyRegex_aa.pat $(AA_FILE)
	(time -p $(PYX_BIN) `cat $<` $(AA_FILE)) &> $@


# Summary file
benchmark.dat: $(OUTPUT_FILES)
	bash collect_benchmark_data.sh $(OUTPUT_DIRS) > $@

# Rules for generating plots
benchmark.png: benchmark.dat
	gnuplot -e "set term png;set output '$@'" plot_benchmark.gp 

benchmark.svg: benchmark.dat
	gnuplot -e "set term svg;set output '$@'" plot_benchmark.gp 

# Cleaning rule. Remember to add new targets here
clean:
	rm -f $(OUTPUT_FILES)
	rm -f benchmark.???

