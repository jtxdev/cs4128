#include <cstdio>


int max(int x, int y) {
	if (x > y) {	
		return x;
	}
	return y;
}

int main() {
	int N;
	scanf("%d", &N);

	int triangle[5050];
	int sum[5050];


	int i = 0;
	while (scanf("%d", &triangle[i]) == 1) {
		i++;
	}

	int indexes = 0;
	for (i = 0; i < N; i++) {
		indexes += i + 1;
	}
	//printf("indexes %d\n", indexes);

	int h = 0;
	int c = 0;
	int best = 0;

	for (i = 0; i < indexes; i++) {
		if (c == h) {
			sum[i] = sum[i - h] + triangle[i];
			//printf("%d\n", sum[i]);
			if (sum[i] > best) {
				best = sum[i];
			}
			h++;
			c = 0;
			//printf("i = %d h = %d\n", i, h);
		} else if (c == h - 1) {
			sum[i] = sum[i - h] + triangle[i];
			//printf("%d\n", sum[i]);
			if (sum[i] > best) {
				best = sum[i];
			}
			//printf("i = %d h = %d\n", i, h);
		} else {
			sum[i] = max(sum[i-h], sum[i-h+1]) + triangle[i];
			if (sum[i] > best) {
				best = sum[i];
			}
			//printf("%d\n", sum[i]);
		}
		c++;
	}
	printf("%d\n", best);

}