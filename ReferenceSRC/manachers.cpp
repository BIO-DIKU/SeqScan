#include <stdlib.h>
#include <string>
#include <limits.h>
#include "fasta.h"

// Implementation of Manacher's algorithm (see http://johanjeuring.blogspot.com/2007/08/finding-palindromes.html )
// Thanks to Frederick Akalin (see http://www.akalin.cx/2007/11/28/finding-the-longest-palindromic-substring-in-linear-time/ )
// Brian Bi (bbi5291), 2010-11-14
// From: http://wcipeg.com/wiki/Longest_palindromic_substring/lps.cpp
// See also: http://tristan-interview.blogspot.dk/2011/11/longest-palindrome-substring-manachers.html

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class RAI1,class RAI2>
void fastLongestPalindromes(RAI1 seq,RAI1 seqEnd,RAI2 out)
{
	int seqLen=seqEnd-seq;
	int i=0,j,d,s,e,lLen,k=0;
	int palLen=0;
	//while (i<seqLen)
	for (i=0;i<seqLen;i++)
	{
		if (i>palLen && seq[i-palLen-1]==seq[i])
		{
			palLen+=2;
			//i++;
			continue;
		}
		out[k++]=palLen;
		s=k-2;
		e=s-palLen;
		bool b=true;
		for (j=s; j>e; j--)
		{
			d=j-e-1;
			if (out[j]==d)
			{
				palLen=d;
				b=false;
				break;
			}
			out[k++]=min(d,out[j]);
		}
		if (b){
			palLen=1;
			//i++;
		}else i--;
	}
	out[k++]=palLen;
	lLen=k;
	s=lLen-2;
	e=s-(2*seqLen+1-lLen);
	for (i=s; i>e; i--)
	{
		d=i-e-1;
		out[k++]=min(d,out[i]);
	}
}

//string LongestPalindrome(const string input)
//{
//	int c = 0;
//	int max = 0;
//	// create an indexed accessor for a virtual string S which has $a$b$c$ for  input string abc
//	auto S_at = [&input](int index)->char { return ((index & 1) ? input[index / 2] : '$'); };
//	int sizeP = (input.length() * 2) + 1;
//	int* P = new int[sizeP];
//	P[0] = 0;
//	// find longest Palindromes forcentered on each index in S
//	for (int i = 1; i<sizeP; i++){
//	   	? min(P[c - (i - c)], max - i) : 0;
//		// Try to expand Palindrome but not past string boundaries
//		int bounds = min(sizeP - i - 1, i - 1);
//		while (bounds-- >= 0 && S_at(i + P[i] + 1) == S_at(i - P[i] - 1))
//		{
//			P[i]++;
//		}
//		// If palindrome was extend past max then update Center to i and update the right edge
//		if (i + P[i] > max) 
//		{
//			c = i;
//			max = i + P[i];
//		}
//	}
//	auto maxP = std::max_element(P, P + sizeP);
//	int start = (maxP - P - *maxP)/2;
//	cout<<"> Index: "<<start<<", len: "<<*maxP<<endl;
//	return input.substr(start, *maxP);
//}

int main(int argc, char** argv){
	if(argc!=2){
		printf("Usage: %s <fasta file>\n",argv[0]);
		exit(-1);
	}


	for(auto &pair_it: read_file(argv[1])){
		string& s = pair_it.second;
		//string ret = LongestPalindrome(s);
		//cout<<"Longest palindrome: "<<ret<<endl;

		vector<int> V(2*s.length()+1);
		fastLongestPalindromes(s.begin(),s.end(),V.begin());

		int best=0, bestpos = 0;
		for (int i=0; i<V.size(); i++)
		{
			//if (i>0) cout << ", ";
			//cout << V[i];
			if(V[i]>best){
				best = V[i];
				bestpos = i;
			}
			//best=max(best,V[i]);
		}
		cout << "Longest palindrome has length " << best << " (pos: "<<bestpos/2<<")"<<endl;
	}

	return 0;
}
