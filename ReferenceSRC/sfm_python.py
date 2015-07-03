#!/usr/bin/python

#####################################

class SequenceUnit:
    """
    A pattern unit with a prespecified sequence and, possibly, an allowed number of 
    mismatches, insertions, and deletions.
    """
    def __init__(self, seq, M, I, D):
        self.sequence = seq
        self.M = M
        self.I = I
        self.D = D
        self.match_set = MatchSet()

    def matches(self, seq, pos):
        self.match_set.reset(pos)
        loose_match(seq, pos, self.sequence, self.M, self.I, self.D, 0, self.match_set)
        print self.match_set.end_positions
        return len(self.match_set.end_positions) != 0 
        
class RangeUnit:
    """
    A pattern unit matching any character sequence with length in a certain a range.
    """
    def __init__(self, min_len, max_len):
        self.min_len = min_len
        self.max_len = max_len
        self.match_set = MatchSet()

    def matches(self, seq, pos):
        self.match_set.reset(pos)
        range_match(seq, pos, self.min_len, self.max_len, self.match_set)
        return len(self.match_set.end_positions) != 0 

class ReferenceUnit:
    """
    A pattern unit that extracts previous matches from another "referenced" pattern unit and 
    attempts to match the sequence of these matches, allowing for a number of mismatches, 
    insertions and deletions.
    """
    def __init__(self, ref_unit, M, I, D, reverse, complement):
        self.ref_unit = ref_unit
        self.M = M
        self.I = I
        self.D = D
        self.reverse = reverse
        self.complement = complement
        self.match_set = MatchSet()

    def matches(self, seq, pos):
        self.match_set.reset(pos)
        reference_match(seq, pos, self.ref_unit.match_set, self.M, self.I, self.D,self.reverse, self.complement, self.match_set)
        return len(self.match_set.end_positions) != 0 

class CompositeUnit:
    """
    A pattern that is composed of other pattern units that must match consequtively for the 
    composite to pass
    """
    def __init__(self, units):
        self.units = units
        self.match_set = MatchSet()

    def rest_matches(self, seq, positions, pu_idx):
        if pu_idx>=len(self.units):
            return True

        for pos in positions:
            if self.units[pu_idx].matches(seq,pos) and self.rest_matches(seq,self.units[pu_idx].match_set.end_positions, pu_idx+1):
                return True

        return False


    def matches(self, seq, pos):
        return self.rest_matches(seq, [pos], 0)


#####################################


class MatchSet:
    """
    Represents a set of matches using their common start position and the set of all possible 
    end-positions. The end-position is the index of the first character that comes after the 
    match, so e.g. the match starting at 2 with end-position 5 in the sequence "ATCCAG" will be 
    the sub-sequence "CCA".
    """
    def __init__(self, pos=-1):
        self.pos = pos
        self.end_positions = set([])

    def __str__(self):
        return "Match["+str(self.pos)+","+str(self.end_positions)+"]"

    def reset(self, new_pos):
        self.pos = new_pos
        self.end_positions.clear()

#####################################

from string import maketrans
complement_table = maketrans("ATUCG","TAAGC")
def nucl_complement(S):
    return S.translate(complement_table)[::-1]

def nucl_reverse(S):
    return S[::-1]



def reference_match(S,i, match_set, M, I, D, reverse, complement, ret=MatchSet()):
    """
    Take the string of a previous match and match it to S, allowing for a number of mismatches,
    insertions, and deletions.
    S --- The string in which to search for matches
    i --- The position in S from which to search
    match_set --- The matches of the referenced pattern-unit
    M --- The allowed number of mismatches
    I --- The allowed number of insertions
    D --- The allowed number of deletions
    ret --- An accumulating set of matches
    """
    if match_set is None: return None

    ret.pos = i
    for ep in match_set.end_positions:
        P = S[match_set.pos:ep]
        if reverse: P = nucl_reverse(P)
        if complement: P = nucl_complement(P)
        loose_match(S,i,P,M,I,D,0,ret)

    if ret.end_positions:
        return ret
    else:
        return None



def range_match(S,i, minLen, maxLen, ret=MatchSet(0)):
    """
    Match a range to a string given the minimum and maximum length of the range.
    S --- The string in which to search for matches
    i --- The position in S from which to search
    minLen --- The minimum length of the range
    maxLen --- The maximum length of the range
    ret --- An accumulating set of matches
    """
    ret.pos = i
    ret.end_positions.update( range(i+minLen, min(i+maxLen+1,len(S))) )

    if ret.end_positions:
        return ret
    else:
        return None



def loose_match(S,i,P,M,I,D,j=0, ret=MatchSet(None)):
    """
    Match a pattern to a string given an allowed number of mismatches, insertions and deletions.
    S --- The string in which to search for matches
    i --- The position in S from which to search
    P --- The pattern string
    M --- The allowed number of mismatches
    I --- The allowed number of insertions
    D --- The allowed number of deletions
    j --- The position in P from which to search
    ret --- An accumulating set of matches
    """
    if ret.pos is None: ret.pos = i

    if j==len(P): 
        ret.end_positions.add(i)
        return ret
    if i==len(S):
        return None

    if I>0: loose_match(S,i+1,P,M,  I-1,D,  j,   ret)
    if D>0: loose_match(S,i  ,P,M,  I,  D-1,j+1, ret)

    if S[i]==P[j]:
        loose_match(S,i+1,P,M,I,D,j+1,ret)

    if M>0: loose_match(S,i+1,P,M-1,I,  D,  j+1, ret)

    if not ret.end_positions: 
        return None
    else:
        return ret
        

def scan_for_matches(P, S):
    for pos in range(0,len(S)):
        if P.matches(S,pos):
            print "Full pattern match at position",pos

#p1 = SequenceUnit("ATA",1,0,1)
#p2 = SequenceUnit("AAA",0,0,0)
#P = CompositeUnit([ p1,p2 ])
#S = "AATAAAGAA"

#p1 = SequenceUnit("ATA",0,0,0)
#p2 = RangeUnit(2,5)
#p3 = ReferenceUnit(p1,1,0,0, False, False)
#P = CompositeUnit([ p1,p2,p3 ]) # Corresponds to the SFM pattern "p1=AAG[1,0,0] 2..5 p1"
#S = "AATAAAAGAA"

#p1 = RangeUnit(4,10)
#p2 = RangeUnit(4,4)
#p3 = ReferenceUnit(p1,0,0,0, True, True)
#P = CompositeUnit([p1,p2,p3]) # "p1=4...10 4...4 ~p1"

# scan_for_matches(P, S)
