#include <cstdio>

#define MAX_N 10000

int main() {

	int N;
	int s[MAX_N];
	int dpl[MAX_N];
	int dpr[MAX_N];
	int L = 0;
	int R = 0;
	int MinL[MAX_N + 1];
	int MinR[MAX_N + 1];
	int markedR[MAX_N + 1];
	int markedL[MAX_N + 1];

	int i;

	while (scanf("%d\n", &N) != EOF) {
		
		for (i = 0; i < N; i++) {
			scanf("%d\n", &s[i]);
		}

		// for (i = 0; i < N; i++) {
		// 	printf("%d", s[i]);
		// }

		for (i = 0; i < N; i++) {
			dpl[i] = 0;
			dpr[i] = 0;
		}

		for (i = 0; i < N + 1; i++) {
			MinL[i] = -1;
			MinR[i] = -1;
			markedL[i] = 0;
			markedR[i] = 0;
		}



		//longest increasing subsequence
		//for each i, find the previous longest subsequence ending in a value < i and +1.
		L = 0;
		for (i = 0; i < N; i++) {
			
			//Binary search for the highest length ending in a number < s[i];

			int lo = 1;
			int hi = L;

			// printf("i = %d\n", i);
			// printf("s[i] = %d\n", s[i]);
			while (lo <= hi) {
				int mid = (lo + hi) / 2;
				if (s[MinL[mid]] < s[i]) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}

			int newL = lo;
			dpl[i] = lo;

			// printf("newL = %d\n", lo);
			if (s[i] < s[MinL[newL]] || markedL[newL] == 0) {
				MinL[newL] = i;
				markedL[newL] = 1;
			}
			if (newL > L) {
				L = newL;
			}
			// printf("MinL[%d] = %d\n", lo, MinL[lo]);
			// printf("s[MinL[%d]] = %d\n", lo, s[MinL[lo]]);
			// printf("L = %d\n\n", L);
		}

		R = 0;
		for (i = N - 1; i >= 0; i--) {
			int lo = 1;
			int hi = R;
			while (lo <= hi) {
				int mid = (lo + hi) / 2;
				if (s[MinR[mid]] < s[i]) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}

			//printf("dpr = %d\n", lo);
			int newR = lo;
			dpr[i] = lo;
			if (s[i] < s[MinR[newR]] || markedR[newR] == 0) {
				MinR[newR] = i;
				markedR[newR] = 1;
			}
			if (newR > R) {
				R = newR;
			}
		}

		// for (i = 0; i < N; i++) {
		// 	printf("%d %d %d\n", i, dpl[i], dpr[i]);
		// }

		int ans = 0;
		for (i = 0; i < N; i++) {
			if (dpl[i] > dpr[i]) {
				if ((2 * dpr[i] - 1) > ans) {
					ans = (2 * dpr[i] - 1);
				}
			} else if (dpl[i] < dpr[i]) {
				if ((2 * dpl[i] - 1) > ans) {
					ans = (2 * dpl[i] - 1);
				}
			} else {
				if ((dpr[i] + dpl[i] - 1) > ans) {
					ans = (dpr[i] + dpl[i] - 1);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}