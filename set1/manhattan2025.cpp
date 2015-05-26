#include <cstdio>
#include <cstdlib>
	int main() {
		int i, j, k, l, u, curr;
		int size;
		scanf("%d", &u);
		for (i = 0; i < u; i++) {
			scanf("%d", &curr);
			size = 2 * curr + 1;

			printf("Scenario #%d:\n", i+1);

			for (j = 0; j < size; j++) {
				printf("slice #%d:\n", j+1);
				for (k = 0; k < size; k++) {
					for (l = 0; l < size; l++) {
						int dist = abs((size / 2) - j) + abs((size / 2) - k) + abs((size / 2) - l);
						if (dist > curr) {
							printf(".");
						} else {
							printf("%d", dist);
						}
					}
					printf("\n");
				}
			}
			printf("\n");
		}
	 	return 0;
} 