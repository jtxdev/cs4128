#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_V 210
#define MAX_E 6010

using namespace std;

struct edge
{
	int u;
	int v;
	int w;
};

bool operator<(const edge& a, const edge& b) {
 return a.w < b.w;
} 

edge edges[MAX_E];
int p[MAX_V];
int k;
int C, c;

void addEdge(int u, int v, int w) {
	edges[k].u = u;
	edges[k].v = v;
	edges[k].w = w;
	k++;
}

int root(int u) {
 	return u == p[u] ? u : p[u] = root(p[u]);
}

void join(int u, int v) {
  	u = root(u);
  	v = root(v);
  	p[u] = v;
}

int mst() {
	int n = k;
  	sort(edges, edges + n);
  	int total_weight = 0;
  	for (int i = 0; i < n; i++) {
  		edge e = edges[i];
  		//printf("%d->%d\n", e.u, e.v);
  		if (root(e.v) != root(e.u)) {
	  		total_weight += e.w;
	 		join(e.v, e.u);
	  	} else {
	  		k--;
	  		edges[i].w = 10010;
	  	}
	}
	sort(edges, edges + n);
 	return total_weight;
}

int main() {

	int T, t;
	scanf("%d", &T);
	t = 1;
	while (t <= T) {
		printf("Case %d:\n", t);
		int N, M;
		scanf("%d%d\n", &N, &M);
		for (int i = 0; i < MAX_E; i++) {
			edges[i].u = 0;
	  		edges[i].v = 0;
	  		edges[i].w = 10010;
		}
		k = 0;
		while (M > 0) {
			int a, b, l;
			scanf("%d %d %d\n", &a, &b, &l);
			addEdge(a, b, l);
			for (int i = 0; i <= N; i++) {
				p[i] = i;
			}
			int total = mst();
			int pass = 1;
			for (int i = 1; i <= N; i++) {
				//printf("root[%d] = %d\n", i, root(i));
				if (root(i) != root(1)) {
					pass = 0;
				}
			}
			if (pass == 1) {
				printf("%d\n", total);
			} else {
				printf("-1\n");
			}
			M--;
		}
	t++;
	}

	return 0;
}