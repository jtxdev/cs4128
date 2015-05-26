/* Minimum Spannign Tree Kruskals */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAX_V 210
#define MAX_E MAX_V*MAX_V

using namespace std;

struct vertex {
	int x;
	int y;
	int id;
};

struct edge
{
	vertex u;
	vertex v;
	double w;
};

bool operator<(const edge& a, const edge& b) {
 return a.w < b.w;
} 

edge edges[MAX_E];
vertex vertices[MAX_V];

int start[MAX_V], to[2*MAX_V], nextID[2*MAX_V], m;
double weight[2*MAX_V];

int p[MAX_V];
int k;

int seen[MAX_V];


void addEdge(vertex u, vertex v, double w) {

	edges[k].u = u;
	edges[k].v = v;
	edges[k].w = w;
	k++;
}

void add(int u, int v, double w) {

	to[m] = v;
	weight[m] = w;
	nextID[m] = start[u];
	start[u] = m++;
}

double dist(double x1, double y1, double x2, double y2)
{
    double x = x2 - x1;
    double y = y2 - y1;

    return sqrt(pow(x,2)+pow(y,2));
}

int root(int u) {
 	return u == p[u] ? u : p[u] = root(p[u]);
}

void join(int u, int v) {
  	u = root(u);
  	v = root(v);
  	p[u] = v;
}

void dfs(int u, int x, double fd) {
	if ( u == x ) {
		printf("Frog Distance = %.3f\n", fd);
	}
	seen[u] = 1;
	for (int ID = start[u]; ID != -1; ID = nextID[ID]) {
		int v = to[ID];
		double w = weight[ID];
		if (!seen[v]) {
			double newfd = fd;
			if (w > newfd) {
				newfd = w;
			}
			dfs(v, x, newfd);
		}
	}
}

double mst() {
	int n = k;
	m = 0;
	memset(start, -1, sizeof(start));
  	sort(edges, edges + n);
  	double total_weight = 0;
  	for (int i = 0; i < n; i++) {
  		edge e = edges[i];

  		if (root(e.u.id) != root(e.v.id)) {

	  		total_weight += e.w;
	 		join(e.v.id, e.u.id);
	 		add(e.u.id, e.v.id, e.w);
			add(e.v.id, e.u.id, e.w);
	  	} else {
	  		k--;
	  	}
	}
 	return total_weight;
}

int main() {

		int i, j, N, T = 0;
		while (scanf("%d\n", &N) == 1) {
			T++;
			if (N == 0) {
				break;
			}
			k = 0;

			memset(vertices, 0, sizeof(vertices));
			memset(edges, 0, sizeof(edges));

			i = 0;
			while (i < N) {
				int a, b;
				scanf("%d %d\n", &a, &b);
				vertex v = {a, b, i};
				vertices[i] = v;
				//printf("%d %d\n", v.x, v.y);
				i++;
			}
			for (i = 0; i <= N; i++) {
				p[i] = i;
			}
			for (i = 0; i < N - 1; i++) {
				for (j = i + 1; j < N; j++) {
					vertex u = vertices[i];
					vertex v = vertices[j];
					double w = dist(u.x, u.y, v.x, v.y);
					// printf("%d %d\n", u.x, u.y);
					// printf("%d %d\n", v.x, v.y);
					// printf("%f\n", w);
					addEdge(u, v, w);
					addEdge(v, u, w);
				}
			}
			mst();
			memset(seen, 0, sizeof(seen));
			printf("Scenario #%d\n", T);
			dfs(0, 1, 0);
			printf("\n");
		}
	return 0;
}