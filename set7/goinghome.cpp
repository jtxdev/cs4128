#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

#define MAX_M 100
#define MAX_H 100

#define SOURCE 0
#define SINK 201

#define INF 200000

using namespace std;

struct Edge
{
	int u;
	int v;
	int w;
	int cap;
	int nextID;

} edges[2 * (MAX_M+2) * (MAX_H+2) ];

int start[SINK+1], k;

void add(int u, int v, int w, int cap) {
	edges[k].u = u;
	edges[k].v = v;
	edges[k].w = w;
	edges[k].cap = cap;
	edges[k].nextID = start[u];
	start[u] = k++;
	//printf("%d\n", k);
}

int pre[SINK+1];
int dist[SINK+1];

int inv(int e) {
	return e^1;
}

pair<int, int> mincostmaxflow(int s, int t) {
	int total_flow = 0, total_cost = 0;
	while (true) {
		for (int i = 0; i <= t; i++) {
			dist[i] = INF;
			pre[i] = -1;
		}
		dist[s] = 0;
		pre[s] = -1;
		// use bellman-ford to find a shortest augmenting path
		bool relaxed = true;
		while (relaxed) {
			relaxed = false;
			for (int u = 0; u <= t; u++) {
				for (int e = start[u]; e != -1; e = edges[e].nextID) {
					int v = edges[e].v;
					int w = edges[e].w;
					int cap = edges[e].cap;
					if (cap > 0) {
						if (dist[u] + w < dist[v]) {
							dist[v] = dist[u] + w;
							pre[v] = e;
							relaxed = true;
						}
					}
				}
			}
		}

		// if we didn't find any augmenting paths, break
		if (dist[t] == INF) {
			break;
		}

		// push the unit of flow through the shortest augmenting path found
		total_flow++;
		total_cost += dist[t];
		// move along the shortest augmenting path found and maintain the residual graph
		for (int e = pre[t]; ~e; e = pre[edges[e].u]) {
			edges[e].cap--;
			edges[inv(e)].cap++;
		}
	}
	return make_pair(total_flow, total_cost);
} 

int mandist(int x1, int y1, int x2, int y2) {
	//printf("%d %d %d %d\n", x1, y1, x2, y2);
	int x = x1 - x2;
	int y = y1 - y2;
	if (x < 0) {
		x *= -1;
	}
	if (y < 0) {
		y *= -1;
	}
	return x+y;
}

pair<int, int> men[MAX_M+1];
pair<int, int> house[MAX_H+1];

int main() {
		
	while (true) {
		//init
		k = 0;
		memset(start, -1, sizeof(start));
		memset(men, -1, sizeof(men));
		memset(house, -1, sizeof(house));
		int N, M;
		scanf("%d%d", &N, &M);
		if (N == 0 && M == 0) {
			break;
		}

		//start reading input
		int numMen = 1;
		int numHouses = 1;
		for (int i = 0; i < N; ++i)
		{
			char str[MAX_M+1];
			scanf("%s", str);
			for (int j = 0; j < strlen(str); ++j)
			{
				if (str[j] == 'm') {

					add(SOURCE, numMen, 0, 1);
					add(numMen, SOURCE, 0, 0);
					men[numMen++] = make_pair(i, j);

				}
				if (str[j] == 'H') {

					//Remember to offset by MAX_M
					add(MAX_M + numHouses, SINK, 0, 1);
					add(SINK, MAX_M + numHouses, 0, 0);
					house[numHouses++] = make_pair(i, j);
				}
			}
		}

		// printf("%d\n", numMen);
		// printf("%d\n", numHouses);

		for (int m = 1; m < numMen; ++m)
		{
			for (int h = 1; h < numHouses; ++h)
			{
				pair<int, int> man = men[m];
				pair<int, int> home = house[h];
				int d = mandist(man.first, man.second, home.first, home.second);
				add(m, MAX_M+h, d, INF);
				add(MAX_M+h, m, 0, 0);
				//printf("%d\n", k);
			}
		}

		pair<int, int> res = mincostmaxflow(SOURCE, SINK);
		printf("%d\n", res.second);

	}


	return 0;
}