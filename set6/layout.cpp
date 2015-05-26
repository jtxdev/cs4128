#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX_V 1010
#define MAX_ML 10010
#define MAX_MD 10010

#define UNDEFINED 1<<29

int dist[MAX_V];
int pre[MAX_V];

struct Edge
{
	int to;
	int nextID;
	int w;

} edges[MAX_ML+MAX_MD];

int start[MAX_V], m;

void add(int u, int v, int w) {
	edges[m].to = v;
	edges[m].nextID = start[u];
	edges[m].w = w;
	start[u] = m++;
}

bool relax(int N) {
	bool relaxed = false;
	for (int u = 1; u <= N; u++) {
		for (int ID = start[u]; ID != -1; ID = edges[ID].nextID) {
			int v = edges[ID].to;
			int w = edges[ID].w;
			if (dist[v] > dist[u] + w) {
				relaxed = true;
				pre[v] = u;
				dist[v] = dist[u] + w;
			}
		}
	}
	return relaxed;
}

bool BellmanFord(int N) {
	for (int u = 1; u <= N; u++) {
		dist[u] = UNDEFINED;
		pre[u] = -1;
	}
	dist[1] = 0;
	pre[1] = -2;
	for (int u = 0; u < N - 1; u++) {
		bool relaxed = relax(N);
		if (!relaxed) return relaxed;
	}
	return relax(N);
}

int main() {

	int N, ML, MD;
	m = 0;
	memset(start, -1, sizeof(start));
	scanf("%d%d%d", &N, &ML, &MD);
	for (int i = 0; i < ML; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
		// printf("%d->%d %d\n", u, v, -w);
	}
	for (int i = 0; i < MD; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(v, u, -w);
		// printf("%d->%d %d\n", v, u, w);
	}
	for (int i = 1; i < N; ++i)
	{
		add(i+1, i, 0);
		// printf("%d->%d %d\n", i, i+1, 0);
	}
	if (BellmanFord(N)) {
		printf("%d\n", -1);
	} else if (dist[N] == UNDEFINED) {
		printf("%d\n", -2);
	} else {
		printf("%d\n", dist[N]);
	}
}