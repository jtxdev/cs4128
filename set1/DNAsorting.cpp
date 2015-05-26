/* 
Problem: Count the number of number of letters to the right less than the current index
A always contributes 0 // can ignore
C = number of A's to the right
G = number of A's and C's to the right
T = number of A's C's and G's to the right | number of non-T's the the right


count number of letters in each string
do basic arithmetic
*/

#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

#define A 0
#define C 1
#define G 2
#define T 3
#define MAXTYPES 4
#define MAXLENGTH 50
#define MAXSTRINGS 100


	int main() {
	//n length, m strings
	char c;
 	int i, j;
 	int n = 0;
 	int m = 0;
 	scanf("%d%d", &n, &m);

 	//initialise string array
 	char str[MAXSTRINGS][MAXLENGTH+1];
 	int count[MAXSTRINGS][MAXTYPES];
 	int score[MAXSTRINGS];
 	pair<int, int> rank[MAXSTRINGS];


 	//initialise to 0
 	for (i = 0; i < m; i++) {
 		for (j = 0; j < MAXTYPES; j++) {
 			count[i][j] = 0;
 		}
 	}

 	//counter for each string
 	for (i = 0; i < m; i++) {
 		scanf("%s", str[i]);
 		for (j = 0; j < n; j++) {
	 		if 		(str[i][j] == 'A') { count[i][A]++; } 
	 	   	else if (str[i][j] == 'C') { count[i][C]++; }
	 	   	else if (str[i][j] == 'G') { count[i][G]++; }
	 	 	else if	(str[i][j] == 'T') { count[i][T]++; }
 		}
 	}

 	//calculate
 	for (i = 0; i < m; i++) {
 		score[i] = 0;
 		for (j = 0; j < n; j++) {
 			switch (str[i][j]) {
 				case 'A':
 					count[i][A]--;
 					break;
 				case 'C':
 					count[i][C]--;
 					score[i] += count[i][A];
 					break;
 				case 'G':
 					count[i][G]--;
 					score[i] += count[i][A] + count[i][C];
 					break;
 				case 'T':
 					count[i][T]--;
 					score[i] += count[i][A] + count[i][C] + count[i][G];
 					break;
 				default:
 					break;
 			}
 		}
 		rank[i].first = score[i];
 		rank[i].second = i;
 	}

 	sort(rank, rank+m);
 	//print
 	for (i = 0; i < m; i++) {
 		printf("%s\n", str[rank[i].second]);
 	}

 	return 0;
} 