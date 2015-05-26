#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#define MAXDIGITS 20
#define MAXSPACE 1000

using namespace std;

int genNext(int prev, int i, int n, int tenModN[]) {
	int val = 10 * prev;
	val %= n;
	tenModN[i] = val;
	return val;
}

int main() {

	int tenModN[MAXDIGITS] = {0};
	int answer[MAXDIGITS] = {0};
	vector<int> possibleSums[MAXSPACE];
	vector<int> tmp; 

	int n = -1;
	int i, j, k;
	int prev;
	int done;
	while (1) {
		for (i = 0; i < MAXDIGITS; i++) {
			tenModN[i] = 0;
			answer[i] = 0;
		}
		for (i = 0; i < MAXSPACE; i++) {
			possibleSums[i].clear();
		}
		possibleSums[1].push_back(0);
		done = 0;
		scanf("%d", &n);
		if (n == 0) {
			return 0;
		}
		tenModN[0] = 1;
		prev = 1;
		for (i = 1; i < MAXDIGITS && done == 0; i++) {
			prev = genNext(prev, i, n, tenModN);
			if (prev == 0) {
				printf("%d\n", static_cast<int>(pow(static_cast<double>(10), i)));
				done = 1;
			} else {	
				for (j = MAXSPACE - 1; j > 0; j--) {
					if (j + prev < MAXSPACE) {
						if (!possibleSums[j].empty() && possibleSums[j + prev].empty()) {
							vector<int> tmp (possibleSums[j]);
							tmp.push_back(i);
							possibleSums[j + prev] = tmp;
						}
					}
				}
				if (possibleSums[prev].empty()) {
					possibleSums[prev].push_back(i);
				}
				for (j = 0; j < MAXSPACE && done == 0; j += n) {
					if (!possibleSums[j].empty()) {
						sort(possibleSums[j].begin(), possibleSums[j].end());
						i = 0;
						for (vector<int>::reverse_iterator it = possibleSums[j].rbegin(); it != possibleSums[j].rend(); it++) {
						   	answer[i] = *it;
						   	i++; 
						}

						int digits = answer[0];
						for (j = 0; j < i - 1; j++) {
							printf("1");
							digits--;
							for (k = answer[j]; k > answer[j+1] + 1; k--) {
								printf("0");
								digits--;
							}
						}
						printf("1");
						for (j = 0; j < digits; j++) {
							printf("0");
						}
						printf("\n");
						done = 1;
					}
				}
			}
		}
	}
	return 0;
}