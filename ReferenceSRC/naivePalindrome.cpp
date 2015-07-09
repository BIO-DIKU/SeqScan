#include <stdlib.h>
#include <string>
#include <limits.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "fasta.h"

using namespace std;

void naiveLongestPalindrome(const string& seq)
{
	int n=seq.length();

	int max_pos = 0;
	int max_len = 0;

	int pal_len, pal_pos;

	//Check all positions
	for(int i=0;i<n;i++){

		//Find longest odd palindrome centered at i
		int j;
		for(j=1;i-j>=0 && i+j<n;j++)
			if(seq[i+j]!=seq[i-j]) break;

		pal_len = 2*j-1;
		pal_pos = i-j+1;
		if(pal_len>max_len){
			max_len = pal_len;
			max_pos = pal_pos;
		}

		//Find longest even palindrome centered between i and i+1
		for(j=0;i-j>=0&&i+j+1<n;j++)
			if(seq[i-j]!=seq[i+j+1]) break;
		pal_len = 2*j;
		pal_pos = i-j+1;
		if(pal_len>max_len){
			max_len = pal_len;
			max_pos = pal_pos;
		}
	}

	cout<<"Longest palindrome:"<<endl;
	cout<<"> pos: "<<max_pos<<endl;
	cout<<"> len: "<<max_len<<endl;
	cout<<"> str: "<<seq.substr(max_pos,max_len)<<endl;
}

void naiveGappedPalindrome(const string& seq, int min_gap, int max_gap)
{
	int n=seq.length();

	int max_pos = 0;
	int max_len = 0;

	int pal_len, pal_pos;

	//Check all positions
	for(int i=0;i<n;i++){

		//Find longest odd palindrome centered at i
		int j;
		for(j=1;i-j>=0 && i+j<n;j++)
			if(seq[i+j]!=seq[i-j]) break;

		pal_len = 2*j-1;
		pal_pos = i-j+1;
		if(pal_len>max_len){
			max_len = pal_len;
			max_pos = pal_pos;
		}

		//Find longest even palindrome centered between i and i+1
		for(j=0;i-j>=0&&i+j+1<n;j++)
			if(seq[i-j]!=seq[i+j+1]) break;
		pal_len = 2*j;
		pal_pos = i-j+1;
		if(pal_len>max_len){
			max_len = pal_len;
			max_pos = pal_pos;
		}
	}

	cout<<"Longest palindrome:"<<endl;
	cout<<"> pos: "<<max_pos<<endl;
	cout<<"> len: "<<max_len<<endl;
	cout<<"> str: "<<seq.substr(max_pos,max_len)<<endl;

}

int main(int argc, char** argv){
	if(argc!=2){
		printf("Usage: %s <fasta file>\n",argv[0]);
		exit(-1);
	}

	//naiveLongestPalindrome(string(argv[1])); //Provide cmdline string instead of fasta file


	for(auto &pair_it: read_file(argv[1])){
		string& s = pair_it.second;
		naiveLongestPalindrome(s);
	}

	return 0;
}
