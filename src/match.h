#ifndef MATCH_H_
#define MATCH_H_

class Match
{
public:
  Match(const int &pos, const int &len, const int &edits):
      pos(pos), len(len), edits(edits)
  {}

  const int pos;
  const int len;
  const int edits;
};

#endif  // MATCH_H_
