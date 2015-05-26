#include <cstdio>

#define MAX_N 10001

int main() {

	int parent[MAX_N];
	int been[MAX_N];

	int T;
	scanf("%d", &T);
	int i, j, k;
	for (i = 0; i < T; i++) {

		for (j = 0; j < MAX_N; j++) {
			parent[j] = 0;
			been[j] = 0;
		}
		int a, b;
		int N;
		scanf("%d", &N);
		for (j = 0; j < N - 1; j++) {
			scanf("%d %d", &a, &b);
			parent[b] = a;
		}
		scanf("%d %d", &a, &b);
		//printf("%d %d\n", a, b);
		while (parent[a] != 0) {
			been[a] = 1;
			a = parent[a];
		}

		while (parent[b] != 0 && been[b] != 1) {
			been[b] = 1;
			b = parent[b];
		}

		// for (j = 0; j < MAX_N; j++) {
		// 	printf("parent of %d = %d\n", j, parent[j]);
		// }

		printf("%d\n", b);
	}

	return 0;
}