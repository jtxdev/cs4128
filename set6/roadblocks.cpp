#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <set>
#include <vector>

using namespace std;

#define MAX_V 5010
#define MAX_E 100010

struct Edge
{
	int to;
	int nextID;
	int w;

} edges[2*MAX_E];

int start[MAX_V], m;

void add(int u, int v, int w) {
	edges[m].to = v;
	edges[m].nextID = start[u];
	edges[m].w = w;
	start[u] = m++;
}

typedef pair<int, int> E;

int dist1[MAX_V];
int prev1[MAX_V];

void shortestpath1() {
	set<E> s;
	vector<bool> seen(MAX_V+1);
	prev1[1] = -2;
	for (s.insert(make_pair(0, 1)); !s.empty(); s.erase(s.begin())) {
		E cur = *s.begin();
		int d = cur.first;
		int u = cur.second;
		if (seen[u]) continue;
		dist1[u] = d;
		seen[u] = true;
		for (int ID = start[u]; ID != -1; ID = edges[ID].nextID) {
			int v = edges[ID].to;
			int w = edges[ID].w;
			if (!seen[v]) {
				if (dist1[v] == -1 || dist1[v] > d + w) {
					prev1[v] = u;
					s.insert(make_pair(d+w, v));
				}
			}
		}
	}
}

int dist2[MAX_V];
int prev2[MAX_V];

void shortestpathN(int N) {
	set<E> s;
	vector<bool> seen(MAX_V+1);
	prev2[N] = -2;
	for (s.insert(make_pair(0, N)); !s.empty(); s.erase(s.begin())) {
		E cur = *s.begin();
		int d = cur.first;
		int u = cur.second;
		if (seen[u]) continue;
		dist2[u] = d;
		seen[u] = true;
		for (int ID = start[u]; ID != -1; ID = edges[ID].nextID) {
			int v = edges[ID].to;
			int w = edges[ID].w;
			if (!seen[v]) {
				if (dist2[v] == -1 || dist2[v] > d + w) {
					prev2[v] = u;
					s.insert(make_pair(d+w, v));
				}
			}
		}
	}
}

int main() {

	int N, R;
	scanf("%d%d", &N, &R);
	memset(start, -1, sizeof(start));
	int i;
	m = 0;
	for (i = 0; i < R; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	memset(prev1, -1, sizeof(prev1));
	memset(dist1, -1, sizeof(dist1));
	memset(prev2, -1, sizeof(prev2));
	memset(dist2, -1, sizeof(dist2));
	shortestpath1();
	shortestpathN(N);
	//printf("%d\n", dist1[N]);
	int bad = dist1[N];
	int res = 1<<30;
	for (int u = N; u != -2; u = prev1[u]) {
		for (int ID = start[u]; ID != -1; ID = edges[ID].nextID) {
			int v = edges[ID].to;
			int w = edges[ID].w;
			int d = dist1[u] + w + dist2[v];
			if (d != bad) {
				res = min(res, d);
			}
		}
	}
	printf("%d\n", res);
}

