
DATADIR = ../data
SEQFILE = $(DATADIR)/chr22.fa

# Assumes that you put scan_for_matches and seqscan in your path
SFM_BIN = scan_for_matches
SQS_BIN = seqscan

SFM_PATS = $(wildcard pat_*/sfm.pat)
SQS_PATS = $(wildcard pat_*/seqscan.pat)
ALL_PATS = $(SFM_PATS) $(SQS_PATS)

OUTPUT_FILES = $(subst .pat,.txt,$(ALL_PATS))

# Ensures that intermediate files dont get deleted after each target creation
.SECONDARY:

# Add any targets you want auto-generated here
all: $(OUTPUT_FILES)

# General wild-card rules
%.fa: %.fa.gz
	gunzip -k $<
	chmod a-w $<

%/seqscan.txt: %/seqscan.pat $(SEQFILE)
	(time $(SQS_BIN) -P $< -V $(SEQFILE)) &> $@

%/sfm.txt: %/sfm.pat $(SEQFILE)
	(time $(SFM_BIN) $< < $(SEQFILE)) &> $@


# Rules for generating plots


# Cleaning rule. Remember to add new targets here
clean:
	rm -f $(OUTPUT_FILES)

