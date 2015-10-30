/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#ifndef SEQSCAN_RES_MATCHER_H_
#define SEQSCAN_RES_MATCHER_H_

#include <bitset>

static const size_t kSizeOfChar = 8;
static const size_t kMaxHash    = 1 << (2 * kSizeOfChar);

/*
 * Inline method to hash two chars for lookup in a match structure. Hashing is
 * done by shifting the ASCII value of one char and performing a bitwise or (|)
 * operation. E.g, for the residue pair T-U the binary representations are:
 *
 * T:          0000000001010100 = 84
 * U:          0000000001010101 = 85
 * T << 8 | U: 0101010001010101 = 21589
 *
 * Thus the resulting hash value 21589 can be used in a lookup structure.
 */
inline size_t HashResidues(const char a, const char b) {
  return (a << kSizeOfChar) | b;
}

// For Matrices below the first row is the sequence and the first column is the
// pattern.

static const std::string kMatrix1  = R"MATRIX(
 ACGTU
A+
C +
G  +
T   ++
U   ++
)MATRIX";

static const std::string kMatrix1_comp = R"MATRIX(
~ACGTU
A   ++
C  +
G +
T+
U+
)MATRIX";

static const std::string kMatrix2 = R"MATRIX(
 ACGTUacgtu
A+    +
C +    +
G  +    +
T   ++   ++
U   ++   ++
a+    +
c +    +
g  +    +
t   ++   ++
u   ++   ++
)MATRIX";

static const std::string kMatrix2_comp = R"MATRIX(
~ACGTUacgtu
A   ++   ++
C  +    +
G +    +
T+    +
U+    +
a   ++   ++
c  +    +
g +    +
t+    +
u+    +
)MATRIX";

static const std::string kMatrix3 = R"MATRIX(
 ACGTURYWSMKHDVBN
A+    + + + +++ +
C +    + ++ + +++
G  +  +  + + ++++
T   ++ ++  +++ ++
U   ++ ++  +++ ++
)MATRIX";

static const std::string kMatrix3_comp = R"MATRIX(
~ACGTURYWSMKHDVBN
A   ++ ++  +++ ++
C  +  +  + + ++++
G +    + ++ + +++
T+    + + + +++ +
U+    + + + +++ +
)MATRIX";

static const std::string kMatrix4 = R"MATRIX(
 ACGTURYWSMKHDVBNacgturywsmkhdvbn
A+    + + + +++ ++    + + + +++ +
C +    + ++ + +++ +    + ++ + +++
G  +  +  + + ++++  +  +  + + ++++
T   ++ ++  +++ ++   ++ ++  +++ ++
U   ++ ++  +++ ++   ++ ++  +++ ++
a+    + + + +++ ++    + + + +++ +
c +    + ++ + +++ +    + ++ + +++
g  +  +  + + ++++  +  +  + + ++++
t   ++ ++  +++ ++   ++ ++  +++ ++
u   ++ ++  +++ ++   ++ ++  +++ ++
)MATRIX";

static const std::string kMatrix4_comp = R"MATRIX(
~ACGTURYWSMKHDVBNacgturywsmkhdvbn
A   ++ ++  +++ ++   ++ ++  +++ ++
C  +  +  + + ++++  +  +  + + ++++
G +    + ++ + +++ +    + ++ + +++
T+    + + + +++ ++    + + + +++ +
U+    + + + +++ ++    + + + +++ +
a   ++ ++  +++ ++   ++ ++  +++ ++
c  +  +  + + ++++  +  +  + + ++++
g +    + ++ + +++ +    + ++ + +++
t+    + + + +++ ++    + + + +++ +
u+    + + + +++ ++    + + + +++ +
)MATRIX";

static const std::string kMatrix5 = R"MATRIX(
 ACGTU
A+
C +
G  +
T   ++
U   ++
R+ +
Y + ++
W+  ++
S ++
M++
K  +++
H++ ++
D+ +++
V+++
B ++++
N+++++
)MATRIX";

static const std::string kMatrix5_comp = R"MATRIX(
~ACGTU
A   ++
C  +
G +
T+
U+
R + ++
Y+ +
W+  ++
S ++
M  +++
K++
H+ +++
D++ ++
V ++++
B+++
N+++++
)MATRIX";

static const std::string kMatrix6 = R"MATRIX(
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
)MATRIX";

static const std::string kMatrix6_comp = R"MATRIX(
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
)MATRIX";

static const std::string kMatrix7 = R"MATRIX(
 ACGTURYWSMKHDVBN
A+    + + + +++ +
C +    + ++ + +++
G  +  +  + + ++++
T   ++ ++  +++ ++
U   ++ ++  +++ ++
R+ +  + +++++++++
Y + ++ ++++++++++
W+  +++++ +++++++
S ++  ++ ++++++++
M++   +++++ +++++
K  +++++++ ++++++
H++ +++++++++++++
D+ ++++++++++++++
V+++  +++++++++++
B +++++++++++++++
N++++++++++++++++
)MATRIX";

static const std::string kMatrix7_comp = R"MATRIX(
~ACGTURYWSMKHDVBN
A   ++ ++  +++ ++
C  +  +  + + ++++
G +    + ++ + +++
T+    + + + +++ +
U+    + + + +++ +
R + ++ ++++++++++
Y+ +  + +++++++++
W+  +++++ +++++++
S ++  ++ ++++++++
M  +++++++ ++++++
K++   +++++ +++++
H+ ++++++++++++++
D++ +++++++++++++
V +++++++++++++++
B+++  +++++++++++
N++++++++++++++++
)MATRIX";

static const std::string kMatrix8 = R"MATRIX(
 ACGTURYWSMKHDVBNacgturywsmkhdvbn
A+    + + + +++ ++    + + + +++ +
C +    + ++ + +++ +    + ++ + +++
G  +  +  + + ++++  +  +  + + ++++
T   ++ ++  +++ ++   ++ ++  +++ ++
U   ++ ++  +++ ++   ++ ++  +++ ++
R+ +  + ++++++++++ +  + +++++++++
Y + ++ ++++++++++ + ++ ++++++++++
W+  +++++ ++++++++  +++++ +++++++
S ++  ++ ++++++++ ++  ++ ++++++++
M++   +++++ +++++++   +++++ +++++
K  +++++++ ++++++  +++++++ ++++++
H++ +++++++++++++++ +++++++++++++
D+ +++++++++++++++ ++++++++++++++
V+++  ++++++++++++++  +++++++++++
B +++++++++++++++ +++++++++++++++
N++++++++++++++++++++++++++++++++
a+    + + + +++ ++    + + + +++ +
c +    + ++ + +++ +    + ++ + +++
g  +  +  + + ++++  +  +  + + ++++
t   ++ ++  +++ ++   ++ ++  +++ ++
u   ++ ++  +++ ++   ++ ++  +++ ++
r+ +  + ++++++++++ +  + +++++++++
y + ++ ++++++++++ + ++ ++++++++++
w+  +++++ ++++++++  +++++ +++++++
s ++  ++ ++++++++ ++  ++ ++++++++
m++   +++++ +++++++   +++++ +++++
k  +++++++ ++++++  +++++++ ++++++
h++ +++++++++++++++ +++++++++++++
d+ +++++++++++++++ ++++++++++++++
v+++  ++++++++++++++  +++++++++++
b +++++++++++++++ +++++++++++++++
n++++++++++++++++++++++++++++++++
)MATRIX";

static const std::string kMatrix8_comp = R"MATRIX(
~ACGTURYWSMKHDVBNacgturywsmkhdvbn
A   ++ ++  +++ ++   ++ ++  +++ ++
C  +  +  + + ++++  +  +  + + ++++
G +    + ++ + +++ +    + ++ + +++
T+    + + + +++ ++    + + + +++ +
U+    + + + +++ ++    + + + +++ +
R + ++ ++++++++++ + ++ ++++++++++
Y+ +  + ++++++++++ +  + +++++++++
W+  +++++ ++++++++  +++++ +++++++
S ++  ++ ++++++++ ++  ++ ++++++++
M  +++++++ ++++++  +++++++ ++++++
K++   +++++ +++++++   +++++ +++++
H+ +++++++++++++++ ++++++++++++++
D++ +++++++++++++++ +++++++++++++
V +++++++++++++++ +++++++++++++++
B+++  ++++++++++++++  +++++++++++
N++++++++++++++++++++++++++++++++
a   ++ ++  +++ ++   ++ ++  +++ ++
c  +  +  + + ++++  +  +  + + ++++
g +    + ++ + +++ +    + ++ + +++
t+    + + + +++ ++    + + + +++ +
u+    + + + +++ ++    + + + +++ +
r + ++ ++++++++++ + ++ ++++++++++
y+ +  + ++++++++++ +  + +++++++++
w+  +++++ ++++++++  +++++ +++++++
s ++  ++ ++++++++ ++  ++ ++++++++
m  +++++++ ++++++  +++++++ ++++++
k++   +++++ +++++++   +++++ +++++
h+ +++++++++++++++ ++++++++++++++
d++ +++++++++++++++ +++++++++++++
v +++++++++++++++ +++++++++++++++
b+++  ++++++++++++++  +++++++++++
n++++++++++++++++++++++++++++++++
)MATRIX";

static const std::string kMatrix9 = R"MATRIX(
 FLSYCWPHQRIMTNKVADEGX
F+                   +
L +                  +
S  +                 +
Y   +                +
C    +               +
W     +              +
P      +             +
H       +            +
Q        +           +
R         +          +
I          +         +
M           +        +
T            +       +
N             +      +
K              +     +
V               +    +
A                +   +
D                 +  +
E                  + +
G                   ++
X+++++++++++++++++++++
)MATRIX";

static const std::string kMatrix10 = R"MATRIX(
 FLSYCWPHQRIMTNKVADEGXflsycwphqrimtnkvadegx
F+                   ++                   +
L +                  + +                  +
S  +                 +  +                 +
Y   +                +   +                +
C    +               +    +               +
W     +              +     +              +
P      +             +      +             +
H       +            +       +            +
Q        +           +        +           +
R         +          +         +          +
I          +         +          +         +
M           +        +           +        +
T            +       +            +       +
N             +      +             +      +
K              +     +              +     +
V               +    +               +    +
A                +   +                +   +
D                 +  +                 +  +
E                  + +                  + +
G                   ++                   ++
X++++++++++++++++++++++++++++++++++++++++++
f+                   ++                   +
l +                  + +                  +
s  +                 +  +                 +
y   +                +   +                +
c    +               +    +               +
w     +              +     +              +
p      +             +      +             +
h       +            +       +            +
q        +           +        +           +
r         +          +         +          +
i          +         +          +         +
m           +        +           +        +
t            +       +            +       +
n             +      +             +      +
k              +     +              +     +
v               +    +               +    +
a                +   +                +   +
d                 +  +                 +  +
e                  + +                  + +
g                   ++                   ++
x++++++++++++++++++++++++++++++++++++++++++
)MATRIX";

 /**
 * @brief Exception class for ResMatcher class.
 *
 * @example
 *   std::string msg = "Exception message";
 *   throw ResMatcherException(msg);
 */
class ResMatcherException : public std::exception {
 public:
  ResMatcherException(std::string &msg) :
    exceptionMsg(msg)
  {}

  ResMatcherException(const ResMatcherException &e) :
    exceptionMsg(e.exceptionMsg)
  {}

  virtual const char* what() const throw() { return exceptionMsg.c_str(); }

  const std::string exceptionMsg;
};

/**
 * @brief Class for creating a match matcher, which contians a lookup structure
 * on matching residue pairs. The match matcher consists of a bitset and the index
 * of matching residues pairs are set by hashing the chars and use the resulting
 * hash value as an index in the loopup structure.
 */
class ResMatcher {
 public:
  /*
   * Predifined matchers.
   */
  ResMatcher(int matrix_num);

  /*
   * Custom complement matrix from file.
   */
  ResMatcher(std::string matrix_file, bool comp=false);

  ~ResMatcher();

  /**
   * Match two residues and return true if they match according to the
   * res_matcher.
   *
   * @param a First residue
   * @parem b Second residue
   */
  bool Match(const char a, const char b) const;

 private:

  /*
   * Set the value at index.
   */
  void set(size_t index);

  /*
   * Test if the value at index is set.
   */
  bool is_set(size_t index) const;

  /*
   * Residue matcher.
   */
  std::bitset<kMaxHash> res_matcher_;

  /*
   * Path to file with custom matcher matrix.
   */
  std::string matrix_file_;

  /*
   * Number of hardcoded matcher matrix to use. Negative matrix_num_ is used
   * to denote complementary matrix.
   */
  int matrix_num_;

  /*
   * Parse a custom matrix from file.
   *
   * @param comp get the complemnt matrix from the file.
   */
  void MatrixFileToMatcher(bool comp);

  /*
   * Create a match matcher from a hard coded matrix.
   */
  void MatrixToMatcher();

  /*
   * Parse a hardcoded matrix.
   */
  void ParseMatrix(const std::string matrix_str);
};

#endif  // SEQSCAN_RES_MATCHER_H_
