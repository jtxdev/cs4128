#include <cstdio>


int main() {
	
	int N;
	// while (scanf("%d", &N) == 1) {
	// 	//for (i = 0; i < 30; i++)
	// }
	int dp[31] = {0};
	int i, j;
	dp[0] = 1;
	dp[1] = 0;
	dp[2] = 3;
	dp[3] = 0;
	for (i = 4; i <= 30; i = i+2) {
		dp[i] = dp[i-2] * 3;
		for (j = 4; j <= i; j = j + 2) {
			//printf("dp[%d] = %d | i - j = %d\n | dp[%d] = %d\n", i, dp[i], i-j, i-j, dp[i-j]);
			dp[i] += dp[i - j] * 2;
			//printf("%d\n", dp[i]);
		}
	}

	// for (i = 0; i <= 30; i++) {
	// 	printf("dp[%d] = %d\n", i, dp[i]);
	// }

	while (scanf("%d", &N) == 1) {
		if (N == -1) {
			break;
		}
		printf("%d\n", dp[N]);
	}

}