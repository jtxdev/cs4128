#include <cstdio>
#include <cstring>

#define MAX_N 500

#define IN 0
#define OUT 500
#define SOURCE 0
#define SINK 1001

#define DEBUG

using namespace std;

struct Edge
{
	int u;
	int v;
	int cap;
	int nextID;

} edges[MAX_N*MAX_N];

int start[SINK+1], k;

void add(int u, int v, int cap) {
	edges[k].u = u;
	edges[k].v = v;
	edges[k].cap = cap;
	edges[k].nextID = start[u];
	start[u] = k++;
	//printf("%d->%d %d\n", u, v, k);
}

int seen[SINK+1];

int inv(int e) {
	return e^1;
}

bool augment(int u, int t, int f) {
 	if (u == t) return true;
 	if (seen[u]) return false;
 	seen[u] = true;
 	for (int e = start[u]; e != -1; e = edges[e].nextID) {
 		if (edges[e].cap >= f && augment(edges[e].v, t, f)) {
 			edges[e].cap -= f;
 			edges[inv(e)].cap += f;
	 		return true;
	 	}
	}
	return false;
}

int max_flow(int s, int t) {
	int res = 0;
	memset(seen, 0, sizeof(seen));
	while (augment(s, t, 1)) {
		memset(seen, 0, sizeof(seen));
		res += 1;
	}
	return res;
}

int grid[MAX_N][MAX_N];

int main() {
	int N, K;
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			grid[i][j] = 0;
		}
	}

	memset(start, -1, sizeof(start));
	k = 0;

	for (int i = 1; i <= N; ++i)
	{
		/* Add a edge from the source to every v.in */
		add(SOURCE, i+IN, 1);	
		add(i+IN, SOURCE, 0);

		/* Add a edge from every v.out to the sink */
		add(i+OUT, SINK, 1);
		add(SINK, i+OUT, 0);
	}

	for (int i = 0; i < K; i++) 
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a+IN, b+OUT, 1);
		add(b+OUT, a+IN, 0);
	}


	int res = max_flow(SOURCE, SINK);

	printf("%d\n", res);
	return 0;
}