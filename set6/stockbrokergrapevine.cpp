#include <cstdio>
#include <cstring>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define MAX 110
#define UNDEFINED 10000

int dist[MAX][MAX];
void floyd(int n) {
	for (int i = 1; i <= n; i++) {
		for (int u = 1; u <= n; u++) {
		 	for (int v = 1; v <= n; v++) {
		 		dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
		 	}
		}
	} 
}

int main() {
	int N;
	while (~scanf("%d", &N)) {
		if (N == 0) break;
		for (int u = 0; u <= N; u++) {
		 	for (int v = 0; v <= N; v++) {
		 		dist[u][v] = UNDEFINED;
		 	}
		}

		for (int u = 1; u <= N; u++) {
			int S;
			scanf("%d", &S);
			for (int j = 1; j <= S; j++) {
				int v, w;
				scanf("%d %d", &v, &w);
				dist[u][v] = w;
				//printf("%d->%d %d\n", u, v, dist[u][v]);
			}
		}

		floyd(N);

		int bestperson = -1;
		int besttime = UNDEFINED;
		for (int u = 1; u <= N; u++) {
			int highest = 0;
		 	for (int v = 1; v <= N; v++) {
		 		if (u != v) {
		 			if (highest < dist[u][v]) {
		 				highest = dist[u][v];
		 			}
		 			//printf("%d->%d %d\n", u, v, dist[u][v]);
		 		}
		 	}
		 	
		 	if (highest != UNDEFINED) {
		 		if (highest < besttime) {
		 			bestperson = u;
		 			besttime = highest;
		 		}
		 	}
		}
		if (bestperson != -1) {
			printf("%d %d\n", bestperson, besttime);
		} else {
			printf("disjoint\n");
		}
	}

}