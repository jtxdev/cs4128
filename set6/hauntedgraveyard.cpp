#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX 30
#define MAX_V 900
#define GRASS 0
#define GRAVE 1
#define UNDEFINED 1<<29

int map[MAX][MAX];
int ff[MAX][MAX];
int dist[MAX_V];
int pre[MAX_V];

struct hole {
	int a;
	int b;
	int t;
} hole[MAX_V];

struct Edge
{
	int to;
	int nextID;
	int w;

} edges[4*MAX_V];

int start[MAX_V], m;

void add(int u, int v, int w) {
	edges[m].to = v;
	edges[m].nextID = start[u];
	edges[m].w = w;
	start[u] = m++;
}

void floodfill(int i, int j, int W, int H) {
	int type = map[i][j];
	if (type != GRAVE && ff[i][j] == 0) {
		ff[i][j] = 1;
		if (i == W-1 && j== H-1) return;
		if (type > GRAVE) { floodfill(hole[type].a, hole[type].b, W, H); }
		else {
			if (i+1 < W)  { floodfill(i+1, j, W, H); }
			if (i-1 >= 0) { floodfill(i-1, j, W, H); }
			if (j+1 < H)  { floodfill(i, j+1, W, H); }
			if (j-1 >= 0) { floodfill(i, j-1, W, H); }
		}
	}
}

bool relax(int N) {
	bool relaxed = false;
	for (int u = 0; u < N; u++) {
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
	for (int u = 0; u < N; u++) {
		dist[u] = UNDEFINED;
		pre[u] = -1;
	}
	dist[0] = 0;
	pre[0] = -2;
	for (int u = 0; u < N - 1; u++) {
		bool relaxed = relax(N);
		if (!relaxed) return relaxed;
	}
	return relax(N);
}

int main() {

	int W, H;
	int a, b;
	while (scanf("%d%d", &W, &H) == 2) {
		if (W == 0 && H == 0) break;
		for (int i = 0; i < W; ++i)
		{
			for (int j = 0; j < H; ++j)
			{
				map[i][j] = GRASS;
				ff[i][j] = GRASS;
			}
		}
		int G;
		scanf("%d", &G);
		for (int i = 0; i < G; ++i)
		{
			scanf("%d%d", &a, &b);
			map[a][b] = GRAVE;
		}
		int E;
		scanf("%d", &E);
		int h = 2;
		for (int i = 0; i < E; ++i)
		{
			int c, d, t;
			scanf("%d%d%d%d%d", &a, &b, &c, &d, &t);
			hole[h].a = c;
			hole[h].b = d;
			hole[h].t = t;
			map[a][b] = h++;
		}
		memset(start, -1, sizeof(start));
		m = 0;
		floodfill(0, 0, W, H);
		for (int i = 0; i < W; ++i)
		{
			for (int j = 0; j < H; ++j)
			{
				if (i == W - 1 && j == H - 1) continue;
				if (map[i][j] == GRASS && ff[i][j] == 1) {
					if (i+1 < W && map[i+1][j] != GRAVE) {
						add(i*H+j, (i+1)*H+j, 1);
						// dist[i*H+j][(i+1)*H+j] = 1;
					}
					if (i-1 >= 0 && map[i-1][j] != GRAVE) {
						add(i*H+j, (i-1)*H+j, 1);
						// dist[i*H+j][(i-1)*H+j] = 1;
					}
					if (j+1 < H && map[i][j+1] != GRAVE) {
						add(i*H+j, i*H+(j+1), 1);
						// dist[i*H+j][i*H+(j+1)] = 1;
					}
					if (j-1 >= 0 && map[i][j-1] != GRAVE) {
						add(i*H+j, i*H+(j-1), 1);
						// dist[i*H+j][i*H+(j-1)] = 1;
					}
				} else if (map[i][j] != GRAVE && ff[i][j] == 1) {
				
					int jmp = map[i][j];
					add(i*H+j, (hole[jmp].a)*H+(hole[jmp].b), hole[jmp].t);
					// dist[i*H+j][(hole[jmp].a)*H+(hole[jmp].b)] = hole[jmp].t;
				}
			}
		}

		if (BellmanFord(W*H)) {
			printf("Never\n");
		} else if (dist[W*H - 1] == UNDEFINED) {
			printf("Impossible\n");
		} else {
			printf("%d\n", dist[W*H-1]);
		}

	}
	return 0;
}