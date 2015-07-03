/*
   Copyright 2011 Shao-Chuan Wang <shaochuan.wang AT gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

/*
From http://code.activestate.com/recipes/577908-implementation-of-knuthmorrispratt-algorithm/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fasta.h"

int *compute_prefix_function(const char *pattern, int psize)
{
	int k = -1;
	int i = 1;
	int *pi = (int*)malloc(sizeof(int)*psize);
	if (!pi)
		return NULL;

	pi[0] = k;
	for (i = 1; i < psize; i++) {
		while (k > -1 && pattern[k+1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k+1])
			k++;
		pi[i] = k;
	}
	return pi;
}

int kmp(const char *target, int tsize, const char *pattern, int psize)
{
	int i;
	int *pi = compute_prefix_function(pattern, psize);
	int k = -1;
	if (!pi)
		return -1;
	for (i = 0; i < tsize; i++) {
		while (k > -1 && pattern[k+1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k+1])
			k++;
		if (k == psize - 1) {
			//free(pi);
			printf("Found match at %d\n",i-k);
			//return i-k;
		}
	}
	free(pi);
	return -1;
}

int main(int argc, char** argv){
	if(argc!=3){
		printf("Usage: %s <fasta file> <pattern>\n",argv[0]);
		exit(-1);
	}

	for(auto pair_it: read_file(argv[1])){
		const char* needle = argv[2];
		const char* haystack = pair_it.second.c_str();

		kmp(haystack, pair_it.second.length(), needle, pair_it.first.length());
	}
}


