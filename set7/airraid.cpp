#include <cstdio>
#include <cstring>

#define MAX_V 120
#define MAX_E 200000

#define IN 0
#define OUT 120
#define SOURCE 0
#define SINK 241

#define DEBUG

using namespace std;

struct Edge
{
	int u;
	int v;
	int cap;
	int nextID;

} edges[MAX_E];

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

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; ++t)
	{
		memset(start, -1, sizeof(start));
		k = 0;

		int V, E;
		scanf("%d%d", &V, &E);
		for (int i = 1; i <= V; ++i)
		{
			/* Add a edge from the source to every v.in */
			add(SOURCE, i+IN, 1);	
			add(i+IN, SOURCE, 0);

			// /* Add a edge from v.in to v.out */
			// add(i+IN, i+OUT, 1);
			// add(i+IN, i+OUT, 0);

			/* Add a edge from every v.out to the sink */
			add(i+OUT, SINK, 1);
			add(SINK, i+OUT, 0);
		}

		for (int e = 0; e < E; ++e)
		{
			int u, v;
			scanf("%d %d", &u, &v);

			/* Add a edge from every u.out to v.in */
			add(v+IN, u+OUT, 10000);
			add(u+OUT, v+IN, 0);
		}

		int res = max_flow(SOURCE, SINK);

		printf("%d\n", V-res);
	}
	return 0;
}