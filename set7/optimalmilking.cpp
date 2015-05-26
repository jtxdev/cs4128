#include <cstdio>
#include <cstring>
#include <utility>
#include <set>

#define MAX_V 230

#define SOURCE 0
#define SINK 231

#define INF 100000000

using namespace std;

struct Edge
{
	int u;
	int v;
	int w;
	int cap;
	int nextID;

} edges[SINK*SINK];

int start[SINK+1], k;

void add(int u, int v, int w, int cap) {
	edges[k].u = u;
	edges[k].v = v;
	edges[k].w = w;
	edges[k].cap = cap;
	edges[k].nextID = start[u];
	start[u] = k++;
	// printf("%d->%d %d %d\n", u, v, w, cap);
}

int dist[SINK+1][SINK+1];
void floyd(int n) {
	for (int i = 1; i <= n; i++) {
		for (int u = 1; u <= n; u++) {
		 	for (int v = 1; v <= n; v++) {
		 		dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
		 	}
		}
	} 
}

int seen[SINK+1];
int maxd;

int inv(int e) {
	return e^1;
}

bool augment(int u, int t, int f, Edge edges[]) {
 	if (u == t) return true;
 	if (seen[u]) return false;
 	seen[u] = true;
 	for (int e = start[u]; e != -1; e = edges[e].nextID) {
 		if (edges[e].cap < f) continue;
 		if (edges[e].w > maxd) continue; 
 		if (augment(edges[e].v, t, f, edges)) {
 			edges[e].cap -= f;
 			edges[inv(e)].cap += f;
	 		return true;
	 	}
	}
	return false;
}

int max_flow(int s, int t, Edge edges[]) {
	int res = 0;
	memset(seen, 0, sizeof(seen));
	while (augment(s, t, 1, edges)) {
		memset(seen, 0, sizeof(seen));
		res += 1;
	}
	return res;
};

int main() {
	memset(start, -1, sizeof(start));
	k = 0;

	int K, C, M;
	scanf("%d%d%d", &K, &C, &M);

	for (int u = 1; u <= K+C; ++u) {
	 	for (int v = 1; v <= K+C; ++v) {
	 		dist[u][v] = INF;
	 	}
	}

	for (int u = 1; u <= K+C; ++u) {
		dist[u][u] = 0;
	}

	for (int u = 1; u <= K+C; ++u)
	{
		for (int v = 1; v <= K+C; ++v)
		{
			int d;
			scanf("%d", &d);
			if (d != 0) {
				dist[u][v] = d;
			}
		}
	}

	floyd(K+C);

	for (int u = 1; u <= K+C; ++u)
	{
		if (u <= K) {
			add(u, SINK, 0, M);
			add(SINK, u, 0, 0);
		} else {
			add(SOURCE, u, 0, 1);
			add(u, SOURCE, 0, 0);
		}
	}

	for (int u = K+1; u <= K+C; ++u)	//each cow
	{
		for (int v = 1; v <= K; ++v) 	//each statin
		{
			if (dist[u][v] != INF) {
				// printf("%d->%d = %d\n", u, v, dist[u][v]);
				add(u, v, dist[u][v], 1);
				add(v, u, -(dist[u][v]), 0);

			}
		}
	}

	int lo = 0, hi = 10000000;
	Edge temp[SINK*SINK];
	for (int it = 0; it < 70; it++) {
		maxd = (lo + hi)/2;
		for (int i = 0; i < k; ++i)
		{
			temp[i] = edges[i];
		}
		if (max_flow(SOURCE, SINK, temp) == C) {
			hi = maxd;
		} else {
			lo = maxd;
		}
	}
	printf("%d\n", hi);
	return 0;
}